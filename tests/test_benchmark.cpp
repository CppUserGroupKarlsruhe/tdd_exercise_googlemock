#include <benchmark/benchmark.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace {

}

using ::testing::Return;
using ::testing::Throw;

TEST(BenchmarkTest, ExecuteFunction) {
    benchmark::benchmark(benchmark_cases::heavy_computation);
}
