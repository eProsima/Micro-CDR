// Copyright 2017 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <microcdr/common.h>

#if __BIG_ENDIAN__
    const Endianness MACHINE_ENDIANNESS = BIG_ENDIANNESS;
#else
    const Endianness MACHINE_ENDIANNESS = LITTLE_ENDIANNESS;
#endif

// -------------------------------------------------------------------
//                      INTERNAL IMPLEMENTATIONS
// -------------------------------------------------------------------

uint32_t get_alignment_offset(MicroBuffer* buffer, const uint32_t data_size)
{
    if(data_size > buffer->last_data_size)
    {
        return (data_size - ((uint32_t)(buffer->iterator - buffer->init) % data_size)) & (data_size - 1);
    }

    return 0;
}

bool check_size(MicroBuffer* buffer, const uint32_t bytes)
{
    return buffer->iterator + bytes <= buffer->final;
}

