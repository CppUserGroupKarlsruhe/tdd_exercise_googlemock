#pragma once

#include <chrono>
#include <string>
#include <functional>

namespace benchmark_cases {
    /**
     * @brief This is a computationally heavy function that should be benchmarked
     */
    void heavy_computation();
}

namespace api {

    /**
     * @brief Query the benchmark result server for the fastest result recorded for the given ID
     * @param id The ID that identifies the machine
     * @return The fastest time in milliseconds
     * @throws std::runtime_error in case of communication errors with the server
     * @throws std::invalid_argument when there is no previous result for the given ID
     */
    std::chrono::milliseconds get_fastest_time_for(std::string const & id);

    /**
     * @brief Upload a new fastest result to the benchmark result server for a machine indentified
     *        by the given ID
     * @param id The ID that identifies the machine
     * @param time The new fastest time in milliseconds
     * @throws std::runtime_error in case of communication errors with the server
     * @throws std::invalid_argument when the uploaded time is not better than the best one known for the given ID
     */
    void upload_fastest_time_for(std::string const & id, std::chrono::milliseconds const & time);

}

namespace benchmark {

struct clock {
    virtual std::chrono::time_point<std::chrono::steady_clock> now() const = 0;
};

struct api {
    virtual std::chrono::milliseconds get_fastest_time_for(std::string const &) const = 0;
    virtual void upload_fastest_time_for(std::string const &, std::chrono::milliseconds const &) = 0;
};

void benchmark(std::function<void()> to_benchmark, clock const & clock, api & api);

}