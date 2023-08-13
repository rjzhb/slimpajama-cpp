//
// Created by 86183 on 2023/8/13.
//

#ifndef SLIMPAJAMA_TOHASH_H
#define SLIMPAJAMA_TOHASH_H

#include <iostream>
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

class ToHash {
public:
    ToHash(const std::string& dataset_name, const std::string& input_dir, const std::string& output_dir, int n_docs, int iter, int index_start, int index_end, int w, int k)
            : dataset_name_(dataset_name), input_dir_(input_dir), output_dir_(output_dir), n_docs_(n_docs), iter_(iter), index_start_(index_start), index_end_(index_end), w_(w), k_(k) {}

    std::string get_features(const std::string& s, int width);


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
