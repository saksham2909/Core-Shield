cmake_minimum_required(VERSION 3.16)
project(CoreShield)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(
    CoreShieldDemo
    examples/hello.cpp
    src/RateLimiter.cpp
    src/SlidingWindow.cpp
    src/FixedWindow.cpp
    src/RateLimitStrategyFactory.cpp
    src/TokenBucket.cpp
    src/AlgorithmSelector.cpp
)

add_executable(CoreShieldApiDemo
    examples/api_demo.cpp
    src/RateLimiter.cpp
    src/SlidingWindow.cpp
    src/FixedWindow.cpp
    src/TokenBucket.cpp
    src/RateLimitStrategyFactory.cpp
    src/AlgorithmSelector.cpp
)

add_executable(CoreShieldTests
    tests/RateLimiterTests.cpp
    src/RateLimiter.cpp
    src/SlidingWindow.cpp
    src/FixedWindow.cpp
    src/TokenBucket.cpp
    src/RateLimitStrategyFactory.cpp
    src/AlgorithmSelector.cpp
)

add_executable(CoreShieldBenchmark
    tests/Benchmark.cpp
    src/RateLimiter.cpp
    src/SlidingWindow.cpp
    src/FixedWindow.cpp
    src/TokenBucket.cpp
    src/RateLimitStrategyFactory.cpp
    src/AlgorithmSelector.cpp
)

enable_testing()

add_test(
    NAME CoreShieldUnitTests
    COMMAND CoreShieldTests
)