//
// Created by 86183 on 2023/8/13.
//

#include <unordered_map>
#include "ToHash.h"
#include "../utils/MinHash.h"

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

void ToHash::get_documents(const std::string &input_dir, int index_start, int index_end, const std::string &output_dir,
                           const std::string &dataset_name) {
    std::vector<std::string> files;
    std::string extension = ".jsonl";

    // Read and filter files
    for (const auto &entry: fs::directory_iterator(input_dir)) {
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

void ToHash::output_results(const std::string &output_dir, const std::vector<int> &results, int chunk_id, int iter) {
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
            boost::hash_combine(m, feature);
        }

        std::unordered_map<std::string, std::string> bucket;
        bucket["file_name"] = output_name;
        bucket["doc_id"] = std::to_string(doc_id);
        bucket["hash"] = m.toString();

        buckets.push_back(bucket);

        ++progress;
    }

    return buckets;
}
