function(add_gap_library name headers)
	add_library(${name} INTERFACE)

	add_library(gap::${name} ALIAS ${name})

	target_compile_features(${name} INTERFACE cxx_std_20)

	target_include_directories(${name}
		INTERFACE
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	    	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
	)

	set_target_properties(${name} PROPERTIES PUBLIC_HEADER "${headers}")

	target_link_libraries(${name} INTERFACE gap-settings)

endfunction(add_gap_lib)
