// Copyright 2022-present, Trail of Bits, Inc.

#pragma once

#include <gap/core/concepts.hpp>
#include <gap/core/hash.hpp>

#include <tuple>
#include <unordered_map>
#include <utility>

namespace gap
{
    namespace detail
    {
        template< typename T, typename enable_t = void >
        struct function_signature;

        template< typename T >
        struct function_signature< T, std::enable_if_t< std::is_class_v< std::remove_cvref_t< T > > > >
            : function_signature< decltype(&std::remove_cvref_t< T >::operator()) >
        {};

        template< typename T, typename result_t, typename... args_t >
        struct function_signature< result_t (T::*)(args_t...) > {
            using type = result_t(args_t...);
        };

        template< typename T, typename result_t, typename... args_t >
        struct function_signature< result_t (T::*)(args_t...) const > {
            using type = result_t(args_t...);
        };

        template< typename result_t, typename... args_t >
        struct function_signature< result_t(args_t...) > {
            using type = result_t(args_t...);
        };

        template< typename result_t, typename... args_t >
        struct function_signature< result_t (&)(args_t...) > {
            using type = result_t(args_t...);
        };

        template< typename result_t, typename... args_t >
         struct function_signature< result_t (*)(args_t...) > {
            using type = result_t(args_t...);
        };

        template< typename T >
        using function_signature_t = typename function_signature< T >::type;

        template< typename T >
        struct drop_first_arg;

        template< typename result_t, typename first_t, typename... args_t >
        struct drop_first_arg< result_t(first_t, args_t...) > {
            using type = result_t(args_t...);
        };

        struct dummy {};

        template< typename T, typename result_t = dummy, typename enable_t = void >
        struct recursive_function_signature;

        template< typename T, typename result_t >
        struct recursive_function_signature<
            T,
            result_t,
            std::enable_if_t< std::is_class_v< std::remove_cvref_t< T > > > >
        {
            using type = typename drop_first_arg< function_signature_t<
                decltype(&std::remove_cvref_t< T >::template operator()< result_t (*)(...) >) > >::type;
        };

        template< typename... T >
        using recursive_function_signature_t = typename recursive_function_signature< T... >::type;

        template< typename T, typename U >
        inline constexpr bool is_same_base
            = std::is_same_v< std::remove_cvref_t< T >, std::remove_cvref_t< U > >;

    } // namespace detail

    template< typename signature, typename function, bool recursive = false >
    struct memoizer;

    template< typename result_t, typename... args_t, typename function, bool recursive >
    struct memoizer< result_t(args_t...), function, recursive > {
        using function_type      = function;
        using function_signature = result_t(args_t...);

        using tuple_type       = std::tuple< std::remove_reference_t< args_t >... >;
        using result_type      = result_t;
        using return_reference = const result_type &;

        using hash_type  = gap::hash< tuple_type >;
        using cache_type = std::unordered_map< tuple_type, result_type, hash_type >;

        explicit memoizer(function_type &&fn) : fn(std::forward< function_type >(fn)) {}

        template< typename... call_args_t >
        return_reference operator()(call_args_t &&...args) {
            return call< std::conditional_t<
                detail::is_same_base< call_args_t, args_t >, call_args_t &&,
                std::remove_cvref_t< args_t > && >... >(std::forward< call_args_t >(args)...);
        }

        std::size_t cache_size() const { return cache.size(); }

        template< typename... call_args_t >
        bool cached(call_args_t &&...args) const {
            auto tuple = std::forward_as_tuple(std::forward< call_args_t >(args)...);
            return cache.count(tuple);
        }

      private:
        template< typename... call_args_t >
        return_reference call(call_args_t &&...args) {
            auto tuple = std::forward_as_tuple(std::forward< call_args_t >(args)...);
            if (auto res = cache.find(tuple); res != cache.end()) {
                return res->second;
            } else {
                if constexpr (recursive) {
                    return cache_call([this] (auto && ...args) {
                            return fn(*this, std::forward<decltype(args)>(args)...);
                        }, std::move(tuple))->second;
                } else {
                    return cache_call(fn, std::move(tuple))->second;
                }
            }
        }

        template< typename function_t >
        auto cache_call(function_t &&f, tuple_type &&args) {
            auto result = std::apply(std::forward< function_t >(f), args);
            return cache.emplace(std::move(args), std::move(result)).first;
        }

        function_type fn;
        cache_type cache;
    };

    template< typename signature, typename function_t >
    inline auto memoize(function_t &&fn) {
        return memoizer< signature, function_t >(std::forward< function_t >(fn));
    }

    template< typename function_t >
    inline auto memoize(function_t &&fn) {
        return memoizer< detail::function_signature_t< function_t >, function_t >(
            std::forward< function_t >(fn)
        );
    }

    template< typename signature, typename function_t >
    inline auto recursive_memoize(function_t &&fn) {
        if constexpr (std::is_function_v< signature >) {
            return memoizer< signature, function_t, true >(std::forward< function_t >(fn));
        } else {
            using rec_sig = detail::recursive_function_signature_t< function_t, signature >;
            return memoizer< rec_sig, function_t, true >(std::forward< function_t >(fn));
        }
    }

    template< typename function_t >
    inline auto recursive_memoize(function_t &&fn) {
        return memoizer<
            detail::recursive_function_signature_t< function_t >, function_t, true >(
            std::forward< function_t >(fn)
        );
    }

} // namespace gap
