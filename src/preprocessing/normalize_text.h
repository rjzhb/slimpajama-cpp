//
// Created by 86183 on 2023/8/8.
//

#ifndef CPPMODELPROJECT_NORMALIZE_TEXT_H
#define CPPMODELPROJECT_NORMALIZE_TEXT_H

#include <vector>
#include <string>
#include <mutex>

struct Args {
    std::string data_dir;
    std::string target_dir;
    int idx;
};

class NormalizeText {
public:
    NormalizeText(const std::string& data_dir, const std::string& target_dir, bool zst, int idx);
    void run(Args args);

private:
    void recreate_dataset(const std::vector<std::string>& files, const Args& args, int process_no, std::mutex& pbar_mutex);

    std::string data_dir_;
    std::string target_dir_;
    bool zst_;
    int idx_;
};

#endif //CPPMODELPROJECT_NORMALIZE_TEXT_H
