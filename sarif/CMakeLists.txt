# Copyright (c) 2024-present, Trail of Bits, Inc. All rights reserved.

find_package(nlohmann_json CONFIG REQUIRED)

add_headers(sarif GAP_SARIF_HEADERS
	definitions.hpp
)

add_gap_library(gap-sarif "${GAP_SARIF_HEADERS}")
target_link_libraries(gap-sarif INTERFACE nlohmann_json::nlohmann_json)