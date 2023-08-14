#include <iostream>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>
#include <numeric>
#include "src/preprocessing/normalize_text.h"
#include "src/preprocessing/filter.h"
#include "src/preprocessing/ToHash.h"
#include "src/dedup/DuplicatePairs.h"

namespace fs = boost::filesystem;

std::vector<std::string> ds_names = {
        "arxiv",
        "stackexchange",
        "book",
        "wikipedia",
        "github",
        "c4",
        "common_crawl"
};

std::vector<std::string> cc_years = {
        "2019-30",
        "2020-05",
        "2021-04",
        "2022-05",
        "2023-06"
};

std::vector<int> n_documents = {
        1558306,
        29825086,
        205744,
        29834171,
        28793312,
        364868892,
        81085420,
        90850492,
        98878523,
        94058868,
        111402716
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Please provide the input directory." << std::endl;
        return 1;
    }

    std::vector<std::string> ds_dirs = ds_names;
    ds_dirs.erase(std::remove(ds_dirs.begin(), ds_dirs.end(), "common_crawl"), ds_dirs.end());
    for (const auto &cc: cc_years) {
        ds_dirs.push_back("common_crawl/" + cc);
    }

    //norm
    std::string input_dir = argv[1];
    std::string redPajamaNormDir = (fs::path(input_dir) / "RedPajama_norm").string();
    fs::create_directories(redPajamaNormDir);


    for (const auto &dataset: ds_dirs) {
        const std::string normArgsDataDir = (fs::path(input_dir) / dataset).string();
        const std::string normArgsTargetDir = (fs::path(redPajamaNormDir) / dataset).string();
        int idx = -1;
        NormalizeText normalize(normArgsDataDir, normArgsTargetDir, idx);
        normalize.run();
    }

    //filter docs
    std::string short_docs = (fs::path(redPajamaNormDir) / "red_pj_filter.pickle").string();
    Filter filter(redPajamaNormDir, short_docs, std::accumulate(n_documents.begin(), n_documents.end(), 0), "all", 200);
    filter.filter_dataset();

    //generate minhash
    for (auto dataset : ds_dirs) {
        const std::string input_dir = (fs::path(redPajamaNormDir) / dataset).string();
        const std::string output_dir = (fs::path(redPajamaNormDir) / dataset).string();
        const int n_docs = std::accumulate(n_documents.begin(), n_documents.end(), 0);
        const int iter = 0;
        const int index_start = 0;
        const int index_end = -1;
        const int w = 13;
        const int k = 10000;
        ToHash to_hash(dataset, input_dir, output_dir, n_docs, iter, index_start, index_end, w, k);
        to_hash.generate_hashes();
    }

    //generate duplicates
    std::string dup_dir = (fs::path(redPajamaNormDir) / "dup").string();
    fs::create_directories(dup_dir);
    const std::string out_file = (fs::path(dup_dir) / "duplicate_pairs.txt").string();
    int range = 13;
    int bands = 9;
    int processes = 45;
    DuplicatePairs duplicate_pairs(redPajamaNormDir, out_file, range, bands, processes);
    duplicate_pairs.generate_pairs();


    return 0;
}