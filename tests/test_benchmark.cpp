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

    struct mock_api : public benchmark::api {
        MOCK_CONST_METHOD1(get_fastest_time_for, std::chrono::milliseconds(std::string const &));
        MOCK_METHOD2(upload_fastest_time_for, void(std::string const &, std::chrono::milliseconds const &));
    };

}

using ::testing::Return;
using ::testing::Throw;

TEST(BenchmarkTest, BenchmarkMeasuresTimeBeforeAndAfterFunctionCall) {
    mock_function f;
    std::string const machine_id("this is me");
    mock_clock clock;
    ::testing::NiceMock<mock_api> api;

    ::testing::InSequence enforce_sequence;
    EXPECT_CALL(clock, now())
        .Times(1);
    EXPECT_CALL(f, call())
        .Times(1);
    EXPECT_CALL(clock, now())
        .Times(1);

    benchmark::benchmark(std::ref(f), machine_id, clock, api);
}

TEST(BenchmarkTest, ResultIsTransferredToServer) {
    ::testing::NiceMock<mock_function> f;
    std::string const machine_id("this is me");
    mock_clock clock;
    mock_api api;

    std::chrono::time_point<std::chrono::steady_clock> const before;
    std::chrono::milliseconds const duration(10);
    auto const after = before + duration;

    EXPECT_CALL(clock, now())
        .WillOnce(Return(before))
        .WillOnce(Return(after));
    EXPECT_CALL(api, upload_fastest_time_for(machine_id, duration))
        .Times(1);

    benchmark::benchmark(std::ref(f), machine_id, clock, api);
}

TEST(BenchmarkTest, ResultIsWorseThanWhatIsOnTheServer) {
    ::testing::NiceMock<mock_function> f;
    std::string const machine_id("this is me");
    ::testing::NiceMock<mock_clock> clock;
    mock_api api;

    EXPECT_CALL(api, upload_fastest_time_for(testing::_, testing::_))
        .WillOnce(Throw(std::invalid_argument("Result is not better than current best")));

    benchmark::benchmark(std::ref(f), machine_id, clock, api);
}

TEST(BenchmarkTest, UnavailableServerLeadsToException) {
    ::testing::NiceMock<mock_function> f;
    std::string const machine_id("this is me");
    ::testing::NiceMock<mock_clock> clock;
    mock_api api;

    EXPECT_CALL(api, upload_fastest_time_for(testing::_, testing::_))
        .WillRepeatedly(Throw(std::runtime_error("Server unavailable")));

    EXPECT_THROW(benchmark::benchmark(std::ref(f), machine_id, clock, api), std::runtime_error);
}
