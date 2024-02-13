// Copyright (c) 2022-present, Trail of Bits, Inc.

#include <gap/core/generator.hpp>
#include <iostream>

gap::generator< int > iota() {
    int value = 0;
    while (true) {
        co_yield value;
        ++value;
    }
}

int main() {
    for (int v : iota()) {
        if (v > 5)
            break;
        std::cout << v << '\n';
    }
}
