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

#include <ucdr/common.h>

#include <string.h>

#if __BIG_ENDIAN__
    const ucdrEndianness UCDR_MACHINE_ENDIANNESS = UCDR_BIG_ENDIANNESS;
#else
    const ucdrEndianness UCDR_MACHINE_ENDIANNESS = UCDR_LITTLE_ENDIANNESS;
#endif

// -------------------------------------------------------------------
//                   INTERNAL UTIL IMPLEMENTATIONS
// -------------------------------------------------------------------
bool ucdr_check_buffer(ucdrBuffer* ub, const uint32_t bytes)
{
    if(!ub->error)
    {
        bool fit = ub->iterator + bytes <= ub->final;
        if(!fit)
        {
            ub->error = true;
        }
    }

    return !ub->error;
}

// -------------------------------------------------------------------
//                       PUBLIC IMPLEMENTATION
// -------------------------------------------------------------------
void ucdr_init_buffer(ucdrBuffer* ub, uint8_t* data, const uint32_t size)
{
    ucdr_init_buffer_offset(ub, data, size, 0U);
}

void ucdr_init_buffer_offset(ucdrBuffer* ub, uint8_t* data, const uint32_t size, uint32_t offset)
{
    ucdr_init_buffer_offset_endian(ub, data, size, offset, UCDR_MACHINE_ENDIANNESS);
}

void ucdr_init_buffer_offset_endian(ucdrBuffer* ub, uint8_t* data, const uint32_t size, uint32_t offset, ucdrEndianness endianness)
{
    ub->init = data;
    ub->final = ub->init + size;
    ub->iterator = ub->init + offset;
    ub->last_data_size = 0U;
    ub->endianness = endianness;
    ub->error = false;
}


void ucdr_copy_buffer(ucdrBuffer* ub_dest, const ucdrBuffer* ub_source)
{
    memcpy(ub_dest, ub_source, sizeof(ucdrBuffer));
}

void ucdr_reset_buffer(ucdrBuffer* ub)
{
    ucdr_reset_buffer_offset(ub, 0U);
}

void ucdr_reset_buffer_offset(ucdrBuffer* ub, const uint32_t offset)
{
    ub->iterator = ub->init + offset;
    ub->last_data_size = 0U;
    ub->error = false;
}

void ucdr_align_to(ucdrBuffer* ub, const uint32_t size)
{
    uint32_t offset = ucdr_buffer_alignment(ub, size);
    ub->iterator += offset;
    if(ub->iterator > ub->final)
    {
        ub->iterator = ub->final;
    }

    ub->last_data_size = size;
}

uint32_t ucdr_alignment(uint32_t current_alignment, const uint32_t data_size)
{
    return ((data_size - (current_alignment % data_size)) & (data_size - 1));
}

uint32_t ucdr_buffer_alignment(const ucdrBuffer* ub, const uint32_t data_size)
{
    if(data_size > ub->last_data_size)
    {
        return (data_size - ((uint32_t)(ub->iterator - ub->init) % data_size)) & (data_size - 1);
    }

    return 0;
}

size_t ucdr_buffer_size(const ucdrBuffer* ub)
{
    return (size_t)(ub->final - ub->init);
}

size_t ucdr_buffer_length(const ucdrBuffer* ub)
{
    return (size_t)(ub->iterator - ub->init);
}

size_t ucdr_buffer_remaining(const ucdrBuffer* ub)
{
    return (size_t)(ub->final - ub->iterator);
}

ucdrEndianness ucdr_buffer_endianness(const ucdrBuffer* ub)
{
    return ub->endianness;
}

bool ucdr_buffer_has_error(const ucdrBuffer* ub)
{
    return ub->error;
}
