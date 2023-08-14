//
// Created by 86183 on 2023/8/14.
//

#ifndef SLIMPAJAMA_MINHASH_H
#define SLIMPAJAMA_MINHASH_H


#include <vector>
#include <algorithm>
#include <limits>
#include <random>
#include "Utils.h"

class MinHash {
public:
    int K; // number of hash functions
    std::vector<std::pair<unsigned short, unsigned short>> hf;  // hash functions
    std::vector<unsigned short> hashvalues; // hash values

public:
    MinHash(const int _K) : K(_K), hashvalues(_K, std::numeric_limits<unsigned short>::max()) {
        // Generate hash functions
        for (int i = 1; i <= _K; i++) {
            generateHashFunc(i, hf);
        }
    }



    void update(const std::string& b) {
        // Convert the string to an unsigned short value
        unsigned short word = static_cast<unsigned short>(std::hash<std::string>{}(b));

        for (int i = 0; i < K; ++i) {
            unsigned short hash_val = hval(hf[i], word);
            hashvalues[i] = std::min(hashvalues[i], hash_val);
        }
    }


};

#endif //SLIMPAJAMA_MINHASH_H
