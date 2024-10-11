# Copyright (c) 2024, Trail of Bits, Inc. All rights reserved.

add_headers(mlir GAP_MLIR_HEADERS
	common.hpp
	functors.hpp
	views.hpp
)

add_sources(coro GAP_MLIR_SOURCES
	views.cpp
)

add_gap_static_library(gap-mlir
	"${GAP_MLIR_HEADERS}"
	"${GAP_MLIR_SOURCES}"
	SYSTEM_INCLUDE_DIRECTORIES
		"${MLIR_INCLUDE_DIRS}"
		"${LLVM_INCLUDE_DIRS}"
	LINK_LIBRARIES
		MLIRIR
		MLIRSupport
)
