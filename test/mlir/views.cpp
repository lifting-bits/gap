// Copyright (c) 2024, Trail of Bits, Inc.

#include <doctest/doctest.h>

#include <mlir/IR/MLIRContext.h>
#include <mlir/IR/BuiltinTypes.h>
#include <mlir/Dialect/Func/IR/FuncOps.h>

#include <gap/mlir/common.hpp>
#include <gap/mlir/views.hpp>

#include "mlir_module_fixture.hpp"

namespace gap::test
{
    struct MLIRTestFixture : MLIRModuleTestFixture
    {
        using base = MLIRModuleTestFixture;

        MLIRTestFixture() : base() {
            ::mlir::DialectRegistry registry;
            registry.insert< ::mlir::func::FuncDialect >();
            mctx->appendDialectRegistry(registry);

            mctx->loadAllAvailableDialects();

            auto uloc = bld.getUnknownLoc();
            auto fty = bld.getFunctionType({}, {});

            bld.setInsertionPointToStart(mod->getBody());
            fn = bld.create< ::mlir::func::FuncOp >(uloc, "test", fty);

            auto mk_block = [&] (auto &region) {
                auto& blk = region.emplaceBlock();
                bld.setInsertionPointToEnd(&blk);
                bld.create< ::mlir::func::ReturnOp >(uloc);
            };

            mk_block(fn.getBody());
            mk_block(fn.getBody());
            mk_block(fn.getBody());
        }

        ::mlir::func::FuncOp fn;
    };

    using namespace gap::mlir::views;

    TEST_SUITE("views") {

        TEST_CASE_FIXTURE(MLIRTestFixture, "operation views") {
            CHECK(std::ranges::distance(regions(fn)) == 1);
            CHECK(std::ranges::distance(blocks(fn)) == 3);
            CHECK(std::ranges::distance(operations(fn)) == 3);

            CHECK(std::ranges::distance(regions(mod->getOperation())) == 1);
            CHECK(std::ranges::distance(blocks(mod->getOperation())) == 1);
            CHECK(std::ranges::distance(operations(mod->getOperation())) == 1);
        }

        TEST_CASE_FIXTURE(MLIRTestFixture, "cast views") {
            auto rets = operations(fn) | isa< ::mlir::func::ReturnOp >;
            CHECK(std::ranges::distance(rets) == 3);

            auto rets_casted = operations(fn) | filter_cast< ::mlir::func::ReturnOp >;
            CHECK(std::ranges::distance(rets_casted) == 3);

            auto fns = operations(mod->getOperation()) | isa< ::mlir::func::FuncOp >;
            CHECK(std::ranges::distance(fns) == 1);
        }

    } // TEST_SUITE("views")

} // namespace gap::test
