// Copyright 2022-present, Trail of Bits, Inc.

#pragma once

#include <atomic>
#include <cassert>
#include <deque>
#include <gap/core/strong_type.hpp>
#include <numeric>
#include <utility>
#include <vector>

namespace gap
{
    namespace detail
    {
        struct union_tag {};
        struct rank_tag {};
    } // namespace detail

    using union_type = strong_type< std::uint32_t, detail::union_tag >;
    using rank_type  = strong_type< std::uint32_t, detail::rank_tag >;

    namespace detail
    {
        template< bool thread_safe >
        struct union_find_t {
            struct element_type_t {
                constexpr element_type_t() = default;

                explicit constexpr element_type_t(union_type p)
                    : parent(p) {}

                explicit constexpr element_type_t(union_type p, rank_type r)
                    : parent(p), rank(r) {}

                friend constexpr auto operator<=>(const element_type_t &, const element_type_t &)
                    = default;

                element_type_t &operator++() requires incrementable< union_type > {
                    ++parent;
                    return *this;
                }

                element_type_t operator++(int) requires incrementable< union_type > {
                    element_type_t tmp = *this;
                    ++parent;
                    return tmp;
                }

                union_type parent = union_type(0);
                rank_type rank    = rank_type(0);
            };

            static consteval bool is_thread_safe() { return thread_safe; }

            using element_type
                = std::conditional_t< thread_safe, std::atomic< element_type_t >, element_type_t >;

            static_assert(sizeof(element_type) == 8);

            explicit union_find_t(std::size_t size)
                : _data(size) {
                std::iota(std::begin(_data), std::end(_data), element_type_t(union_type(0)));
            }

            [[nodiscard]] union_type find(union_type idx) requires(thread_safe) {
                while (idx != parent(idx)) {
                    auto value  = at(idx).load();
                    auto update = element_type_t(parent(value), rank(value));
                    if (value != update)
                        _data[idx.ref()].compare_exchange_weak(value, update);
                    idx = parent(value);
                }
                return idx;
            }

            [[nodiscard]] union_type find(union_type idx) requires(!thread_safe) {
                while (idx != parent(idx)) {
                    auto &par = parent(idx);
                    par       = parent(par);
                    idx       = par;
                }

                return idx;
            }

            [[nodiscard]] std::uint32_t size() const { return std::uint32_t(_data.size()); }

            [[nodiscard]] rank_type rank(const element_type &elem) const {
                if constexpr (thread_safe)
                    return elem.load().rank;
                else
                    return elem.rank;
            }

            [[nodiscard]] rank_type rank(union_type idx) const { return rank(at(idx)); }

            [[nodiscard]] const union_type &parent_impl(const element_type &elem) const {
                if constexpr (thread_safe)
                    return elem.load().parent;
                else
                    return elem.parent;
            }

            [[nodiscard]] union_type &parent_impl(element_type &elem) {
                if constexpr (thread_safe)
                    return elem.load().parent;
                else
                    return elem.parent;
            }

            [[nodiscard]] const union_type &parent(union_type idx) const { return parent_impl(at(idx)); }
            [[nodiscard]] union_type &parent(union_type idx) { return parent_impl(at(idx)); }
            [[nodiscard]] const union_type &parent(element_type elem) const { return parent(elem.parent); }
            [[nodiscard]] union_type &parent(element_type elem) { return parent(elem.parent); }

            union_type merge(union_type a, union_type b) noexcept requires(!thread_safe) {
                assert(a == parent(a));
                assert(b == parent(b));
                assert(a != b);

                at(b).parent = a;
                return a;
            }

            template< typename stream >
            friend auto operator<<(stream &os, const union_find_t &uf) -> decltype(os << "") {
                for (const auto &value : uf.data()) {
                    os << value;
                }
                return os;
            }

          protected:
            [[nodiscard]] inline const std::deque< element_type > &data() const { return _data; }

            [[nodiscard]] inline const element_type &at(union_type idx) const {
                assert(size() > idx.ref());
                return _data[idx.ref()];
            }

            [[nodiscard]] inline element_type &at(union_type idx) {
                assert(size() > idx.ref());
                return _data[idx.ref()];
            }

            std::deque< element_type > _data;
        };

        static constexpr bool thread_safe_tag = true;

        struct thread_safe_resizable_base {
          protected:
            std::mutex _mutex;
        };

        struct non_thread_safe_resizable_base {};

        template< bool thread_safe >
        struct resizable_base
            : std::conditional<
                  thread_safe,
                  thread_safe_resizable_base,
                  non_thread_safe_resizable_base >
        {};

        template< typename base >
        struct resizable
            : base
            , resizable_base< base::is_thread_safe() >
        {
            using base::base;

            using base::size;
            using base::_data;

            // TODO(heno) return new set
            auto &make_new_set() requires(base::is_thread_safe()) {
                std::lock_guard guard(this->_mutex);
                return _data.emplace_back(union_type(size()));
            }

            auto &make_new_set() requires(!base::is_thread_safe()) {
                return _data.emplace_back(union_type(size()));
            }
        };

        template< typename element_t, typename base >
        struct with_storage : base {
            // TODO(heno) constuctor from range of elements
          protected:
            std::vector< element_t > _elements;
        };

        template< typename element_t, typename base >
        struct resizable_with_storage : with_storage< element_t, resizable< base > > {
            using underlying_t = with_storage< element_t, resizable< base > >;
            using underlying_t::make_new_set;

            using base::_data;
            using base::_elements;

            union_type make_set(element_t &&elem) requires(base::thread_safe()) {
                // TODO(heno) make thread_safe
                _elements.push_back(std::forward< element_t >(elem));
                make_new_set();
                assert(_elements.size() == _data.size());
            }

            union_type make_set(element_t &&elem) {
                _elements.push_back(std::forward< element_t >(elem));
                make_new_set();
                assert(_elements.size() == _data.size());
            }
        };

    } // namespace detail

    using thread_safe_union_find = detail::union_find_t< detail::thread_safe_tag >;
    using union_find             = detail::union_find_t< !detail::thread_safe_tag >;

    template< typename element_t >
    using thread_safe_union_find_with_storage
        = detail::with_storage< element_t, thread_safe_union_find >;

    template< typename element_t >
    using union_find_with_storage = detail::with_storage< element_t, union_find >;

    using resizable_thread_safe_union_find = detail::resizable< thread_safe_union_find >;
    using resizable_union_find             = detail::resizable< union_find >;

    template< typename element_t >
    using resizable_thread_safe_union_find_with_storage
        = detail::resizable_with_storage< element_t, thread_safe_union_find >;

    template< typename element_t >
    using resizable_union_find_with_storage
        = detail::resizable_with_storage< element_t, union_find >;

} // namespace gap
