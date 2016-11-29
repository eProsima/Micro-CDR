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

# Copy configure.ac
file(INSTALL /home/carlosgomez/Documents/fastCDR/nanoCDR/configure.ac
    DESTINATION /home/carlosgomez/Documents/fastCDR/nanoCDR/autotools
    )

# Copy m4 diretory
file(INSTALL /home/carlosgomez/Documents/fastCDR/nanoCDR/m4
    DESTINATION /home/carlosgomez/Documents/fastCDR/nanoCDR/autotools
    )

# Create include/nanocdr
file(MAKE_DIRECTORY /home/carlosgomez/Documents/fastCDR/nanoCDR/autotools/include/nanocdr)

# Run autoreconf
execute_process(COMMAND autoreconf -fi /home/carlosgomez/Documents/fastCDR/nanoCDR/autotools
    RESULT_VARIABLE EXECUTE_RESULT)

if(NOT EXECUTE_RESULT EQUAL 0)
    message(FATAL_ERROR "Failed the execution of autoreconf")
endif()

# Copy include/nanocdr/config.h.in
file(INSTALL /home/carlosgomez/Documents/fastCDR/nanoCDR/include/nanocdr/config.h.in
    DESTINATION /home/carlosgomez/Documents/fastCDR/nanoCDR/autotools/include/nanocdr
    )

# Copy licenses
file(INSTALL /home/carlosgomez/Documents/fastCDR/nanoCDR/LICENSE
    DESTINATION /home/carlosgomez/Documents/fastCDR/nanoCDR/autotools
    )
