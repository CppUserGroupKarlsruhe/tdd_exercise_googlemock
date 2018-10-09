#include <benchmark/benchmark.h>

#include <stdexcept>
#include <thread>

namespace benchmark_cases {

    void heavy_computation()
    {
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

}

namespace api {

    std::chrono::milliseconds get_fastest_time_for(std::string const &)
    {
        throw std::runtime_error("The benchmark server cannot be reached. Please contact your administrator.");
    }

    void upload_fastest_time_for(std::string const &, std::chrono::milliseconds const &)
    {
        throw std::runtime_error("The benchmark server cannot be reached. Please contact your administrator.");
    }

}


namespace benchmark {

void benchmark(std::function<void()> to_benchmark, clock const & clock)
{
    to_benchmark();
    clock.now();
    clock.now();
}

}