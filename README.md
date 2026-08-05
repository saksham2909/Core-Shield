# CoreShield

A modular and reusable C++ request management framework with production-inspired architecture.

---

## Overview

CoreShield is being developed as a reusable C++ library for request management.

The project starts with a Sliding Window Rate Limiter and is designed to support multiple rate limiting algorithms in the future.

The primary objective is to learn software engineering, reusable library design, and production-style C++ development.

---

## Current Features

- Project structure
- CMake build system
- Ninja build support
- Example application

---

## Project Structure

```text
CoreShield/
├── docs/
├── examples/
├── include/
├── src/
├── tests/
```

---

## Build

```bash
mkdir build
cd build

cmake -G Ninja ..

cmake --build .

CoreShieldDemo.exe
```

---

## Roadmap

- Sliding Window
- Multi-user support
- Fixed Window
- Token Bucket
- Logging
- Statistics
- Thread Safety