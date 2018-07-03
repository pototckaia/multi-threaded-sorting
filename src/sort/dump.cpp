#include <iterator>
#include <ctime>
#include <memory>
#include <bits/shared_ptr.h>
#include <random>
#include <stack>
#include <glog/logging.h>

#include "dump.h"

void set_random(std::string& s) {
    static const char alphanum[] =
            "0123456789"
            "abcdefghiklmnopqrstuvwxyz"
            "ABSDEFGHIKLMNOPQRSTUVWXYZ";

    double lower_bound = 0;
    double upper_bound = 100000000;
    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    std::random_device rd;
    std::mt19937 re(rd());

    for (std::size_t i = 0; i < s.size(); ++i) {
        int rand = std::ceil(unif(re));
        s[i] = alphanum[rand % (sizeof(alphanum) - 1)];
    }
}

std::shared_ptr<std::vector<std::string >> get_test_vector(long long int size)
{
    auto v = std::make_shared<std::vector<std::string>>(size);
    std::string s(' ', 100);
    for (long long int i = 0; i < size; ++i) {
        set_random(s);
        (*v)[i] = s;// * a_random_double;
    }
    return v;
}


void logger::start(int count_thread, int size) {

    is_time_log = prev_count_thread != count_thread;
    prev_count_thread = count_thread;

    LOG_IF(INFO, is_time_log)
    << std::endl << std::endl
    << "Начало многопоточной сортировки" << std::endl
    << "Количество потоков " << count_thread << " " << std::endl
    << "Размер массива: " << size;
}

void logger::partition(int size_1, int size_2) {
    LOG_IF(INFO, is_time_log)
    << "Первый - " << size_1
    << " Второй - " << size_2 << std::endl;
}

void logger::create_thread(int count_thread, int size) {

    LOG_IF(INFO, is_time_log)
    << " Создание потока. "
    << "Потоков " << count_thread  << " " << std::endl;

    LOG_IF(WARNING, size <= 2)
    << std::endl
    << "Создание потока зря";
}

void logger::main_thread(int size) {

    LOG_IF(INFO, is_time_log)
    << "Потоки кончились. Размер массива - " << size
    << std::endl;
}

void logger::end(int size) {
    LOG_IF(INFO, is_time_log)
    << "Конец многопоточности. "
    << "Размер массива - " << size;
}

