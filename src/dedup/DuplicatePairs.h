//
// Created by 86183 on 2023/8/14.
//

#ifndef SLIMPAJAMA_DUPLICATEPAIRS_H
#define SLIMPAJAMA_DUPLICATEPAIRS_H

#include <boost/filesystem.hpp>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <string>
#include <chrono>
#include <queue>
#include <future>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/unordered_set.hpp>
#include <utility>
#include <boost/functional/hash.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

namespace fs = boost::filesystem;

class DuplicatePairs {
public:
    DuplicatePairs(std::string input_dir, std::string out_file, int range, int bands, int processes)
            : input_dir_(std::move(input_dir)), out_file_(std::move(out_file)), range_(range), bands_(bands), processes_(processes) {}

    static std::string byteswap(const std::string& hs);

    static std::vector<std::vector<std::string>> split_files(const std::string& input_dir, int n_proc);

    void lsh(const std::string& out_file, std::queue<std::pair<std::string, std::string>>& doc_queue, int idx);

    void get_hashes(const std::vector<std::string>& files, std::vector<std::queue<std::pair<std::string, std::string>>>& doc_queues, int r);

    void generate_pairs();
private:
    std::string input_dir_;
    std::string out_file_;
    int range_;
    int bands_;
    int processes_;
};


#endif //SLIMPAJAMA_DUPLICATEPAIRS_H
