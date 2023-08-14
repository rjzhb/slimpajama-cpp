//
// Created by 86183 on 2023/8/14.
//

#ifndef SLIMPAJAMA_UTILS_H
#define SLIMPAJAMA_UTILS_H
#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>


extern std::vector<std::string> glob_files(const std::string& path);

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
// Generate random hash functions based on given seed
// ab: the output argument
void generateHashFunc(int seed, std::vector<std::pair<unsigned short, unsigned short>> &hf);

// The hash value function
unsigned short hval(const std::pair<unsigned short, unsigned short> &hf, unsigned short word);

#endif //SLIMPAJAMA_UTILS_H
