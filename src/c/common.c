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

void init_micro_buffer(MicroBuffer* buffer, uint8_t* data, const uint32_t size)
{
    init_micro_buffer_offset(buffer, data, size, 0U);
}

void init_micro_buffer_offset(MicroBuffer* buffer, uint8_t* data, const uint32_t size, uint32_t offset)
{
    buffer->init = data;
    buffer->final = buffer->init + size;
    buffer->iterator = buffer->init + offset;
    buffer->last_data_size = 0U;
    buffer->endianness = MACHINE_ENDIANNESS;
    buffer->error = false;
}

void reset_micro_buffer(MicroBuffer* buffer)
{
    reset_micro_buffer_offset(buffer, 0U);
}

void reset_micro_buffer_offset(MicroBuffer* buffer, const uint32_t offset)
{
    buffer->iterator = buffer->init + offset;
    buffer->last_data_size = 0U;
    buffer->error = false;
}

void align_to(MicroBuffer* buffer, const uint32_t size)
{
    uint32_t offset = get_alignment_offset(buffer, size);
    buffer->iterator += offset;
    if(buffer->iterator > buffer->final)
    {
        buffer->iterator = buffer->final;
    }

    buffer->last_data_size = size;
}

// Deprecated: used get_alignment_offset instead (common.h)
uint32_t get_alignment(uint32_t current_alignment, const uint32_t data_size)
{
    return ((data_size - (current_alignment % data_size)) & (data_size - 1));
}

uint32_t get_alignment_offset(MicroBuffer* mb, const uint32_t data_size)
{
    if(data_size > mb->last_data_size)
    {
        return (data_size - ((uint32_t)(mb->iterator - mb->init) % data_size)) & (data_size - 1);
    }

    return 0;
}

size_t micro_buffer_size(const MicroBuffer* buffer)
{
    return (size_t)(buffer->final - buffer->init);
}

size_t micro_buffer_length(const MicroBuffer* buffer)
{
    return (size_t)(buffer->iterator - buffer->init);
}

size_t micro_buffer_remaining(const MicroBuffer* buffer)
{
    return (size_t)(buffer->final - buffer->iterator);
}

MicroState get_micro_state(MicroBuffer* buffer)
{
    MicroState state;
    state.position = buffer->iterator;
    state.last_data_size = buffer->last_data_size;
    state.error = buffer->error;
    return state;
}

void restore_micro_state(MicroBuffer* buffer, const MicroState state)
{
    buffer->iterator = state.position;
    buffer->last_data_size = state.last_data_size;
    buffer->error = state.error;
}
