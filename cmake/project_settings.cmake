# Copyright (c) 2022-present, Trail of Bits, Inc. All rights reserved.

# generate a compile commands JSON file.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set a default build type if none was specified
if( NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES )
  message( STATUS "Setting build type to 'RelWithDebInfo' as none was specified." )
  set(CMAKE_BUILD_TYPE
      RelWithDebInfo
      CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui, ccmake
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
                                               "MinSizeRel" "RelWithDebInfo")
endif()

find_program( CCACHE ccache )
if ( CCACHE )
  message( STATUS "Using ccache" )
  set( CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE} )
else()
  message( WARNING "CCache was not found." )
endif()

# Generate compile_commands.json to make it easier to work with clang based tools
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

option( ENABLE_IPO
  "Enable Interprocedural Optimization, aka Link Time Optimization (LTO)" OFF
)

if( ENABLE_IPO )
  include( CheckIPOSupported )
  check_ipo_supported( RESULT res OUTPUT out )
  if( res )
    set( CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE )
  else()
    message( SEND_ERROR "IPO is not supported: ${out}" )
  endif()
endif()
