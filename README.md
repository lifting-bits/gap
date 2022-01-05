[![Build and Test](https://github.com/lifting-bits/gap/actions/workflows/build.yml/badge.svg)](https://github.com/lifting-bits/gap/actions/workflows/build.yml)

# GAP
A utility library to bridge llvm and mlir gaps.

## Build & Configure

```
cmake --preset ninja-multi-vcpkg
```

```
cmake  --build --preset ninja-multi-vcpkg
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
