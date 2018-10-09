#include <benchmark/benchmark.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace {

    struct mock_function {
        MOCK_CONST_METHOD0(call, void());
        void operator()(){call();}
    };

    struct mock_clock : public benchmark::clock {
        MOCK_CONST_METHOD0(now, std::chrono::time_point<std::chrono::steady_clock>());
    };

}

using ::testing::Return;
using ::testing::Throw;

TEST(BenchmarkTest, BenchmarkMeasuresTimeBeforeAndAfterFunctionCall) {
    mock_function f;
    mock_clock clock;

    ::testing::InSequence enforce_sequence;
    EXPECT_CALL(clock, now())
        .Times(1);
    EXPECT_CALL(f, call())
        .Times(1);
    EXPECT_CALL(clock, now())
        .Times(1);

    benchmark::benchmark(std::ref(f), clock);
}

