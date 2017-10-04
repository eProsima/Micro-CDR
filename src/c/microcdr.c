#include "microcdr/micro_cdr.h"



#if __BIG_ENDIAN__
#define MACHINE_ENDIANNES BIG_ENDIANNESS
#else
#define MACHINE_ENDIANNES LITTLE_ENDIANNESS
#endif

// -------------------------------------------------------------------
//                  INTERNAL SERIALIZATION FUNCTIONS
// -------------------------------------------------------------------

uint32_t check_alignment(MicroBuffer* micro_buffer, uint32_t data_size);

// NOTE: remove inline from byte's functions will reduce significally the size of the compiler data.
//          put inline from byte's functions will increase the performance.

inline int serialize_byte(MicroBuffer* micro_buffer, uint8_t value);
inline int serialize_byte_2(MicroBuffer* micro_buffer, Endianness endianness, uint16_t value);
inline int serialize_byte_4(MicroBuffer* micro_buffer, Endianness endianness, uint32_t value);
inline int serialize_byte_8(MicroBuffer* micro_buffer, Endianness endianness, uint64_t value);

inline int deserialize_byte(MicroBuffer* micro_buffer, uint8_t* value);
inline int deserialize_byte_2(MicroBuffer* micro_buffer, Endianness endianness, uint16_t* value);
inline int deserialize_byte_4(MicroBuffer* micro_buffer, Endianness endianness, uint32_t* value);
inline int deserialize_byte_8(MicroBuffer* micro_buffer, Endianness endianness, uint64_t* value);

// -------------------------------------------------------------------
//                          IMPLEMENTATION
// -------------------------------------------------------------------

void init_micro_buffer(MicroBuffer* micro_buffer, uint8_t* buffer, uint32_t size)
{
    micro_buffer->buffer = buffer;
    micro_buffer->final = buffer + size;
    micro_buffer->iterator = buffer;
    micro_buffer->last_data_size = 0;
}

void reset_micro_buffer(MicroBuffer* micro_buffer)
{
    buffer->iterator = buffer->data;
}

void make_alignment(MicroBuffer* buffer, uint32_t aligment)
{
    // TODO
}

uint32_t check_alignment(MicroBuffer* buffer, uint32_t data_size)
{
    if(dataSize > m_cdrBuffer->m_lastDataSize)
        return (dataSize - ((buffer->iterator - buffer->buffer) % dataSize)) & (dataSize - 1);

    return 0;
}

int serialize_byte_2(MicroBuffer* buffer, Endianness endianness, uint16_t value)
{
    uint32_t data_size = sizeof(uint16_t);
    uint32_t alignment = check_alignment(data_size);

    if(buffer->iterator + data_size + alignment > buffer->final)
        return 0;

    buffer->iterator += alignment;

    if(MACHINE_ENDIANNESS == endianes)
        *((uint16_t*)buffer->iterator) = bytes;
    else
    {
        *buffer->iterator = *(bytes_pointer + 1);
        *(buffer->iterator + 1) = *bytes_pointer;
    }

    buffer->iterator += data_size;
    buffer->last_data_size = data_size;

    return 1;
}

int serialize_byte_4(MicroBuffer* buffer, Endianness endianness, uint32_t value)
{
    uint32_t data_size = sizeof(uint32_t);
    uint32_t alignment = check_alignment(data_size);

    if(buffer->iterator + data_size + alignment > buffer->final)
        return 0;

    buffer->iterator += alignment;

    if(MACHINE_ENDIANNESS == endianes)
        *((uint32_t*)buffer->iterator) = bytes;
    else
    {
        *buffer->iterator = *(bytes_pointer + 3);
        *(buffer->iterator + 1) = *(bytes_pointer + 2);
        *(buffer->iterator + 2) = *(bytes_pointer + 1);
        *(buffer->iterator + 3) = *bytes_pointer;
    }

    buffer->iterator += data_size;
    buffer->last_data_size = data_size;

    return 1;
}

int deserialize_byte_4(MicroBuffer* buffer, Endianness endianness, uint32_t* value)
{
    uint32_t data_size = sizeof(uint32_t);
    uint32_t alignment = check_alignment(data_size);

    if(buffer->iterator + data_size + alignment >= buffer->final)
        return 0;

    buffer->iterator += alignment;

    uint8_t* bytes_pointer = (uint8_t*)bytes;
    if(MACHINE_ENDIANNESS == endianes)
        *bytes = *(uint32_t*)buffer->iterator;
    else
    {
        *bytes_pointer = *(buffer->iterator + 3);
        *(bytes_pointer + 1) = *(buffer->iterator + 2);
        *(bytes_pointer + 2) = *(buffer->iterator + 1);
        *(bytes_pointer + 3) = *buffer->iterator;
    }

    buffer->iterator += data_size;
    buffer->last_data_size = data_size;

    return 1;
}



