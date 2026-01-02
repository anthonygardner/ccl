# cpp-lib-template

A template for C++ libraries with Python bindings, testing, and marimo notebook support.

## Prerequisites

- CMake 3.15+
- C++17 compiler
- uv (Python package manager)

## Setup

```bash
# Configure CMake
cmake -B build -DCMAKE_INSTALL_PREFIX=build/install

# Build C++ library and tests
make build.cpp

# Install Python package in development mode
make build.python
```

## Testing

```bash
# Run C++ tests
make test.cpp

# Run Python tests
make test.python
```

## Development

```bash
# Remove build artifacts
make clean

# Open marimo notebook
make notebook
```

## Project Structure
```
cpp-lib-template/
├── include/           # C++ headers
├── src/               # C++ source files
├── tests/             # C++ and Python tests
├── python/mylib/      # Python package with bindings
├── notebooks/         # Marimo notebooks
└── CMakeLists.txt
```