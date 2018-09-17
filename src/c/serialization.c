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

#include <microcdr/serialization.h>
#include <string.h>

// -------------------------------------------------------------------
//                      INTERNAL IMPLEMENTATIONS
// -------------------------------------------------------------------
inline static bool check_buffer(MicroBuffer* mb, const uint32_t bytes)
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
//                INTERNAL SERIALIZATION IMPLEMENTATION
// -------------------------------------------------------------------

bool serialize_byte_1(MicroBuffer* mb, const uint8_t* byte)
{
    uint32_t data_size = sizeof(uint8_t);
    if(check_buffer(mb, data_size))
    {
        *mb->iterator = *byte;

        mb->iterator += data_size;
        mb->last_data_size = data_size;
        return true;
    }
    return false;
}

bool serialize_byte_2(MicroBuffer* mb, const Endianness endianness, const uint16_t* bytes)
{
    uint32_t data_size = sizeof(uint16_t);
    uint32_t alignment = get_alignment_offset(mb, data_size);

    if(check_buffer(mb, alignment + data_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(mb->iterator, bytes, data_size);
        }
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *mb->iterator = *(bytes_pointer + 1);
            *(mb->iterator + 1) = *bytes_pointer;
        }

        mb->iterator += data_size;
        mb->last_data_size = data_size;
        return true;
    }
    return false;
}

bool serialize_byte_4(MicroBuffer* mb, const Endianness endianness, const uint32_t* bytes)
{
    uint32_t data_size = sizeof(uint32_t);
    uint32_t alignment = get_alignment_offset(mb, data_size);

    if(check_buffer(mb, alignment + data_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(mb->iterator, bytes, data_size);
        }
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *mb->iterator = *(bytes_pointer + 3);
            *(mb->iterator + 1) = *(bytes_pointer + 2);
            *(mb->iterator + 2) = *(bytes_pointer + 1);
            *(mb->iterator + 3) = *bytes_pointer;
        }

        mb->iterator += data_size;
        mb->last_data_size = data_size;
        return true;
    }
    return false;
}

bool serialize_byte_8(MicroBuffer* mb, const Endianness endianness, const uint64_t* bytes)
{
    uint32_t data_size = sizeof(uint64_t);
    uint32_t alignment = get_alignment_offset(mb, data_size);

    if(check_buffer(mb, alignment + data_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(mb->iterator, bytes, data_size);
        }
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *mb->iterator = *(bytes_pointer + 7);
            *(mb->iterator + 1) = *(bytes_pointer + 6);
            *(mb->iterator + 2) = *(bytes_pointer + 5);
            *(mb->iterator + 3) = *(bytes_pointer + 4);
            *(mb->iterator + 4) = *(bytes_pointer + 3);
            *(mb->iterator + 5) = *(bytes_pointer + 2);
            *(mb->iterator + 6) = *(bytes_pointer + 1);
            *(mb->iterator + 7) = *bytes_pointer;
        }

        mb->iterator += data_size;
        mb->last_data_size = data_size;
        return true;
    }
    return false;
}

bool deserialize_byte_1(MicroBuffer* mb, uint8_t* byte)
{
    uint32_t data_size = sizeof(uint8_t);
    if(check_buffer(mb, data_size))
    {
        *byte = *mb->iterator;

        mb->iterator += data_size;
        mb->last_data_size = data_size;
        return true;
    }
    return false;
}

bool deserialize_byte_2(MicroBuffer* mb, const Endianness endianness, uint16_t* bytes)
{
    uint32_t data_size = sizeof(uint16_t);
    uint32_t alignment = get_alignment_offset(mb, data_size);

    if(check_buffer(mb, alignment + data_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(bytes, mb->iterator, data_size);
        }
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *bytes_pointer = *(mb->iterator + 1);
            *(bytes_pointer + 1) = *mb->iterator ;
        }

        mb->iterator += data_size;
        mb->last_data_size = data_size;
        return true;
    }
    return false;
}

bool deserialize_byte_4(MicroBuffer* mb, const Endianness endianness, uint32_t* bytes)
{
    uint32_t data_size = sizeof(uint32_t);
    uint32_t alignment = get_alignment_offset(mb, data_size);

    if(check_buffer(mb, alignment + data_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(bytes, mb->iterator, data_size);
        }
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *bytes_pointer = *(mb->iterator + 3);
            *(bytes_pointer + 1) = *(mb->iterator + 2);
            *(bytes_pointer + 2) = *(mb->iterator + 1);
            *(bytes_pointer + 3) = *mb->iterator;
        }

        mb->iterator += data_size;
        mb->last_data_size = data_size;
        return true;
    }
    return false;
}

bool deserialize_byte_8(MicroBuffer* mb, const Endianness endianness, uint64_t* bytes)
{
    uint32_t data_size = sizeof(uint64_t);
    uint32_t alignment = get_alignment_offset(mb, data_size);

    if(check_buffer(mb, alignment + data_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(bytes, mb->iterator, data_size);
        }
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *bytes_pointer = *(mb->iterator + 7);
            *(bytes_pointer + 1) = *(mb->iterator + 6);
            *(bytes_pointer + 2) = *(mb->iterator + 5);
            *(bytes_pointer + 3) = *(mb->iterator + 4);
            *(bytes_pointer + 4) = *(mb->iterator + 3);
            *(bytes_pointer + 5) = *(mb->iterator + 2);
            *(bytes_pointer + 6) = *(mb->iterator + 1);
            *(bytes_pointer + 7) = *mb->iterator;
        }

        mb->iterator += data_size;
        mb->last_data_size = data_size;
        return true;
    }
    return false;
}

bool serialize_array_byte_1(MicroBuffer* mb, const uint8_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint8_t);
    if(check_buffer(mb, size))
    {
        memcpy(mb->iterator, array, size);

        mb->iterator += size;
        mb->last_data_size = data_size;
        return true;
    }
    return false;
}

bool serialize_array_byte_2(MicroBuffer* mb, const Endianness endianness, const uint16_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint16_t);
    uint32_t array_size = size * data_size;
    uint32_t alignment = get_alignment_offset(mb, sizeof(uint16_t));

    if(check_buffer(mb, alignment + array_size))
    {
        mb->iterator += alignment;
        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(mb->iterator, array, array_size);

            mb->iterator += array_size;
            mb->last_data_size = data_size;
        }
        else
        {
            for(uint32_t i = 0; i < size; i++)
            {
                serialize_byte_2(mb, endianness, array + i);
            }
        }
        return true;
    }
    return false;
}

bool serialize_array_byte_4(MicroBuffer* mb, const Endianness endianness, const uint32_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint32_t);
    uint32_t array_size = size * data_size;
    uint32_t alignment = get_alignment_offset(mb, sizeof(uint32_t));

    if(check_buffer(mb, alignment + array_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(mb->iterator, array, array_size);
            mb->iterator += array_size;
            mb->last_data_size = data_size;
        }
        else
        {
            for(uint32_t i = 0; i < size; i++)
            {
                serialize_byte_4(mb, endianness, array + i);
            }
        }
        return true;
    }
    return false;
}

bool serialize_array_byte_8(MicroBuffer* mb, const Endianness endianness, const uint64_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint64_t);
    uint32_t array_size = size * data_size;
    uint32_t alignment = get_alignment_offset(mb, sizeof(uint64_t));

    if(check_buffer(mb, alignment + array_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(mb->iterator, array, array_size);
            mb->iterator += array_size;
            mb->last_data_size = data_size;
        }
        else
        {
            for(uint32_t i = 0; i < size; i++)
            {
                serialize_byte_8(mb, endianness, array + i);
            }
        }
        return true;
    }
    return false;
}

bool deserialize_array_byte_1(MicroBuffer* mb, uint8_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint8_t);
    if(check_buffer(mb, size))
    {
        memcpy(array, mb->iterator, size);

        mb->iterator += size;
        mb->last_data_size = data_size;
        return true;
    }
    return false;
}

bool deserialize_array_byte_2(MicroBuffer* mb, const Endianness endianness, uint16_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint16_t);
    uint32_t array_size = size * data_size;
    uint32_t alignment = get_alignment_offset(mb, sizeof(uint16_t));

    if(check_buffer(mb, alignment + array_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(array, mb->iterator, array_size);
            mb->iterator += array_size;
            mb->last_data_size = data_size;
        }
        else
        {
            for(uint32_t i = 0; i < size; i++)
            {
                deserialize_byte_2(mb, endianness, array + i);
            }
        }
        return true;
    }
    return false;
}

bool deserialize_array_byte_4(MicroBuffer* mb, const Endianness endianness, uint32_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint32_t);
    uint32_t array_size = size * data_size;
    uint32_t alignment = get_alignment_offset(mb, sizeof(uint32_t));

    if(check_buffer(mb, alignment + array_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(array, mb->iterator, array_size);
            mb->iterator += array_size;
            mb->last_data_size = data_size;
        }
        else
        {
            for(uint32_t i = 0; i < size; i++)
            {
                deserialize_byte_4(mb, endianness, array + i);
            }
        }
        return true;
    }
    return false;
}

bool deserialize_array_byte_8(MicroBuffer* mb, const Endianness endianness, uint64_t* array, const uint32_t size)
{
    uint32_t data_size = sizeof(uint64_t);
    uint32_t array_size = size * data_size;
    uint32_t alignment = get_alignment_offset(mb, sizeof(uint64_t));

    if(check_buffer(mb, alignment + array_size))
    {
        mb->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
        {
            memcpy(array, mb->iterator, array_size);
            mb->iterator += array_size;
            mb->last_data_size = data_size;
        }
        else
        {
            for(uint32_t i = 0; i < size; i++)
            {
                deserialize_byte_8(mb, endianness, array + i);
            }
        }
        return true;
    }
    return false;
}
