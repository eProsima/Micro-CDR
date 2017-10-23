#include "microcdr/microcdr.h"

#include <string.h>
#include <stdlib.h>

#define MACHINE_ENDIANNESS !__BIG_ENDIAN__

// -------------------------------------------------------------------
//                  INTERNAL SERIALIZATION FUNCTIONS
// -------------------------------------------------------------------

// NOTE: remove inline from byte's functions will reduce significally the size of the compiler data.
//          put inline from byte's functions will increase the performance.

inline static void serialize_byte_1(MicroBuffer* buffer, const uint8_t* byte);
inline static void serialize_byte_2(MicroBuffer* buffer, Endianness endianness, const uint16_t* bytes);
inline static void serialize_byte_4(MicroBuffer* buffer, Endianness endianness, const uint32_t* bytes);
inline static void serialize_byte_8(MicroBuffer* buffer, Endianness endianness, const uint64_t* bytes);

inline static void deserialize_byte_1(MicroBuffer* buffer, uint8_t* byte);
inline static void deserialize_byte_2(MicroBuffer* buffer, Endianness endianness, uint16_t* bytes);
inline static void deserialize_byte_4(MicroBuffer* buffer, Endianness endianness, uint32_t* bytes);
inline static void deserialize_byte_8(MicroBuffer* buffer, Endianness endianness, uint64_t* bytes);

inline static void serialize_array_byte_1(MicroBuffer* buffer, const uint8_t* array, uint32_t size);
inline static void serialize_array_byte_2(MicroBuffer* buffer, Endianness endianness, const uint16_t* array, uint32_t size);
inline static void serialize_array_byte_4(MicroBuffer* buffer, Endianness endianness, const uint32_t* array, uint32_t size);
inline static void serialize_array_byte_8(MicroBuffer* buffer, Endianness endianness, const uint64_t* array, uint32_t size);

inline static void deserialize_array_byte_1(MicroBuffer* buffer, uint8_t* array, uint32_t size);
inline static void deserialize_array_byte_2(MicroBuffer* buffer, Endianness endianness, uint16_t* array, uint32_t size);
inline static void deserialize_array_byte_4(MicroBuffer* buffer, Endianness endianness, uint32_t* array, uint32_t size);
inline static void deserialize_array_byte_8(MicroBuffer* buffer, Endianness endianness, uint64_t* array, uint32_t size);

// -------------------------------------------------------------------
//                      INTERNAL UTIL FUNCTIONS
// -------------------------------------------------------------------
inline static bool resize(MicroBuffer* buffer, uint32_t byte);
inline static uint32_t get_alignment_offset(MicroBuffer* buffer, uint32_t data_size);
inline static bool check_size(MicroBuffer* buffer, uint32_t bytes);

// -------------------------------------------------------------------
//                 BUFFER MANAGEMENT IMPLEMENTATION
// -------------------------------------------------------------------

void init_external_buffer(MicroBuffer* buffer, uint8_t* data, uint32_t size)
{
    buffer->init = data;
    buffer->final = buffer->init + size;
    buffer->iterator = buffer->init;
    buffer->last_data_size = 0;
    buffer->endianness = BIG_ENDIANNESS;

    buffer->internal_buffer_management = false;
}

void init_internal_buffer(MicroBuffer* buffer, uint32_t initial_size)
{
    buffer->init = malloc(initial_size);
    buffer->final = buffer->init + initial_size;
    buffer->iterator = buffer->init;
    buffer->last_data_size = 0;
    buffer->endianness = BIG_ENDIANNESS;

    buffer->internal_buffer_management = true;
}

void free_internal_buffer(MicroBuffer* buffer)
{
    free(buffer->init);
}

void reset_buffer(MicroBuffer* buffer)
{
    buffer->iterator = buffer->init;
    buffer->last_data_size = 0;
}

MicroState get_micro_state(MicroBuffer* buffer)
{
    return (MicroState)
    {
        .position = buffer->iterator,
        .last_data_size = buffer->last_data_size
    };
}

void restore_micro_state(MicroBuffer* buffer, MicroState state)
{
    buffer->iterator = state.position;
    buffer->last_data_size = state.last_data_size;
}

uint32_t align_to(MicroBuffer* buffer, uint32_t size)
{
    uint32_t offset = get_alignment_offset(buffer, size);
    buffer->iterator += offset;
    buffer->last_data_size = size;
    return offset;
}

uint32_t get_alignment_offset(MicroBuffer* buffer, uint32_t data_size)
{
    if(data_size > buffer->last_data_size)
        return (data_size - ((buffer->iterator - buffer->init) % data_size)) & (data_size - 1);

    return 0;
}

bool check_size(MicroBuffer* buffer, uint32_t bytes)
{
    return buffer->iterator + bytes < buffer->final;
}

bool resize(MicroBuffer* buffer, uint32_t request)
{
    if(buffer->internal_buffer_management)
    {
        uint32_t current_position = buffer->iterator - buffer->init;
        uint32_t buffer_size = (current_position + request) * 2;

        buffer->init = realloc(buffer->init, buffer_size);
        buffer->final = buffer->init + buffer_size;
        buffer->iterator = buffer->init + current_position;

        return true;
    }

    return false;
}

// -------------------------------------------------------------------
//                  SERIALIZATION IMPLEMENTATION
// -------------------------------------------------------------------
void serialize_byte_1(MicroBuffer* buffer, const uint8_t* byte)
{
    uint32_t data_size = sizeof(uint8_t);
    if(check_size(buffer, data_size) || resize(buffer, data_size))
    {
        *buffer->iterator = *byte;

        buffer->iterator += data_size;
        buffer->last_data_size = data_size;
    }
}

void serialize_byte_2(MicroBuffer* buffer, Endianness endianness, const uint16_t* bytes)
{
    uint32_t data_size = sizeof(uint16_t);
    uint32_t alignment = get_alignment_offset(buffer, data_size);

    if(check_size(buffer, alignment + data_size) || resize(buffer, alignment + data_size))
    {
        buffer->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
            *((uint16_t*)buffer->iterator) = *bytes;
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *buffer->iterator = *(bytes_pointer + 1);
            *(buffer->iterator + 1) = *bytes_pointer;
        }

        buffer->iterator += data_size;
        buffer->last_data_size = data_size;
    }
}

void serialize_byte_4(MicroBuffer* buffer, Endianness endianness, const uint32_t* bytes)
{
    uint32_t data_size = sizeof(uint32_t);
    uint32_t alignment = get_alignment_offset(buffer, data_size);

    if(check_size(buffer, alignment + data_size) || resize(buffer, alignment + data_size))
    {
        buffer->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
            *((uint32_t*)buffer->iterator) = *bytes;
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *buffer->iterator = *(bytes_pointer + 3);
            *(buffer->iterator + 1) = *(bytes_pointer + 2);
            *(buffer->iterator + 2) = *(bytes_pointer + 1);
            *(buffer->iterator + 3) = *bytes_pointer;
        }

        buffer->iterator += data_size;
        buffer->last_data_size = data_size;
    }
}

void serialize_byte_8(MicroBuffer* buffer, Endianness endianness, const uint64_t* bytes)
{
    uint32_t data_size = sizeof(uint64_t);
    uint32_t alignment = get_alignment_offset(buffer, data_size);

    if(check_size(buffer, alignment + data_size) || resize(buffer, alignment + data_size))
    {
        buffer->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
            *((uint64_t*)buffer->iterator) = *bytes;
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *buffer->iterator = *(bytes_pointer + 7);
            *(buffer->iterator + 1) = *(bytes_pointer + 6);
            *(buffer->iterator + 2) = *(bytes_pointer + 5);
            *(buffer->iterator + 3) = *(bytes_pointer + 4);
            *(buffer->iterator + 4) = *(bytes_pointer + 3);
            *(buffer->iterator + 5) = *(bytes_pointer + 2);
            *(buffer->iterator + 6) = *(bytes_pointer + 1);
            *(buffer->iterator + 7) = *bytes_pointer;
        }

        buffer->iterator += data_size;
        buffer->last_data_size = data_size;
    }
}

void deserialize_byte_1(MicroBuffer* buffer, uint8_t* byte)
{
    uint32_t data_size = sizeof(uint8_t);
    if(check_size(buffer, data_size) || resize(buffer, data_size))
    {
        *byte = *buffer->iterator;

        buffer->iterator += data_size;
        buffer->last_data_size = data_size;
    }
}

void deserialize_byte_2(MicroBuffer* buffer, Endianness endianness, uint16_t* bytes)
{
    uint32_t data_size = sizeof(uint16_t);
    uint32_t alignment = get_alignment_offset(buffer, data_size);

    if(check_size(buffer, alignment + data_size) || resize(buffer, alignment + data_size))
    {
        buffer->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
            *bytes = *(uint16_t*)buffer->iterator;
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *bytes_pointer = *(buffer->iterator + 1);
            *(bytes_pointer + 1) = *buffer->iterator ;
        }

        buffer->iterator += data_size;
        buffer->last_data_size = data_size;
    }
}

void deserialize_byte_4(MicroBuffer* buffer, Endianness endianness, uint32_t* bytes)
{
    uint32_t data_size = sizeof(uint32_t);
    uint32_t alignment = get_alignment_offset(buffer, data_size);

    if(check_size(buffer, alignment + data_size) || resize(buffer, alignment + data_size))
    {
        buffer->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
            *bytes = *(uint32_t*)buffer->iterator;
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *bytes_pointer = *(buffer->iterator + 3);
            *(bytes_pointer + 1) = *(buffer->iterator + 2);
            *(bytes_pointer + 2) = *(buffer->iterator + 1);
            *(bytes_pointer + 3) = *buffer->iterator;
        }

        buffer->iterator += data_size;
        buffer->last_data_size = data_size;
    }
}

void deserialize_byte_8(MicroBuffer* buffer, Endianness endianness, uint64_t* bytes)
{
    uint32_t data_size = sizeof(uint64_t);
    uint32_t alignment = get_alignment_offset(buffer, data_size);

    if(check_size(buffer, alignment + data_size) || resize(buffer, alignment + data_size))
    {
        buffer->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
            *bytes = *(uint64_t*)buffer->iterator;
        else
        {
            uint8_t* bytes_pointer = (uint8_t*)bytes;
            *bytes_pointer = *(buffer->iterator + 7);
            *(bytes_pointer + 1) = *(buffer->iterator + 6);
            *(bytes_pointer + 2) = *(buffer->iterator + 5);
            *(bytes_pointer + 3) = *(buffer->iterator + 4);
            *(bytes_pointer + 4) = *(buffer->iterator + 3);
            *(bytes_pointer + 5) = *(buffer->iterator + 2);
            *(bytes_pointer + 6) = *(buffer->iterator + 1);
            *(bytes_pointer + 7) = *buffer->iterator;
        }

        buffer->iterator += data_size;
        buffer->last_data_size = data_size;
    }
}

void serialize_array_byte_1(MicroBuffer* buffer, const uint8_t* array, uint32_t size)
{
    if(check_size(buffer, size) || resize(buffer, size))
    {
        memcpy(buffer->iterator, array, size);

        buffer->iterator += size;
    }
}

void serialize_array_byte_2(MicroBuffer* buffer, Endianness endianness, const uint16_t* array, uint32_t size)
{
    uint32_t data_size = size * sizeof(uint16_t);
    uint32_t alignment = get_alignment_offset(buffer, sizeof(uint16_t));

    if(check_size(buffer, alignment + data_size) || resize(buffer, alignment + data_size))
    {
        buffer->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
            memcpy(buffer->iterator, array, data_size);
        else
        {
            for(uint32_t i = 0; i < size; i++)
                serialize_byte_2(buffer, !MACHINE_ENDIANNESS, array + i);
        }

        buffer->iterator += data_size;
    }
}

void serialize_array_byte_4(MicroBuffer* buffer, Endianness endianness, const uint32_t* array, uint32_t size)
{
    uint32_t data_size = size * sizeof(uint32_t);
    uint32_t alignment = get_alignment_offset(buffer, sizeof(uint32_t));

    if(check_size(buffer, alignment + data_size) || resize(buffer, alignment + data_size))
    {
        buffer->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
            memcpy(buffer->iterator, array, data_size);
        else
        {
            for(uint32_t i = 0; i < size; i++)
                serialize_byte_4(buffer, !MACHINE_ENDIANNESS, array + i);
        }

        buffer->iterator += data_size;
    }
}

void serialize_array_byte_8(MicroBuffer* buffer, Endianness endianness, const uint64_t* array, uint32_t size)
{
    uint32_t data_size = size * sizeof(uint64_t);
    uint32_t alignment = get_alignment_offset(buffer, sizeof(uint64_t));

    if(check_size(buffer, alignment + data_size) || resize(buffer, alignment + data_size))
    {
        buffer->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
            memcpy(buffer->iterator, array, data_size);
        else
        {
            for(uint32_t i = 0; i < size; i++)
                serialize_byte_8(buffer, !MACHINE_ENDIANNESS, array + i);
        }

        buffer->iterator += data_size;
    }
}

void deserialize_array_byte_1(MicroBuffer* buffer, uint8_t* array, uint32_t size)
{
    if(check_size(buffer, size) || resize(buffer, size))
    {
        memcpy(array, buffer->iterator, size);

        buffer->iterator += size;
    }
}

void deserialize_array_byte_2(MicroBuffer* buffer, Endianness endianness, uint16_t* array, uint32_t size)
{
    uint32_t data_size = size * sizeof(uint16_t);
    uint32_t alignment = get_alignment_offset(buffer, sizeof(uint16_t));

    if(check_size(buffer, alignment + data_size) || resize(buffer, alignment + data_size))
    {
        buffer->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
            memcpy(array, buffer->iterator, data_size);
        else
        {
            for(uint32_t i = 0; i < size; i++)
                serialize_byte_2(buffer, !MACHINE_ENDIANNESS, array + i);
        }

        buffer->iterator += data_size;
    }
}

void deserialize_array_byte_4(MicroBuffer* buffer, Endianness endianness, uint32_t* array, uint32_t size)
{
    uint32_t data_size = size * sizeof(uint32_t);
    uint32_t alignment = get_alignment_offset(buffer, sizeof(uint32_t));

    if(check_size(buffer, alignment + data_size) || resize(buffer, alignment + data_size))
    {
        buffer->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
            memcpy(array, buffer->iterator, data_size);
        else
        {
            for(uint32_t i = 0; i < size; i++)
                serialize_byte_4(buffer, !MACHINE_ENDIANNESS, array + i);
        }

        buffer->iterator += data_size;
    }
}

void deserialize_array_byte_8(MicroBuffer* buffer, Endianness endianness, uint64_t* array, uint32_t size)
{
    uint32_t data_size = size * sizeof(uint64_t);
    uint32_t alignment = get_alignment_offset(buffer, sizeof(uint64_t));

    if(check_size(buffer, alignment + data_size) || resize(buffer, alignment + data_size))
    {
        buffer->iterator += alignment;

        if(MACHINE_ENDIANNESS == endianness)
            memcpy(array, buffer->iterator, data_size);
        else
        {
            for(uint32_t i = 0; i < size; i++)
                serialize_byte_8(buffer, !MACHINE_ENDIANNESS, array + i);
        }

        buffer->iterator += data_size;
    }
}

void serialize_char(MicroBuffer* buffer, char value)
{
    serialize_byte_1(buffer, &value);
}

void serialize_bool(MicroBuffer* buffer, bool value)
{
    serialize_byte_1(buffer, (uint8_t*)&value);
}

void serialize_uint8_t(MicroBuffer* buffer, uint8_t value)
{
    serialize_byte_1(buffer, &value);
}

void serialize_uint16_t(MicroBuffer* buffer, uint16_t value)
{
    serialize_byte_2(buffer, buffer->endianness, &value);
}

void serialize_uint32_t(MicroBuffer* buffer, uint32_t value)
{
    serialize_byte_4(buffer, buffer->endianness, &value);
}

void serialize_uint64_t(MicroBuffer* buffer, uint64_t value)
{
    serialize_byte_8(buffer, buffer->endianness, &value);
}

void serialize_int16_t(MicroBuffer* buffer, int16_t value)
{
    serialize_byte_2(buffer, buffer->endianness, &value);
}

void serialize_int32_t(MicroBuffer* buffer, int32_t value)
{
    serialize_byte_4(buffer, buffer->endianness, &value);
}

void serialize_int64_t(MicroBuffer* buffer, int64_t value)
{
    serialize_byte_8(buffer, buffer->endianness, &value);
}

void serialize_float(MicroBuffer* buffer, float value)
{
    serialize_byte_4(buffer, buffer->endianness, (uint32_t*)&value);
}

void serialize_double(MicroBuffer* buffer, double value)
{
    serialize_byte_8(buffer, buffer->endianness, (uint64_t*)&value);
}

void deserialize_char(MicroBuffer* buffer, char* value)
{
    deserialize_byte_1(buffer, value);
}

void deserialize_bool(MicroBuffer* buffer, bool* value)
{
    deserialize_byte_1(buffer, (uint8_t*)value);
}

void deserialize_uint8_t(MicroBuffer* buffer, uint8_t* value)
{
    deserialize_byte_1(buffer, value);
}

void deserialize_uint16_t(MicroBuffer* buffer, uint16_t* value)
{
    deserialize_byte_2(buffer, buffer->endianness, value);
}

void deserialize_uint32_t(MicroBuffer* buffer, uint32_t* value)
{
    deserialize_byte_4(buffer, buffer->endianness, value);
}

void deserialize_uint64_t(MicroBuffer* buffer, uint64_t* value)
{
    deserialize_byte_8(buffer, buffer->endianness, value);
}

void deserialize_int16_t(MicroBuffer* buffer, int16_t* value)
{
    deserialize_byte_2(buffer, buffer->endianness, value);
}

void deserialize_int32_t(MicroBuffer* buffer, int32_t* value)
{
    deserialize_byte_4(buffer, buffer->endianness, value);
}

void deserialize_int64_t(MicroBuffer* buffer, int64_t* value)
{
    deserialize_byte_8(buffer, buffer->endianness, value);
}

void deserialize_float(MicroBuffer* buffer, float* value)
{
    deserialize_byte_4(buffer, buffer->endianness, (int32_t*) value);
}

void deserialize_double(MicroBuffer* buffer, double* value)
{
    deserialize_byte_8(buffer, buffer->endianness, (int64_t*) value);
}

void serialize_array_char(MicroBuffer* buffer, const char* array, uint32_t size)
{
    serialize_array_byte_1(buffer, array, size);
}

void serialize_array_bool(MicroBuffer* buffer, const bool* array, uint32_t size)
{
    serialize_array_byte_1(buffer, (uint8_t*)array, size);
}

void serialize_array_uint8_t(MicroBuffer* buffer, const uint8_t* array, uint32_t size)
{
    serialize_array_byte_1(buffer, array, size);
}

void serialize_array_uint16_t(MicroBuffer* buffer, const uint16_t* array, uint32_t size)
{
    serialize_array_byte_2(buffer, buffer->endianness, array, size);
}

void serialize_array_uint32_t(MicroBuffer* buffer, const uint32_t* array, uint32_t size)
{
    serialize_array_byte_4(buffer, buffer->endianness, array, size);
}

void serialize_array_uint64_t(MicroBuffer* buffer, const uint64_t* array, uint32_t size)
{
    serialize_array_byte_8(buffer, buffer->endianness, array, size);
}

void serialize_array_int16_t(MicroBuffer* buffer, const int16_t* array, uint32_t size)
{
    serialize_array_byte_2(buffer, buffer->endianness, array, size);
}

void serialize_array_int32_t(MicroBuffer* buffer, const int32_t* array, uint32_t size)
{
    serialize_array_byte_4(buffer, buffer->endianness, array, size);
}

void serialize_array_int64_t(MicroBuffer* buffer, const int64_t* array, uint32_t size)
{
    serialize_array_byte_8(buffer, buffer->endianness, array, size);
}

void serialize_array_float(MicroBuffer* buffer, const float* array, uint32_t size)
{
    serialize_array_byte_4(buffer, buffer->endianness, (uint32_t*)array, size);
}

void serialize_array_double(MicroBuffer* buffer, const double* array, uint32_t size)
{
    serialize_array_byte_8(buffer, buffer->endianness, (uint64_t*)array, size);
}

void deserialize_array_char(MicroBuffer* buffer, char* array, uint32_t size)
{
    deserialize_array_byte_1(buffer, array, size);
}

void deserialize_array_bool(MicroBuffer* buffer, bool* array, uint32_t size)
{
    deserialize_array_byte_1(buffer, (uint8_t*)array, size);
}

void deserialize_array_uint8_t(MicroBuffer* buffer, uint8_t* array, uint32_t size)
{
    deserialize_array_byte_1(buffer, array, size);
}

void deserialize_array_uint16_t(MicroBuffer* buffer, uint16_t* array, uint32_t size)
{
    deserialize_array_byte_2(buffer, buffer->endianness, array, size);
}

void deserialize_array_uint32_t(MicroBuffer* buffer, uint32_t* array, uint32_t size)
{
    deserialize_array_byte_4(buffer, buffer->endianness, array, size);
}

void deserialize_array_uint64_t(MicroBuffer* buffer, uint64_t* array, uint32_t size)
{
    deserialize_array_byte_8(buffer, buffer->endianness, array, size);
}

void deserialize_array_int16_t(MicroBuffer* buffer, int16_t* array, uint32_t size)
{
    deserialize_array_byte_2(buffer, buffer->endianness, array, size);
}

void deserialize_array_int32_t(MicroBuffer* buffer, int32_t* array, uint32_t size)
{
    deserialize_array_byte_4(buffer, buffer->endianness, array, size);
}

void deserialize_array_int64_t(MicroBuffer* buffer, int64_t* array, uint32_t size)
{
    deserialize_array_byte_8(buffer, buffer->endianness, array, size);
}

void deserialize_array_float(MicroBuffer* buffer, float* array, uint32_t size)
{
    deserialize_array_byte_4(buffer, buffer->endianness, (uint32_t*)array, size);
}

void deserialize_array_double(MicroBuffer* buffer, double* array, uint32_t size)
{
    deserialize_array_byte_8(buffer, buffer->endianness, (uint64_t*)array, size);
}

void serialize_sequence_char(MicroBuffer* buffer, const char* sequence, uint32_t size)
{
    serialize_byte_4(buffer, buffer->endianness, &size);
    serialize_array_byte_1(buffer, sequence, size);
}

void serialize_sequence_bool(MicroBuffer* buffer, const bool* sequence, uint32_t size)
{
    serialize_byte_4(buffer, buffer->endianness, &size);
    serialize_array_byte_1(buffer, (uint8_t*)sequence, size);
}

void serialize_sequence_uint8_t(MicroBuffer* buffer, const uint8_t* sequence, uint32_t size)
{
    serialize_byte_4(buffer, buffer->endianness, &size);
    serialize_array_byte_1(buffer, sequence, size);
}

void serialize_sequence_uint16_t(MicroBuffer* buffer, const uint16_t* sequence, uint32_t size)
{
    serialize_byte_4(buffer, buffer->endianness, &size);
    serialize_array_byte_2(buffer, buffer->endianness, sequence, size);
}

void serialize_sequence_uint32_t(MicroBuffer* buffer, const uint32_t* sequence, uint32_t size)
{
    serialize_byte_4(buffer, buffer->endianness, &size);
    serialize_array_byte_4(buffer, buffer->endianness, sequence, size);
}

void serialize_sequence_uint64_t(MicroBuffer* buffer, const uint64_t* sequence, uint32_t size)
{
    serialize_byte_4(buffer, buffer->endianness, &size);
    serialize_array_byte_8(buffer, buffer->endianness, sequence, size);
}

void serialize_sequence_int16_t(MicroBuffer* buffer, const int16_t* sequence, uint32_t size)
{
    serialize_byte_4(buffer, buffer->endianness, &size);
    serialize_array_byte_2(buffer, buffer->endianness, sequence, size);
}

void serialize_sequence_int32_t(MicroBuffer* buffer, const int32_t* sequence, uint32_t size)
{
    serialize_byte_4(buffer, buffer->endianness, &size);
    serialize_array_byte_4(buffer, buffer->endianness, sequence, size);
}

void serialize_sequence_int64_t(MicroBuffer* buffer, const int64_t* sequence, uint32_t size)
{
    serialize_byte_4(buffer, buffer->endianness, &size);
    serialize_array_byte_8(buffer, buffer->endianness, sequence, size);
}

void serialize_sequence_float(MicroBuffer* buffer, const float* sequence, uint32_t size)
{
    serialize_byte_4(buffer, buffer->endianness, &size);
    serialize_array_byte_4(buffer, buffer->endianness, (uint32_t*)sequence, size);
}

void serialize_sequence_double(MicroBuffer* buffer, const double* sequence, uint32_t size)
{
    serialize_byte_4(buffer, buffer->endianness, &size);
    serialize_array_byte_8(buffer, buffer->endianness, (uint64_t*)sequence, size);
}

void deserialize_sequence_char(MicroBuffer* buffer, char* sequence, uint32_t* size)
{
    deserialize_byte_4(buffer, buffer->endianness, size);
    deserialize_array_byte_1(buffer, sequence, *size);
}

void deserialize_sequence_bool(MicroBuffer* buffer, bool* sequence, uint32_t* size)
{
    deserialize_byte_4(buffer, buffer->endianness, size);
    deserialize_array_byte_1(buffer, (uint8_t*)sequence, *size);
}

void deserialize_sequence_uint8_t(MicroBuffer* buffer, uint8_t*  sequence, uint32_t* size)
{
    deserialize_byte_4(buffer, buffer->endianness, size);
    deserialize_array_byte_1(buffer, sequence, *size);
}

void deserialize_sequence_uint16_t(MicroBuffer* buffer, uint16_t* sequence, uint32_t* size)
{
    deserialize_byte_4(buffer, buffer->endianness, size);
    deserialize_array_byte_2(buffer, buffer->endianness, sequence, *size);
}

void deserialize_sequence_uint32_t(MicroBuffer* buffer, uint32_t* sequence, uint32_t* size)
{
    deserialize_byte_4(buffer, buffer->endianness, size);
    deserialize_array_byte_4(buffer, buffer->endianness, sequence, *size);
}

void deserialize_sequence_uint64_t(MicroBuffer* buffer, uint64_t* sequence, uint32_t* size)
{
    deserialize_byte_4(buffer, buffer->endianness, size);
    deserialize_array_byte_8(buffer, buffer->endianness, sequence, *size);
}

void deserialize_sequence_int16_t(MicroBuffer* buffer, int16_t* sequence, uint32_t* size)
{
    deserialize_byte_4(buffer, buffer->endianness, size);
    deserialize_array_byte_2(buffer, buffer->endianness, sequence, *size);
}

void deserialize_sequence_int32_t(MicroBuffer* buffer, int32_t* sequence, uint32_t* size)
{
    deserialize_byte_4(buffer, buffer->endianness, size);
    deserialize_array_byte_4(buffer, buffer->endianness, sequence, *size);
}

void deserialize_sequence_int64_t(MicroBuffer* buffer, int64_t* sequence, uint32_t* size)
{
    deserialize_byte_4(buffer, buffer->endianness, size);
    deserialize_array_byte_8(buffer, buffer->endianness, sequence, *size);
}

void deserialize_sequence_float(MicroBuffer* buffer, float* sequence, uint32_t* size)
{
    deserialize_byte_4(buffer, buffer->endianness, size);
    deserialize_array_byte_4(buffer, buffer->endianness, (uint32_t*)sequence, *size);
}

void deserialize_sequence_double(MicroBuffer* buffer, double* sequence, uint32_t* size)
{
    deserialize_byte_4(buffer, buffer->endianness, size);
    deserialize_array_byte_8(buffer, buffer->endianness, (uint64_t*)sequence, *size);
}

void serialize_endian_uint16_t(MicroBuffer* buffer, Endianness endianness, uint16_t value)
{
    serialize_byte_2(buffer, endianness, &value);
}

void serialize_endian_uint32_t(MicroBuffer* buffer, Endianness endianness, uint32_t value)
{
    serialize_byte_4(buffer, endianness, &value);
}

void serialize_endian_uint64_t(MicroBuffer* buffer, Endianness endianness, uint64_t value)
{
    serialize_byte_8(buffer, endianness, &value);
}

void serialize_endian_int16_t(MicroBuffer* buffer, Endianness endianness, int16_t value)
{
    serialize_byte_2(buffer, endianness, &value);
}

void serialize_endian_int32_t(MicroBuffer* buffer, Endianness endianness, int32_t value)
{
    serialize_byte_4(buffer, endianness, &value);
}

void serialize_endian_int64_t(MicroBuffer* buffer, Endianness endianness, int64_t value)
{
    serialize_byte_8(buffer, endianness, &value);
}

void serialize_endian_float(MicroBuffer* buffer, Endianness endianness, float value)
{
    serialize_byte_4(buffer, endianness, (uint32_t*)&value);
}

void serialize_endian_double(MicroBuffer* buffer, Endianness endianness, double value)
{
    serialize_byte_8(buffer, endianness, (uint64_t*)&value);
}

void deserialize_endian_uint16_t(MicroBuffer* buffer, Endianness endianness, uint16_t* value)
{
    deserialize_byte_2(buffer, endianness, value);
}

void deserialize_endian_uint32_t(MicroBuffer* buffer, Endianness endianness, uint32_t* value)
{
    deserialize_byte_4(buffer, endianness, value);
}

void deserialize_endian_uint64_t(MicroBuffer* buffer, Endianness endianness, uint64_t* value)
{
    deserialize_byte_8(buffer, endianness, value);
}

void deserialize_endian_int16_t(MicroBuffer* buffer, Endianness endianness, int16_t* value)
{
    deserialize_byte_2(buffer, endianness, value);
}

void deserialize_endian_int32_t(MicroBuffer* buffer, Endianness endianness, int32_t* value)
{
    deserialize_byte_4(buffer, endianness, value);
}

void deserialize_endian_int64_t(MicroBuffer* buffer, Endianness endianness, int64_t* value)
{
    deserialize_byte_8(buffer, endianness, value);
}

void deserialize_endian_float(MicroBuffer* buffer, Endianness endianness, float* value)
{
    deserialize_byte_4(buffer, endianness, (uint32_t*)value);
}

void deserialize_endian_double(MicroBuffer* buffer, Endianness endianness, double* value)
{
    deserialize_byte_8(buffer, endianness, (uint64_t*)value);
}

void serialize_endian_array_uint16_t(MicroBuffer* buffer, Endianness endianness, const uint16_t* array, uint32_t size)
{
    serialize_array_byte_2(buffer, endianness, array, size);
}

void serialize_endian_array_uint32_t(MicroBuffer* buffer, Endianness endianness, const uint32_t* array, uint32_t size)
{
    serialize_array_byte_4(buffer, endianness, array, size);
}

void serialize_endian_array_uint64_t(MicroBuffer* buffer, Endianness endianness, const uint64_t* array, uint32_t size)
{
    serialize_array_byte_8(buffer, endianness, array, size);
}

void serialize_endian_array_int16_t(MicroBuffer* buffer, Endianness endianness, const int16_t* array, uint32_t size)
{
    serialize_array_byte_2(buffer, endianness, array, size);
}

void serialize_endian_array_int32_t(MicroBuffer* buffer, Endianness endianness, const int32_t* array, uint32_t size)
{
    serialize_array_byte_4(buffer, endianness, array, size);
}

void serialize_endian_array_int64_t(MicroBuffer* buffer, Endianness endianness, const int64_t* array, uint32_t size)
{
    serialize_array_byte_8(buffer, endianness, array, size);
}

void serialize_endian_array_float(MicroBuffer* buffer, Endianness endianness, const float* array, uint32_t size)
{
    serialize_array_byte_4(buffer, endianness, (uint32_t*)array, size);
}

void serialize_endian_array_double(MicroBuffer* buffer, Endianness endianness, const double* array, uint32_t size)
{
    serialize_array_byte_8(buffer, endianness, (uint64_t*)array, size);
}

void deserialize_endian_array_uint16_t(MicroBuffer* buffer, Endianness endianness, uint16_t* array, uint32_t size)
{
    deserialize_array_byte_2(buffer, endianness, array, size);
}

void deserialize_endian_array_uint32_t(MicroBuffer* buffer, Endianness endianness, uint32_t* array, uint32_t size)
{
    deserialize_array_byte_4(buffer, endianness, array, size);
}

void deserialize_endian_array_uint64_t(MicroBuffer* buffer, Endianness endianness, uint64_t* array, uint32_t size)
{
    deserialize_array_byte_8(buffer, endianness, array, size);
}

void deserialize_endian_array_int16_t(MicroBuffer* buffer, Endianness endianness, int16_t* array, uint32_t size)
{
    deserialize_array_byte_2(buffer, endianness, array, size);
}

void deserialize_endian_array_int32_t(MicroBuffer* buffer, Endianness endianness, int32_t* array, uint32_t size)
{
    deserialize_array_byte_4(buffer, endianness, array, size);
}

void deserialize_endian_array_int64_t(MicroBuffer* buffer, Endianness endianness, int64_t* array, uint32_t size)
{
    deserialize_array_byte_8(buffer, endianness, array, size);
}

void deserialize_endian_array_float(MicroBuffer* buffer, Endianness endianness, float* array, uint32_t size)
{
    deserialize_array_byte_4(buffer, endianness, (uint32_t*)array, size);
}

void deserialize_endian_array_double(MicroBuffer* buffer, Endianness endianness, double* array, uint32_t size)
{
    deserialize_array_byte_8(buffer, endianness, (uint64_t*)array, size);
}

void serialize_endian_sequence_uint16_t(MicroBuffer* buffer, Endianness endianness, const uint16_t* sequence, uint32_t size)
{
    serialize_byte_4(buffer, endianness, &size);
    serialize_array_byte_2(buffer, endianness, sequence, size);
}

void serialize_endian_sequence_uint32_t(MicroBuffer* buffer, Endianness endianness, const uint32_t* sequence, uint32_t size)
{
    serialize_byte_4(buffer, endianness, &size);
    serialize_array_byte_4(buffer, endianness, sequence, size);
}

void serialize_endian_sequence_uint64_t(MicroBuffer* buffer, Endianness endianness, const uint64_t* sequence, uint32_t size)
{
    serialize_byte_4(buffer, endianness, &size);
    serialize_array_byte_8(buffer, endianness, sequence, size);
}

void serialize_endian_sequence_int16_t(MicroBuffer* buffer, Endianness endianness, const int16_t* sequence, uint32_t size)
{
    serialize_byte_4(buffer, endianness, &size);
    serialize_array_byte_2(buffer, endianness, sequence, size);
}

void serialize_endian_sequence_int32_t(MicroBuffer* buffer, Endianness endianness, const int32_t* sequence, uint32_t size)
{
    serialize_byte_4(buffer, endianness, &size);
    serialize_array_byte_4(buffer, endianness, sequence, size);
}

void serialize_endian_sequence_int64_t(MicroBuffer* buffer, Endianness endianness, const int64_t* sequence, uint32_t size)
{
    serialize_byte_4(buffer, endianness, &size);
    serialize_array_byte_8(buffer, endianness, sequence, size);
}

void serialize_endian_sequence_float(MicroBuffer* buffer, Endianness endianness, const float* sequence, uint32_t size)
{
    serialize_byte_4(buffer, endianness, &size);
    serialize_array_byte_4(buffer, endianness, (uint32_t*)sequence, size);
}

void serialize_endian_sequence_double(MicroBuffer* buffer, Endianness endianness, const double* sequence, uint32_t size)
{
    serialize_byte_4(buffer, endianness, &size);
    serialize_array_byte_8(buffer, endianness, (uint64_t*)sequence, size);
}

void deserialize_endian_sequence_uint16_t(MicroBuffer* buffer, Endianness endianness, uint16_t* sequence, uint32_t* size)
{
    deserialize_byte_4(buffer, endianness, size);
    deserialize_array_byte_2(buffer, endianness, sequence, *size);
}

void deserialize_endian_sequence_uint32_t(MicroBuffer* buffer, Endianness endianness, uint32_t* sequence, uint32_t* size)
{
    deserialize_byte_4(buffer, endianness, size);
    deserialize_array_byte_4(buffer, endianness, sequence, *size);
}

void deserialize_endian_sequence_uint64_t(MicroBuffer* buffer, Endianness endianness, uint64_t* sequence, uint32_t* size)
{
    deserialize_byte_4(buffer, endianness, size);
    deserialize_array_byte_8(buffer, endianness, sequence, *size);
}

void deserialize_endian_sequence_int16_t(MicroBuffer* buffer, Endianness endianness, int16_t* sequence, uint32_t* size)
{
    deserialize_byte_4(buffer, endianness, size);
    deserialize_array_byte_2(buffer, endianness, sequence, *size);
}

void deserialize_endian_sequence_int32_t(MicroBuffer* buffer, Endianness endianness, int32_t* sequence, uint32_t* size)
{
    deserialize_byte_4(buffer, endianness, size);
    deserialize_array_byte_4(buffer, endianness, sequence, *size);
}

void deserialize_endian_sequence_int64_t(MicroBuffer* buffer, Endianness endianness, int64_t* sequence, uint32_t* size)
{
    deserialize_byte_4(buffer, endianness, size);
    deserialize_array_byte_8(buffer, endianness, sequence, *size);
}

void deserialize_endian_sequence_float(MicroBuffer* buffer, Endianness endianness, float* sequence, uint32_t* size)
{
    deserialize_byte_4(buffer, endianness, size);
    deserialize_array_byte_4(buffer, endianness, (uint32_t*)sequence, *size);
}

void deserialize_endian_sequence_double(MicroBuffer* buffer, Endianness endianness, double* sequence, uint32_t* size)
{
    deserialize_byte_4(buffer, endianness, size);
    deserialize_array_byte_8(buffer, endianness, (uint64_t*)sequence, *size);
}
