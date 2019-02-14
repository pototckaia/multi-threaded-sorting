#include <benchmark/benchmark.h>
#include <glog/logging.h>
#include <iostream>

#include "sort.h"
#include "dump.h"

enum sort_mode { SINGLE, MUlTI };

static void CustomThreads(benchmark::internal::Benchmark* b) {
    b->Args({sort_mode::SINGLE, 0});
    for (int i = 1; i <= 15; ++i)
        b->Args({sort_mode::MUlTI, i});
}


static auto test_vector_little = get_test_vector(container_size::little);
static void BM_Sort_little(benchmark::State& state)
{
    for (auto _ : state) {
        state.PauseTiming();
        auto v = test_vector_little;
        state.ResumeTiming();

        if (state.range(0) == sort_mode::SINGLE) {
            std::sort(v->begin(), v->end());
        }
        else if (state.range(0) == sort_mode::MUlTI) {
            tst::multi_sort(v->begin(), v->end(), state.range(1));
        }
    }
}

BENCHMARK(BM_Sort_little)
->Apply(CustomThreads);


static auto test_vector_big = get_test_vector(container_size::big);
static void BM_Sort_big(benchmark::State& state)
{
    for (auto _ : state) {
        state.PauseTiming();
        auto v = test_vector_big;
        state.ResumeTiming();

        if (state.range(0) == sort_mode::SINGLE) {
            std::sort(v->begin(), v->end());
        }
        else if (state.range(0) == sort_mode::MUlTI) {
            tst::multi_sort(v->begin(), v->end(), state.range(1));
        }
    }
}

BENCHMARK(BM_Sort_big)
    ->Apply(CustomThreads);

//static auto test_vector_great = get_test_vector(container_size::great);
//static void BM_Sort_great(benchmark::State& state)
//{
//    for (auto _ : state) {
//        state.PauseTiming();
//        auto v = test_vector_great;
//        state.ResumeTiming();
//
//        if (state.range(0) == sort_mode::SINGLE) {
//            std::sort(v->begin(), v->end());
//        }
//        else if (state.range(0) == sort_mode::MUlTI) {
//            tst::multi_sort(v->begin(), v->end(), state.range(1));
//        }
//    }
//}
//BENCHMARK(BM_Sort_great)
//    ->Apply(CustomThreads);
//


int main(int argc, char** argv)
{

//    FLAGS_logtostderr = true;
    std::cout << argv[0];
    //google::SetLogDestination(google::GLOG_INFO, "../logger" );
    //google::InitGoogleLogging(argv[0]);


    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
}
