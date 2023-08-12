//
// Created by 86183 on 2023/8/12.
//

#include "filter.h"
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <cctype>
#include <locale>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/unordered_set.hpp>

Filter::Filter(std::string input_dir, std::string output_file, int n_docs, std::string dataset_name, int threshold)
        : input_dir_(std::move(input_dir)), output_file_(std::move(output_file)), n_docs_(n_docs),
          dataset_name_(std::move(dataset_name)), threshold_(threshold) {}


std::string Filter::clean(std::string s) {
    // lower cased
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });

    // remove punctuation
    s.erase(std::remove_if(s.begin(), s.end(), [](unsigned char c) { return std::ispunct(c); }), s.end());

    // remove consecutive spaces, newlines, tabs in the middle and in the beginning / end
    s = std::regex_replace(s, std::regex("\\s+"), " ");
    s = std::regex_replace(s, std::regex("^\\s+|\\s+$"), "");

    return s;
}


void Filter::get_short_documents(
        const std::string &input_dir,
        int threshold,
        int n_proc,
        int proc_idx,
        std::queue<std::string> &docs_queue,
        const std::string &dataset_name
) {
    std::vector<std::string> files;

    if (dataset_name == "all") {
        for (const std::string &dataset: {
                "arxiv",
                "stackexchange",
                "book",
                "wikipedia",
                "github",
                "c4",
                "common_crawl"
        }) {
            if (dataset == "common_crawl") {
                for (const auto &entry: fs::directory_iterator(input_dir + "/" + dataset)) {
                    files.push_back(entry.path().string());
                }
            } else {
                for (const auto &entry: fs::directory_iterator(input_dir + "/" + dataset)) {
                    files.push_back(entry.path().string());
                }
            }
        }
    } else if (dataset_name == "common_crawl") {
        for (const auto &entry: fs::directory_iterator(input_dir + "/" + dataset_name)) {
            files.push_back(entry.path().string());
        }
    } else {
        for (const auto &entry: fs::directory_iterator(input_dir + "/" + dataset_name)) {
            files.push_back(entry.path().string());
        }
    }

    std::sort(files.begin(), files.end());

    for (int i = proc_idx; i < files.size(); i += n_proc) {
        std::ifstream input_file(files[i]);
        std::string line;
        int doc_id = 0;

        while (std::getline(input_file, line)) {
            Json::Value doc;
            Json::Reader reader;
            if (!reader.parse(line, doc)) {
                std::cerr << "parse error" << std::endl;
                continue;
            }

            std::string text = doc["text"].asString();
            if (text.empty()) {
                continue;
            }

            if (clean(text).length() < threshold) {
                docs_queue.push(files[i].substr(input_dir.length() + 1) + "@" + std::to_string(doc_id));
            }

            doc_id++;
        }
    }
}


void Filter::filter_dataset() {
    std::unordered_map<std::string, std::unordered_set<int>> short_documents;
    std::queue<std::string> docs_queue;
    int n_proc = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    for (int process_id = 0; process_id < n_proc; process_id++) {
        threads.emplace_back([&docs_queue, n_proc, process_id, &short_documents, this]() {
            get_short_documents(input_dir_, threshold_, n_proc, process_id, docs_queue, dataset_name_, short_documents);
        });
    }

    int i = 0;
    auto start_time = std::chrono::steady_clock::now();
    while (true) {
        if (!docs_queue.empty()) {
            std::string item = docs_queue.front();
            docs_queue.pop();

            std::istringstream iss(item);
            std::string file_name, doc_idx;
            std::getline(iss, file_name, '@');
            std::getline(iss, doc_idx);

            short_documents[file_name].insert(std::stoi(doc_idx));

            if (i % 10 == 0) {
                auto current_time = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);
                std::cout << "Processed " << static_cast<double>(i) / n_docs_ * 100 << "%. "
                          << duration.count() / 1000.0 << " seconds" << std::endl;
            }
            i++;
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        if (i >= n_docs_ || i >= max_docs_)
            break;
    }

    for (auto &thread: threads) {
        thread.join();
    }

    std::cout << "Finished processing, writing to disk!" << std::endl;
    std::ofstream fout(output_file_, std::ios::binary);
    if (fout) {
        boost::archive::binary_oarchive oa(fout);
        oa << short_documents;
        std::cout << "Serialization successful!" << std::endl;
    } else {
        std::cout << "Failed to open file for serialization!" << std::endl;
    }
    fout.close();
}
