// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include <gap/core/concepts.hpp>
#include <iterator>
#include <numeric>

namespace gap::ranges
{
    template< typename R >
    concept range = requires(R&& r) {
        typename std::decay_t< R >::value_type;
        std::begin(r);
        std::end(r);
    };

    template< range R >
    constexpr auto size(R&& r) {
        return std::size(r);
    }

    template< typename R >
    concept sized_range = range< R > && requires(R&& r) { ranges::size(r); };

    template< typename R >
    concept arithmetic_range = range< R > && arithmetic< typename R::value_type >;

    template< typename R, typename V >
    concept value_range = range< R > && convertible_to< typename R::value_type, V >;

    constexpr auto accumulate(range auto r, auto init) {
        return std::accumulate(r.begin(), r.end(), init);
    }

    constexpr auto accumulate(range auto r, auto init, auto bop) {
        return std::accumulate(r.begin(), r.end(), init, bop);
    }

    template< range R >
    using iterator_t = decltype(std::begin(std::declval< R& >()));

    template< range R >
    using range_value_t = std::iter_value_t< iterator_t< R > >;

    template< typename T >
    concept has_reserve = requires(T t, std::size_t s) { t.reserve(s); };

    template< typename container_t, std::ranges::input_range R >
    void move_or_copy_elements(R&& rng, container_t& container) {
        if constexpr (std::is_rvalue_reference_v< decltype(rng) >) {
            std::move(std::ranges::begin(rng), std::ranges::end(rng),
                std::back_inserter(container)
            );
        } else {
            std::copy(std::ranges::begin(rng), std::ranges::end(rng),
                std::back_inserter(container)
            );
        }
    }

    template< template< typename... > class container_t >
    struct to_fn {
        template< std::ranges::input_range R >
        auto operator()(R&& range) const {
            using value_type         = std::ranges::range_value_t< R >;
            using result_container_t = container_t< value_type >;

            result_container_t container;

            if constexpr (has_reserve< result_container_t >) {
                if constexpr (requires { std::ranges::size(range); }) {
                    container.reserve(std::ranges::size(range));
                }
            }

            move_or_copy_elements(std::forward< R >(range), container);
            return container;
        }

        template< std::ranges::input_range R >
        friend auto operator|(R&& range, const to_fn& to) {
            return to(std::forward< R >(range));
        }
    };

    template< template< typename... > class container_t >
    inline constexpr to_fn< container_t > to{};

    template< template< typename... > class container_t, std::ranges::input_range R >
    auto operator|(R&& range, to_fn< container_t > const& to) {
        return to(std::forward< R >(range));
    }

} // namespace gap::ranges
