[![Build and Test](https://github.com/lifting-bits/gap/actions/workflows/build.yml/badge.svg)](https://github.com/lifting-bits/gap/actions/workflows/build.yml)

# GAP
A utility library to bridge llvm and mlir gaps.

## Build & Configure
NOTE: if using the vcpkg preset, `VCPKG_ROOT` must be set to the root directory of the vcpkg instance

```
cmake --preset ninja-multi-vcpkg
```

```
cmake  --build --preset ninja-multi-vcpkg
```

## Install & Integrate

Simply use cmake install infrastructure:

```
cmake -DCMAKE_INSTALL_PREFIX:PATH=<path> --build --preset ninja-multi-vcpkg --target install
```

where installation path might be for example `~/opt/gap`.

To integrate into other `cmake` project simply include:

```
find_package(gap CONFIG REQUIRED)
```

and point `cmake` to `gap` install directory:

```
cmake -Dgap_DIR=~/opt/gap/lib/cmake/gap ...
```

## Test

```
ctest ./builds/ --preset ninja-multi-vcpkg
```

## Dependencies

| Name | Version |
| ---- | ------- |
| [Git](https://git-scm.com/) | Latest |
| [CMake](https://cmake.org/) | 3.21+ |
| [Clang](http://clang.llvm.org/) | 12+ |
| [ccache](https://ccache.dev/) | Latest |

Cmake takes care of downloading and building the vcpkg dependencies listed in `vcpkg.json`.

## Dependencies for development

- [pre-commit](https://pre-commit.com/) `pip install pre-commit`
- [cmake-format](https://cmake-format.readthedocs.io/en/latest/) `pip install cmakelang`
  recommended together with vscode cmake-format extension
  
## Structure

1. __Core GAP__

    - contracts
    - error handling
    - parsing
    - logging
    - coroutines
    - ranges
    - benchmarks
    - data structures
    - cmake utils

2. __LLVM GAP__

    - ranges
    - single context library (sc)
    - monadic builders

3. __MLIR GAP__

    - parser
    - fmt
    - single context library (sc)
    - ranges

4. __Any IR GAP__

    - serialize/deserialize uniform ir representation
