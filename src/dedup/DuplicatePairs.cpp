//
// Created by 86183 on 2023/8/14.
//

#include "DuplicatePairs.h"
#include "../utils/Utils.h"

std::string DuplicatePairs::byteswap(const std::string &hs) {
    std::string swapped(hs.size(), '\0');
    for (std::size_t i = 0; i < hs.size(); ++i) {
        swapped[i] = hs[i] ^ 0xFF;
    }
    return swapped;
}


std::vector<std::vector<std::string>> DuplicatePairs::split_files(const std::string &input_dir, int n_proc) {
    std::vector<std::string> files;
    for (const std::string &dataset: {"arxiv", "stackexchange", "book", "wikipedia", "github", "c4", "common_crawl"}) {
        if (dataset == "common_crawl") {
            std::vector<std::string> common_crawl_files = glob_files(input_dir + "/" + dataset + "/*/minhash_nfc/*");
            files.insert(files.end(), common_crawl_files.begin(), common_crawl_files.end());
        } else {
            std::vector<std::string> other_files = glob_files(input_dir + "/" + dataset + "/minhash_nfc/*");
            files.insert(files.end(), other_files.begin(), other_files.end());
        }
    }

    std::sort(files.begin(), files.end());

    std::vector<std::vector<std::string>> parts = divide(n_proc, files);

    return parts;
}


void
DuplicatePairs::lsh(const std::string &out_file, std::queue<std::pair<std::string, std::string>> &doc_queue, int idx) {
    std::unordered_map<std::string, std::string> lsh_dict;
    int i = 0;
    auto start_time = std::chrono::steady_clock::now();
    std::string out_file_modified = out_file;
    out_file_modified.replace(out_file_modified.find(".txt"), 4, "-" + std::to_string(idx) + ".txt");
    std::ofstream f(out_file_modified);
    while (true) {
        try {
            auto key_H = doc_queue.front();
            doc_queue.pop();
            const std::string &key = key_H.first;
            const std::string &H = key_H.second;
            auto it = lsh_dict.find(H);
            if (it != lsh_dict.end()) {
                const std::string &cand = it->second;
                if (cand != "None") {
                    f << key << " :: " << cand << "\n";
                }
            } else {
                lsh_dict[H] = key;
            }

            if (i % 100000 == 0) {
                auto elapsed_time = std::chrono::steady_clock::now() - start_time;
                double progress = static_cast<double>(i) / 931361530 * 100;
                std::cout << idx << ": Processed " << progress << "%. "
                          << std::chrono::duration<double>(elapsed_time).count() << "s.\n";
            }
            ++i;
        } catch (const std::exception &e) {
            break;
        }
    }

    std::cout << "Total number of documents: " << i << "\n";
    f.close();
}


struct Item {
    std::string file_name;
    int doc_id;
    std::string hash;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & file_name;
        ar & doc_id;
        ar & hash;
    }
};

void DuplicatePairs::get_hashes(const std::vector<std::string> &files,
                                std::vector<std::queue<std::pair<std::string, std::string>>> &doc_queues, int r) {
    for (const std::string &fp: files) {
        std::ifstream fin(fp, std::ios::binary);
        if (fin) {
            boost::archive::binary_iarchive ia(fin);
            std::vector<Item> items;
            ia >> items;
            for (const auto &item: items) {
                std::string key = item.file_name + "@" + std::to_string(item.doc_id);
                std::vector<unsigned short> hash_values;
                std::string hash_string = item.hash;
                std::vector<std::string> hash_components;
                boost::split(hash_components, hash_string, boost::is_any_of(","));
                for (const std::string& component : hash_components) {
                    auto value = boost::lexical_cast<unsigned short>(component);
                    hash_values.push_back(value);
                }
                for (size_t i = 0; i < doc_queues.size(); ++i) {
                    std::vector<unsigned short> H(hash_values.begin() + i * r, hash_values.begin() + (i + 1) * r);
                    std::string H_string(reinterpret_cast<const char*>(H.data()), H.size() * sizeof(unsigned short));
                    std::string swapped_H = byteswap(H_string);
                    doc_queues[i].push(std::make_pair(key, swapped_H));
                }
            }
            fin.close();
        }
    }
}

void DuplicatePairs::generate_pairs() {
    std::vector<std::queue<std::pair<std::string, std::string>>> doc_queues(bands_);
    std::vector<std::vector<std::string>> files = split_files(input_dir_, processes_);

    std::vector<std::thread> threads;
    for (int process_id = 0; process_id < processes_; ++process_id) {
        threads.emplace_back([&files, &doc_queues, process_id, this]() {
            get_hashes(files[process_id], doc_queues, range_);
        });
    }

    for (int process_id = 0; process_id < bands_; ++process_id) {
        threads.emplace_back([this, &doc_queues, process_id]() {
            lsh(out_file_, doc_queues[process_id], process_id);
        });
    }

    for (auto &thread: threads) {
        thread.join();
    }
}