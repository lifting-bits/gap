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
endfunction()

function(add_gap_static_library name headers sources)
	add_library(${name} STATIC ${sources})

	add_library(gap::${name} ALIAS ${name})

	target_compile_features(${name} INTERFACE cxx_std_20)

	target_include_directories(${name}
		PUBLIC
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	    	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
	)

	set_target_properties(${name} PROPERTIES PUBLIC_HEADER "${headers}")

	target_link_libraries(${name} INTERFACE gap-settings)
endfunction()

function(install_gap_target name include_dir)
	set(GAP_EXPORT_NAME gapTargets)

	install(TARGETS ${name}
		EXPORT ${GAP_EXPORT_NAME}
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
			NAMELINK_SKIP
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/gap/${include_dir}
	)

	install(EXPORT ${GAP_EXPORT_NAME}
		FILE ${GAP_EXPORT_NAME}.cmake
		NAMESPACE gap::
		DESTINATION ${GAP_CMAKE_INSTALL_DIR}
	)

	install(TARGETS ${name}
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
			NAMELINK_ONLY
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/gap/${include_dir}
	)
endfunction()
