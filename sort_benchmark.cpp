#include <benchmark/benchmark.h>

#include "sort.h"
#include "dump.h"

enum sort_mode { SINGLE, MUlTI };


static void BM_Sort(benchmark::State& state)
{
    for (auto _ : state) {
        state.PauseTiming();
        auto v = get_test_vector(state.range(1));
        state.ResumeTiming();

        if (state.range(0) == sort_mode::SINGLE) {
            tst::sort(v->begin(), v->end());
        }
        else if (state.range(0) == sort_mode::MUlTI) {
            tst::multi_sort(v->begin(), v->end(), state.range(2));
        }
    }
}

static void CustomTheards(benchmark::internal::Benchmark* b) {
    for (int i = 1; i <= 16; i*=2)
        b->Args({sort_mode::MUlTI, container_size::little, i});
}

BENCHMARK(BM_Sort)
    ->Args({sort_mode::SINGLE, container_size::little})
    ->Apply(CustomTheards);

BENCHMARK_MAIN();