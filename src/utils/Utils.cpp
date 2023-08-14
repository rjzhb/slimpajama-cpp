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


template <typename T>
std::vector<std::vector<T>> divide(int n, const std::vector<T>& iterable) {
    std::vector<std::vector<T>> parts(n);
    int size = iterable.size();
    int partSize = (size + n - 1) / n; // 向上取整

    auto it = iterable.begin();
    for (int i = 0; i < n; ++i) {
        int count = std::min(partSize, size);
        parts[i].reserve(count);
        std::copy_n(it, count, std::back_inserter(parts[i]));
        std::advance(it, count);
        size -= count;
    }

    return parts;
}