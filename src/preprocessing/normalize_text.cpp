//
// Created by 86183 on 2023/8/8.
//
#include "normalize_text.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <thread>
#include <mutex>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <unicode/utypes.h>
#include <unicode/unistr.h>
#include <unicode/normalizer2.h>
#include <boost/filesystem.hpp>
#include <boost/progress.hpp>

namespace fs = boost::filesystem;

NormalizeText::NormalizeText(std::string data_dir, std::string target_dir, int idx)
        : data_dir_(std::move(data_dir)), target_dir_(std::move(target_dir)), idx_(idx) {}


std::string normalize_text(const std::string &text) {
    UErrorCode status = U_ZERO_ERROR;
    icu::UnicodeString unicodeStr = icu::UnicodeString::fromUTF8(text.c_str());
    auto *normalizer = icu::Normalizer2::getNFCInstance(status);

    if (U_SUCCESS(status)) {
        normalizer->normalize(unicodeStr, status);
        std::string normalizedText;
        unicodeStr.toUTF8String(normalizedText);
        delete normalizer;
        return normalizedText;
    } else {
        std::cerr << "Error: Failed to normalize text" << std::endl;
        return text;
    }
}


void NormalizeText::recreate_dataset(const std::vector<std::string> &files, int process_no,
                                     std::mutex &pbar_mutex) {
    boost::progress_display pbar(files.size());

    for (const auto &file: files) {
        fs::path file_path = fs::path(data_dir_) / file;
        fs::path target_path = fs::path(target_dir_) / file;

        std::ifstream input_file(file_path.string());
        std::ofstream output_file(target_path.string());

        std::string line;
        while (std::getline(input_file, line)) {
            std::istringstream iss(line);
            Json::Value record;
            Json::Reader reader;

            if (!reader.parse(iss, record)) {
                std::cerr << "parse error" << std::endl;
            }

            if (record.isObject()) {
                std::string doc = record["text"].asString();
                doc = normalize_text(doc);

                Json::Value normalized_record;
                normalized_record["text"] = doc;
                normalized_record["meta"] = record["meta"];

                output_file << normalized_record.toStyledString() << "\n";
            }
        }


        {
            std::lock_guard<std::mutex> lock(pbar_mutex);
            ++pbar;
        }
    }
}

void NormalizeText::run() {
    fs::create_directories(target_dir_);

    std::vector<std::string> files;
    for (const auto &entry: fs::directory_iterator(data_dir_)) {
        if (is_regular_file(entry) && entry.path().extension() == ".jsonl") {
            files.push_back(entry.path().filename().string());
        }
    }

    std::sort(files.begin(), files.end());

    if (idx_ != -1) {
        int start_idx = idx_ * 64;
        int end_idx = (idx_ + 1) * 64;
        files.erase(files.begin(), files.begin() + start_idx);
        files.resize(end_idx - start_idx);
    }

    int n_proc = std::thread::hardware_concurrency();
    int n_chunks = std::ceil(files.size() / static_cast<double>(n_proc));
    int remain = files.size() % n_proc;
    if (n_chunks == 1 && remain) {
        n_proc = remain;
    }
    std::cout << "resetting to " << n_proc << " for number of processes" << std::endl;

    std::vector<std::vector<std::string>> file_chunks;
    for (size_t i = 0; i < files.size(); i += n_chunks) {
        file_chunks.emplace_back(files.begin() + i, files.begin() + i + n_chunks);
    }

    std::vector<std::thread> threads;
    std::mutex pbar_mutex;

    for (int i = 0; i < n_proc; ++i) {
        threads.emplace_back([&] {
            recreate_dataset(file_chunks[i], i, pbar_mutex);
        });
    }

    for (auto &thread: threads) {
        thread.join();
    }
}