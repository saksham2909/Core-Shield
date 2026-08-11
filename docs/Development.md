# CoreShield Development Log

---

## Milestone 1 - Project Setup

### Goal

Set up a professional C++ project structure.

### Completed

- Created project structure.
- Added CMake.
- Configured Ninja build.
- Successfully built the first executable.
- Verified the build system.

### Learnings

- Difference between compiler and build system.
- What CMake does.
- What Ninja does.
- Out-of-source builds.

### Problems Faced

- CMake selected NMake by default.
- Ninja was not installed initially.

### Solution

Installed Ninja and configured CMake to use the Ninja generator.

---

## Milestone 2 - RateLimiter Skeleton

### Goal

Create the main public interface of CoreShield.

### Completed

- Added `RateLimiter` class.
- Added configurable constructor.
- Added `allowRequest()` public API.
- Verified the library builds successfully.
- Verified the example application uses `RateLimiter`.

### Next

Implement the first rate limiting algorithm.

---

## Milestone 3 - Sliding Window

### Goal

Implement the Sliding Window rate limiting algorithm.

### Completed

- Implemented `SlidingWindow`.
- Added per-user request tracking.
- Added time-window based request rejection.
- Integrated Sliding Window with `RateLimiter`.
- Added strategy interface.

### Result

CoreShield could now accept or reject requests based on a configurable
request limit and time window.

---

## Milestone 4 - Strategy Architecture

### Goal

Make different rate limiting algorithms interchangeable.

### Completed

- Added `IRateLimitStrategy`.
- Added `Algorithm` enum.
- Added `FixedWindow`.
- Added `TokenBucket`.
- Added `RateLimitStrategyFactory`.
- Integrated strategy creation with `RateLimiter`.

### Architecture

```text
RateLimiter
     |
     v
RateLimitStrategyFactory
     |
     +-------------------+
     |         |         |
     v         v         v
 Sliding    Fixed     Token
 Window     Window    Bucket