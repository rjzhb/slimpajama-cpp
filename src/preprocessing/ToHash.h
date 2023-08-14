//
// Created by 86183 on 2023/8/13.
//

#ifndef SLIMPAJAMA_TOHASH_H
#define SLIMPAJAMA_TOHASH_H

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <regex>
#include <fstream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <boost/filesystem.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/functional/hash.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/progress.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/unordered_set.hpp>
#include <boost/lexical_cast.hpp>

class ToHash {
public:
    struct Document {
        std::string text;
        std::string file_path;
        int doc_id;
    };


    ToHash(std::string dataset_name, std::string input_dir, std::string output_dir, int n_docs, int iter, int index_start, int index_end, int w, int k)
            : dataset_name_(std::move(dataset_name)), input_dir_(std::move(input_dir)), output_dir_(std::move(output_dir)), n_docs_(n_docs), iter_(iter), index_start_(index_start), index_end_(index_end), w_(w), k_(k) {}

    std::vector<Document> get_documents(const std::string& input_dir, int index_start, int index_end, const std::string& output_dir, const std::string& dataset_name);

    std::vector<std::string> get_features(const std::string& s, int width);

    void output_results(const std::string& output_dir, std::vector<std::unordered_map<std::string, std::string>>, int chunk_id, int iter);

    std::vector<std::unordered_map<std::string, std::string>> to_minhash(const std::vector<Document>& documents, const std::string& output_dir, int width, const std::string& dataset_name, int n_docs);

    void generate_hashes();

private:
    std::string dataset_name_;
    std::string input_dir_;
    std::string output_dir_;
    int n_docs_;
    int iter_;
    int index_start_;
    int index_end_;
    //the window size
    int w_;
    //number of batches to output with
    int k_;
};


#endif //SLIMPAJAMA_TOHASH_H
