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

TEST(BenchmarkTest, BenchmarkExecutesFunctionExactlyOnce) {
    mock_function f;

    EXPECT_CALL(f, call())
        .Times(1);

    benchmark::benchmark(std::ref(f));
}
