//
// Created by 86183 on 2023/8/8.
//

#ifndef CPPMODELPROJECT_NORMALIZE_TEXT_H
#define CPPMODELPROJECT_NORMALIZE_TEXT_H

#include <vector>
#include <string>
#include <mutex>

class NormalizeText {
public:
    NormalizeText(std::string data_dir, std::string target_dir, int idx);

    void run();

private:
    void recreate_dataset(const std::vector<std::string> &files, int process_no, std::mutex &pbar_mutex);

    std::string data_dir_;
    std::string target_dir_;
    int idx_;
};

#endif //CPPMODELPROJECT_NORMALIZE_TEXT_H
