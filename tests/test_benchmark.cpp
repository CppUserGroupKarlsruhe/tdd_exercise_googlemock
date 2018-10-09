#include <benchmark/benchmark.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace {

    struct mock_function {
        MOCK_CONST_METHOD0(call, void());
        void operator()(){call();}
    };

}

using ::testing::Return;
using ::testing::Throw;

TEST(BenchmarkTest, ExecuteFunction) {
    mock_function f;
    benchmark::benchmark(std::ref(f));
}
