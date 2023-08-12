//
// Created by 86183 on 2023/8/12.
//

#ifndef SLIMPAJAMA_FILTER_H
#define SLIMPAJAMA_FILTER_H

#include <iostream>
#include <queue>
#include <boost/filesystem.hpp>


namespace fs = boost::filesystem;

class Filter {
public:
    Filter(std::string input_dir, std::string output_file, int n_docs, std::string dataset_name, int threshold);


    std::string clean(std::string s);

    void get_short_documents(
            const std::string &input_dir,
            int threshold,
            int n_proc,
            int proc_idx,
            std::queue<std::string> &docs_queue,
            const std::string &dataset_name
    );

    void filter_dataset();

private:
    std::string input_dir_;
    std::string output_file_;
    int n_docs_;
    std::string dataset_name_;
    int threshold_;
    int max_docs_;
};


#endif //SLIMPAJAMA_FILTER_H
