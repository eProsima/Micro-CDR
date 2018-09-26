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

#include <string.h>

#if __BIG_ENDIAN__
    const mrEndianness MC_MACHINE_ENDIANNESS = MC_BIG_ENDIANNESS;
#else
    const mrEndianness MC_MACHINE_ENDIANNESS = MC_LITTLE_ENDIANNESS;
#endif

// -------------------------------------------------------------------
//                   INTERNAL UTIL IMPLEMENTATIONS
// -------------------------------------------------------------------
bool check_buffer(mcBuffer* mb, const uint32_t bytes)
{
    if(!mb->error)
    {
        bool fit = mb->iterator + bytes <= mb->final;
        if(!fit)
        {
            mb->error = true;
        }
    }

    return !mb->error;
}

// -------------------------------------------------------------------
//                       PUBLIC IMPLEMENTATION
// -------------------------------------------------------------------
void mc_init_micro_buffer(mcBuffer* mb, uint8_t* data, const uint32_t size)
{
    mc_init_micro_buffer_offset(mb, data, size, 0U);
}

void mc_init_micro_buffer_offset(mcBuffer* mb, uint8_t* data, const uint32_t size, uint32_t offset)
{
    mc_init_micro_buffer_offset_endian(mb, data, size, offset, MC_MACHINE_ENDIANNESS);
}

void mc_init_micro_buffer_offset_endian(mcBuffer* mb, uint8_t* data, const uint32_t size, uint32_t offset, mrEndianness endianness)
{
    mb->init = data;
    mb->final = mb->init + size;
    mb->iterator = mb->init + offset;
    mb->last_data_size = 0U;
    mb->endianness = endianness;
    mb->error = false;
}


void mc_copy_micro_buffer(mcBuffer* mb_dest, const mcBuffer* mb_source)
{
    memcpy(mb_dest, mb_source, sizeof(mcBuffer));
}

void mc_reset_micro_buffer(mcBuffer* mb)
{
    mc_reset_micro_buffer_offset(mb, 0U);
}

void mc_reset_micro_buffer_offset(mcBuffer* mb, const uint32_t offset)
{
    mb->iterator = mb->init + offset;
    mb->last_data_size = 0U;
    mb->error = false;
}

void mc_align_to(mcBuffer* mb, const uint32_t size)
{
    uint32_t offset = mc_micro_buffer_alignment(mb, size);
    mb->iterator += offset;
    if(mb->iterator > mb->final)
    {
        mb->iterator = mb->final;
    }

    mb->last_data_size = size;
}

uint32_t mc_alignment(uint32_t current_alignment, const uint32_t data_size)
{
    return ((data_size - (current_alignment % data_size)) & (data_size - 1));
}

uint32_t mc_micro_buffer_alignment(const mcBuffer* mb, const uint32_t data_size)
{
    if(data_size > mb->last_data_size)
    {
        return (data_size - ((uint32_t)(mb->iterator - mb->init) % data_size)) & (data_size - 1);
    }

    return 0;
}

size_t mc_micro_buffer_size(const mcBuffer* mb)
{
    return (size_t)(mb->final - mb->init);
}

size_t mc_micro_buffer_length(const mcBuffer* mb)
{
    return (size_t)(mb->iterator - mb->init);
}

size_t mc_micro_buffer_remaining(const mcBuffer* mb)
{
    return (size_t)(mb->final - mb->iterator);
}

mrEndianness mc_micro_buffer_endianness(const mcBuffer* mb)
{
    return mb->endianness;
}

bool mc_micro_buffer_has_error(const mcBuffer* mb)
{
    return mb->error;
}
