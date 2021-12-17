// Copyright 2021-present, Trail of Bits, Inc.

#pragma once

#include <string>
#include <string_view>

namespace gap
{
    struct source_location {
        using file_name = std::string_view;
        using func_name = std::string_view;

        static constexpr source_location current(
            file_name file     = __builtin_FILE(),
            func_name function = __builtin_FUNCTION(),
            unsigned line      = __builtin_LINE()) noexcept {
            return source_location(file, function, line);
        }

        constexpr source_location(file_name file, func_name func, unsigned line) noexcept
            : _file(file)
            , _func(func)
            , _line(line) {}

        constexpr file_name file() const noexcept { return _file; }
        constexpr func_name function() const noexcept { return _func; }

        constexpr unsigned line() const noexcept { return _line; }

      private:
        file_name _file;
        func_name _func;
        unsigned _line;
    };

    template< typename stream >
    auto operator<<(stream &os, const source_location &loc) noexcept -> decltype(os << "") {
        return os << loc.file() << ":" << loc.function() << ":" << std::to_string(loc.line());
    }

} // namespace gap
