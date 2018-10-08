#include <benchmark/benchmark.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

/* Use this file to test-drive the implementation of a `benchmark(...)`
 * function. Repeat the following steps until you have solved the task:
 *
 * 1. Write a _minimal_ failing test.
 * 2. Pass the test with a _minimal_ change to your production code.
 * 3. Improve both tests and production code with refactorings.
 *
 * Think about reasonable interfaces and appropriate mocks while you code.
 *
 * Compile your project and execute the tests with
 *
 *     make && ctest --verbose
 *
 * This test file will fail when it is freshly checked out.
 */

namespace {

    // check https://github.com/google/googletest/blob/master/googlemock/docs/ForDummies.md
    // for an introduction to googlemock
    struct sample_mock {
        MOCK_CONST_METHOD1(method_name, int(int));
    };

}

using ::testing::Return;
using ::testing::Throw;

TEST(BenchmarkTest, Dummy) {
    // see https://github.com/google/googletest/blob/master/googletest/docs/Primer.md#basic-assertions
    // for basic assertions or
    // https://github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md#exception-assertions
    // for asserting exceptions

    sample_mock my_mock;
    EXPECT_CALL(my_mock, method_name(42))
        .WillOnce(Return(17));

//  EXPECT_EQ(1, 0);
}
