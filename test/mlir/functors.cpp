// Copyright (c) 2024, Trail of Bits, Inc.

#include <doctest/doctest.h>

#include <mlir/IR/MLIRContext.h>
#include <mlir/IR/BuiltinTypes.h>

#include <gap/mlir/functors.hpp>

namespace gap::test
{
    using namespace gap::mlir;

    TEST_SUITE("functors") {

        auto mctx = std::make_unique< ::mlir::MLIRContext >();

        auto i32  = ::mlir::IntegerType::get(mctx.get(), 32);

        TEST_CASE("isa") {
            CHECK(gap::mlir::isa< ::mlir::IntegerType >(i32));
        }

        TEST_CASE("cast") {
            CHECK(gap::mlir::cast< ::mlir::IntegerType >(i32));
        }

        TEST_CASE("dyn_cast") {
            CHECK(gap::mlir::dyn_cast< ::mlir::IntegerType >(i32));
            CHECK(!gap::mlir::dyn_cast< ::mlir::FloatType >(i32));
        }

    } // TEST_SUITE("functors")

} // namespace gap::mlir::test
