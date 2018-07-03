#pragma once

#include <thread>
#include <future>
#include <iterator>
#include <algorithm>

#include "dump.h"


static logger info;

namespace tst
{


template <class Iter>
void sort(Iter left, Iter right, std::random_access_iterator_tag) {
    if (std::distance(left, right) <= 1) {
        return;
    }
    auto pivot = *std::next(left, std::distance(left, right)/2);
    Iter middle1 = std::partition(left, right,
                                       [pivot](const auto& em){ return em < pivot; });
    Iter middle2 = std::partition(middle1, right,
                                       [pivot](const auto& em){ return !(em > pivot   ); });

    tst::sort(left, middle1, std::random_access_iterator_tag());
    tst::sort(middle2, right, std::random_access_iterator_tag());

}

template <typename Iter>
void sort(Iter left, Iter right) {
    tst::sort(left, right,
         typename std::iterator_traits<Iter>::iterator_category());
}


template <typename Iter>
void multi_sort(Iter left, Iter right, int count_thread, std::random_access_iterator_tag) {
    if (std::distance(left, right) <= 1) {
        return;
    }

    auto pivot = *std::next(left, std::distance(left, right)/2);
    Iter middle1 = std::partition(left, right,
                                  [pivot](const auto& em){ return em < pivot; });
    Iter middle2 = std::partition(middle1, right,
                                  [pivot](const auto& em){ return !(em > pivot   ); });


        info.partition(std::distance(left, middle1), std::distance(middle2, right));


    std::future<void> han_1;
    std::future<void> han_2;

    if (count_thread <= 0) {

        info.end(std::distance(left, right));
        tst::sort(left, middle1);
        tst::sort(middle2, right);
    }
    else if (count_thread == 1) {

        info.create_thread(0, std::distance(left, middle1));
        han_1 = std::async(
                    std::launch::async,
                    [&] { return tst::sort(left, middle1); }
        );


        info.main_thread(std::distance(middle2, right));
        tst::sort(middle2, right, std::random_access_iterator_tag());
    }
    else if (count_thread >= 2) {
        count_thread -= 2;
        int thread_1 = count_thread / 2;
        int thread_2 = count_thread - thread_1;

        info.create_thread(thread_1, std::distance(left, middle1));
        han_1 = std::async(
                std::launch::async,
                multi_sort<Iter>,
                left, middle1, thread_1, std::random_access_iterator_tag()
        );

        info.create_thread(thread_2, std::distance(middle2, right));
        han_2 = std::async(
                std::launch::async,
                multi_sort<Iter>,
                middle2, right, thread_2, std::random_access_iterator_tag()
        );
    }


    if (han_1.valid()) { han_1.get(); }
    if (han_2.valid()) { han_2.get(); }

}

template <typename Iter>
void multi_sort(Iter left, Iter right, int count_thread = 4) {

    info.start(count_thread, std::distance(left, right));

    tst::multi_sort(left, right, count_thread,
                    typename std::iterator_traits<Iter>::iterator_category());
}



} // tst
