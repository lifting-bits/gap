// Copyright (c) 2024, Trail of Bits, Inc.

#pragma once

namespace gap::core {

    template< typename T, template< typename > class crtp_type >
    struct crtp
    {
        T &underlying() { return static_cast< T & >(*this); }

        const T &underlying() const { return static_cast< const T & >(*this); }

      private:
        crtp() {}

        friend crtp_type< T >;
    };

} // namespace gap::core
