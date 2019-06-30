#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <cstdio>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>

std::mutex mutex;
const size_t batch_size = 500000;
const size_t buf_in_size = 150000;
const size_t buf_out_size = 200000;
const std::string random_prefix = "Zq0SUP";
const std::string dir_name(random_prefix + "temp");

void sorter(const std::string& file_name, int& batch_num, int& file_num) {
    std::ifstream f(file_name, std::ios::binary | std::ios::in);
    uint64_t* batch = new uint64_t[batch_size];
    while (true) {
        mutex.lock();
        if (batch_num < 0) {
            mutex.unlock();
            break;
        }
        f.seekg(batch_num * batch_size * sizeof(uint64_t));
        f.read((char*) (batch), batch_size * sizeof(uint64_t));
        file_num = batch_num++;
        int count = f.gcount();
        if (count < batch_size * sizeof(uint64_t)) {
            batch_num = -1;
            if (count == 0) {
                file_num--;
                mutex.unlock();
                break;
            }
        }
        mutex.unlock();
        std::sort(batch, batch + count / sizeof(uint64_t));
        std::string out_file_name = std::to_string(file_num);
        std::ofstream out(dir_name + "/" + out_file_name,
                        std::ios::binary | std::ios::out);
        out.write((char*) batch, count);
        out.close();
    }
    delete[] batch;
    f.close();
}

void merger(int& min_file_num, int& max_file_num, int thread_id) {
    uint64_t* buf_in_1 = new uint64_t[buf_in_size];
    uint64_t* buf_in_2 = new uint64_t[buf_in_size];
    uint64_t* buf_out = new uint64_t[buf_out_size];
    std::string temp_file_name = dir_name + "/temp" + std::to_string(thread_id);
    while (true) {
        mutex.lock();
        if (min_file_num >= max_file_num) {
            mutex.unlock();
            break;
        }
        std::string f1_name(dir_name + "/" + std::to_string(min_file_num++));
        std::string f2_name(dir_name + "/" + std::to_string(min_file_num++));
        mutex.unlock();
        std::ifstream f1(f1_name, std::ios::binary | std::ios::in);
        std::ifstream f2(f2_name, std::ios::binary | std::ios::in);
        std::ofstream out(temp_file_name, std::ios::binary | std::ios::out);

        f1.read((char*) buf_in_1, buf_in_size * sizeof(uint64_t));
        int count1 = f1.gcount();
        f2.read((char*) buf_in_2, buf_in_size * sizeof(uint64_t));
        int count2 = f2.gcount();

        int i = 0, j = 0, k = 0;
        while (true) {
            if (buf_in_1[i] < buf_in_2[j]) {
                buf_out[k++] = buf_in_1[i++];
            } else {
                buf_out[k++] = buf_in_2[j++];
            }
            if (k == buf_out_size) {
                out.write((char*) buf_out, buf_out_size * sizeof(uint64_t));
                k = 0;
            }
            if (i == (count1 / sizeof(uint64_t))) {
                f1.read((char*) buf_in_1, buf_in_size * sizeof(uint64_t));
                count1 = f1.gcount();
                i = 0;
                if (count1 == 0) {
                    out.write((char*) buf_out, k * sizeof(uint64_t));
                    out.write((char*) (buf_in_2 + j),
                            count2 - j * sizeof(uint64_t));
                    while (count2) {
                        f2.read((char*) buf_in_2, buf_in_size * sizeof(uint64_t));
                        count2 = f2.gcount();
                        out.write((char*) buf_in_2, count2);
                    }
                    break;
                }
            }
            if (j == (count2 / sizeof(uint64_t))) {
                f2.read((char*) buf_in_2, buf_in_size * sizeof(uint64_t));
                count2 = f2.gcount();
                j = 0;
                if (count2 == 0) {
                    out.write((char*) buf_out, k * sizeof(uint64_t));
                    out.write((char*) (buf_in_1 + i),
                            count1 - i * sizeof(uint64_t));
                    while (count1) {
                        f1.read((char*) buf_in_1, buf_in_size * sizeof(uint64_t));
                        count1 = f1.gcount();
                        out.write((char*) buf_in_1, count1);
                    }
                    break;
                }
            }
        }
        
        f1.close();
        f2.close();
        out.close();
        std::remove(f1_name.c_str());
        std::remove(f2_name.c_str());

        mutex.lock();
        rename(temp_file_name.c_str(),
            (dir_name + "/" + std::to_string(++max_file_num)).c_str());
        mutex.unlock();
    }

    delete[] buf_in_1;
    delete[] buf_in_2;
    delete[] buf_out;
}

int main(int argc, char* argv[]) {
    int batch_num = 0;
    int file_num = -1;
    mkdir(dir_name.c_str(), ACCESSPERMS);
    
    std::thread t1(sorter, argv[1], std::ref(batch_num), std::ref(file_num));
    std::thread t2(sorter, argv[1], std::ref(batch_num), std::ref(file_num));

    t1.join();
    t2.join();

    int min_file_num = 0;
    int max_file_num = file_num;

    std::thread t3(merger, std::ref(min_file_num), std::ref(max_file_num), 0);
    std::thread t4(merger, std::ref(min_file_num), std::ref(max_file_num), 1);

    t3.join();
    t4.join();

    rename((dir_name + "/" +
        std::to_string(max_file_num)).c_str(), "res.dat");
    rmdir(dir_name.c_str());
}