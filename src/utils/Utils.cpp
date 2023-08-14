//
// Created by 86183 on 2023/8/14.
//
#include "Utils.h"


std::vector<std::string> glob_files(const std::string& path) {
    namespace fs = boost::filesystem;
    std::vector<std::string> files;

    fs::path dir_path(path);
    if (fs::exists(dir_path) && fs::is_directory(dir_path)) {
        fs::directory_iterator end_itr;
        for (fs::directory_iterator itr(dir_path); itr != end_itr; ++itr) {
            if (fs::is_regular_file(itr->status())) {
                files.push_back(itr->path().string());
            }
        }
    }

    return files;
}




void generateHashFunc(int seed, std::vector<std::pair<unsigned short, unsigned short>> &hf) {
    // TODO: knuth shuffling?
    // TODO: random_seed
    srand(seed);
    unsigned short a = 0;
    while (a == 0)
        a = (unsigned short)rand();
    unsigned short b =(unsigned short) rand();
    hf.emplace_back(a, b);
}

// The hash value function
unsigned short hval(const std::pair<unsigned short, unsigned short> &hf, unsigned short word) {
    return hf.first * word + hf.second;
}
