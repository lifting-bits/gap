## Building & Testing

## Structure

1. Core GAP
    - contracts
    - error handling
    - parsing
    - logging
    - coroutines
    - ranges
    - cmake utils?

2. LLVM GAP
    - ranges
    - sc

3. MLIR GAP
    - parser
    - fmt
    - sc
    - ranges

4. Interpreter?

5. Eqsat?

6. anyir

- peter request: copy and move constant around modules
- llvm constant interpreter (ask ian) + value domain:
    https://github.com/lifting-bits/anvill/blob/api_simplifications_and_extensions/lib/CrossReferenceFolder.cpp
- https://github.com/trailofbits/multiplier-old/blob/8576bc13b81cb0138fcf2e456db60374d7ddf8f5/multiplier/Util/Init.cpp
    - llvm init stuff
- llvm setup:
    - https://github.com/lifting-bits/anvill/blob/api_simplifications_and_extensions/cmake/llvm.cmake
