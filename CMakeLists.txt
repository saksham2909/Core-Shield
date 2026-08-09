# BY THIS FILE , THE WAY OF COMPILING WHOLE CODE CHANGES , IT MAKES THE USUAL COMPILATION EASY.
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