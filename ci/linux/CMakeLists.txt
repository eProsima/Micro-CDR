cmake_minimum_required(VERSION 3.5.0 FATAL_ERROR)

project(microcdr_ci LANGUAGES C CXX)

include(ExternalProject)

set(_c_flags "-fwrapv -fprofile-arcs -ftest-coverage")
set(_cxx_flags "-fwrapv -fprofile-arcs -ftest-coverage")
set(_exe_linker_flags "-fprofile-arcs -ftest-coverage")
set(_shared_linker_flags "-fprofile-arcs -ftest-coverage")

ExternalProject_Add(microcdr
    SOURCE_DIR
        ${CMAKE_CURRENT_SOURCE_DIR}/../../
    BINARY_DIR
        ${PROJECT_BINARY_DIR}/microcdr-build
    INSTALL_DIR
        ${PROJECT_BINARY_DIR}/temp_install
    TEST_AFTER_INSTALL
        TRUE
    TEST_COMMAND
        COMMAND ${CMAKE_CTEST_COMMAND} -VV -T Test
        COMMAND ${CMAKE_CTEST_COMMAND} -VV -T MemCheck -E "test-case*"
        COMMAND ${CMAKE_CTEST_COMMAND} -VV -T Coverage -E "test-case*"
    CMAKE_CACHE_ARGS
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_C_FLAGS:STRING=${_c_flags}
        -DCMAKE_CXX_FLAGS:STRING=${_cxx_flags}
        -DCMAKE_EXE_LINKER_FLAGS:STRING=${_exe_linker_flags}
        -DCMAKE_SHARED_LINKER_FLAGS:STRING=${_shared_linker_flags}
        -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
        -DUCDR_BUILD_CI_TESTS:BOOL=ON
        -DGTEST_INDIVIDUAL:BOOL=ON
    )