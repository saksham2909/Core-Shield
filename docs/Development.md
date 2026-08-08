# Development Log

---

## Milestone 1 - Project Setup

### Goal

Set up a professional C++ project structure.

### Completed

- Created project structure
- Added CMake
- Configured Ninja build
- Successfully built first executable
- Verified build system

### Learnings

- Difference between compiler and build system
- What CMake does
- What Ninja does
- Out-of-source builds

### Problems Faced

- CMake selected NMake by default.
- Ninja was not installed initially.

### Solution

Installed Ninja and configured CMake to use the Ninja generator.

### Next Milestone

Design the CoreShield architecture.

## Milestone 2 - RateLimiter Skeleton

### Completed
- Added RateLimiter class.
- Added configurable constructor (maxRequests, windowSize).
- Added allowRequest() public API.
- Verified library builds successfully.
- Verified example application uses RateLimiter.

### Next
- Implement Sliding Window algorithm (Single User).