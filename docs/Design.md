# CoreShield Design

## Objective

CoreShield is designed as a modular rate limiting framework
where different rate limiting algorithms can be used through
a common interface.

## Strategy Pattern

All algorithms implement:

`IRateLimitStrategy`

Current strategies:

- SlidingWindow
- FixedWindow
- TokenBucket

This allows algorithms to be changed without changing the
main RateLimiter interface.

## Factory

`RateLimitStrategyFactory` creates the required strategy based
on the selected Algorithm.

This keeps object creation separate from RateLimiter.

## Algorithm Selection

`AlgorithmSelector` provides a simple policy for selecting
an algorithm using request rate and rejection rate.

The current policy is intentionally simple and can be extended
in the future.

## Metrics

RateLimiter maintains:

- Total requests
- Allowed requests
- Rejected requests

These metrics can later be exposed to monitoring systems.

## Thread Safety

Shared state inside RateLimiter and individual strategies is
protected using mutexes.

Concurrent tests verify that multiple threads can use the
rate limiter safely.

## Design Goal

The project prioritizes:

- Modularity
- Reusability
- Testability
- Simple interfaces
- Extensibility