#pragma once

#include <gap/mlir/common.hpp>

#include "mlir_context_fixture.hpp"

namespace gap::test
{
    struct MLIRModuleTestFixture : MLIRContextTestFixture
    {
        using base = MLIRContextTestFixture;

        MLIRModuleTestFixture()
            : base(std::make_unique< gap::mlir::context >())
            , bld(mctx.get())
            , mod(bld.create< gap::mlir::module >(bld.getUnknownLoc()))
        {}

        gap::mlir::op_builder bld;
        gap::mlir::owning_module_ref mod;
    };

} // namespace gap::test