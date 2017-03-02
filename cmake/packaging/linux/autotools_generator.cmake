# Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

macro(generate_sources_for_autotools)
    set(microcdr_SOURCES_TMP microCdr.c)
    set(microcdr_SOURCES_AUTOTOOLS "")
    foreach(microcdr_SOURCE ${microcdr_SOURCES_TMP})
        set(microcdr_SOURCES_AUTOTOOLS "${microcdr_SOURCES_AUTOTOOLS} ${microcdr_SOURCE}")
    endforeach()
endmacro()

macro(generate_public_headers_for_autotools)
    set(microcdr_PUBLIC_HEADERS_DIRECTORIES_TMP /home/carlosgomez/Documents/fastCDR/microCDR/include)
    set(microcdr_PUBLIC_HEADERS_AUTOTOOLS "")
    foreach(directory ${microcdr_PUBLIC_HEADERS_DIRECTORIES_TMP})
        file(GLOB_RECURSE microcdr_PUBLIC_HEADERS_TMP RELATIVE ${directory} ${directory}/*.h)
        foreach(microcdr_PUBLIC_HEADER ${microcdr_PUBLIC_HEADERS_TMP})
            set(microcdr_PUBLIC_HEADERS_AUTOTOOLS "${microcdr_PUBLIC_HEADERS_AUTOTOOLS} ${microcdr_PUBLIC_HEADER}")
        endforeach()
    endforeach()

    set(microcdr_PUBLIC_HEADERS_FILES_TMP microcdr/config.h)
    foreach(file ${microcdr_PUBLIC_HEADERS_FILES_TMP})
        set(microcdr_PUBLIC_HEADERS_AUTOTOOLS "${microcdr_PUBLIC_HEADERS_AUTOTOOLS} ${file}")
    endforeach()
endmacro()
