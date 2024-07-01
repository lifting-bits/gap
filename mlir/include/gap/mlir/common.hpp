// Copyright 2024, Trail of Bits, Inc.

#pragma once

#include <mlir/IR/Attributes.h>
#include <mlir/IR/Block.h>
#include <mlir/IR/Builders.h>
#include <mlir/IR/BuiltinOps.h>
#include <mlir/IR/BuiltinTypes.h>
#include <mlir/IR/Location.h>
#include <mlir/IR/MLIRContext.h>
#include <mlir/IR/Operation.h>
#include <mlir/IR/Region.h>
#include <mlir/IR/TypeRange.h>
#include <mlir/IR/Value.h>

namespace gap::mlir
{
    using attr       = ::mlir::Attribute;
    using type       = ::mlir::Type;
    using type_range = ::mlir::TypeRange;
    using value      = ::mlir::Value;
    using block      = ::mlir::Block;
    using region     = ::mlir::Region;
    using operation  = ::mlir::Operation *;
    using context    = ::mlir::MLIRContext;
    using location   = ::mlir::Location;

    using module = ::mlir::ModuleOp;
    using owning_module_ref = ::mlir::OwningOpRef< module >;

    using builder = ::mlir::Builder;
    using op_builder = ::mlir::OpBuilder;

} // namespace gap::mlir