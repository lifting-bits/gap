#pragma once

#include <gap/mlir/common.hpp>

namespace gap::test
{
    struct MLIRContextTestFixture
    {
        MLIRContextTestFixture()
            : mctx(std::make_unique< gap::mlir::context >())
        {}

        explicit MLIRContextTestFixture(std::unique_ptr< gap::mlir::context > &&mctx)
            : mctx(std::move(mctx))
        {}

        std::unique_ptr< gap::mlir::context > mctx;
    };

} // namespace gap::test