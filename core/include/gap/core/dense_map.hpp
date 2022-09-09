// Copyright (c) 2022-present, Trail of Bits, Inc.

#pragma once

#include <gap/core/concepts.hpp>
#include <utility>
#include <vector>

namespace gap
{

    //
    // Dense map stores map from integers to values in a flat container.
    //
    // It keeps empty slots for unmapped keys.
    // NOTE: The implementation uses default value as a flag to denote missing
    // value in the map.
    //
    template<
        gap::unsigned_integral key_t,
        typename value_t,
        typename container_t = std::vector< value_t > >
    struct dense_map {
        using key_type    = key_t;
        using mapped_type = value_t;
        using value_type  = std::pair< key_type, mapped_type >;

        using size_type       = typename container_t::size_type;
        using reference       = std::pair< key_type, mapped_type& >;
        using const_reference = std::pair< key_type, const mapped_type& >;

        using base_iterator       = typename container_t::iterator;
        using base_const_iterator = typename container_t::const_iterator;

        container_t _container;

        constexpr dense_map() = default;

        template< typename reference_type >
        struct proxy {
            reference_type ref;
            reference_type* operator->() { return &ref; }
        };

        template< typename base, typename reference_type >
        struct iterator_t {
            base _iter;
            key_type _index;

            constexpr iterator_t(key_type idx, base it)
                : _iter(it)
                , _index(idx) {}

            constexpr reference_type operator*() { return { _index, *_iter }; }
            constexpr proxy< reference_type > operator->() {
                return {
                    {_index, *_iter}
                };
            }

            constexpr bool operator<(iterator_t other) const { return _iter < other._iter; }
            constexpr bool operator==(iterator_t other) const { return _iter == other._iter; }

            constexpr iterator_t operator+(key_type key) const {
                return { _index + key, _iter + key };
            }

            constexpr iterator_t& operator++() {
                ++_iter;
                ++_index;
                return *this;
            }

            constexpr iterator_t operator++(int) {
                auto rv = *this;
                ++*this;
                return rv;
            }

            constexpr iterator_t operator-(key_type key) const {
                return { _index - key, _iter - key };
            }

            constexpr iterator_t& operator--() {
                --_iter;
                --_index;
                return *this;
            }

            constexpr iterator_t operator--(int) {
                auto rv = *this;
                --*this;
                return rv;
            }
        };

        using const_iterator = iterator_t< base_const_iterator, const_reference >;
        using iterator       = iterator_t< base_iterator, reference >;

        constexpr auto begin() { return iterator(0, _container.begin()); }
        constexpr auto begin() const { return cbegin(); }
        constexpr auto cbegin() const { return const_iterator(0, _container.cbegin()); }

        constexpr auto end() { return iterator(size(), _container.end()); }
        constexpr auto end() const { return cend(); }
        constexpr auto cend() const { return const_iterator(size(), _container.cend()); }

        constexpr auto empty() const { return _container.empty(); }
        constexpr key_type size() const { return key_type(_container.size()); }

        constexpr bool full() const {
            return std::all_of(_container.begin(), _container.end(), [](const auto& value) {
                return value != mapped_type();
            });
        }

        constexpr void clear() noexcept { _container.clear(); }

        constexpr bool _bump(key_type k) {
            if (size_t(k) < _container.size())
                return false;
            else
                return _container.resize(k + 1), true;
        }

        constexpr mapped_type& operator[](key_type k) {
            _bump(k);
            return _container[k];
        }

        constexpr std::pair< iterator, bool > insert(const_reference value) {
            key_type idx = value.first;
            bool is_new  = _bump(value.first);
            if (is_new || _container[idx] == mapped_type())
                _container[idx] = value.second;
            return { iterator(idx, _container.begin() + idx), is_new };
        }

        constexpr std::pair< iterator, bool > emplace(key_type idx, mapped_type val) {
            return insert(std::make_pair(idx, val));
        }

        constexpr void erase(iterator pos) { pos->second = mapped_type(); }
        constexpr void erase(key_type key) { _container[key] = mapped_type(); }

        constexpr size_type count(key_type key) const {
            return size_t(key) < size() && _container[key] != mapped_type();
        }

        constexpr bool contains(key_type key) const { return count(key) == 1; }

        constexpr iterator find(key_type k) { return count(k) ? begin() + k : end(); }
        constexpr const_iterator find(key_type k) const { return count(k) ? cbegin() + k : end(); }

        constexpr bool operator<(const dense_map& o) const { return _container < o._container; }
        constexpr bool operator==(const dense_map& o) const { return _container == o._container; }
    };

} // namespace gap
