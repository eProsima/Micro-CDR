# Copyright 2017 Proyectos y Sistemas de Mantenimiento SL (eProsima).
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

###############################################################################
# CMake build rules for Micro CDR
###############################################################################
cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

set(IS_TOP_LEVEL TRUE)
if(PROJECT_SOURCE_DIR)
    set(IS_TOP_LEVEL FALSE)
endif()

# Set CMAKE_BUILD_TYPE to Release by default.
if(DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
        )
else()
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
        )
endif()

###############################################################################
# Product information                                                         #
###############################################################################
if(CMAKE_VERSION VERSION_LESS 3.0)
    project(microcdr C)
    set(PROJECT_VERION_MAYOR 2)
    set(PROJECT_VERION_MINOR 0)
    set(PROJECT_VERION_PATCH 0)
    set(PROJECT_VERSION ${PROJECT_VERION_MAYOR}.${PROJECT_VERION_MINOR}.${PROJECT_VERION_PATCH})
else()
    cmake_policy(SET CMP0048 NEW)
    project(microcdr VERSION "2.0.0" LANGUAGES C)
endif()

# Set product name
if(DEFINED PRODUCT_NAME)
    set(PRODUCT_NAME ${PRODUCT_NAME} CACHE STRING "Choose the product name in which this project is included")
else()
    set(PRODUCT_NAME microcdr CACHE STRING "Choose the product name in which this project is included")
endif()

###############################################################################
# Check MSVC architecture
###############################################################################
include(${PROJECT_SOURCE_DIR}/cmake/dev/check_configuration.cmake)
if(MSVC OR MSVC_IDE)
    check_msvc_arch()
endif()

###############################################################################
# Targets
###############################################################################

# Library
add_library(${PROJECT_NAME} src/c/microcdr.c)
target_include_directories(${PROJECT_NAME} 
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )

###############################################################################
# Compile options
###############################################################################

# Install path
set(BIN_INSTALL_DIR bin/ CACHE PATH "Installation directory for binaries")
set(INCLUDE_INSTALL_DIR include/ CACHE PATH "Installation directory for C headers")
set(LIB_INSTALL_DIR lib/ CACHE PATH "Installation directory for libraries")
set(DATA_INSTALL_DIR share/ CACHE PATH "Installation directory for data")
if(WIN32)
    set(LICENSE_INSTALL_DIR . CACHE PATH "Installation directory for licenses")
else()
    set(LICENSE_INSTALL_DIR ${DATA_INSTALL_DIR}/${PROJECT_NAME} CACHE PATH "Installation directory for licenses")
endif()

# Endianness configuration
include(${PROJECT_SOURCE_DIR}/cmake/dev/check_configuration.cmake)

option(CHECK_ENDIANNESS "Enable/disable endiannes checking" ON)
if(CHECK_ENDIANNESS)
    check_endianness()
else()
    message(STATUS "micro-CDR without check endianness")
endif()

# Config.h
configure_file(${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/config.h.in
    ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}/config.h
)

###############################################################################
# Compile settings
###############################################################################

# Definitions
get_target_property(TARGET_TYPE ${PROJECT_NAME} TYPE)
if((MSVC OR MSVC_IDE) AND (TARGET_TYPE STREQUAL "SHARED_LIBRARY"))
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC
            -DBUILDING_SHARED_LIB
        )
endif()

# Warnings
if(MSVC OR MSVC_IDE)
    target_compile_options(${PROJECT_NAME}
        PRIVATE
            /W4
            /wd4700
            /wd4996
            /wd4820
            /wd4255
            /wd4668
            -DSERIALIZATION_LOGS
            -DMESSAGE_LOGS
        )
else()
    target_compile_options(${PROJECT_NAME}
        PRIVATE
            -pedantic
            -Wconversion
            -fstrict-aliasing
            -Wall
            -Wextra
            -Wcast-align
            -Wshadow
            -DSERIALIZATION_LOGS
            -DMESSAGE_LOGS
        )
endif()

###############################################################################
# Testing
###############################################################################
option(EPROSIMA_BUILD_TESTS "Enable to compile tests." OFF)
if(EPROSIMA_BUILD_TESTS AND NOT EPROSIMA_INSTALLER)
    include(${PROJECT_SOURCE_DIR}/cmake/dev/gtest.cmake)
    check_gtest()
    if(GTEST_FOUND)
        enable_testing()
        include(CTest)
        add_subdirectory(test)
    endif()
endif()

###############################################################################
# Packaging
###############################################################################
include(${PROJECT_SOURCE_DIR}/cmake/dev/set_sources.cmake)

# Install public headers
set_public_headers_directory(${PROJECT_SOURCE_DIR}/include ${PROJECT_NAME}
    DESTINATION ${INCLUDE_INSTALL_DIR}
    COMPONENT headers
    )

# Install config.h header
set_public_header(${PROJECT_BINARY_DIR}/include ${PROJECT_NAME} config.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/${PROJECT_NAME}
    COMPONENT headers
    INSTALL
    )

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    RUNTIME DESTINATION ${BIN_INSTALL_DIR}
    LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
    COMPONENT libraries
    )

install(EXPORT ${PROJECT_NAME}Targets
    DESTINATION ${LIB_INSTALL_DIR}/${PROJECT_NAME}/cmake
    COMPONENT cmake
    )
