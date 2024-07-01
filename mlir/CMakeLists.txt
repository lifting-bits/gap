# Copyright (c) 2024, Trail of Bits, Inc. All rights reserved.

add_headers(mlir GAP_MLIR_HEADERS
	common.hpp
	functors.hpp
)

add_gap_library(gap-mlir "${GAP_MLIR_HEADERS}")

target_include_directories(gap-mlir SYSTEM
	INTERFACE
		"${MLIR_INCLUDE_DIRS}"
)

target_link_libraries(gap-mlir
	INTERFACE
		MLIRIR
		MLIRSupport
)
