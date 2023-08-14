//
// Created by 86183 on 2023/8/14.
//

#ifndef SLIMPAJAMA_UTILS_H
#define SLIMPAJAMA_UTILS_H

#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>
#include <bits/stdc++.h>
#include <sys/sysinfo.h>

std::vector<std::string> glob_files(const std::string& path);

template <typename T>
std::vector<std::vector<T>> divide(int n, const std::vector<T>& iterable);


using namespace std;
// Generate random hash functions based on given seed
// ab: the output argument
void generateHashFunc(int seed, vector<pair<unsigned short, unsigned short>> &hf) {
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
inline unsigned short hval(const pair<unsigned short, unsigned short> &hf, unsigned short word) {
    return hf.first * word + hf.second;
}

// Turn on timer
std::chrono::_V2::system_clock::time_point LogTime() {
    return chrono::high_resolution_clock::now();
}

// Turn off timer
double RepTime(const std::chrono::_V2::system_clock::time_point &start) {
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    return duration.count() / 1000000.0;
}


std::string vectorToString(const std::vector<unsigned short>& vec) {
    std::string str;
    for(const auto& num : vec) {
        str.append(std::to_string(num));
    }
    return str;
}

/**
 * Function: deduplicate_and_free_memory
 * Template version that works for any type of vector.
 * Removes duplicates from a vector and frees up unused memory.
 *
 * @param vec - Reference to the vector from which duplicates are to be removed.
 */
template<typename T>
void deduplicate_vec(std::vector<T>& vec) {
    // Sort the vector.
    std::sort(vec.begin(), vec.end());
    // Use std::unique which returns an iterator to the first element in the
    // duplicate range (which should be removed).
    auto it = std::unique(vec.begin(), vec.end());
    // Resize the vector to new size.
    vec.resize(std::distance(vec.begin(), it));

    // Shrink-to-fit idiom:
    // std::vector<T>(vec).swap(vec);
}

#endif //SLIMPAJAMA_UTILS_H
