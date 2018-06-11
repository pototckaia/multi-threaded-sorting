#pragma once

#include <iterator>
#include <vector>
#include <bits/shared_ptr.h>
#include <ctime>
#include <random>

namespace container_size
{
static long long int great =  100000000;
static long long int big =    100000;
static long long int little = 10000;
} // container_size

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

    for (int i = 0; i < s.size(); ++i) {
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