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
    set(nanocdr_SOURCES_TMP nanoCdr.c)
    set(nanocdr_SOURCES_AUTOTOOLS "")
    foreach(nanocdr_SOURCE ${nanocdr_SOURCES_TMP})
        set(nanocdr_SOURCES_AUTOTOOLS "${nanocdr_SOURCES_AUTOTOOLS} ${nanocdr_SOURCE}")
    endforeach()
endmacro()

macro(generate_public_headers_for_autotools)
    set(nanocdr_PUBLIC_HEADERS_DIRECTORIES_TMP /home/carlosgomez/Documents/fastCDR/nanoCDR/include)
    set(nanocdr_PUBLIC_HEADERS_AUTOTOOLS "")
    foreach(directory ${nanocdr_PUBLIC_HEADERS_DIRECTORIES_TMP})
        file(GLOB_RECURSE nanocdr_PUBLIC_HEADERS_TMP RELATIVE ${directory} ${directory}/*.h)
        foreach(nanocdr_PUBLIC_HEADER ${nanocdr_PUBLIC_HEADERS_TMP})
            set(nanocdr_PUBLIC_HEADERS_AUTOTOOLS "${nanocdr_PUBLIC_HEADERS_AUTOTOOLS} ${nanocdr_PUBLIC_HEADER}")
        endforeach()
    endforeach()

    set(nanocdr_PUBLIC_HEADERS_FILES_TMP nanocdr/config.h)
    foreach(file ${nanocdr_PUBLIC_HEADERS_FILES_TMP})
        set(nanocdr_PUBLIC_HEADERS_AUTOTOOLS "${nanocdr_PUBLIC_HEADERS_AUTOTOOLS} ${file}")
    endforeach()
endmacro()
