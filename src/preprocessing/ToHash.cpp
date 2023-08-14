//
// Created by 86183 on 2023/8/13.
//

#include <unordered_map>
#include <thread>
#include "ToHash.h"
#include "../utils/MinHash.h"
#include <boost/filesystem.hpp>

std::string remove_punctuation(const std::string &s) {
    std::string result;
    std::copy_if(s.begin(), s.end(), std::back_inserter(result), [](unsigned char c) {
        return !std::ispunct(c);
    });
    return result;
}


std::vector<std::string> ToHash::get_features(const std::string &s, int width) {
    std::string lowercased = s;
    std::transform(lowercased.begin(), lowercased.end(), lowercased.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    std::string without_punctuation = remove_punctuation(lowercased);
    std::regex regex_whitespace("\\s+");
    std::string trimmed = std::regex_replace(without_punctuation, regex_whitespace, " ");

    std::vector<std::string> features;
    for (int i = 0; i <= trimmed.length() - width; i++) {
        std::string ngram = trimmed.substr(i, width);
        features.push_back(ngram);
    }

    return features;
}


namespace fs = boost::filesystem;

std::vector<ToHash::Document> ToHash::get_documents(const std::string& input_dir, int index_start, int index_end, const std::string& output_dir, const std::string& dataset_name) {
    std::vector<Document> documents;

    std::vector<std::string> files;
    std::string extension = ".jsonl";

    boost::filesystem::path input_path(input_dir);
    boost::filesystem::directory_iterator end_itr;

    for (boost::filesystem::directory_iterator itr(input_path); itr != end_itr; ++itr) {
        boost::filesystem::path file_path = itr->path();
        if (file_path.extension() == extension) {
            files.push_back(file_path.string());
        }
    }

    std::sort(files.begin(), files.end());

    for (int i = index_start; i < std::min(index_end, static_cast<int>(files.size())); i++) {
        std::string file_path = files[i];
        std::string file_name = file_path.substr(file_path.find_last_of('/') + 1);

        std::string output_name;
        if (dataset_name == "common_crawl") {
            std::string dir_2 = file_path.substr(0, file_path.find_last_of('/'));
            dir_2 = dir_2.substr(dir_2.find_last_of('/') + 1);
            output_name = dataset_name + "/" + dir_2 + "/" + file_name;
        } else {
            output_name = dataset_name + "/" + file_name;
        }

        std::ifstream file(file_path);
        Json::Value json;
        Json::Reader reader;
        while (file >> json) {
            std::string doc = json["text"].asString();

            Document document;
            document.text = doc;
            document.file_path = file_path;
            document.doc_id = documents.size();

            documents.push_back(document);
        }
    }

    return documents;
}


void ToHash::output_results(const std::string &output_dir, std::vector<std::unordered_map<std::string, std::string>> results, int chunk_id, int iter) {
    std::ostringstream oss;
    oss << output_dir << "/minhash_nfc/" << iter << "-" << chunk_id << ".pickle";
    std::string file_path = oss.str();

    std::ofstream fout(file_path, std::ios::binary);
    if (fout) {
        boost::archive::binary_oarchive oa(fout);
        oa << results;
        std::cout << "Serialization successful!" << std::endl;
    } else {
        std::cerr << "Failed to open file: " << file_path << std::endl;
    }
}


std::vector<std::unordered_map<std::string, std::string>>
ToHash::to_minhash(const std::vector<Document> &documents, const std::string &output_dir, int width,
                   const std::string &dataset_name, int n_docs) {
    std::vector<std::unordered_map<std::string, std::string>> buckets;
    buckets.reserve(n_docs);

    boost::progress_display progress(n_docs); // tqdm equivalent

    for (const Document &doc: documents) {
        std::string text = doc.text;
        std::string file_path = doc.file_path;
        int doc_id = doc.doc_id;

        std::vector<std::string> path_components;
        boost::split(path_components, file_path, boost::is_any_of("/"));

        std::string file_name = path_components.back();

        std::string output_name;
        if (dataset_name == "common_crawl") {
            std::string dir_2 = path_components[path_components.size() - 2];
            output_name = dataset_name + "/" + dir_2 + "/" + file_name;
        } else {
            output_name = dataset_name + "/" + file_name;
        }

        MinHash m(128);

        std::vector<std::string> features = get_features(text, width);
        for (const std::string &feature: features) {
            m.update(feature);
        }

        std::unordered_map<std::string, std::string> bucket;
        bucket["file_name"] = output_name;
        bucket["doc_id"] = std::to_string(doc_id);

        std::vector<unsigned short> hashValues = m.hashvalues;

        std::string hashString;
        for (const unsigned short& value : hashValues) {
            hashString += std::to_string(value) + ",";
        }

        if (!hashString.empty()) {
            hashString.pop_back();
        }

        bucket["hash"] = hashString;

        buckets.push_back(bucket);

        ++progress;
    }

    return buckets;
}


template <typename T>
std::vector<std::vector<T>> chunked(const std::vector<T>& input, size_t chunk_size) {
    size_t num_chunks = (input.size() + chunk_size - 1) / chunk_size;
    std::vector<std::vector<T>> chunks(num_chunks);

    // 计算线程数量
    int cpu_count = std::thread::hardware_concurrency();

    // 并行处理
    std::vector<std::thread> threads;
    for (int i = 0; i < cpu_count; ++i) {
        threads.emplace_back([i, cpu_count, &input, chunk_size, &chunks]() {
            size_t start = i * chunk_size;
            size_t end = std::min(start + chunk_size, input.size());
            std::vector<T> chunk(input.begin() + start, input.begin() + end);
            chunks[i] = std::move(chunk);
        });
    }

    // 等待所有线程完成
    for (auto& thread : threads) {
        thread.join();
    }

    return chunks;
}

void ToHash::generate_hashes() {
    if (!boost::filesystem::exists(output_dir_ + "/minhash_nfc")) {
        boost::filesystem::create_directory(output_dir_ + "/minhash_nfc");
    }

    std::vector<Document> documents = get_documents(input_dir_, index_start_, index_end_, output_dir_, dataset_name_);
    std::vector<std::unordered_map<std::string, std::string>> results;
    int chunk_id = 0;
    int cpu_count = std::thread::hardware_concurrency();
    std::vector<std::vector<Document>> chunks = chunked(documents, n_docs_ / cpu_count);

    for (int i = 0; i < cpu_count; ++i) {
        std::vector<std::unordered_map<std::string, std::string>> chunk_results = to_minhash(chunks[i], output_dir_, w_, dataset_name_, n_docs_ / cpu_count);
        results.insert(results.end(), chunk_results.begin(), chunk_results.end());

        if (results.size() == k_) {
            output_results(output_dir_, results, chunk_id, iter_);
            results.clear();
            chunk_id++;
        }
    }

    if (!results.empty()) {
        output_results(output_dir_, results, chunk_id, iter_);
    }

    }
