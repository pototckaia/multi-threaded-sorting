#pragma once

#include <vector>
#include <string>

namespace container_size
{
static long long int great =  10000000;
static long long int big =    1000000;
static long long int little = 10000;
} // container_size

void set_random(std::string& s);

std::shared_ptr<std::vector<std::string >> get_test_vector(long long int size);

class logger {
public:
    logger() : prev_count_thread(-1), is_time_log(true) {};
    logger(const logger& log_) = default;

    void start(int count_thread, int size);
    void partition(int size_1, int size_2);
    void create_thread(int count_thread, int size);
    void main_thread(int size);
    void end(int size);
private:
    int prev_count_thread;
    bool is_time_log;
};

