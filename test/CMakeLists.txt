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

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

if(CMAKE_VERSION VERSION_LESS 3.0)
    project(microcdr_tests C CXX)
else()
    cmake_policy(SET CMP0048 NEW)
    project(microcdr_tests LANGUAGES C CXX)
endif()

include(${PROJECT_SOURCE_DIR}/cmake/dev/gtest.cmake)
check_gtest()
if(GTEST_FOUND)
    include(CTest)
    set(SRCS
        SerializationDeserialization.cpp
        Alignment.cpp
        BufferError.cpp)
    add_executable(${PROJECT_NAME} ${SRCS})
    add_gtest(${PROJECT_NAME} ${SRCS})
    target_include_directories(${PROJECT_NAME} PRIVATE ${GTEST_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} microcdr ${GTEST_BOTH_LIBRARIES})

    if(WIN32)
        string(REPLACE ";" "\\;" WIN_PATH "$ENV{PATH}")
        set_property(TEST ${PROJECT_NAME} APPEND PROPERTY ENVIRONMENT
            "PATH=$<SHELL_PATH:$<TARGET_FILE_DIR:microcdr>>\\;${WIN_PATH}"
    )
    endif()
endif()

