#pragma once

#include <thread>
#include <future>
#include <iterator>
#include <iostream>

#include "dump.h"

namespace tst
{

template <class Iter>
void sort(Iter, Iter);

template <typename Iter>
Iter partition(Iter left, Iter right) {
    auto pivot = *std::next(left, std::distance(left, right) / 2);
    Iter head = left;
    Iter tail = std::prev(right);

    if (head == tail) { return head; }

    while (head <= tail) {
        while (pivot > *head)
            if (++head == tail) { return head; }
        while (pivot < *tail)
            if (--tail == head) { return head; }

        if (head <= tail) {
            std::iter_swap(head, tail);
            head++;
            tail--;
        }
    };

    return head;
}

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

    tst::sort(left, middle1);
    tst::sort(middle2, right);

}

template <typename Iter>
void sort(Iter left, Iter right) {
    tst::sort(left, right,
         typename std::iterator_traits<Iter>::iterator_category());
}


template <typename Iter>
void multi_sort(Iter left, Iter right, int count_thread) {
    if (std::distance(left, right) <= 1) {
        return;
    }

    auto pivot = *std::next(left, std::distance(left, right)/2);
    Iter middle1 = std::partition(left, right,
                                  [pivot](const auto& em){ return em < pivot; });
    Iter middle2 = std::partition(middle1, right,
                                  [pivot](const auto& em){ return !(em > pivot   ); });

    if (count_thread > 0) {
        --count_thread;
        auto handle = std::async(std::launch::async, multi_sort<Iter>, left, middle1, count_thread);
        tst::multi_sort(middle2, right, count_thread);
    } else {
        tst::sort(left, middle1);
        tst::sort(middle2, right);
    }

}

} // tst