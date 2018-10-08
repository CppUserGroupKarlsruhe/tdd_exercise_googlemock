Online benchmark TDD kata
=========================

Test-driven development is a software development process that
basically puts writing a failing unit test before modifying your
production code. Googlemock is a framework that supports you
with generating mock objects for use in place of real objects.
Mock objects can be loaded with expected method calls plus
appropriate responses. Any missed expectation will lead to an error.

This repository provides a C++ scaffold to use googlemock with a
simple example to help you learn practice TDD together with googlemock.


The task
--------

Implement a benchmarking function that measures the time required to
execute a computationally heavy function and upload the result to an online
server.

The online server "distinguishes" systems by a nickname. The server will
only accept a result for a nickname if it is better than any previously
recorded results for the same nickname. Since the server is often under
heavy load, interacting with the server may temporarily fail, so please
retry the respective operation up to three times in these cases.

You can find the "API" for the "online" server at `benchmark/benchmark/benchmark.h`
together with relevant documentation.


Quickstart with C++
-------------------

```
> git clone https://github.com/blue-yonder/tdd_exercise_googlemock.git
> cd tdd_exercise_googlemock
> cmake .
```

The header file `benchmark/benchmark/benchmark.h` is supposed to hold any public
declarations you require. The source file `benchmark/src/benchmark.cpp` is supposed
to hold your implementation. Finally, drive your implementation by adding
tests to the `tests/test_benchmark.cpp` file.

To compile your code and execute the unit tests, use the following commands:

```
> make && ctest --verbose
```

Running this command for the first time will present you with a _failing_ unit
test. The unit test does not do anything meaningful, it is just there to
illustrate how writing tests with googlemock works.
