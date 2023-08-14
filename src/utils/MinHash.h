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
    std::vector<pair<unsigned short, unsigned short>> hf;  // hash functions

public:
    MinHash(const int _K) : K(_K) {
        // the seeds are 1 to K
        for(int i = 1 ;i<=_K; i++){
            generateHashFunc(i, hf);
        }

        // for(int i = 1 ;i<=_K; i++){
        //     cout<<hf[i-1].first<<" "<< hf[i-1].second<<endl;
        // }
    }

    void update(const std::string& b) {
        uint64_t hv = hashfunc(b);
        for (int i = 0; i < K; ++i) {
            unsigned short hash_val = hval(hf[i], hv);
            hashvalues[i] = std::min(hashvalues[i], hash_val);
        }
    }


    std::vector<unsigned short> getMinHashes(const std::vector<unsigned short>& doc) {
        if(doc.size() == 0){
            return std::vector<unsigned short>();
        }


        std::vector<unsigned short> min_hashes(K, std::numeric_limits<unsigned short>::max());

        for (unsigned short element : doc) {
            for (int i = 0; i < K; ++i) {
                unsigned short hash_val = hval(hf[i], element);
                // cout<<"i"<<i<<" hash_val:" << hash_val<<endl;
                min_hashes[i] = std::min(min_hashes[i], hash_val);
            }
        }

        return min_hashes;
    }
};

#endif //SLIMPAJAMA_MINHASH_H
