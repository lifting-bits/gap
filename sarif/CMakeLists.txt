# Copyright (c) 2024-present, Trail of Bits, Inc. All rights reserved.

find_package(nlohmann_json CONFIG REQUIRED)

add_headers(sarif GAP_SARIF_HEADERS
	sarif.hpp
)

add_sources(sarif GAP_SARIF_SOURCES
	sarif.cpp
)

add_gap_static_library(gap-sarif "${GAP_SARIF_HEADERS}" "${GAP_SARIF_SOURCES}")
target_link_libraries(gap-sarif PUBLIC nlohmann_json::nlohmann_json)