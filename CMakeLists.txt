cmake_minimum_required(VERSION 3.16)
project(CoreShield)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

option(ENABLE_COVERAGE "Enable code coverage" OFF)

add_library(CoreShield
    src/RateLimiter.cpp
    src/SlidingWindow.cpp
    src/FixedWindow.cpp
    src/TokenBucket.cpp
    src/RateLimitStrategyFactory.cpp
    src/AlgorithmSelector.cpp
)

add_executable(
    CoreShieldDemo
    examples/hello.cpp
)

target_link_libraries(CoreShieldDemo PRIVATE CoreShield)

add_executable(CoreShieldApiDemo
    examples/api_demo.cpp
)
add_executable(CoreShieldExternalDemo
    examples/external_demo.cpp
)

target_link_libraries(CoreShieldExternalDemo PRIVATE CoreShield)

target_link_libraries(CoreShieldApiDemo PRIVATE CoreShield)

add_executable(CoreShieldTests
    tests/RateLimiterTests.cpp
)

target_link_libraries(CoreShieldTests PRIVATE CoreShield)

add_executable(CoreShieldBenchmark
    tests/Benchmark.cpp
)

target_link_libraries(CoreShieldBenchmark PRIVATE CoreShield)

enable_testing()

add_test(
    NAME CoreShieldUnitTests
    COMMAND CoreShieldTests
)

if(ENABLE_COVERAGE)

    target_compile_options(CoreShield PRIVATE --coverage)
    target_compile_options(CoreShieldTests PRIVATE --coverage)

    target_link_options(CoreShieldTests PRIVATE --coverage)

endif()