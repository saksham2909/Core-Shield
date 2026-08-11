# CoreShield

CoreShield is a modular C++ rate limiting library designed to control
the number of requests accepted by an application.

The project focuses on multiple rate limiting algorithms, interchangeable
strategies, metrics, benchmarking, adaptive selection and thread-safe
request handling.

## Features

- Sliding Window Rate Limiting
- Fixed Window Rate Limiting
- Token Bucket Rate Limiting
- Strategy-based architecture
- Factory-based strategy creation
- Runtime request metrics
- Workload benchmarking
- Adaptive algorithm selection
- Thread-safe request handling
- Automated tests

## Architecture

```text
Application
     |
     v
RateLimiter
     |
     v
Algorithm Selection
     |
     v
RateLimitStrategyFactory
     |
     +-------------------+
     |         |         |
     v         v         v
 Sliding    Fixed     Token
 Window     Window    Bucket
     |
     v
Allow / Reject
     |
     v
Metrics