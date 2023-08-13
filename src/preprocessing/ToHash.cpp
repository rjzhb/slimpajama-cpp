//
// Created by 86183 on 2023/8/13.
//

#include "ToHash.h"

std::string get_features(const std::string& s, int width) {
    // Convert to lowercase
    std::string lowercased = s;
    std::transform(lowercased.begin(), lowercased.end(), lowercased.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    // Remove punctuation
    std::string without_punctuation;
    std::remove_copy_if(lowercased.begin(), lowercased.end(), std::back_inserter(without_punctuation), ispunct);

    // Remove consecutive spaces, newlines, and tabs
    std::regex regex_whitespace("\\s+");
    std::string trimmed = std::regex_replace(without_punctuation, regex_whitespace, " ");

    // Generate ngrams
    std::string features;
    for (int i = 0; i <= trimmed.length() - width; i++) {
        std::string ngram = trimmed.substr(i, width);
        features += ngram;
    }

    return features;
}


namespace fs = boost::filesystem;

void get_documents(const std::string& input_dir, int index_start, int index_end, const std::string& output_dir, const std::string& dataset_name) {
    std::vector<std::string> files;
    std::string extension = ".jsonl";

    // Read and filter files
    for (const auto& entry : fs::directory_iterator(input_dir)) {
        std::string file_path = entry.path().string();
        if (file_path.find(extension) != std::string::npos) {
            files.push_back(file_path);
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

        if (dataset_name == "common_crawl") {
            std::ifstream file(file_path);
            Json::Value json;
            Json::Reader reader;
            while (reader.parse(file, json)) {
                std::string doc = json["text"].asString();
                // Process the document
                // ...
            }
        } else {
            std::ifstream file(file_path);
            Json::Value json;
            Json::Reader reader;
            while (file >> json) {
                std::string doc = json["text"].asString();
                // Process the document
                // ...
            }
        }
    }
}

void output_results(const std::string& output_dir, const std::vector<int>& results, int chunk_id, int iter) {
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

