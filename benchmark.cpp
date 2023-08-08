#include <iostream>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>

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

void normalizeText(const std::string& inputDir, const std::string& dataset, const std::string& targetDir, bool isZst, int idx) {
    std::cout << "Normalizing text for dataset: " << dataset << std::endl;
    // Implement your text normalization logic here
    // Use inputDir, dataset, targetDir, isZst, and idx as needed
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Please provide the input directory." << std::endl;
        return 1;
    }

    std::string inputDir = argv[1];
    std::string redPajamaNormDir = (fs::path(inputDir) / "RedPajama_norm").string();
    fs::create_directories(redPajamaNormDir);

    std::vector<std::string> dsDirs = ds_names;
    dsDirs.erase(std::remove(dsDirs.begin(), dsDirs.end(), "common_crawl"), dsDirs.end());
    for (const auto& cc : cc_years) {
        dsDirs.push_back("common_crawl/" + cc);
    }

    for (const auto& dataset : dsDirs) {
        std::string normArgsDataDir = (fs::path(inputDir) / dataset).string();
        std::string normArgsTargetDir = (fs::path(redPajamaNormDir) / dataset).string();
        bool isZst = dataset.find("common_crawl") != std::string::npos;
        int idx = -1;

        normalizeText(normArgsDataDir, dataset, normArgsTargetDir, isZst, idx);
    }

    return 0;
}