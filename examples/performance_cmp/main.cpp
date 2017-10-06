#include <microcdr/microcdr.h>
#include <microcdr/microCdr.h>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ITERATIONS 10000
#define BUFFER_LENGTH 33600 //multiply of 14 and 240

typedef struct Times
{
    float s_byte;
    float s_bytes;
    float s_array_byte;
    float s_array_bytes;
    float d_byte;
    float d_bytes;
    float d_array_byte;
    float d_array_bytes;

} Times;

void print_comparation(Times t1, Times t2);
Times micro_cdr_1(Endianness endianness);
Times micro_cdr_2(Endianness endianness);

char buffer_cdr_1[BUFFER_LENGTH];
uint8_t buffer_cdr_2[BUFFER_LENGTH];

uint8_t ubyte1 = 0x09;
uint16_t ubyte2 = 0x0A0B;
uint32_t ubyte4 = 0x0C0D0E0F;
uint64_t ubyte8 = 0x0102030405060708;

uint8_t array1[80] = {0x09};
uint16_t array2[80] = {0x0A0B};
uint32_t array4[80] = {0x0C0D0E0F};
uint64_t array8[80] = {0x0102030405060708};

int main(int args, char** argv)
{
    Times t1_big = micro_cdr_1(BIG_ENDIANNESS);
    Times t2_big = micro_cdr_2(BIG_ENDIANNESS);

    Times t1_little = micro_cdr_1(LITTLE_ENDIANNESS);
    Times t2_little = micro_cdr_2(LITTLE_ENDIANNESS);

    printf("BIG_ENDIANNESS:\n");
    print_comparation(t1_big, t2_big);
    printf("\n");

    printf("LITTLE_ENDIANNESS:\n");
    print_comparation(t1_little, t2_little);
    printf("\n");
    return 0;
}

Times micro_cdr_1(Endianness endianness)
{
    struct microBuffer* microBufferWriter = NULL;
    struct microBuffer* microBufferReader = NULL;
    newStaticAlignedBuffer(buffer_cdr_1, BUFFER_LENGTH, &microBufferWriter);
    newDeserializedAlignedBuffer(buffer_cdr_1, BUFFER_LENGTH, &microBufferReader);

    struct microCDR* microCDRWriter = NULL;
    struct microCDR* microCDRReader = NULL;
    newMicroCDR(&microCDRWriter, microBufferWriter);
    newMicroCDR(&microCDRReader, microBufferReader);

    clock_t c1 = clock();
    for(unsigned i = 0; i < ITERATIONS; i++)
    {
        for(unsigned j = 0; j < BUFFER_LENGTH; j += 1)
        {
            serializeUnsignedChar(ubyte1, microCDRWriter);
        }
        resetStaticMicroCDRForSerialize(microCDRWriter);
    }

    clock_t c2 = clock();
    for(unsigned i = 0; i < ITERATIONS; i++)
    {
        for(unsigned j = 0; j < BUFFER_LENGTH; j += 14)
        {
            serializeUnsignedShortEndianness(ubyte2, endianness, microCDRWriter);
            serializeUnsignedIntEndianness(ubyte4, endianness, microCDRWriter);
            serializeUnsignedLongEndianness(ubyte8, endianness, microCDRWriter);
        }
        resetStaticMicroCDRForSerialize(microCDRWriter);
    }

    clock_t c3 = clock();
    for(unsigned i = 0; i < ITERATIONS; i++)
    {
        for(unsigned j = 0; j < BUFFER_LENGTH; j += 80)
        {
            serializeUnsignedCharArray(array1, 80, microCDRWriter);
        }
        resetStaticMicroCDRForSerialize(microCDRWriter);
    }

    clock_t c4 = clock();
    for(unsigned i = 0; i < ITERATIONS; i++)
    {
        for(unsigned j = 0; j < BUFFER_LENGTH; j += 240)
        {
            serializeUnsignedShortArrayEndianness(array2, 40, endianness, microCDRWriter);
            serializeUnsignedIntArrayEndianness(array4, 20, endianness, microCDRWriter);
            serializeUnsignedLongArrayEndianness(array8, 10, endianness, microCDRWriter);
        }
        resetStaticMicroCDRForSerialize(microCDRWriter);
    }

    clock_t c5 = clock();
    for(unsigned i = 0; i < ITERATIONS; i++)
    {
        for(unsigned j = 0; j < BUFFER_LENGTH; j += 1)
        {
            deserializeUnsignedChar(&ubyte1, microCDRReader);
        }
        resetStaticMicroCDRForDeserialize(microCDRReader);
    }

    clock_t c6 = clock();
    for(unsigned i = 0; i < ITERATIONS; i++)
    {
        for(unsigned j = 0; j < BUFFER_LENGTH; j += 14)
        {
            deserializeUnsignedShortEndianness(&ubyte2, endianness, microCDRReader);
            deserializeUnsignedIntEndianness(&ubyte4, endianness, microCDRReader);
            deserializeUnsignedLongEndianness(&ubyte8, endianness, microCDRReader);
        }
        resetStaticMicroCDRForDeserialize(microCDRReader);
    }

    clock_t c7 = clock();
    for(unsigned i = 0; i < ITERATIONS; i++)
    {
        for(unsigned j = 0; j < BUFFER_LENGTH; j += 80)
        {
            uint8_t* l_array1;
            if(deserializeUnsignedCharArray(&l_array1, 80, microCDRReader) > 0)
                free(l_array1);
        }
        resetStaticMicroCDRForDeserialize(microCDRReader);
    }

    clock_t c8 = clock();

    for(unsigned i = 0; i < ITERATIONS; i++)
    {
        for(unsigned j = 0; j < BUFFER_LENGTH; j += 240)
        {
            uint16_t* l_array2;
            if(deserializeUnsignedShortArrayEndianness(&l_array2, 40, endianness, microCDRReader) > 0)
                free(l_array2);

            uint32_t* l_array4;
            if(deserializeUnsignedIntArrayEndianness(&l_array4, 20, endianness, microCDRReader) > 0)
                free(l_array4);

            uint64_t* l_array8;
            if(deserializeUnsignedLongArrayEndianness(&l_array8, 10, endianness, microCDRReader) > 0)
                free(l_array8);
        }
        resetStaticMicroCDRForDeserialize(microCDRReader);
    }

    clock_t c9 = clock();

    free(microBufferWriter);
    free(microBufferReader);
    free(microCDRWriter);
    free(microCDRReader);

    Times times;
    times.s_byte = ((float)(c2 - c1) / CLOCKS_PER_SEC) * 1000;
    times.s_bytes = ((float)(c3 - c2) / CLOCKS_PER_SEC) * 1000;
    times.s_array_byte = ((float)(c4 - c3) / CLOCKS_PER_SEC) * 1000;
    times.s_array_bytes = ((float)(c5 - c4) / CLOCKS_PER_SEC) * 1000;
    times.d_byte = ((float)(c6 - c5) / CLOCKS_PER_SEC) * 1000;
    times.d_bytes = ((float)(c7 - c6) / CLOCKS_PER_SEC) * 1000;
    times.d_array_byte = ((float)(c8 - c7) / CLOCKS_PER_SEC) * 1000;
    times.d_array_bytes = ((float)(c9 - c8) / CLOCKS_PER_SEC) * 1000;

    return times;
}

Times micro_cdr_2(Endianness endianness)
{
    MicroBuffer writer;
    MicroBuffer reader;

    init_external_buffer(&writer, buffer_cdr_2, BUFFER_LENGTH);
    init_external_buffer(&reader, buffer_cdr_2, BUFFER_LENGTH);

    clock_t c1 = clock();
    for(unsigned i = 0; i < ITERATIONS; i++)
    {
        for(unsigned j = 0; j < BUFFER_LENGTH; j += 1)
        {
            serialize_uint8(&writer, ubyte1);
        }
        reset_buffer(&writer);
    }

    clock_t c2 = clock();
    for(unsigned i = 0; i < ITERATIONS; i++)
    {
        for(unsigned j = 0; j < BUFFER_LENGTH; j += 14)
        {
            serialize_endian_uint16(&writer, endianness, ubyte2);
            serialize_endian_uint32(&writer, endianness, ubyte4);
            serialize_endian_uint64(&writer, endianness, ubyte8);
        }
        reset_buffer(&writer);
    }

    clock_t c3 = clock();
    for(unsigned i = 0; i < ITERATIONS; i++)
    {
        for(unsigned j = 0; j < BUFFER_LENGTH; j += 80)
        {
            serialize_array_uint8(&writer, array1, 80);
        }
        reset_buffer(&writer);
    }

    clock_t c4 = clock();
    for(unsigned i = 0; i < ITERATIONS; i++)
    {
        for(unsigned j = 0; j < BUFFER_LENGTH; j += 240)
        {
            serialize_array_endian_uint16(&writer, endianness, array2, 40);
            serialize_array_endian_uint32(&writer, endianness, array4, 20);
            serialize_array_endian_uint64(&writer, endianness, array8, 10);
        }
        reset_buffer(&writer);
    }

    clock_t c5 = clock();
    for(unsigned i = 0; i < ITERATIONS; i++)
    {
        for(unsigned j = 0; j < BUFFER_LENGTH; j += 1)
        {
            deserialize_uint8(&reader, &ubyte1);
        }
        reset_buffer(&reader);
    }

    clock_t c6 = clock();
    for(unsigned i = 0; i < ITERATIONS; i++)
    {
        for(unsigned j = 0; j < BUFFER_LENGTH; j += 14)
        {
            deserialize_endian_uint16(&reader, endianness, &ubyte2);
            deserialize_endian_uint32(&reader, endianness, &ubyte4);
            deserialize_endian_uint64(&reader, endianness, &ubyte8);
        }
        reset_buffer(&reader);
    }

    clock_t c7 = clock();
    for(unsigned i = 0; i < ITERATIONS; i++)
    {
        for(unsigned j = 0; j < BUFFER_LENGTH; j += 80)
        {
            deserialize_array_uint8(&reader, array1, 80);
        }
        reset_buffer(&reader);
    }

    clock_t c8 = clock();

    for(unsigned i = 0; i < ITERATIONS; i++)
    {
        for(unsigned j = 0; j < BUFFER_LENGTH; j += 240)
        {
            deserialize_array_endian_uint16(&reader, endianness, array2, 40);
            deserialize_array_endian_uint32(&reader, endianness, array4, 20);
            deserialize_array_endian_uint64(&reader, endianness, array8, 10);
        }
        reset_buffer(&reader);
    }

    clock_t c9 = clock();

    Times times;
    times.s_byte = ((float)(c2 - c1) / CLOCKS_PER_SEC) * 1000;
    times.s_bytes = ((float)(c3 - c2) / CLOCKS_PER_SEC) * 1000;
    times.s_array_byte = ((float)(c4 - c3) / CLOCKS_PER_SEC) * 1000;
    times.s_array_bytes = ((float)(c5 - c4) / CLOCKS_PER_SEC) * 1000;
    times.d_byte = ((float)(c6 - c5) / CLOCKS_PER_SEC) * 1000;
    times.d_bytes = ((float)(c7 - c6) / CLOCKS_PER_SEC) * 1000;
    times.d_array_byte = ((float)(c8 - c7) / CLOCKS_PER_SEC) * 1000;
    times.d_array_bytes = ((float)(c9 - c8) / CLOCKS_PER_SEC) * 1000;

    return times;
}

void print_comparation(Times t1, Times t2)
{
    printf("Serialize byte                 | % 8.2f | % 8.2f | % 5.2f\n",
        t1.s_byte,        t2.s_byte,        t1.s_byte / t2.s_byte);
    printf("Serialize bytes (2,4,8)        | % 8.2f | % 8.2f | % 5.2f\n",
        t1.s_bytes,       t2.s_bytes,       t1.s_bytes/ t2.s_bytes);
    printf("Serialize array byte           | % 8.2f | % 8.2f | % 5.2f\n",
        t1.s_array_byte,  t2.s_array_byte,  t1.s_array_byte / t2.s_array_byte);
    printf("Serialize array bytes (2,4,8)  | % 8.2f | % 8.2f | % 5.2f\n",
        t1.s_array_bytes, t2.s_array_bytes, t1.s_array_bytes / t2.s_array_bytes);
    printf("Deserialize byte               | % 8.2f | % 8.2f | % 5.2f\n",
        t1.d_byte,        t2.d_byte,        t1.d_byte / t2.d_byte);
    printf("Deserialize bytes (2,4,8)      | % 8.2f | % 8.2f | % 5.2f\n",
        t1.d_bytes,       t2.d_bytes,       t1.d_bytes / t2.d_bytes);
    printf("Deserialize array byte         | % 8.2f | % 8.2f | % 5.2f\n",
        t1.d_array_byte,  t2.d_array_byte,  t1.d_array_byte / t2.d_array_byte);
    printf("Deserialize array bytes (2,4,8)| % 8.2f | % 8.2f | % 5.2f\n",
        t1.d_array_bytes, t2.d_array_bytes, t1.d_array_bytes / t2.d_array_bytes);
}
