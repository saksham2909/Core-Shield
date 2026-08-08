# CoreShield Design

---

## Project Vision

Build a reusable C++ request management framework.

The project should remain modular, maintainable, and easy to extend.

---

## Initial Architecture

Current project contains:

- Source files
- Header files
- Documentation
- Examples
- Tests

Business logic has not been implemented yet.

---

## Design Decisions

### Why CMake?

- Cross-platform
- Industry standard
- Simplifies builds

### Why Ninja?

- Lightweight
- Fast
- Works well with CMake

### Why Out-of-Source Build?

Keeping generated files inside the build directory keeps the source tree clean and improves maintainability.

---

## Future Modules

- Sliding Window
- Fixed Window
- Token Bucket
- Logging
- Analytics

## Design Decisions

### Public API

CoreShield exposes a RateLimiter class instead of algorithm-specific classes.

Current API:

RateLimiter(maxRequests, windowSize)

Reason:
- Stable public interface.
- Internal algorithm can change later.

---

### Current Scope

- Single User
- Sliding Window (next milestone)
- No Factory
- No Multi-user support