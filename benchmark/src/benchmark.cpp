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

void benchmark(std::function<void()> to_benchmark, std::string const & id, clock const & clock, api & api)
{
    auto const start = clock.now();
    to_benchmark();
    auto const stop = clock.now();
    auto const elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    unsigned int const max_retries = 3;
    for (unsigned int retries = 0; retries <= max_retries; ++retries) {
        try {
            api.upload_fastest_time_for(id, elapsed);
            return;
        } catch (std::invalid_argument const &) {
            return;
        } catch (std::runtime_error const &) {
            if (retries == max_retries) {
                throw;
            }
        }
    }
}

}