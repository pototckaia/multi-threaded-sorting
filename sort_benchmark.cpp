#include <benchmark/benchmark.h>

#include "sort.h"
#include "dump.h"

namespace container_size
{
    static std::size_t great = 100000000000000000;
    static std::size_t big =   100000000000;
    static std::size_t little = 10000;
} // container_size

enum sort_mode { SINGLE, MUlTI };

static void BM_Sort(benchmark::State& state)
{
    state.PauseTiming();
    auto v = rand_vector(state.range(2));
    state.ResumeTiming();

    if (state.range(0) == sort_mode::SINGLE) {
        tst::sort(v->begin(), v->end());
    }
    else if (state.range(0) == sort_mode::MUlTI) {
        tst::multi_sort(v->begin(), v->end(), state.range(3) );
    }
}

BENCHMARK(BM_Sort)
    ->Args({sort_mode::SINGLE, container_size::little})
    ->Args({sort_mode::MUlTI, container_size::little, 1});

BENCHMARK_MAIN();