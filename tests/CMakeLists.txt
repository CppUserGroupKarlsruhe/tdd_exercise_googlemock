set(TEST_FILES test_benchmark.cpp)

add_executable(test_benchmark ${TEST_FILES})
add_dependencies(test_benchmark benchmark)

target_link_libraries(test_benchmark
    benchmark
    gmock_main
    gtest
    gmock
    )

add_test(NAME test_benchmark_test COMMAND test_benchmark)
