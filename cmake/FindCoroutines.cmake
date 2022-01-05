# Copyright (c) 2019-present, Facebook, Inc.
#
# This source code is licensed under the Apache License found in the LICENSE.txt file in the root
# directory of this source tree.

#[=======================================================================[.rst:

FindCoroutines
##############

This module supports the C++ standard support for coroutines. Use
the :imp-target:`std::coroutines` imported target to

Options
*******

The ``COMPONENTS`` argument to this module supports the following values:

.. find-component:: Experimental
    :name: coro.Experimental

    Allows the module to find the "experimental" Coroutines TS
    version of the coroutines library. This is the library that should be
    used with the ``std::experimental`` namespace.

.. find-component:: Final
    :name: coro.Final

    Finds the final C++20 standard version of coroutines.

If no components are provided, behaves as if the
:find-component:`coro.Final` component was specified.

If both :find-component:`coro.Experimental` and :find-component:`coro.Final` are
provided, first looks for ``Final``, and falls back to ``Experimental`` in case
of failure. If ``Final`` is found, :imp-target:`std::coroutines` and all
:ref:`variables <coro.variables>` will refer to the ``Final`` version.


Imported Targets
****************

.. imp-target:: std::coroutines

    The ``std::coroutines`` imported target is defined when any requested
    version of the C++ coroutines library has been found, whether it is
    *Experimental* or *Final*.

    If no version of the coroutines library is available, this target will not
    be defined.

    .. note::
        This target has ``cxx_std_17`` as an ``INTERFACE``
        :ref:`compile language standard feature <req-lang-standards>`. Linking
        to this target will automatically enable C++17 if no later standard
        version is already required on the linking target.


.. _coro.variables:

Variables
*********

.. variable:: CXX_COROUTINES_HAVE_COROUTINES

    Set to ``TRUE`` when coroutines are supported in both the language and the
    library.

.. variable:: CXX_COROUTINES_HEADER

    Set to either ``coroutine`` or ``experimental/coroutine`` depending on
    whether :find-component:`coro.Final` or :find-component:`coro.Experimental` was
    found.

.. variable:: CXX_COROUTINES_NAMESPACE

    Set to either ``std`` or ``std::experimental``
    depending on whether :find-component:`coro.Final` or
    :find-component:`coro.Experimental` was found.


Examples
********

Using `find_package(Coroutines)` with no component arguments:

.. code-block:: cmake

    find_package(Coroutines REQUIRED)

    add_executable(my-program main.cpp)
    target_link_libraries(my-program PRIVATE std::coroutines)


#]=======================================================================]

if (TARGET std::coroutines)
  # This module has already been processed. Don't do it again.
  return()
endif ()

include(CheckCXXCompilerFlag)
include(CMakePushCheckState)
include(CheckIncludeFileCXX)
include(CheckCXXSourceCompiles)

cmake_push_check_state()

set(CMAKE_REQUIRED_QUIET ${Coroutines_FIND_QUIETLY})

check_cxx_compiler_flag(/await _CXX_COROUTINES_SUPPORTS_MS_FLAG)
check_cxx_compiler_flag(/await:heapelide _CXX_COROUTINES_SUPPORTS_MS_HEAPELIDE_FLAG)
check_cxx_compiler_flag(-fcoroutines-ts _CXX_COROUTINES_SUPPORTS_TS_FLAG)
check_cxx_compiler_flag(-fcoroutines _CXX_COROUTINES_SUPPORTS_CORO_FLAG)

if (_CXX_COROUTINES_SUPPORTS_MS_FLAG)
  set(CXX_COROUTINES_EXTRA_FLAGS "/await")
  if (_CXX_COROUTINES_SUPPORTS_MS_HEAPELIDE_FLAG AND CMAKE_SIZEOF_VOID_P GREATER_EQUAL 8)
    list(APPEND CXX_COROUTINES_EXTRA_FLAGS "/await:heapelide")
  endif ()
elseif (_CXX_COROUTINES_SUPPORTS_TS_FLAG)
  set(CXX_COROUTINES_EXTRA_FLAGS "-fcoroutines-ts")
elseif (_CXX_COROUTINES_SUPPORTS_CORO_FLAG)
  set(CXX_COROUTINES_EXTRA_FLAGS "-fcoroutines")
endif ()

# Normalize and check the component list we were given
set(REQUIRED_COMPONENTS ${Coroutines_FIND_COMPONENTS})
if (Coroutines_FIND_COMPONENTS STREQUAL "")
  set(REQUIRED_COMPONENTS Final)
endif ()

# Warn on any unrecognized components
set(EXTRA_COMPONENTS ${REQUIRED_COMPONENTS})
list(REMOVE_ITEM EXTRA_COMPONENTS Final Experimental)
foreach (component IN LISTS EXTRA_COMPONENTS)
  message(WARNING "Extraneous find_package component for Coroutines: ${component}")
endforeach ()

# Detect which of Experimental and Final we should look for
set(FOUND_EXPERIMENTAL TRUE)
set(FOUND_FINAL TRUE)
if (NOT "Final" IN_LIST REQUIRED_COMPONENTS)
  set(FOUND_FINAL FALSE)
endif ()
if (NOT "Experimental" IN_LIST REQUIRED_COMPONENTS)
  set(FOUND_EXPERIMENTAL FALSE)
endif ()

if (FOUND_FINAL)
  check_include_file_cxx("coroutine" CXX_COROUTINES_HAVE_HEADER)
  if (CXX_COROUTINES_HAVE_HEADER)
    check_cxx_source_compiles(
      "#include <coroutine> \n typedef std::suspend_never blub; \nint main() {} "
      _CXX_COROUTINES_FINAL_HEADER_COMPILES
    )
    set(CXX_COROUTINES_HAVE_HEADER "${_CXX_COROUTINES_FINAL_HEADER_COMPILES}")
  endif ()

  if (NOT CXX_COROUTINES_HAVE_HEADER)
    cmake_push_check_state()
    set(CMAKE_REQUIRED_FLAGS "${CXX_COROUTINES_EXTRA_FLAGS}")
    check_include_file_cxx("coroutine" CXX_COROUTINES_HAVE_HEADER_WITH_FLAG)
    if (CXX_COROUTINES_HAVE_HEADER_WITH_FLAG)
      check_cxx_source_compiles(
        "#include <coroutine> \n typedef std::suspend_never blub; \nint main() {} "
        _CXX_COROUTINES_FINAL_HEADER_COMPILES_WITH_FLAG
      )
      set(CXX_COROUTINES_HAVE_HEADER_WITH_FLAG
          "${_CXX_COROUTINES_FINAL_HEADER_COMPILES_WITH_FLAG}"
      )
    endif ()
    set(CXX_COROUTINES_HAVE_HEADER "${CXX_COROUTINES_HAVE_HEADER_WITH_FLAG}")
    cmake_pop_check_state()
  endif ()
  mark_as_advanced(CXX_COROUTINES_HAVE_HEADER)
  if (CXX_COROUTINES_HAVE_HEADER)
    # We found the non-experimental header. Don't bother looking for the experimental one.
    set(FOUND_EXPERIMENTAL FALSE)
  endif ()
else ()
  set(CXX_COROUTINES_HAVE_HEADER FALSE)
endif ()

if (FOUND_EXPERIMENTAL)
  check_include_file_cxx("experimental/coroutine" CXX_COROUTINES_HAVE_EXPERIMENTAL_HEADER)
  if (NOT CXX_COROUTINES_HAVE_EXPERIMENTAL_HEADER)
    cmake_push_check_state()
    set(CMAKE_REQUIRED_FLAGS "${CXX_COROUTINES_EXTRA_FLAGS}")
    check_include_file_cxx(
      "experimental/coroutine" CXX_COROUTINES_HAVE_EXPERIMENTAL_HEADER_WITH_FLAG
    )
    set(CXX_COROUTINES_HAVE_EXPERIMENTAL_HEADER
        "${CXX_COROUTINES_HAVE_EXPERIMENTAL_HEADER_WITH_FLAG}"
    )
    cmake_pop_check_state()
  endif ()
  mark_as_advanced(CXX_COROUTINES_HAVE_EXPERIMENTAL_HEADER)
else ()
  set(CXX_COROUTINES_HAVE_EXPERIMENTAL_HEADER FALSE)
endif ()

if (CXX_COROUTINES_HAVE_HEADER)
  set(_have_coro TRUE)
  set(_coro_header coroutine)
  set(_coro_namespace std)
elseif (CXX_COROUTINES_HAVE_EXPERIMENTAL_HEADER)
  set(_have_coro TRUE)
  set(_coro_header experimental/coroutine)
  set(_coro_namespace std::experimental)
else ()
  set(_have_coro FALSE)
endif ()

set(CXX_COROUTINES_HAVE_COROUTINES
    ${_have_coro}
    CACHE BOOL "TRUE if we have the C++ coroutines feature"
)
set(CXX_COROUTINES_HEADER
    ${_coro_header}
    CACHE STRING "The header that should be included to obtain the coroutines APIs"
)
set(CXX_COROUTINES_NAMESPACE
    ${_coro_namespace}
    CACHE STRING "The C++ namespace that contains the coroutines APIs"
)

set(_found FALSE)

if (CXX_COROUTINES_HAVE_COROUTINES)
  # We have some coroutines library available. Do link checks
  string(
    CONFIGURE
      [[
        #include <utility>
        #include <@CXX_COROUTINES_HEADER@>

        struct present {
          struct promise_type {
            int result;
            present get_return_object() { return present{*this}; }
            @CXX_COROUTINES_NAMESPACE@::suspend_never initial_suspend() { return {}; }
            @CXX_COROUTINES_NAMESPACE@::suspend_always final_suspend() noexcept { return {}; }
            void return_value(int i) { result = i; }
            void unhandled_exception() {}
          };
          friend struct promise_type;
          present(present&& that) : coro_(std::exchange(that.coro_, {})) {}
          ~present() { if(coro_) coro_.destroy(); }
          bool await_ready() const { return true; }
          void await_suspend(@CXX_COROUTINES_NAMESPACE@::coroutine_handle<>) const {}
          int await_resume() const { return coro_.promise().result; }
        private:
          present(promise_type& promise)
            : coro_(
                @CXX_COROUTINES_NAMESPACE@::coroutine_handle<promise_type>::from_promise(promise)
            ) {}
          @CXX_COROUTINES_NAMESPACE@::coroutine_handle<promise_type> coro_;
        };

        present f(int n) {
          if (n < 2)
            co_return 1;
          else
            co_return n * co_await f(n - 1);
        }

        int main() {
          return f(5).await_resume() != 120;
        }
    ]]
      code
    @ONLY
  )

  # Try to compile a simple coroutines program without any compiler flags
  check_cxx_source_compiles("${code}" CXX_COROUTINES_NO_AWAIT_NEEDED)

  set(COROUTINES_CAN_LINK ${CXX_COROUTINES_NO_AWAIT_NEEDED})

  if (NOT CXX_COROUTINES_NO_AWAIT_NEEDED)
    # Add the -fcoroutines-ts (or /await) flag
    set(CMAKE_REQUIRED_FLAGS "${CXX_COROUTINES_EXTRA_FLAGS}")
    check_cxx_source_compiles("${code}" CXX_COROUTINES_AWAIT_NEEDED)
    set(COROUTINES_CAN_LINK "${CXX_COROUTINES_AWAIT_NEEDED}")
  endif ()

  if (COROUTINES_CAN_LINK)
    add_library(std::coroutines INTERFACE IMPORTED)
    set(_found TRUE)

    if (CXX_COROUTINES_NO_AWAIT_NEEDED)
      # Nothing to add...
    elseif (CXX_COROUTINES_AWAIT_NEEDED)
      target_compile_options(std::coroutines INTERFACE ${CXX_COROUTINES_EXTRA_FLAGS})
    endif ()
  else ()
    set(CXX_COROUTINES_HAVE_COROUTINES FALSE)
  endif ()
endif ()

cmake_pop_check_state()

set(COROUTINES_FOUND
    ${_found}
    CACHE BOOL "TRUE if we can compile and link a program using std::coroutines" FORCE
)

if (Coroutines_FIND_REQUIRED AND NOT COROUTINES_FOUND)
  message(
    FATAL_ERROR "Cannot compile simple program using std::coroutines."
  )
endif ()
