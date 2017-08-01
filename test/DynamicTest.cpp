#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cstring>

#include <gtest/gtest.h>

extern "C"
{
#include <microcdr/microCdr.h>
}

const signed char octet_t = 32;
const char char_t = 'Z';

const uint16_t ushort_t = 65500;
const int16_t short_t = -32700;
const uint32_t ulong_t = 4294967200;
const int32_t long_t = -2147483600;

const uint64_t ulonglong_t = 18446744073709551600u;
const int64_t longlong_t = -9223372036800;

const unsigned long long ulonglonglong_t = (uint64_t) 18446744073709551600u;
const long long longlonglong_t = (int64_t) - 9223372036800;

const float float_tt = FLT_MIN;
const double double_tt = DBL_MIN;
const long double longdouble_t = DBL_MIN;

//TODO bool
//static const bool bool_t = true;

const char* string_t = "Hola a todos, esto es un test";
const char* emptystring_t = "";

const unsigned char octet_array_t[5] = { 1, 2, 3, 4, 5 };
const char char_array_t[5] = { 'A', 'B', 'C', 'D', 'E' };

const uint16_t ushort_array_t[5] = { 65500, 65501, 65502, 65503, 65504 };
const int16_t short_array_t[5] = { -32700, -32701, -32702, -32703, -32704 };

const uint32_t ulong_array_t[5] = { 4294967200, 4294967201, 4294967202, 4294967203, 4294967204 };
const int32_t long_array_t[5] = { -2147483600, -2147483601, -2147483602, -2147483603, -2147483604 };

const uint64_t ulonglong_array_t[5] = { (uint64_t) 18446744073709551600u, (uint64_t) 18446744073709551601u, (uint64_t) 18446744073709551602u, (uint64_t) 18446744073709551603u, (uint64_t) 18446744073709551604u };
const int64_t longlong_array_t[5] = { (int64_t) - 9223372036800, (int64_t) - 9223372036801, (int64_t) - 9223372036802, (int64_t) - 9223372036803, (int64_t) - 9223372036804 };

const unsigned long long ulonglonglong_array_t[5] = { 18446744073709551600u, 18446744073709551601u, 18446744073709551602u, 18446744073709551603u, 18446744073709551604u };
const long long longlonglong_array_t[5] = { -9223372036800, -9223372036801, -9223372036802, -9223372036803, -9223372036804 };

const float float_array_t[5] = { float_tt, float_tt + 1, float_tt + 2, float_tt + 3, float_tt + 4 };
const double double_array_t[5] = { double_tt, double_tt + 1, double_tt + 2, double_tt + 3, double_tt + 4 };
const long double longdouble_array_t[5] = { longdouble_t, longdouble_t + 1, longdouble_t + 2, longdouble_t + 3, longdouble_t + 4 };

//TODO bool
//static const std::array<bool, 5> bool_array_t = {{true, false, true, false, true}};
//static const bool bool_array_2_t[5] = {false, true, false, true, false};

// Added because error 336.
const unsigned char octet_seq_t[5] = { 5, 4, 3, 2, 1 };
const char char_seq_t[5] = { 'E', 'D', 'C', 'B', 'A' };
const uint16_t ushort_seq_t[5] = { 65504, 65503, 65502, 65501, 65500 };
const int16_t short_seq_t[5] = { -32704, -32703, -32702, -32701, -32700 };
const uint32_t ulong_seq_t[5] = { 4294967204, 4294967203, 4294967202, 4294967201, 4294967200 };
const int32_t long_seq_t[5] = { -2147483604, -2147483603, -2147483602, -2147483601, -2147483600 };

const uint64_t ulonglong_seq_t[5] = { (uint64_t) 18446744073709551604u, (uint64_t) 18446744073709551603u, (uint64_t) 18446744073709551602u, (uint64_t) 18446744073709551601u, (uint64_t) 18446744073709551600u };
const int64_t longlong_seq_t[5] = { (int64_t) - 9223372036804, (int64_t) - 9223372036803, (int64_t) - 9223372036802, (int64_t) - 9223372036801, (int64_t) - 9223372036800 };

const unsigned long long ulonglonglong_seq_t[5] = { 18446744073709551600u, 18446744073709551601u, 18446744073709551602u, 18446744073709551603u, 18446744073709551604u };
const long long longlonglong_seq_t[5] = { -9223372036800, -9223372036801, -9223372036802, -9223372036803, -9223372036804 };

const float float_seq_t[5] = { float_tt + 4, float_tt + 3, float_tt + 2, float_tt + 1, float_tt };
const double double_seq_t[5] = { double_tt + 4, double_tt + 3, double_tt + 2, double_tt + 1, double_tt };
const long double longdouble_seq_t[5] = { longdouble_t, longdouble_t + 1, longdouble_t + 2, longdouble_t + 3, longdouble_t + 4 };

//static const bool bool_seq_t[5] = {true, true, false, false, true};

const char* string_seq_t[5] = { "HELLO", "BYE", "GOODBYE", "HOLA", "ADIOS" };
// Added because error 337
const char* c_string_t = "HOLA";

Endianness endianness = LITTLE_ENDIANNESS;

TEST(microCDRDynamicBasicTests, Char)
{
    char char_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeChar(char_t, microCDRWrite);

    // Deserialization.
    deserializeChar(&char_out, microCDRRead);

    EXPECT_EQ(char_out, char_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicTests, SignedChar)
{
    signed char octect_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeSignedChar(octet_t, microCDRWrite);

    // Deserialization.
    deserializeSignedChar(&octect_out, microCDRRead);

    EXPECT_EQ(octect_out, octet_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicTests, Short)
{
    int16_t short_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeShort(short_t, microCDRWrite);

    // Deserialization.
    deserializeShort(&short_out, microCDRRead);

    EXPECT_EQ(short_out, short_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicTests, UnsignedShort)
{
    uint16_t ushort_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedShort(ushort_t, microCDRWrite);

    // Deserialization.
    deserializeUnsignedShort(&ushort_out, microCDRRead);

    EXPECT_EQ(ushort_out, ushort_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicTests, Int)
{
    int32_t long_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeInt(long_t, microCDRWrite);

    // Deserialization.
    deserializeInt(&long_out, microCDRRead);

    EXPECT_EQ(long_out, long_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicTests, UnsignedInt)
{
    uint32_t ulong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedInt(ulong_t, microCDRWrite);

    // Deserialization.
    deserializeUnsignedInt(&ulong_out, microCDRRead);

    EXPECT_EQ(ulong_out, ulong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicTests, Long)
{
    int64_t long_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLong(longlong_t, microCDRWrite);

    // Deserialization.
    deserializeLong(&long_out, microCDRRead);

    EXPECT_EQ(long_out, longlong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicTests, uLong)
{
    uint64_t ulong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLong(ulonglong_t, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLong(&ulong_out, microCDRRead);

    EXPECT_EQ(ulong_out, ulonglong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicTests, LongLong)
{
    long long longlong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongLong(longlonglong_t, microCDRWrite);

    // Deserialization.
    deserializeLongLong(&longlong_out, microCDRRead);

    EXPECT_EQ(longlong_out, longlonglong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicTests, uLongLong)
{
    unsigned long long ulonglong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongLong(ulonglonglong_t, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongLong(&ulonglong_out, microCDRRead);

    EXPECT_EQ(ulonglong_out, ulonglonglong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicTests, Float)
{
    float float_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeFloat(float_tt, microCDRWrite);

    // Deserialization.
    deserializeFloat(&float_out, microCDRRead);

    EXPECT_EQ(float_out, float_tt);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicTests, Double)
{
    double double_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeDouble(double_tt, microCDRWrite);

    // Deserialization.
    deserializeDouble(&double_out, microCDRRead);

    EXPECT_EQ(double_out, double_tt);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicTests, LongDouble)
{
    long double longdouble_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongDouble(longdouble_t, microCDRWrite);

    // Deserialization.
    deserializeLongDouble(&longdouble_out, microCDRRead);

    EXPECT_EQ(longdouble_out, longdouble_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicTests, String)
{
    char* string_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    const uint32_t length = (uint32_t)std::strlen(string_t);
    uint32_t length_out;

    // Serialization.
    serializeString(string_t, length, microCDRWrite);

    // Deserialization.
    int8_t result = deserializeString(&string_out, &length_out, microCDRRead);

    EXPECT_EQ(result, 0);
    if(result == 0)
    {
        uint32_t comparative = std::strcmp(string_out, string_t);
        EXPECT_EQ(comparative, 0);
        EXPECT_EQ(length, length_out);
        free(string_out);
    }

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicTests, EmptyString)
{
    char* string_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    const uint32_t length = (uint32_t)std::strlen(emptystring_t);
    uint32_t length_out;

    // Serialization.
    serializeString(emptystring_t, length, microCDRWrite);

    // Deserialization.
    deserializeString(&string_out, &length_out, microCDRRead);

    uint32_t comparative = std::strcmp(string_out, emptystring_t);

    EXPECT_EQ(comparative, 0);
    EXPECT_EQ(length, length_out);
    free(string_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayTests, CharArray)
{
    char* char_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeCharArray(char_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeCharArray(&char_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(char_array_t[i], char_out[i]);
    }
    free(char_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayTests, UnsignedCharArray)
{
    unsigned char* char_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedCharArray(octet_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedCharArray(&char_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(octet_array_t[i], char_out[i]);
    }
    free(char_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayTests, ShortArray)
{
    int16_t* short_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeShortArray(short_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeShortArray(&short_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(short_array_t[i], short_out[i]);
    }
    free(short_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayTests, UnsignedShortArray)
{
    uint16_t* ushort_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedShortArray(ushort_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedShortArray(&ushort_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ushort_array_t[i], ushort_out[i]);
    }
    free(ushort_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayTests, IntArray)
{
    int32_t* int_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeIntArray(long_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeIntArray(&int_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(long_array_t[i], int_out[i]);
    }
    free(int_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayTests, UnsignedIntArray)
{
    uint32_t* uint_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedIntArray(ulong_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedIntArray(&uint_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulong_array_t[i], uint_out[i]);
    }
    free(uint_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayTests, LongArray)
{
    int64_t* long_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongArray(longlong_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeLongArray(&long_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longlong_array_t[i], long_out[i]);
    }
    free(long_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayTests, ULongArray)
{
    uint64_t* ulong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongArray(ulonglong_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongArray(&ulong_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulonglong_array_t[i], ulong_out[i]);
    }
    free(ulong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayTests, LongLongArray)
{
    long long* longlong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongLongArray(longlonglong_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeLongLongArray(&longlong_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longlonglong_array_t[i], longlong_out[i]);
    }
    free(longlong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayTests, ULongLongArray)
{
    unsigned long long* ulonglong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongLongArray(ulonglonglong_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongLongArray(&ulonglong_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulonglonglong_array_t[i], ulonglong_out[i]);
    }
    free(ulonglong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayTests, FloatArray)
{
    float* float_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeFloatArray(float_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeFloatArray(&float_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(float_array_t[i], float_out[i]);
    }
    free(float_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayTests, DoubleArray)
{
    double* double_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeDoubleArray(double_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeDoubleArray(&double_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(double_array_t[i], double_out[i]);
    }

    free(double_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayTests, LongDoubleArray)
{
    long double* longdouble_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongDoubleArray(longdouble_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeLongDoubleArray(&longdouble_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longdouble_array_t[i], longdouble_out[i]);
    }
    free(longdouble_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayTests, StringArray)
{
    char** string_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeStringArray(string_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeStringArray(&string_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
        int32_t length_out_aux = (uint32_t)std::strlen(string_out[i]);
        int32_t comparative_aux = std::strcmp(string_seq_t[i], string_out[i]);
        EXPECT_EQ(length_in_aux, length_out_aux);
        EXPECT_EQ(comparative_aux, 0);
        free(string_out[i]);
    }
    free(string_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesTests, CharSequence)
{
    char* char_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeCharSequence(char_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeCharSequence(&char_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(char_seq_t[i], char_out[i]);
    }

    free(char_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesTests, UnsignedCharSequence)
{
    unsigned char* char_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedCharSequence(octet_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedCharSequence(&char_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(octet_seq_t[i], char_out[i]);
    }

    free(char_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesTests, ShortSequence)
{
    int16_t* short_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeShortSequence(short_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeShortSequence(&short_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(short_seq_t[i], short_out[i]);
    }

    free(short_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesTests, UnsignedShortSequence)
{
    uint16_t* ushort_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedShortSequence(ushort_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedShortSequence(&ushort_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ushort_seq_t[i], ushort_out[i]);
    }

    free(ushort_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesTests, IntSequence)
{
    int32_t* int_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeIntSequence(long_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeIntSequence(&int_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(long_seq_t[i], int_out[i]);
    }

    free(int_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesTests, UnsignedIntSequence)
{
    uint32_t* uint_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedIntSequence(ulong_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedIntSequence(&uint_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulong_seq_t[i], uint_out[i]);
    }

    free(uint_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesTests, LongSequence)
{
    int64_t* long_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongSequence(longlong_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeLongSequence(&long_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longlong_seq_t[i], long_out[i]);
    }

    free(long_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesTests, ULongSequence)
{
    uint64_t* ulong_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongSequence(ulonglong_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongSequence(&ulong_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulonglong_seq_t[i], ulong_out[i]);
    }

    free(ulong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesTests, LongLongSequence)
{
    long long* longlong_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongLongSequence(longlonglong_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeLongLongSequence(&longlong_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longlonglong_seq_t[i], longlong_out[i]);
    }

    free(longlong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesTests, ULongLongSequence)
{
    unsigned long long* ulonglong_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongLongSequence(ulonglonglong_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongLongSequence(&ulonglong_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulonglonglong_seq_t[i], ulonglong_out[i]);
    }

    free(ulonglong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesTests, FloatSequence)
{
    float* float_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeFloatSequence(float_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeFloatSequence(&float_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(float_seq_t[i], float_out[i]);
    }

    free(float_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesTests, DoubleSequence)
{
    double* double_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeDoubleSequence(double_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeDoubleSequence(&double_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(double_seq_t[i], double_out[i]);
    }

    free(double_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesTests, LongDoubleSequence)
{
    long double* longdouble_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongDoubleSequence(longdouble_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeLongDoubleSequence(&longdouble_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longdouble_seq_t[i], longdouble_out[i]);
    }

    free(longdouble_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesTests, StringSequence)
{
    char** string_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeStringSequence(string_seq_t, 5, microCDRWrite);

    uint32_t size_out;

    // Deserialization.
    deserializeStringSequence(&string_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
        int32_t length_out_aux = (uint32_t)std::strlen(string_out[i]);
        int32_t comparative_aux = std::strcmp(string_seq_t[i], string_out[i]);
        EXPECT_EQ(length_in_aux, length_out_aux);
        EXPECT_EQ(comparative_aux, 0);
        free(string_out[i]);
    }
    free(string_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicTests, SimpleVar)
{
    char char_out;
    signed char octect_out;
    int16_t short_out;
    uint16_t ushort_out;
    int32_t long_out;
    uint32_t ulong_out;
    int64_t longlong_out;
    uint64_t ulonglong_out;
    long long longlonglong_out;
    unsigned long long ulonglonglong_out;
    float float_out;
    double double_out;
    long double longdouble_out;
    char* string_out;
    char* string_out_2;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    const uint32_t length = (uint32_t)std::strlen(string_t);
    uint32_t length_out;

    const uint32_t length_2 = (uint32_t)std::strlen(emptystring_t);
    uint32_t length_out_2;

    // Serialization.
    serializeChar(char_t, microCDRWrite);
    serializeSignedChar(octet_t, microCDRWrite);
    serializeShort(short_t, microCDRWrite);
    serializeUnsignedShort(ushort_t, microCDRWrite);
    serializeInt(long_t, microCDRWrite);
    serializeUnsignedInt(ulong_t, microCDRWrite);
    serializeLong(longlong_t, microCDRWrite);
    serializeUnsignedLong(ulonglong_t, microCDRWrite);
    serializeLongLong(longlonglong_t, microCDRWrite);
    serializeUnsignedLongLong(ulonglonglong_t, microCDRWrite);
    serializeFloat(float_tt, microCDRWrite);
    serializeDouble(double_tt, microCDRWrite);
    serializeLongDouble(longdouble_t, microCDRWrite);
    serializeString(string_t, length, microCDRWrite);
    serializeString(emptystring_t, length_2, microCDRWrite);

    // Deserialization.
    deserializeChar(&char_out, microCDRRead);
    deserializeSignedChar(&octect_out, microCDRRead);
    deserializeShort(&short_out, microCDRRead);
    deserializeUnsignedShort(&ushort_out, microCDRRead);
    deserializeInt(&long_out, microCDRRead);
    deserializeUnsignedInt(&ulong_out, microCDRRead);
    deserializeLong(&longlong_out, microCDRRead);
    deserializeUnsignedLong(&ulonglong_out, microCDRRead);
    deserializeLongLong(&longlonglong_out, microCDRRead);
    deserializeUnsignedLongLong(&ulonglonglong_out, microCDRRead);
    deserializeFloat(&float_out, microCDRRead);
    deserializeDouble(&double_out, microCDRRead);
    deserializeLongDouble(&longdouble_out, microCDRRead);
    deserializeString(&string_out, &length_out, microCDRRead);
    deserializeString(&string_out_2, &length_out_2, microCDRRead);

    uint32_t comparative = std::strcmp(string_out, string_t);
    uint32_t comparative_2 = std::strcmp(string_out_2, emptystring_t);

    EXPECT_EQ(char_out, char_t);
    EXPECT_EQ(octect_out, octet_t);
    EXPECT_EQ(short_out, short_t);
    EXPECT_EQ(ushort_out, ushort_t);
    EXPECT_EQ(long_out, long_t);
    EXPECT_EQ(ulong_out, ulong_t);
    EXPECT_EQ(longlong_out, longlong_t);
    EXPECT_EQ(ulonglong_out, ulonglong_t);
    EXPECT_EQ(longlonglong_out, longlonglong_t);
    EXPECT_EQ(ulonglonglong_out, ulonglonglong_t);
    EXPECT_EQ(float_out, float_tt);
    EXPECT_EQ(double_out, double_tt);
    EXPECT_EQ(longdouble_out, longdouble_t);
    EXPECT_EQ(comparative, 0);
    EXPECT_EQ(length, length_out);
    EXPECT_EQ(comparative_2, 0);
    EXPECT_EQ(length_2, length_out_2);

    free(string_out);
    free(string_out_2);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicTests, Arrays)
{
    int32_t i;
    char* char_out;
    unsigned char* uchar_out;
    int16_t* short_out;
    uint16_t* ushort_out;
    int32_t* int_out;
    uint32_t* uint_out;
    int64_t* long_out;
    uint64_t* ulong_out;
    long long* longlong_out;
    unsigned long long* ulonglong_out;
    float* float_out;
    double* double_out;
    long double* longdouble_out;
    char** string_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    int16_t result = 0;

    // Serialization.
    result += serializeCharArray(char_array_t, 5, microCDRWrite);//5
    result += serializeUnsignedCharArray(octet_array_t, 5, microCDRWrite);//5
    result += serializeShortArray(short_array_t, 5, microCDRWrite);//10
    result += serializeUnsignedShortArray(ushort_array_t, 5, microCDRWrite);//10
    result += serializeIntArray(long_array_t, 5, microCDRWrite);//20
    result += serializeUnsignedIntArray(ulong_array_t, 5, microCDRWrite);//20
    result += serializeLongArray(longlong_array_t, 5, microCDRWrite);//20
    result += serializeUnsignedLongArray(ulonglong_array_t, 5, microCDRWrite);//20
    result += serializeLongLongArray(longlonglong_array_t, 5, microCDRWrite);//20
    result += serializeUnsignedLongLongArray(ulonglonglong_array_t, 5, microCDRWrite);//20
    result += serializeFloatArray(float_array_t, 5, microCDRWrite);//20
    result += serializeDoubleArray(double_array_t, 5, microCDRWrite);//40
    result += serializeLongDoubleArray(longdouble_array_t, 5, microCDRWrite);//40
    result += serializeStringArray(string_seq_t, 5, microCDRWrite);

    //uint32_t serialized = getSerializedDataLength();

    EXPECT_EQ(result, 0);
    //EXPECT_EQ(serialized, 130);

    if(result == 0)
    {
        // Deserialization.
        result += deserializeCharArray(&char_out, 5, microCDRRead);
        result += deserializeUnsignedCharArray(&uchar_out, 5, microCDRRead);
        result += deserializeShortArray(&short_out, 5, microCDRRead);
        result += deserializeUnsignedShortArray(&ushort_out, 5, microCDRRead);
        result += deserializeIntArray(&int_out, 5, microCDRRead);
        result += deserializeUnsignedIntArray(&uint_out, 5, microCDRRead);
        result += deserializeLongArray(&long_out, 5, microCDRRead);
        result += deserializeUnsignedLongArray(&ulong_out, 5, microCDRRead);
        result += deserializeLongLongArray(&longlong_out, 5, microCDRRead);
        result += deserializeUnsignedLongLongArray(&ulonglong_out, 5, microCDRRead);
        result += deserializeFloatArray(&float_out, 5, microCDRRead);
        result += deserializeDoubleArray(&double_out, 5, microCDRRead);
        result += deserializeLongDoubleArray(&longdouble_out, 5, microCDRRead);
        result += deserializeStringArray(&string_out, 5, microCDRRead);

        EXPECT_EQ(result, 0);

        if(result == 0)
        {
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(char_array_t[i], char_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(octet_array_t[i], uchar_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(short_array_t[i], short_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ushort_array_t[i], ushort_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(long_array_t[i], int_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulong_array_t[i], uint_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlong_array_t[i], long_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglong_array_t[i], ulong_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlonglong_array_t[i], longlong_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglonglong_array_t[i], ulonglong_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(float_array_t[i], float_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(double_array_t[i], double_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longdouble_array_t[i], longdouble_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
                int32_t length_out_aux = (uint32_t)std::strlen(string_out[i]);
                int32_t comparative_aux = std::strcmp(string_seq_t[i], string_out[i]);
                EXPECT_EQ(length_in_aux, length_out_aux);
                EXPECT_EQ(comparative_aux, 0);
                free(string_out[i]);
            }

            free(char_out);
            free(uchar_out);
            free(short_out);
            free(ushort_out);
            free(int_out);
            free(uint_out);
            free(long_out);
            free(ulong_out);
            free(longlong_out);
            free(ulonglong_out);
            free(float_out);
            free(double_out);
            free(longdouble_out);
            free(string_out);

            destroyBuffer(microBuffer);
            free(microCDRWrite);
            free(microCDRRead);
        }
    }
}

TEST(microCDRDynamicTests, Sequences)
{
    int32_t i;
    char* char_out;
    uint32_t char_out_size;
    unsigned char* uchar_out;
    uint32_t uchar_out_size;
    int16_t* short_out;
    uint32_t short_out_size;
    uint16_t* ushort_out;
    uint32_t ushort_out_size;
    int32_t* int_out;
    uint32_t int_out_size;
    uint32_t* uint_out;
    uint32_t uint_out_size;
    int64_t* long_out;
    uint32_t long_out_size;
    uint64_t* ulong_out;
    uint32_t ulong_out_size;
    long long* longlong_out;
    uint32_t longlong_out_size;
    unsigned long long* ulonglong_out;
    uint32_t ulonglong_out_size;
    float* float_out;
    uint32_t float_out_size;
    double* double_out;
    uint32_t double_out_size;
    long double* longdouble_out;
    uint32_t longdouble_out_size;
    char** string_out;
    uint32_t string_out_size;

    int16_t result = 0;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    result += serializeCharSequence(char_seq_t, 5, microCDRWrite);//9
    result += serializeUnsignedCharSequence(octet_seq_t, 5, microCDRWrite);//9
    result += serializeShortSequence(short_seq_t, 5, microCDRWrite);//14
    result += serializeUnsignedShortSequence(ushort_seq_t, 5, microCDRWrite);//14
    result += serializeIntSequence(long_seq_t, 5, microCDRWrite);//24
    result += serializeUnsignedIntSequence(ulong_seq_t, 5, microCDRWrite);//24
    result += serializeLongSequence(longlong_seq_t, 5, microCDRWrite);//24
    result += serializeUnsignedLongSequence(ulonglong_seq_t, 5, microCDRWrite);//24
    result += serializeLongLongSequence(longlonglong_seq_t, 5, microCDRWrite);//24
    result += serializeUnsignedLongLongSequence(ulonglonglong_seq_t, 5, microCDRWrite);//24
    result += serializeFloatSequence(float_seq_t, 5, microCDRWrite);//24
    result += serializeDoubleSequence(double_seq_t, 5, microCDRWrite);//44
    result += serializeLongDoubleSequence(longdouble_seq_t, 5, microCDRWrite);//44
    result += serializeStringSequence(string_seq_t, 5, microCDRWrite);

    //uint32_t serialized = getSerializedDataLength();
    //EXPECT_EQ(serialized, 162);

    EXPECT_EQ(result, 0);

    if(result == 0)
    {
        // Deserialization.
        result += deserializeCharSequence(&char_out, &char_out_size, microCDRRead);
        result += deserializeUnsignedCharSequence(&uchar_out, &uchar_out_size, microCDRRead);
        result += deserializeShortSequence(&short_out, &short_out_size, microCDRRead);
        result += deserializeUnsignedShortSequence(&ushort_out, &ushort_out_size, microCDRRead);
        result += deserializeIntSequence(&int_out, &int_out_size, microCDRRead);
        result += deserializeUnsignedIntSequence(&uint_out, &uint_out_size, microCDRRead);
        result += deserializeLongSequence(&long_out, &long_out_size, microCDRRead);
        result += deserializeUnsignedLongSequence(&ulong_out, &ulong_out_size, microCDRRead);
        result += deserializeLongLongSequence(&longlong_out, &longlong_out_size, microCDRRead);
        result += deserializeUnsignedLongLongSequence(&ulonglong_out, &ulonglong_out_size, microCDRRead);
        result += deserializeFloatSequence(&float_out, &float_out_size, microCDRRead);
        result += deserializeDoubleSequence(&double_out, &double_out_size, microCDRRead);
        result += deserializeLongDoubleSequence(&longdouble_out, &longdouble_out_size, microCDRRead);
        result += deserializeStringSequence(&string_out, &string_out_size, microCDRRead);

        EXPECT_EQ(result, 0);

        if(result == 0)
        {
            EXPECT_EQ(char_out_size, 5);
            EXPECT_EQ(uchar_out_size, 5);
            EXPECT_EQ(short_out_size, 5);
            EXPECT_EQ(ushort_out_size, 5);
            EXPECT_EQ(int_out_size, 5);
            EXPECT_EQ(uint_out_size, 5);
            EXPECT_EQ(long_out_size, 5);
            EXPECT_EQ(ulong_out_size, 5);
            EXPECT_EQ(longlong_out_size, 5);
            EXPECT_EQ(ulonglong_out_size, 5);
            EXPECT_EQ(float_out_size, 5);
            EXPECT_EQ(double_out_size, 5);
            EXPECT_EQ(longdouble_out_size, 5);
            EXPECT_EQ(string_out_size, 5);

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(char_seq_t[i], char_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(octet_seq_t[i], uchar_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(short_seq_t[i], short_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ushort_seq_t[i], ushort_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(long_seq_t[i], int_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulong_seq_t[i], uint_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlong_seq_t[i], long_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglong_seq_t[i], ulong_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlonglong_seq_t[i], longlong_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglonglong_seq_t[i], ulonglong_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(float_seq_t[i], float_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(double_seq_t[i], double_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longdouble_seq_t[i], longdouble_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
                int32_t length_out_aux = (uint32_t)std::strlen(string_out[i]);
                int32_t comparative_aux = std::strcmp(string_seq_t[i], string_out[i]);
                EXPECT_EQ(length_in_aux, length_out_aux);
                EXPECT_EQ(comparative_aux, 0);
                free(string_out[i]);
            }

            free(char_out);
            free(uchar_out);
            free(short_out);
            free(ushort_out);
            free(int_out);
            free(uint_out);
            free(long_out);
            free(ulong_out);
            free(longlong_out);
            free(ulonglong_out);
            free(float_out);
            free(double_out);
            free(longdouble_out);
            free(string_out);

            destroyBuffer(microBuffer);
            free(microCDRWrite);
            free(microCDRRead);
        }
    }
}

TEST(microCDRDynamicTests, All)
{
    //SIMPLE
    char char_out;
    signed char octect_out;
    int16_t short_out;
    uint16_t ushort_out;
    int32_t long_out;
    uint32_t ulong_out;
    int64_t longlong_out;
    uint64_t ulonglong_out;
    long long longlonglong_out;
    unsigned long long ulonglonglong_out;
    float float_out;
    double double_out;
    long double longdouble_out;
    char* string_out;
    char* string_out_2;

    //ARRAYS
    int32_t i;
    char* char_array_out;
    unsigned char* uchar_array_out;
    int16_t* short_array_out;
    uint16_t* ushort_array_out;
    int32_t* int_array_out;
    uint32_t* uint_array_out;
    int64_t* long_array_out;
    uint64_t* ulong_array_out;
    long long* longlong_array_out;
    unsigned long long* ulonglong_array_out;
    float* float_array_out;
    double* double_array_out;
    long double* longdouble_array_out;
    char** string_array_out;

    //SEQUENCES
    char* char_seq_out;
    uint32_t char_out_size;
    unsigned char* uchar_seq_out;
    uint32_t uchar_out_size;
    int16_t* short_seq_out;
    uint32_t short_out_size;
    uint16_t* ushort_seq_out;
    uint32_t ushort_out_size;
    int32_t* int_seq_out;
    uint32_t int_out_size;
    uint32_t* uint_seq_out;
    uint32_t uint_out_size;
    int64_t* long_seq_out;
    uint32_t long_out_size;
    uint64_t* ulong_seq_out;
    uint32_t ulong_out_size;
    long long* longlong_seq_out;
    uint32_t longlong_out_size;
    unsigned long long* ulonglong_seq_out;
    uint32_t ulonglong_out_size;
    float* float_seq_out;
    uint32_t float_out_size;
    double* double_seq_out;
    uint32_t double_out_size;
    long double* longdouble_seq_out;
    uint32_t longdouble_out_size;
    char** string_seq_out;
    uint32_t string_out_size;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    const uint32_t length = (uint32_t)std::strlen(string_t);
    uint32_t length_out;

    int16_t result = 0;

    const uint32_t length_2 = (uint32_t)std::strlen(emptystring_t);
    uint32_t length_out_2;

    // Serialization.
    result += serializeChar(char_t, microCDRWrite);
    result += serializeSignedChar(octet_t, microCDRWrite);
    result += serializeShort(short_t, microCDRWrite);
    result += serializeUnsignedShort(ushort_t, microCDRWrite);
    result += serializeInt(long_t, microCDRWrite);
    result += serializeUnsignedInt(ulong_t, microCDRWrite);
    result += serializeLong(longlong_t, microCDRWrite);
    result += serializeUnsignedLong(ulonglong_t, microCDRWrite);
    result += serializeLongLong(longlonglong_t, microCDRWrite);
    result += serializeUnsignedLongLong(ulonglonglong_t, microCDRWrite);
    result += serializeFloat(float_tt, microCDRWrite);
    result += serializeDouble(double_tt, microCDRWrite);
    result += serializeLongDouble(longdouble_t, microCDRWrite);
    result += serializeString(string_t, length, microCDRWrite);
    result += serializeString(emptystring_t, length_2, microCDRWrite);

    result += serializeCharArray(char_array_t, 5, microCDRWrite);//5
    result += serializeUnsignedCharArray(octet_array_t, 5, microCDRWrite);//5
    result += serializeShortArray(short_array_t, 5, microCDRWrite);//10
    result += serializeUnsignedShortArray(ushort_array_t, 5, microCDRWrite);//10
    result += serializeIntArray(long_array_t, 5, microCDRWrite);//20
    result += serializeUnsignedIntArray(ulong_array_t, 5, microCDRWrite);//20

    result += serializeLongArray(longlong_array_t, 5, microCDRWrite);
    result += serializeUnsignedLongArray(ulonglong_array_t, 5, microCDRWrite);
    result += serializeLongLongArray(longlonglong_array_t, 5, microCDRWrite);
    result += serializeUnsignedLongLongArray(ulonglonglong_array_t, 5, microCDRWrite);

    result += serializeFloatArray(float_array_t, 5, microCDRWrite);//20
    result += serializeDoubleArray(double_array_t, 5, microCDRWrite);//40
    result += serializeLongDoubleArray(longdouble_array_t, 5, microCDRWrite);
    result += serializeStringArray(string_seq_t, 5, microCDRWrite);

    result += serializeCharSequence(char_seq_t, 5, microCDRWrite);//9
    result += serializeUnsignedCharSequence(octet_seq_t, 5, microCDRWrite);//9
    result += serializeShortSequence(short_seq_t, 5, microCDRWrite);//14
    result += serializeUnsignedShortSequence(ushort_seq_t, 5, microCDRWrite);//14
    result += serializeIntSequence(long_seq_t, 5, microCDRWrite);//24
    result += serializeUnsignedIntSequence(ulong_seq_t, 5, microCDRWrite);//24

    result += serializeLongSequence(longlong_seq_t, 5, microCDRWrite);
    result += serializeUnsignedLongSequence(ulonglong_seq_t, 5, microCDRWrite);
    result += serializeLongLongSequence(longlonglong_seq_t, 5, microCDRWrite);
    result += serializeUnsignedLongLongSequence(ulonglonglong_seq_t, 5, microCDRWrite);

    result += serializeFloatSequence(float_seq_t, 5, microCDRWrite);//24
    result += serializeDoubleSequence(double_seq_t, 5, microCDRWrite);//44
    result += serializeLongDoubleSequence(longdouble_seq_t, 5, microCDRWrite);//44
    result += serializeStringSequence(string_seq_t, 5, microCDRWrite);

    //uint32_t serialized = getSerializedDataLength();
    //EXPECT_EQ(serialized, 357);
    EXPECT_EQ(result, 0);

    if(result == 0)
    {
        // Deserialization.
        result += deserializeChar(&char_out, microCDRRead);
        result += deserializeSignedChar(&octect_out, microCDRRead);
        result += deserializeShort(&short_out, microCDRRead);
        result += deserializeUnsignedShort(&ushort_out, microCDRRead);
        result += deserializeInt(&long_out, microCDRRead);
        result += deserializeUnsignedInt(&ulong_out, microCDRRead);
        result += deserializeLong(&longlong_out, microCDRRead);
        result += deserializeUnsignedLong(&ulonglong_out, microCDRRead);
        result += deserializeLongLong(&longlonglong_out, microCDRRead);
        result += deserializeUnsignedLongLong(&ulonglonglong_out, microCDRRead);
        result += deserializeFloat(&float_out, microCDRRead);
        result += deserializeDouble(&double_out, microCDRRead);
        result += deserializeLongDouble(&longdouble_out, microCDRRead);
        result += deserializeString(&string_out, &length_out, microCDRRead);
        result += deserializeString(&string_out_2, &length_out_2, microCDRRead);

        result += deserializeCharArray(&char_array_out, 5, microCDRRead);
        result += deserializeUnsignedCharArray(&uchar_array_out, 5, microCDRRead);
        result += deserializeShortArray(&short_array_out, 5, microCDRRead);
        result += deserializeUnsignedShortArray(&ushort_array_out, 5, microCDRRead);
        result += deserializeIntArray(&int_array_out, 5, microCDRRead);
        result += deserializeUnsignedIntArray(&uint_array_out, 5, microCDRRead);

        result += deserializeLongArray(&long_array_out, 5, microCDRRead);
        result += deserializeUnsignedLongArray(&ulong_array_out, 5, microCDRRead);
        result += deserializeLongLongArray(&longlong_array_out, 5, microCDRRead);
        result += deserializeUnsignedLongLongArray(&ulonglong_array_out, 5, microCDRRead);

        result += deserializeFloatArray(&float_array_out, 5, microCDRRead);
        result += deserializeDoubleArray(&double_array_out, 5, microCDRRead);
        result += deserializeLongDoubleArray(&longdouble_array_out, 5, microCDRRead);
        result += deserializeStringArray(&string_array_out, 5, microCDRRead);

        result += deserializeCharSequence(&char_seq_out, &char_out_size, microCDRRead);
        result += deserializeUnsignedCharSequence(&uchar_seq_out, &uchar_out_size, microCDRRead);
        result += deserializeShortSequence(&short_seq_out, &short_out_size, microCDRRead);
        result += deserializeUnsignedShortSequence(&ushort_seq_out, &ushort_out_size, microCDRRead);
        result += deserializeIntSequence(&int_seq_out, &int_out_size, microCDRRead);
        result += deserializeUnsignedIntSequence(&uint_seq_out, &uint_out_size, microCDRRead);

        result += deserializeLongSequence(&long_seq_out, &long_out_size, microCDRRead);
        result += deserializeUnsignedLongSequence(&ulong_seq_out, &ulong_out_size, microCDRRead);
        result += deserializeLongLongSequence(&longlong_seq_out, &longlong_out_size, microCDRRead);
        result += deserializeUnsignedLongLongSequence(&ulonglong_seq_out, &ulonglong_out_size, microCDRRead);

        result += deserializeFloatSequence(&float_seq_out, &float_out_size, microCDRRead);
        result += deserializeDoubleSequence(&double_seq_out, &double_out_size, microCDRRead);
        result += deserializeLongDoubleSequence(&longdouble_seq_out, &longdouble_out_size, microCDRRead);
        result += deserializeStringSequence(&string_seq_out, &string_out_size, microCDRRead);

        EXPECT_EQ(result, 0);

        if(result == 0)
        {
            uint32_t comparative = (uint32_t)std::strcmp(string_out, string_t);
            uint32_t comparative_2 = (uint32_t)std::strcmp(string_out_2, emptystring_t);

            EXPECT_EQ(char_out, char_t);
            EXPECT_EQ(octect_out, octet_t);
            EXPECT_EQ(short_out, short_t);
            EXPECT_EQ(ushort_out, ushort_t);
            EXPECT_EQ(long_out, long_t);
            EXPECT_EQ(ulong_out, ulong_t);
            EXPECT_EQ(longlong_out, longlong_t);
            EXPECT_EQ(ulonglong_out, ulonglong_t);
            EXPECT_EQ(longlonglong_out, longlonglong_t);
            EXPECT_EQ(ulonglonglong_out, ulonglonglong_t);
            EXPECT_EQ(float_out, float_tt);
            EXPECT_EQ(double_out, double_tt);
            EXPECT_EQ(longdouble_out, longdouble_t);
            EXPECT_EQ(comparative, 0);
            EXPECT_EQ(length, length_out);
            EXPECT_EQ(comparative_2, 0);
            EXPECT_EQ(length_2, length_out_2);

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(char_array_t[i], char_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(octet_array_t[i], uchar_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(short_array_t[i], short_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ushort_array_t[i], ushort_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(long_array_t[i], int_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulong_array_t[i], uint_array_out[i]);
            }

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlong_array_t[i], long_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglong_array_t[i], ulong_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlonglong_array_t[i], longlong_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglonglong_array_t[i], ulonglong_array_out[i]);
            }

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(float_array_t[i], float_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(double_array_t[i], double_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longdouble_array_t[i], longdouble_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
                int32_t length_out_aux = (uint32_t)std::strlen(string_array_out[i]);
                int32_t comparative_aux = std::strcmp(string_seq_t[i], string_array_out[i]);
                EXPECT_EQ(length_in_aux, length_out_aux);
                EXPECT_EQ(comparative_aux, 0);
                free(string_array_out[i]);
            }
            free(string_array_out);

            EXPECT_EQ(char_out_size, 5);
            EXPECT_EQ(uchar_out_size, 5);
            EXPECT_EQ(short_out_size, 5);
            EXPECT_EQ(ushort_out_size, 5);
            EXPECT_EQ(int_out_size, 5);
            EXPECT_EQ(uint_out_size, 5);

            EXPECT_EQ(long_out_size, 5);
            EXPECT_EQ(ulong_out_size, 5);
            EXPECT_EQ(longlong_out_size, 5);
            EXPECT_EQ(ulonglong_out_size, 5);

            EXPECT_EQ(float_out_size, 5);
            EXPECT_EQ(double_out_size, 5);
            EXPECT_EQ(longdouble_out_size, 5);
            EXPECT_EQ(string_out_size, 5);

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(char_seq_t[i], char_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(octet_seq_t[i], uchar_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(short_seq_t[i], short_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ushort_seq_t[i], ushort_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(long_seq_t[i], int_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulong_seq_t[i], uint_seq_out[i]);
            }

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlong_seq_t[i], long_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglong_seq_t[i], ulong_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlonglong_seq_t[i], longlong_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglonglong_seq_t[i], ulonglong_seq_out[i]);
            }

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(float_seq_t[i], float_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(double_seq_t[i], double_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longdouble_seq_t[i], longdouble_seq_out[i]);
            }

            for(i = 0; i < 5; i++)
            {
                int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
                int32_t length_out_aux = (uint32_t)std::strlen(string_seq_out[i]);
                int32_t comparative_aux = std::strcmp(string_seq_t[i], string_seq_out[i]);
                EXPECT_EQ(length_in_aux, length_out_aux);
                EXPECT_EQ(comparative_aux, 0);
                free(string_seq_out[i]);
            }
            free(string_seq_out);

            free(char_array_out);
            free(uchar_array_out);
            free(short_array_out);
            free(ushort_array_out);
            free(int_array_out);
            free(uint_array_out);

            free(long_array_out);
            free(ulong_array_out);
            free(longlong_array_out);
            free(ulonglong_array_out);

            free(float_array_out);
            free(double_array_out);
            free(longdouble_array_out);

            free(char_seq_out);
            free(uchar_seq_out);
            free(short_seq_out);
            free(ushort_seq_out);
            free(int_seq_out);
            free(uint_seq_out);

            free(long_seq_out);
            free(ulong_seq_out);
            free(longlong_seq_out);
            free(ulonglong_seq_out);

            free(float_seq_out);
            free(double_seq_out);
            free(longdouble_seq_out);

            free(string_out);
            free(string_out_2);

            destroyBuffer(microBuffer);
            free(microCDRWrite);
            free(microCDRRead);
        }
    }
}

TEST(microCDRDynamicTests, AllEndianness)
{
    //SIMPLE
    char char_out;
    signed char octect_out;
    int16_t short_out;
    uint16_t ushort_out;
    int32_t long_out;
    uint32_t ulong_out;
    int64_t longlong_out;
    uint64_t ulonglong_out;
    long long longlonglong_out;
    unsigned long long ulonglonglong_out;
    float float_out;
    double double_out;
    long double longdouble_out;
    char* string_out;
    char* string_out_2;

    //ARRAYS
    int32_t i;
    char* char_array_out;
    unsigned char* uchar_array_out;
    int16_t* short_array_out;
    uint16_t* ushort_array_out;
    int32_t* int_array_out;
    uint32_t* uint_array_out;
    int64_t* long_array_out;
    uint64_t* ulong_array_out;
    long long* longlong_array_out;
    unsigned long long* ulonglong_array_out;
    float* float_array_out;
    double* double_array_out;
    long double* longdouble_array_out;
    char** string_array_out;

    //SEQUENCES
    char* char_seq_out;
    uint32_t char_out_size;
    unsigned char* uchar_seq_out;
    uint32_t uchar_out_size;
    int16_t* short_seq_out;
    uint32_t short_out_size;
    uint16_t* ushort_seq_out;
    uint32_t ushort_out_size;
    int32_t* int_seq_out;
    uint32_t int_out_size;
    uint32_t* uint_seq_out;
    uint32_t uint_out_size;
    int64_t* long_seq_out;
    uint32_t long_out_size;
    uint64_t* ulong_seq_out;
    uint32_t ulong_out_size;
    long long* longlong_seq_out;
    uint32_t longlong_out_size;
    unsigned long long* ulonglong_seq_out;
    uint32_t ulonglong_out_size;
    float* float_seq_out;
    uint32_t float_out_size;
    double* double_seq_out;
    uint32_t double_out_size;
    long double* longdouble_seq_out;
    uint32_t longdouble_out_size;
    char** string_seq_out;
    uint32_t string_out_size;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    const uint32_t length = (uint32_t)std::strlen(string_t);
    uint32_t length_out;

    int16_t result = 0;

    const uint32_t length_2 = (uint32_t)std::strlen(emptystring_t);
    uint32_t length_out_2;

    // Serialization.
    result += serializeChar(char_t, microCDRWrite);
    result += serializeSignedChar(octet_t, microCDRWrite);
    result += serializeShortEndianness(short_t, endianness, microCDRWrite);
    result += serializeUnsignedShortEndianness(ushort_t, endianness, microCDRWrite);
    result += serializeIntEndianness(long_t, endianness, microCDRWrite);
    result += serializeUnsignedIntEndianness(ulong_t, endianness, microCDRWrite);
    result += serializeLongEndianness(longlong_t, endianness, microCDRWrite);
    result += serializeUnsignedLongEndianness(ulonglong_t, endianness, microCDRWrite);
    result += serializeLongLongEndianness(longlonglong_t, endianness, microCDRWrite);
    result += serializeUnsignedLongLongEndianness(ulonglonglong_t, endianness, microCDRWrite);
    result += serializeFloatEndianness(float_tt, endianness, microCDRWrite);
    result += serializeDoubleEndianness(double_tt, endianness, microCDRWrite);
    result += serializeLongDoubleEndianness(longdouble_t, endianness, microCDRWrite);
    result += serializeStringEndianness(string_t, length, endianness, microCDRWrite);
    result += serializeStringEndianness(emptystring_t, length_2, endianness, microCDRWrite);

    result += serializeCharArray(char_array_t, 5, microCDRWrite);//5
    result += serializeUnsignedCharArray(octet_array_t, 5, microCDRWrite);//5
    result += serializeShortArrayEndianness(short_array_t, 5, endianness, microCDRWrite);//10
    result += serializeUnsignedShortArrayEndianness(ushort_array_t, 5, endianness, microCDRWrite);//10
    result += serializeIntArrayEndianness(long_array_t, 5, endianness, microCDRWrite);//20
    result += serializeUnsignedIntArrayEndianness(ulong_array_t, 5, endianness, microCDRWrite);//20

    result += serializeLongArrayEndianness(longlong_array_t, 5, endianness, microCDRWrite);
    result += serializeUnsignedLongArrayEndianness(ulonglong_array_t, 5, endianness, microCDRWrite);
    result += serializeLongLongArrayEndianness(longlonglong_array_t, 5, endianness, microCDRWrite);
    result += serializeUnsignedLongLongArrayEndianness(ulonglonglong_array_t, 5, endianness, microCDRWrite);

    result += serializeFloatArrayEndianness(float_array_t, 5, endianness, microCDRWrite);//20
    result += serializeDoubleArrayEndianness(double_array_t, 5, endianness, microCDRWrite);//40
    result += serializeLongDoubleArrayEndianness(longdouble_array_t, 5, endianness, microCDRWrite);
    result += serializeStringArrayEndianness(string_seq_t, 5, endianness, microCDRWrite);

    result += serializeCharSequenceEndianness(char_seq_t, 5, endianness, microCDRWrite);//9
    result += serializeUnsignedCharSequenceEndianness(octet_seq_t, 5, endianness, microCDRWrite);//9
    result += serializeShortSequenceEndianness(short_seq_t, 5, endianness, microCDRWrite);//14
    result += serializeUnsignedShortSequenceEndianness(ushort_seq_t, 5, endianness, microCDRWrite);//14
    result += serializeIntSequenceEndianness(long_seq_t, 5, endianness, microCDRWrite);//24
    result += serializeUnsignedIntSequenceEndianness(ulong_seq_t, 5, endianness, microCDRWrite);//24

    result += serializeLongSequenceEndianness(longlong_seq_t, 5, endianness, microCDRWrite);
    result += serializeUnsignedLongSequenceEndianness(ulonglong_seq_t, 5, endianness, microCDRWrite);
    result += serializeLongLongSequenceEndianness(longlonglong_seq_t, 5, endianness, microCDRWrite);
    result += serializeUnsignedLongLongSequenceEndianness(ulonglonglong_seq_t, 5, endianness, microCDRWrite);

    result += serializeFloatSequenceEndianness(float_seq_t, 5, endianness, microCDRWrite);//24
    result += serializeDoubleSequenceEndianness(double_seq_t, 5, endianness, microCDRWrite);//44
    result += serializeLongDoubleSequenceEndianness(longdouble_seq_t, 5, endianness, microCDRWrite);//44
    result += serializeStringSequenceEndianness(string_seq_t, 5, endianness, microCDRWrite);

    //uint32_t serialized = getSerializedDataLength();
    //EXPECT_EQ(serialized, 357);
    EXPECT_EQ(result, 0);

    if(result == 0)
    {
        // Deserialization.
        result += deserializeChar(&char_out, microCDRRead);
        result += deserializeSignedChar(&octect_out, microCDRRead);
        result += deserializeShortEndianness(&short_out, endianness, microCDRRead);
        result += deserializeUnsignedShortEndianness(&ushort_out, endianness, microCDRRead);
        result += deserializeIntEndianness(&long_out, endianness, microCDRRead);
        result += deserializeUnsignedIntEndianness(&ulong_out, endianness, microCDRRead);
        result += deserializeLongEndianness(&longlong_out, endianness, microCDRRead);
        result += deserializeUnsignedLongEndianness(&ulonglong_out, endianness, microCDRRead);
        result += deserializeLongLongEndianness(&longlonglong_out, endianness, microCDRRead);
        result += deserializeUnsignedLongLongEndianness(&ulonglonglong_out, endianness, microCDRRead);
        result += deserializeFloatEndianness(&float_out, endianness, microCDRRead);
        result += deserializeDoubleEndianness(&double_out, endianness, microCDRRead);
        result += deserializeLongDoubleEndianness(&longdouble_out, endianness, microCDRRead);
        result += deserializeStringEndianness(&string_out, &length_out, endianness, microCDRRead);
        result += deserializeStringEndianness(&string_out_2, &length_out_2, endianness, microCDRRead);

        result += deserializeCharArray(&char_array_out, 5, microCDRRead);
        result += deserializeUnsignedCharArray(&uchar_array_out, 5, microCDRRead);
        result += deserializeShortArrayEndianness(&short_array_out, 5, endianness, microCDRRead);
        result += deserializeUnsignedShortArrayEndianness(&ushort_array_out, 5, endianness, microCDRRead);
        result += deserializeIntArrayEndianness(&int_array_out, 5, endianness, microCDRRead);
        result += deserializeUnsignedIntArrayEndianness(&uint_array_out, 5, endianness, microCDRRead);

        result += deserializeLongArrayEndianness(&long_array_out, 5, endianness, microCDRRead);
        result += deserializeUnsignedLongArrayEndianness(&ulong_array_out, 5, endianness, microCDRRead);
        result += deserializeLongLongArrayEndianness(&longlong_array_out, 5, endianness, microCDRRead);
        result += deserializeUnsignedLongLongArrayEndianness(&ulonglong_array_out, 5, endianness, microCDRRead);

        result += deserializeFloatArrayEndianness(&float_array_out, 5, endianness, microCDRRead);
        result += deserializeDoubleArrayEndianness(&double_array_out, 5, endianness, microCDRRead);
        result += deserializeLongDoubleArrayEndianness(&longdouble_array_out, 5, endianness, microCDRRead);
        result += deserializeStringArrayEndianness(&string_array_out, 5, endianness, microCDRRead);

        result += deserializeCharSequenceEndianness(&char_seq_out, &char_out_size, endianness, microCDRRead);
        result += deserializeUnsignedCharSequenceEndianness(&uchar_seq_out, &uchar_out_size, endianness, microCDRRead);
        result += deserializeShortSequenceEndianness(&short_seq_out, &short_out_size, endianness, microCDRRead);
        result += deserializeUnsignedShortSequenceEndianness(&ushort_seq_out, &ushort_out_size, endianness, microCDRRead);
        result += deserializeIntSequenceEndianness(&int_seq_out, &int_out_size, endianness, microCDRRead);
        result += deserializeUnsignedIntSequenceEndianness(&uint_seq_out, &uint_out_size, endianness, microCDRRead);

        result += deserializeLongSequenceEndianness(&long_seq_out, &long_out_size, endianness, microCDRRead);
        result += deserializeUnsignedLongSequenceEndianness(&ulong_seq_out, &ulong_out_size, endianness, microCDRRead);
        result += deserializeLongLongSequenceEndianness(&longlong_seq_out, &longlong_out_size, endianness, microCDRRead);
        result += deserializeUnsignedLongLongSequenceEndianness(&ulonglong_seq_out, &ulonglong_out_size, endianness, microCDRRead);

        result += deserializeFloatSequenceEndianness(&float_seq_out, &float_out_size, endianness, microCDRRead);
        result += deserializeDoubleSequenceEndianness(&double_seq_out, &double_out_size, endianness, microCDRRead);
        result += deserializeLongDoubleSequenceEndianness(&longdouble_seq_out, &longdouble_out_size, endianness, microCDRRead);
        result += deserializeStringSequenceEndianness(&string_seq_out, &string_out_size, endianness, microCDRRead);

        EXPECT_EQ(result, 0);

        if(result == 0)
        {
            uint32_t comparative = (uint32_t)std::strcmp(string_out, string_t);
            uint32_t comparative_2 = (uint32_t)std::strcmp(string_out_2, emptystring_t);

            EXPECT_EQ(char_out, char_t);
            EXPECT_EQ(octect_out, octet_t);
            EXPECT_EQ(short_out, short_t);
            EXPECT_EQ(ushort_out, ushort_t);
            EXPECT_EQ(long_out, long_t);
            EXPECT_EQ(ulong_out, ulong_t);
            EXPECT_EQ(longlong_out, longlong_t);
            EXPECT_EQ(ulonglong_out, ulonglong_t);
            EXPECT_EQ(longlonglong_out, longlonglong_t);
            EXPECT_EQ(ulonglonglong_out, ulonglonglong_t);
            EXPECT_EQ(float_out, float_tt);
            EXPECT_EQ(double_out, double_tt);
            EXPECT_EQ(longdouble_out, longdouble_t);
            EXPECT_EQ(comparative, 0);
            EXPECT_EQ(length, length_out);
            EXPECT_EQ(comparative_2, 0);
            EXPECT_EQ(length_2, length_out_2);

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(char_array_t[i], char_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(octet_array_t[i], uchar_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(short_array_t[i], short_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ushort_array_t[i], ushort_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(long_array_t[i], int_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulong_array_t[i], uint_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlong_array_t[i], long_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglong_array_t[i], ulong_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlonglong_array_t[i], longlong_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglonglong_array_t[i], ulonglong_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(float_array_t[i], float_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(double_array_t[i], double_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longdouble_array_t[i], longdouble_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
                int32_t length_out_aux = (uint32_t)std::strlen(string_array_out[i]);
                int32_t comparative_aux = std::strcmp(string_seq_t[i], string_array_out[i]);
                EXPECT_EQ(length_in_aux, length_out_aux);
                EXPECT_EQ(comparative_aux, 0);
                free(string_array_out[i]);
            }
            free(string_array_out);

            EXPECT_EQ(char_out_size, 5);
            EXPECT_EQ(uchar_out_size, 5);
            EXPECT_EQ(short_out_size, 5);
            EXPECT_EQ(ushort_out_size, 5);
            EXPECT_EQ(int_out_size, 5);
            EXPECT_EQ(uint_out_size, 5);

            EXPECT_EQ(long_out_size, 5);
            EXPECT_EQ(ulong_out_size, 5);
            EXPECT_EQ(longlong_out_size, 5);
            EXPECT_EQ(ulonglong_out_size, 5);

            EXPECT_EQ(float_out_size, 5);
            EXPECT_EQ(double_out_size, 5);
            EXPECT_EQ(longdouble_out_size, 5);
            EXPECT_EQ(string_out_size, 5);

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(char_seq_t[i], char_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(octet_seq_t[i], uchar_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(short_seq_t[i], short_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ushort_seq_t[i], ushort_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(long_seq_t[i], int_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulong_seq_t[i], uint_seq_out[i]);
            }

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlong_seq_t[i], long_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglong_seq_t[i], ulong_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlonglong_seq_t[i], longlong_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglonglong_seq_t[i], ulonglong_seq_out[i]);
            }

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(float_seq_t[i], float_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(double_seq_t[i], double_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longdouble_seq_t[i], longdouble_seq_out[i]);
            }

            for(i = 0; i < 5; i++)
            {
                int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
                int32_t length_out_aux = (uint32_t)std::strlen(string_seq_out[i]);
                int32_t comparative_aux = std::strcmp(string_seq_t[i], string_seq_out[i]);
                EXPECT_EQ(length_in_aux, length_out_aux);
                EXPECT_EQ(comparative_aux, 0);
                free(string_seq_out[i]);
            }
            free(string_seq_out);

            free(char_array_out);
            free(uchar_array_out);
            free(short_array_out);
            free(ushort_array_out);
            free(int_array_out);
            free(uint_array_out);

            free(long_array_out);
            free(ulong_array_out);
            free(longlong_array_out);
            free(ulonglong_array_out);

            free(float_array_out);
            free(double_array_out);
            free(longdouble_array_out);

            free(char_seq_out);
            free(uchar_seq_out);
            free(short_seq_out);
            free(ushort_seq_out);
            free(int_seq_out);
            free(uint_seq_out);

            free(long_seq_out);
            free(ulong_seq_out);
            free(longlong_seq_out);
            free(ulonglong_seq_out);

            free(float_seq_out);
            free(double_seq_out);
            free(longdouble_seq_out);

            free(string_out);
            free(string_out_2);

            destroyBuffer(microBuffer);
            free(microCDRWrite);
            free(microCDRRead);
        }
    }
}

TEST(microCDRDynamicBasicEndiannessTests, Short)
{
    int16_t short_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeShortEndianness(short_t, endianness, microCDRWrite);

    // Deserialization.
    deserializeShortEndianness(&short_out, endianness, microCDRRead);

    EXPECT_EQ(short_out, short_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicEndiannessTests, UnsignedShort)
{
    uint16_t ushort_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedShortEndianness(ushort_t, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedShortEndianness(&ushort_out, endianness, microCDRRead);

    EXPECT_EQ(ushort_out, ushort_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicEndiannessTests, Int)
{
    int32_t long_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeIntEndianness(long_t, endianness, microCDRWrite);

    // Deserialization.
    deserializeIntEndianness(&long_out, endianness, microCDRRead);

    EXPECT_EQ(long_out, long_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicEndiannessTests, UnsignedInt)
{
    uint32_t ulong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedIntEndianness(ulong_t, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedIntEndianness(&ulong_out, endianness, microCDRRead);

    EXPECT_EQ(ulong_out, ulong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicEndiannessTests, Long)
{
    int64_t long_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongEndianness(longlong_t, endianness, microCDRWrite);

    // Deserialization.
    deserializeLongEndianness(&long_out, endianness, microCDRRead);

    EXPECT_EQ(long_out, longlong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicEndiannessTests, uLong)
{
    uint64_t ulong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongEndianness(ulonglong_t, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongEndianness(&ulong_out, endianness, microCDRRead);

    EXPECT_EQ(ulong_out, ulonglong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicEndiannessTests, LongLong)
{
    long long longlong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongLongEndianness(longlonglong_t, endianness, microCDRWrite);

    // Deserialization.
    deserializeLongLongEndianness(&longlong_out, endianness, microCDRRead);

    EXPECT_EQ(longlong_out, longlonglong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicEndiannessTests, uLongLong)
{
    unsigned long long ulonglong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongLongEndianness(ulonglonglong_t, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongLongEndianness(&ulonglong_out, endianness, microCDRRead);

    EXPECT_EQ(ulonglong_out, ulonglonglong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicEndiannessTests, Float)
{
    float float_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeFloatEndianness(float_tt, endianness, microCDRWrite);

    // Deserialization.
    deserializeFloatEndianness(&float_out, endianness, microCDRRead);

    EXPECT_EQ(float_out, float_tt);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicEndiannessTests, Double)
{
    double double_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeDoubleEndianness(double_tt, endianness, microCDRWrite);

    // Deserialization.
    deserializeDoubleEndianness(&double_out, endianness, microCDRRead);

    EXPECT_EQ(double_out, double_tt);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicEndiannessTests, LongDouble)
{
    long double longdouble_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongDoubleEndianness(longdouble_t, endianness, microCDRWrite);

    // Deserialization.
    deserializeLongDoubleEndianness(&longdouble_out, endianness, microCDRRead);

    EXPECT_EQ(longdouble_out, longdouble_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicEndiannessTests, String)
{
    char* string_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    const uint32_t length = (uint32_t)std::strlen(string_t);
    uint32_t length_out;

    // Serialization.
    serializeStringEndianness(string_t, length, endianness, microCDRWrite);

    // Deserialization.
    deserializeStringEndianness(&string_out, &length_out, endianness, microCDRRead);

    uint32_t comparative = std::strcmp(string_out, string_t);

    EXPECT_EQ(comparative, 0);
    EXPECT_EQ(length, length_out);
    free(string_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicBasicEndiannessTests, EmptyString)
{
    char* string_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    const uint32_t length = (uint32_t)std::strlen(emptystring_t);
    uint32_t length_out;

    // Serialization.
    serializeStringEndianness(emptystring_t, length, endianness, microCDRWrite);

    // Deserialization.
    deserializeStringEndianness(&string_out, &length_out, endianness, microCDRRead);

    uint32_t comparative = std::strcmp(string_out, emptystring_t);

    EXPECT_EQ(comparative, 0);
    EXPECT_EQ(length, length_out);
    free(string_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayEndiannessTests, ShortArray)
{
    int16_t* short_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeShortArrayEndianness(short_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeShortArrayEndianness(&short_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(short_array_t[i], short_out[i]);
    }
    free(short_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayEndiannessTests, UnsignedShortArray)
{
    uint16_t* ushort_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedShortArrayEndianness(ushort_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedShortArrayEndianness(&ushort_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ushort_array_t[i], ushort_out[i]);
    }
    free(ushort_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayEndiannessTests, IntArray)
{
    int32_t* int_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeIntArrayEndianness(long_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeIntArrayEndianness(&int_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(long_array_t[i], int_out[i]);
    }
    free(int_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayEndiannessTests, UnsignedIntArray)
{
    uint32_t* uint_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedIntArrayEndianness(ulong_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedIntArrayEndianness(&uint_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulong_array_t[i], uint_out[i]);
    }
    free(uint_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayEndiannessTests, LongArray)
{
    int64_t* long_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongArrayEndianness(longlong_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeLongArrayEndianness(&long_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longlong_array_t[i], long_out[i]);
    }
    free(long_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayEndiannessTests, ULongArray)
{
    uint64_t* ulong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongArrayEndianness(ulonglong_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongArrayEndianness(&ulong_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulonglong_array_t[i], ulong_out[i]);
    }
    free(ulong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayEndiannessTests, LongLongArray)
{
    long long* longlong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongLongArrayEndianness(longlonglong_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeLongLongArrayEndianness(&longlong_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longlonglong_array_t[i], longlong_out[i]);
    }
    free(longlong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayEndiannessTests, ULongLongArray)
{
    unsigned long long* ulonglong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongLongArrayEndianness(ulonglonglong_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongLongArrayEndianness(&ulonglong_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulonglonglong_array_t[i], ulonglong_out[i]);
    }
    free(ulonglong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayEndiannessTests, FloatArray)
{
    float* float_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeFloatArrayEndianness(float_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeFloatArrayEndianness(&float_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(float_array_t[i], float_out[i]);
    }
    free(float_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayEndiannessTests, DoubleArray)
{
    double* double_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeDoubleArrayEndianness(double_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeDoubleArrayEndianness(&double_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(double_array_t[i], double_out[i]);
    }

    free(double_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayEndiannessTests, LongDoubleArray)
{
    long double* longdouble_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongDoubleArrayEndianness(longdouble_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeLongDoubleArrayEndianness(&longdouble_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longdouble_array_t[i], longdouble_out[i]);
    }
    free(longdouble_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicArrayEndiannessTests, StringArray)
{
    char** string_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeStringArrayEndianness(string_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeStringArrayEndianness(&string_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
        int32_t length_out_aux = (uint32_t)std::strlen(string_out[i]);
        int32_t comparative_aux = std::strcmp(string_seq_t[i], string_out[i]);
        EXPECT_EQ(length_in_aux, length_out_aux);
        EXPECT_EQ(comparative_aux, 0);
        free(string_out[i]);
    }
    free(string_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesEndiannessTests, CharSequence)
{
    char* char_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeCharSequenceEndianness(char_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeCharSequenceEndianness(&char_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(char_seq_t[i], char_out[i]);
    }

    free(char_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesEndiannessTests, UnsignedCharSequence)
{
    unsigned char* char_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedCharSequenceEndianness(octet_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedCharSequenceEndianness(&char_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(octet_seq_t[i], char_out[i]);
    }

    free(char_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesEndiannessTests, ShortSequence)
{
    int16_t* short_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeShortSequenceEndianness(short_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeShortSequenceEndianness(&short_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(short_seq_t[i], short_out[i]);
    }

    free(short_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesEndiannessTests, UnsignedShortSequence)
{
    uint16_t* ushort_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedShortSequenceEndianness(ushort_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedShortSequenceEndianness(&ushort_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ushort_seq_t[i], ushort_out[i]);
    }

    free(ushort_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesEndiannessTests, IntSequence)
{
    int32_t* int_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeIntSequenceEndianness(long_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeIntSequenceEndianness(&int_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(long_seq_t[i], int_out[i]);
    }

    free(int_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesEndiannessTests, UnsignedIntSequence)
{
    uint32_t* uint_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedIntSequenceEndianness(ulong_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedIntSequenceEndianness(&uint_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulong_seq_t[i], uint_out[i]);
    }

    free(uint_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesEndiannessTests, LongSequence)
{
    int64_t* long_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongSequenceEndianness(longlong_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeLongSequenceEndianness(&long_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longlong_seq_t[i], long_out[i]);
    }

    free(long_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesEndiannessTests, ULongSequence)
{
    uint64_t* ulong_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongSequenceEndianness(ulonglong_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongSequenceEndianness(&ulong_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulonglong_seq_t[i], ulong_out[i]);
    }

    free(ulong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesEndiannessTests, LongLongSequence)
{
    long long* longlong_out;
    uint32_t size_out;
    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongLongSequenceEndianness(longlonglong_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeLongLongSequenceEndianness(&longlong_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longlonglong_seq_t[i], longlong_out[i]);
    }

    free(longlong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesEndiannessTests, ULongLongSequence)
{
    unsigned long long* ulonglong_out;
    uint32_t size_out;
    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongLongSequenceEndianness(ulonglonglong_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongLongSequenceEndianness(&ulonglong_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulonglonglong_seq_t[i], ulonglong_out[i]);
    }

    free(ulonglong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesEndiannessTests, FloatSequence)
{
    float* float_out;
    uint32_t size_out;
    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeFloatSequenceEndianness(float_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeFloatSequenceEndianness(&float_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(float_seq_t[i], float_out[i]);
    }

    free(float_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesEndiannessTests, DoubleSequence)
{
    double* double_out;
    uint32_t size_out;
    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeDoubleSequenceEndianness(double_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeDoubleSequenceEndianness(&double_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(double_seq_t[i], double_out[i]);
    }

    free(double_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesEndiannessTests, LongDoubleSequence)
{
    long double* longdouble_out;
    uint32_t size_out;
    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongDoubleSequenceEndianness(longdouble_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeLongDoubleSequenceEndianness(&longdouble_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longdouble_seq_t[i], longdouble_out[i]);
    }

    free(longdouble_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicSequencesEndiannessTests, StringSequence)
{
    char** string_out;
    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicNonAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeStringSequenceEndianness(string_seq_t, 5, endianness, microCDRWrite);

    uint32_t size_out;

    // Deserialization.
    deserializeStringSequenceEndianness(&string_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
        int32_t length_out_aux = (uint32_t)std::strlen(string_out[i]);
        int32_t comparative_aux = std::strcmp(string_seq_t[i], string_out[i]);
        EXPECT_EQ(length_in_aux, length_out_aux);
        EXPECT_EQ(comparative_aux, 0);
        free(string_out[i]);
    }
    free(string_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicTests, Char)
{
    char char_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeChar(char_t, microCDRWrite);

    // Deserialization.
    deserializeChar(&char_out, microCDRRead);

    EXPECT_EQ(char_out, char_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicTests, SignedChar)
{
    signed char octect_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeSignedChar(octet_t, microCDRWrite);

    // Deserialization.
    deserializeSignedChar(&octect_out, microCDRRead);

    EXPECT_EQ(octect_out, octet_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicTests, Short)
{
    int16_t short_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeShort(short_t, microCDRWrite);

    // Deserialization.
    deserializeShort(&short_out, microCDRRead);

    EXPECT_EQ(short_out, short_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicTests, UnsignedShort)
{
    uint16_t ushort_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedShort(ushort_t, microCDRWrite);

    // Deserialization.
    deserializeUnsignedShort(&ushort_out, microCDRRead);

    EXPECT_EQ(ushort_out, ushort_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicTests, Int)
{
    int32_t long_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeInt(long_t, microCDRWrite);

    // Deserialization.
    deserializeInt(&long_out, microCDRRead);

    EXPECT_EQ(long_out, long_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicTests, UnsignedInt)
{
    uint32_t ulong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedInt(ulong_t, microCDRWrite);

    // Deserialization.
    deserializeUnsignedInt(&ulong_out, microCDRRead);

    EXPECT_EQ(ulong_out, ulong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicTests, Long)
{
    int64_t long_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLong(longlong_t, microCDRWrite);

    // Deserialization.
    deserializeLong(&long_out, microCDRRead);

    EXPECT_EQ(long_out, longlong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicTests, uLong)
{
    uint64_t ulong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLong(ulonglong_t, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLong(&ulong_out, microCDRRead);

    EXPECT_EQ(ulong_out, ulonglong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicTests, LongLong)
{
    long long longlong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongLong(longlonglong_t, microCDRWrite);

    // Deserialization.
    deserializeLongLong(&longlong_out, microCDRRead);

    EXPECT_EQ(longlong_out, longlonglong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicTests, uLongLong)
{
    unsigned long long ulonglong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongLong(ulonglonglong_t, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongLong(&ulonglong_out, microCDRRead);

    EXPECT_EQ(ulonglong_out, ulonglonglong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicTests, Float)
{
    float float_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeFloat(float_tt, microCDRWrite);

    // Deserialization.
    deserializeFloat(&float_out, microCDRRead);

    EXPECT_EQ(float_out, float_tt);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicTests, Double)
{
    double double_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeDouble(double_tt, microCDRWrite);

    // Deserialization.
    deserializeDouble(&double_out, microCDRRead);

    EXPECT_EQ(double_out, double_tt);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicTests, LongDouble)
{
    long double longdouble_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongDouble(longdouble_t, microCDRWrite);

    // Deserialization.
    deserializeLongDouble(&longdouble_out, microCDRRead);

    EXPECT_EQ(longdouble_out, longdouble_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicTests, String)
{
    char* string_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    const uint32_t length = (uint32_t)std::strlen(string_t);
    uint32_t length_out;

    // Serialization.
    serializeString(string_t, length, microCDRWrite);

    // Deserialization.
    int8_t result = deserializeString(&string_out, &length_out, microCDRRead);

    EXPECT_EQ(result, 0);
    if(result == 0)
    {
        uint32_t comparative = std::strcmp(string_out, string_t);
        EXPECT_EQ(comparative, 0);
        EXPECT_EQ(length, length_out);
        free(string_out);
    }

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicTests, EmptyString)
{
    char* string_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    const uint32_t length = (uint32_t)std::strlen(emptystring_t);
    uint32_t length_out;

    // Serialization.
    serializeString(emptystring_t, length, microCDRWrite);

    // Deserialization.
    deserializeString(&string_out, &length_out, microCDRRead);

    uint32_t comparative = std::strcmp(string_out, emptystring_t);

    EXPECT_EQ(comparative, 0);
    EXPECT_EQ(length, length_out);
    free(string_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayTests, CharArray)
{
    char* char_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeCharArray(char_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeCharArray(&char_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(char_array_t[i], char_out[i]);
    }
    free(char_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayTests, UnsignedCharArray)
{
    unsigned char* char_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedCharArray(octet_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedCharArray(&char_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(octet_array_t[i], char_out[i]);
    }
    free(char_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayTests, ShortArray)
{
    int16_t* short_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeShortArray(short_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeShortArray(&short_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(short_array_t[i], short_out[i]);
    }
    free(short_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayTests, UnsignedShortArray)
{
    uint16_t* ushort_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedShortArray(ushort_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedShortArray(&ushort_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ushort_array_t[i], ushort_out[i]);
    }
    free(ushort_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayTests, IntArray)
{
    int32_t* int_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeIntArray(long_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeIntArray(&int_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(long_array_t[i], int_out[i]);
    }
    free(int_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayTests, UnsignedIntArray)
{
    uint32_t* uint_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedIntArray(ulong_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedIntArray(&uint_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulong_array_t[i], uint_out[i]);
    }
    free(uint_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayTests, LongArray)
{
    int64_t* long_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongArray(longlong_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeLongArray(&long_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longlong_array_t[i], long_out[i]);
    }
    free(long_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayTests, ULongArray)
{
    uint64_t* ulong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongArray(ulonglong_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongArray(&ulong_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulonglong_array_t[i], ulong_out[i]);
    }
    free(ulong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayTests, LongLongArray)
{
    long long* longlong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongLongArray(longlonglong_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeLongLongArray(&longlong_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longlonglong_array_t[i], longlong_out[i]);
    }
    free(longlong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayTests, ULongLongArray)
{
    unsigned long long* ulonglong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongLongArray(ulonglonglong_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongLongArray(&ulonglong_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulonglonglong_array_t[i], ulonglong_out[i]);
    }
    free(ulonglong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayTests, FloatArray)
{
    float* float_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeFloatArray(float_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeFloatArray(&float_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(float_array_t[i], float_out[i]);
    }
    free(float_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayTests, DoubleArray)
{
    double* double_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeDoubleArray(double_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeDoubleArray(&double_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(double_array_t[i], double_out[i]);
    }

    free(double_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayTests, LongDoubleArray)
{
    long double* longdouble_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongDoubleArray(longdouble_array_t, 5, microCDRWrite);

    // Deserialization.
    deserializeLongDoubleArray(&longdouble_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longdouble_array_t[i], longdouble_out[i]);
    }
    free(longdouble_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayTests, StringArray)
{
    char** string_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeStringArray(string_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeStringArray(&string_out, 5, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
        int32_t length_out_aux = (uint32_t)std::strlen(string_out[i]);
        int32_t comparative_aux = std::strcmp(string_seq_t[i], string_out[i]);
        EXPECT_EQ(length_in_aux, length_out_aux);
        EXPECT_EQ(comparative_aux, 0);
        free(string_out[i]);
    }
    free(string_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesTests, CharSequence)
{
    char* char_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeCharSequence(char_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeCharSequence(&char_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(char_seq_t[i], char_out[i]);
    }

    free(char_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesTests, UnsignedCharSequence)
{
    unsigned char* char_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedCharSequence(octet_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedCharSequence(&char_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(octet_seq_t[i], char_out[i]);
    }

    free(char_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesTests, ShortSequence)
{
    int16_t* short_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeShortSequence(short_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeShortSequence(&short_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(short_seq_t[i], short_out[i]);
    }

    free(short_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesTests, UnsignedShortSequence)
{
    uint16_t* ushort_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedShortSequence(ushort_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedShortSequence(&ushort_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ushort_seq_t[i], ushort_out[i]);
    }

    free(ushort_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesTests, IntSequence)
{
    int32_t* int_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeIntSequence(long_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeIntSequence(&int_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(long_seq_t[i], int_out[i]);
    }

    free(int_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesTests, UnsignedIntSequence)
{
    uint32_t* uint_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedIntSequence(ulong_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedIntSequence(&uint_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulong_seq_t[i], uint_out[i]);
    }

    free(uint_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesTests, LongSequence)
{
    int64_t* long_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongSequence(longlong_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeLongSequence(&long_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longlong_seq_t[i], long_out[i]);
    }

    free(long_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesTests, ULongSequence)
{
    uint64_t* ulong_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongSequence(ulonglong_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongSequence(&ulong_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulonglong_seq_t[i], ulong_out[i]);
    }

    free(ulong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesTests, LongLongSequence)
{
    long long* longlong_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongLongSequence(longlonglong_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeLongLongSequence(&longlong_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longlonglong_seq_t[i], longlong_out[i]);
    }

    free(longlong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesTests, ULongLongSequence)
{
    unsigned long long* ulonglong_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongLongSequence(ulonglonglong_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongLongSequence(&ulonglong_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulonglonglong_seq_t[i], ulonglong_out[i]);
    }

    free(ulonglong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesTests, FloatSequence)
{
    float* float_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeFloatSequence(float_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeFloatSequence(&float_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(float_seq_t[i], float_out[i]);
    }

    free(float_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesTests, DoubleSequence)
{
    double* double_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeDoubleSequence(double_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeDoubleSequence(&double_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(double_seq_t[i], double_out[i]);
    }

    free(double_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesTests, LongDoubleSequence)
{
    long double* longdouble_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongDoubleSequence(longdouble_seq_t, 5, microCDRWrite);

    // Deserialization.
    deserializeLongDoubleSequence(&longdouble_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longdouble_seq_t[i], longdouble_out[i]);
    }

    free(longdouble_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesTests, StringSequence)
{
    char** string_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeStringSequence(string_seq_t, 5, microCDRWrite);

    uint32_t size_out;

    // Deserialization.
    deserializeStringSequence(&string_out, &size_out, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
        int32_t length_out_aux = (uint32_t)std::strlen(string_out[i]);
        int32_t comparative_aux = std::strcmp(string_seq_t[i], string_out[i]);
        EXPECT_EQ(length_in_aux, length_out_aux);
        EXPECT_EQ(comparative_aux, 0);
        free(string_out[i]);
    }
    free(string_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedTests, SimpleVar)
{
    char char_out;
    signed char octect_out;
    int16_t short_out;
    uint16_t ushort_out;
    int32_t long_out;
    uint32_t ulong_out;
    int64_t longlong_out;
    uint64_t ulonglong_out;
    long long longlonglong_out;
    unsigned long long ulonglonglong_out;
    float float_out;
    double double_out;
    long double longdouble_out;
    char* string_out;
    char* string_out_2;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    const uint32_t length = (uint32_t)std::strlen(string_t);
    uint32_t length_out;

    const uint32_t length_2 = (uint32_t)std::strlen(emptystring_t);
    uint32_t length_out_2;

    // Serialization.
    serializeChar(char_t, microCDRWrite);
    serializeSignedChar(octet_t, microCDRWrite);
    serializeShort(short_t, microCDRWrite);
    serializeUnsignedShort(ushort_t, microCDRWrite);
    serializeInt(long_t, microCDRWrite);
    serializeUnsignedInt(ulong_t, microCDRWrite);
    serializeLong(longlong_t, microCDRWrite);
    serializeUnsignedLong(ulonglong_t, microCDRWrite);
    serializeLongLong(longlonglong_t, microCDRWrite);
    serializeUnsignedLongLong(ulonglonglong_t, microCDRWrite);
    serializeFloat(float_tt, microCDRWrite);
    serializeDouble(double_tt, microCDRWrite);
    serializeLongDouble(longdouble_t, microCDRWrite);
    serializeString(string_t, length, microCDRWrite);
    serializeString(emptystring_t, length_2, microCDRWrite);

    // Deserialization.
    deserializeChar(&char_out, microCDRRead);
    deserializeSignedChar(&octect_out, microCDRRead);
    deserializeShort(&short_out, microCDRRead);
    deserializeUnsignedShort(&ushort_out, microCDRRead);
    deserializeInt(&long_out, microCDRRead);
    deserializeUnsignedInt(&ulong_out, microCDRRead);
    deserializeLong(&longlong_out, microCDRRead);
    deserializeUnsignedLong(&ulonglong_out, microCDRRead);
    deserializeLongLong(&longlonglong_out, microCDRRead);
    deserializeUnsignedLongLong(&ulonglonglong_out, microCDRRead);
    deserializeFloat(&float_out, microCDRRead);
    deserializeDouble(&double_out, microCDRRead);
    deserializeLongDouble(&longdouble_out, microCDRRead);
    deserializeString(&string_out, &length_out, microCDRRead);
    deserializeString(&string_out_2, &length_out_2, microCDRRead);

    uint32_t comparative = std::strcmp(string_out, string_t);
    uint32_t comparative_2 = std::strcmp(string_out_2, emptystring_t);

    EXPECT_EQ(char_out, char_t);
    EXPECT_EQ(octect_out, octet_t);
    EXPECT_EQ(short_out, short_t);
    EXPECT_EQ(ushort_out, ushort_t);
    EXPECT_EQ(long_out, long_t);
    EXPECT_EQ(ulong_out, ulong_t);
    EXPECT_EQ(longlong_out, longlong_t);
    EXPECT_EQ(ulonglong_out, ulonglong_t);
    EXPECT_EQ(longlonglong_out, longlonglong_t);
    EXPECT_EQ(ulonglonglong_out, ulonglonglong_t);
    EXPECT_EQ(float_out, float_tt);
    EXPECT_EQ(double_out, double_tt);
    EXPECT_EQ(longdouble_out, longdouble_t);
    EXPECT_EQ(comparative, 0);
    EXPECT_EQ(length, length_out);
    EXPECT_EQ(comparative_2, 0);
    EXPECT_EQ(length_2, length_out_2);

    free(string_out);
    free(string_out_2);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedTests, Arrays)
{
    int32_t i;
    char* char_out;
    unsigned char* uchar_out;
    int16_t* short_out;
    uint16_t* ushort_out;
    int32_t* int_out;
    uint32_t* uint_out;
    int64_t* long_out;
    uint64_t* ulong_out;
    long long* longlong_out;
    unsigned long long* ulonglong_out;
    float* float_out;
    double* double_out;
    long double* longdouble_out;
    char** string_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    int16_t result = 0;

    // Serialization.
    result += serializeCharArray(char_array_t, 5, microCDRWrite);//5
    result += serializeUnsignedCharArray(octet_array_t, 5, microCDRWrite);//5
    result += serializeShortArray(short_array_t, 5, microCDRWrite);//10
    result += serializeUnsignedShortArray(ushort_array_t, 5, microCDRWrite);//10
    result += serializeIntArray(long_array_t, 5, microCDRWrite);//20
    result += serializeUnsignedIntArray(ulong_array_t, 5, microCDRWrite);//20
    result += serializeLongArray(longlong_array_t, 5, microCDRWrite);//20
    result += serializeUnsignedLongArray(ulonglong_array_t, 5, microCDRWrite);//20
    result += serializeLongLongArray(longlonglong_array_t, 5, microCDRWrite);//20
    result += serializeUnsignedLongLongArray(ulonglonglong_array_t, 5, microCDRWrite);//20
    result += serializeFloatArray(float_array_t, 5, microCDRWrite);//20
    result += serializeDoubleArray(double_array_t, 5, microCDRWrite);//40
    result += serializeLongDoubleArray(longdouble_array_t, 5, microCDRWrite);//40
    result += serializeStringArray(string_seq_t, 5, microCDRWrite);

    //uint32_t serialized = getSerializedDataLength();

    EXPECT_EQ(result, 0);
    //EXPECT_EQ(serialized, 130);

    if(result == 0)
    {
        // Deserialization.
        result += deserializeCharArray(&char_out, 5, microCDRRead);
        result += deserializeUnsignedCharArray(&uchar_out, 5, microCDRRead);
        result += deserializeShortArray(&short_out, 5, microCDRRead);
        result += deserializeUnsignedShortArray(&ushort_out, 5, microCDRRead);
        result += deserializeIntArray(&int_out, 5, microCDRRead);
        result += deserializeUnsignedIntArray(&uint_out, 5, microCDRRead);
        result += deserializeLongArray(&long_out, 5, microCDRRead);
        result += deserializeUnsignedLongArray(&ulong_out, 5, microCDRRead);
        result += deserializeLongLongArray(&longlong_out, 5, microCDRRead);
        result += deserializeUnsignedLongLongArray(&ulonglong_out, 5, microCDRRead);
        result += deserializeFloatArray(&float_out, 5, microCDRRead);
        result += deserializeDoubleArray(&double_out, 5, microCDRRead);
        result += deserializeLongDoubleArray(&longdouble_out, 5, microCDRRead);
        result += deserializeStringArray(&string_out, 5, microCDRRead);

        EXPECT_EQ(result, 0);

        if(result == 0)
        {
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(char_array_t[i], char_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(octet_array_t[i], uchar_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(short_array_t[i], short_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ushort_array_t[i], ushort_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(long_array_t[i], int_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulong_array_t[i], uint_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlong_array_t[i], long_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglong_array_t[i], ulong_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlonglong_array_t[i], longlong_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglonglong_array_t[i], ulonglong_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(float_array_t[i], float_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(double_array_t[i], double_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longdouble_array_t[i], longdouble_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
                int32_t length_out_aux = (uint32_t)std::strlen(string_out[i]);
                int32_t comparative_aux = std::strcmp(string_seq_t[i], string_out[i]);
                EXPECT_EQ(length_in_aux, length_out_aux);
                EXPECT_EQ(comparative_aux, 0);
                free(string_out[i]);
            }

            free(char_out);
            free(uchar_out);
            free(short_out);
            free(ushort_out);
            free(int_out);
            free(uint_out);
            free(long_out);
            free(ulong_out);
            free(longlong_out);
            free(ulonglong_out);
            free(float_out);
            free(double_out);
            free(longdouble_out);
            free(string_out);

            destroyBuffer(microBuffer);
            free(microCDRWrite);
            free(microCDRRead);
        }
    }
}

TEST(microCDRDynamicAlignedTests, Sequences)
{
    int32_t i;
    char* char_out;
    uint32_t char_out_size;
    unsigned char* uchar_out;
    uint32_t uchar_out_size;
    int16_t* short_out;
    uint32_t short_out_size;
    uint16_t* ushort_out;
    uint32_t ushort_out_size;
    int32_t* int_out;
    uint32_t int_out_size;
    uint32_t* uint_out;
    uint32_t uint_out_size;
    int64_t* long_out;
    uint32_t long_out_size;
    uint64_t* ulong_out;
    uint32_t ulong_out_size;
    long long* longlong_out;
    uint32_t longlong_out_size;
    unsigned long long* ulonglong_out;
    uint32_t ulonglong_out_size;
    float* float_out;
    uint32_t float_out_size;
    double* double_out;
    uint32_t double_out_size;
    long double* longdouble_out;
    uint32_t longdouble_out_size;
    char** string_out;
    uint32_t string_out_size;

    int16_t result = 0;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    result += serializeCharSequence(char_seq_t, 5, microCDRWrite);//9
    result += serializeUnsignedCharSequence(octet_seq_t, 5, microCDRWrite);//9
    result += serializeShortSequence(short_seq_t, 5, microCDRWrite);//14
    result += serializeUnsignedShortSequence(ushort_seq_t, 5, microCDRWrite);//14
    result += serializeIntSequence(long_seq_t, 5, microCDRWrite);//24
    result += serializeUnsignedIntSequence(ulong_seq_t, 5, microCDRWrite);//24
    result += serializeLongSequence(longlong_seq_t, 5, microCDRWrite);//24
    result += serializeUnsignedLongSequence(ulonglong_seq_t, 5, microCDRWrite);//24
    result += serializeLongLongSequence(longlonglong_seq_t, 5, microCDRWrite);//24
    result += serializeUnsignedLongLongSequence(ulonglonglong_seq_t, 5, microCDRWrite);//24
    result += serializeFloatSequence(float_seq_t, 5, microCDRWrite);//24
    result += serializeDoubleSequence(double_seq_t, 5, microCDRWrite);//44
    result += serializeLongDoubleSequence(longdouble_seq_t, 5, microCDRWrite);//44
    result += serializeStringSequence(string_seq_t, 5, microCDRWrite);

    //uint32_t serialized = getSerializedDataLength();
    //EXPECT_EQ(serialized, 162);

    EXPECT_EQ(result, 0);

    if(result == 0)
    {
        // Deserialization.
        result += deserializeCharSequence(&char_out, &char_out_size, microCDRRead);
        result += deserializeUnsignedCharSequence(&uchar_out, &uchar_out_size, microCDRRead);
        result += deserializeShortSequence(&short_out, &short_out_size, microCDRRead);
        result += deserializeUnsignedShortSequence(&ushort_out, &ushort_out_size, microCDRRead);
        result += deserializeIntSequence(&int_out, &int_out_size, microCDRRead);
        result += deserializeUnsignedIntSequence(&uint_out, &uint_out_size, microCDRRead);
        result += deserializeLongSequence(&long_out, &long_out_size, microCDRRead);
        result += deserializeUnsignedLongSequence(&ulong_out, &ulong_out_size, microCDRRead);
        result += deserializeLongLongSequence(&longlong_out, &longlong_out_size, microCDRRead);
        result += deserializeUnsignedLongLongSequence(&ulonglong_out, &ulonglong_out_size, microCDRRead);
        result += deserializeFloatSequence(&float_out, &float_out_size, microCDRRead);
        result += deserializeDoubleSequence(&double_out, &double_out_size, microCDRRead);
        result += deserializeLongDoubleSequence(&longdouble_out, &longdouble_out_size, microCDRRead);
        result += deserializeStringSequence(&string_out, &string_out_size, microCDRRead);

        EXPECT_EQ(result, 0);

        if(result == 0)
        {
            EXPECT_EQ(char_out_size, 5);
            EXPECT_EQ(uchar_out_size, 5);
            EXPECT_EQ(short_out_size, 5);
            EXPECT_EQ(ushort_out_size, 5);
            EXPECT_EQ(int_out_size, 5);
            EXPECT_EQ(uint_out_size, 5);
            EXPECT_EQ(long_out_size, 5);
            EXPECT_EQ(ulong_out_size, 5);
            EXPECT_EQ(longlong_out_size, 5);
            EXPECT_EQ(ulonglong_out_size, 5);
            EXPECT_EQ(float_out_size, 5);
            EXPECT_EQ(double_out_size, 5);
            EXPECT_EQ(longdouble_out_size, 5);
            EXPECT_EQ(string_out_size, 5);

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(char_seq_t[i], char_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(octet_seq_t[i], uchar_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(short_seq_t[i], short_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ushort_seq_t[i], ushort_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(long_seq_t[i], int_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulong_seq_t[i], uint_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlong_seq_t[i], long_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglong_seq_t[i], ulong_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlonglong_seq_t[i], longlong_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglonglong_seq_t[i], ulonglong_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(float_seq_t[i], float_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(double_seq_t[i], double_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longdouble_seq_t[i], longdouble_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
                int32_t length_out_aux = (uint32_t)std::strlen(string_out[i]);
                int32_t comparative_aux = std::strcmp(string_seq_t[i], string_out[i]);
                EXPECT_EQ(length_in_aux, length_out_aux);
                EXPECT_EQ(comparative_aux, 0);
                free(string_out[i]);
            }

            free(char_out);
            free(uchar_out);
            free(short_out);
            free(ushort_out);
            free(int_out);
            free(uint_out);
            free(long_out);
            free(ulong_out);
            free(longlong_out);
            free(ulonglong_out);
            free(float_out);
            free(double_out);
            free(longdouble_out);
            free(string_out);

            destroyBuffer(microBuffer);
            free(microCDRWrite);
            free(microCDRRead);
        }
    }
}

TEST(microCDRDynamicAlignedTests, All)
{
    //SIMPLE
    char char_out;
    signed char octect_out;
    int16_t short_out;
    uint16_t ushort_out;
    int32_t long_out;
    uint32_t ulong_out;
    int64_t longlong_out;
    uint64_t ulonglong_out;
    long long longlonglong_out;
    unsigned long long ulonglonglong_out;
    float float_out;
    double double_out;
    long double longdouble_out;
    char* string_out;
    char* string_out_2;

    //ARRAYS
    int32_t i;
    char* char_array_out;
    unsigned char* uchar_array_out;
    int16_t* short_array_out;
    uint16_t* ushort_array_out;
    int32_t* int_array_out;
    uint32_t* uint_array_out;
    int64_t* long_array_out;
    uint64_t* ulong_array_out;
    long long* longlong_array_out;
    unsigned long long* ulonglong_array_out;
    float* float_array_out;
    double* double_array_out;
    long double* longdouble_array_out;
    char** string_array_out;

    //SEQUENCES
    char* char_seq_out;
    uint32_t char_out_size;
    unsigned char* uchar_seq_out;
    uint32_t uchar_out_size;
    int16_t* short_seq_out;
    uint32_t short_out_size;
    uint16_t* ushort_seq_out;
    uint32_t ushort_out_size;
    int32_t* int_seq_out;
    uint32_t int_out_size;
    uint32_t* uint_seq_out;
    uint32_t uint_out_size;
    int64_t* long_seq_out;
    uint32_t long_out_size;
    uint64_t* ulong_seq_out;
    uint32_t ulong_out_size;
    long long* longlong_seq_out;
    uint32_t longlong_out_size;
    unsigned long long* ulonglong_seq_out;
    uint32_t ulonglong_out_size;
    float* float_seq_out;
    uint32_t float_out_size;
    double* double_seq_out;
    uint32_t double_out_size;
    long double* longdouble_seq_out;
    uint32_t longdouble_out_size;
    char** string_seq_out;
    uint32_t string_out_size;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    const uint32_t length = (uint32_t)std::strlen(string_t);
    uint32_t length_out;

    int16_t result = 0;

    const uint32_t length_2 = (uint32_t)std::strlen(emptystring_t);
    uint32_t length_out_2;

    // Serialization.
    result += serializeChar(char_t, microCDRWrite);
    result += serializeSignedChar(octet_t, microCDRWrite);
    result += serializeShort(short_t, microCDRWrite);
    result += serializeUnsignedShort(ushort_t, microCDRWrite);
    result += serializeInt(long_t, microCDRWrite);
    result += serializeUnsignedInt(ulong_t, microCDRWrite);
    result += serializeLong(longlong_t, microCDRWrite);
    result += serializeUnsignedLong(ulonglong_t, microCDRWrite);
    result += serializeLongLong(longlonglong_t, microCDRWrite);
    result += serializeUnsignedLongLong(ulonglonglong_t, microCDRWrite);
    result += serializeFloat(float_tt, microCDRWrite);
    result += serializeDouble(double_tt, microCDRWrite);
    result += serializeLongDouble(longdouble_t, microCDRWrite);
    result += serializeString(string_t, length, microCDRWrite);
    result += serializeString(emptystring_t, length_2, microCDRWrite);

    result += serializeCharArray(char_array_t, 5, microCDRWrite);//5
    result += serializeUnsignedCharArray(octet_array_t, 5, microCDRWrite);//5
    result += serializeShortArray(short_array_t, 5, microCDRWrite);//10
    result += serializeUnsignedShortArray(ushort_array_t, 5, microCDRWrite);//10
    result += serializeIntArray(long_array_t, 5, microCDRWrite);//20
    result += serializeUnsignedIntArray(ulong_array_t, 5, microCDRWrite);//20

    result += serializeLongArray(longlong_array_t, 5, microCDRWrite);
    result += serializeUnsignedLongArray(ulonglong_array_t, 5, microCDRWrite);
    result += serializeLongLongArray(longlonglong_array_t, 5, microCDRWrite);
    result += serializeUnsignedLongLongArray(ulonglonglong_array_t, 5, microCDRWrite);

    result += serializeFloatArray(float_array_t, 5, microCDRWrite);//20
    result += serializeDoubleArray(double_array_t, 5, microCDRWrite);//40
    result += serializeLongDoubleArray(longdouble_array_t, 5, microCDRWrite);
    result += serializeStringArray(string_seq_t, 5, microCDRWrite);

    result += serializeCharSequence(char_seq_t, 5, microCDRWrite);//9
    result += serializeUnsignedCharSequence(octet_seq_t, 5, microCDRWrite);//9
    result += serializeShortSequence(short_seq_t, 5, microCDRWrite);//14
    result += serializeUnsignedShortSequence(ushort_seq_t, 5, microCDRWrite);//14
    result += serializeIntSequence(long_seq_t, 5, microCDRWrite);//24
    result += serializeUnsignedIntSequence(ulong_seq_t, 5, microCDRWrite);//24

    result += serializeLongSequence(longlong_seq_t, 5, microCDRWrite);
    result += serializeUnsignedLongSequence(ulonglong_seq_t, 5, microCDRWrite);
    result += serializeLongLongSequence(longlonglong_seq_t, 5, microCDRWrite);
    result += serializeUnsignedLongLongSequence(ulonglonglong_seq_t, 5, microCDRWrite);

    result += serializeFloatSequence(float_seq_t, 5, microCDRWrite);//24
    result += serializeDoubleSequence(double_seq_t, 5, microCDRWrite);//44
    result += serializeLongDoubleSequence(longdouble_seq_t, 5, microCDRWrite);//44
    result += serializeStringSequence(string_seq_t, 5, microCDRWrite);

    //uint32_t serialized = getSerializedDataLength();
    //EXPECT_EQ(serialized, 357);
    EXPECT_EQ(result, 0);

    if(result == 0)
    {
        // Deserialization.
        result += deserializeChar(&char_out, microCDRRead);
        result += deserializeSignedChar(&octect_out, microCDRRead);
        result += deserializeShort(&short_out, microCDRRead);
        result += deserializeUnsignedShort(&ushort_out, microCDRRead);
        result += deserializeInt(&long_out, microCDRRead);
        result += deserializeUnsignedInt(&ulong_out, microCDRRead);
        result += deserializeLong(&longlong_out, microCDRRead);
        result += deserializeUnsignedLong(&ulonglong_out, microCDRRead);
        result += deserializeLongLong(&longlonglong_out, microCDRRead);
        result += deserializeUnsignedLongLong(&ulonglonglong_out, microCDRRead);
        result += deserializeFloat(&float_out, microCDRRead);
        result += deserializeDouble(&double_out, microCDRRead);
        result += deserializeLongDouble(&longdouble_out, microCDRRead);
        result += deserializeString(&string_out, &length_out, microCDRRead);
        result += deserializeString(&string_out_2, &length_out_2, microCDRRead);

        result += deserializeCharArray(&char_array_out, 5, microCDRRead);
        result += deserializeUnsignedCharArray(&uchar_array_out, 5, microCDRRead);
        result += deserializeShortArray(&short_array_out, 5, microCDRRead);
        result += deserializeUnsignedShortArray(&ushort_array_out, 5, microCDRRead);
        result += deserializeIntArray(&int_array_out, 5, microCDRRead);
        result += deserializeUnsignedIntArray(&uint_array_out, 5, microCDRRead);

        result += deserializeLongArray(&long_array_out, 5, microCDRRead);
        result += deserializeUnsignedLongArray(&ulong_array_out, 5, microCDRRead);
        result += deserializeLongLongArray(&longlong_array_out, 5, microCDRRead);
        result += deserializeUnsignedLongLongArray(&ulonglong_array_out, 5, microCDRRead);

        result += deserializeFloatArray(&float_array_out, 5, microCDRRead);
        result += deserializeDoubleArray(&double_array_out, 5, microCDRRead);
        result += deserializeLongDoubleArray(&longdouble_array_out, 5, microCDRRead);
        result += deserializeStringArray(&string_array_out, 5, microCDRRead);

        result += deserializeCharSequence(&char_seq_out, &char_out_size, microCDRRead);
        result += deserializeUnsignedCharSequence(&uchar_seq_out, &uchar_out_size, microCDRRead);
        result += deserializeShortSequence(&short_seq_out, &short_out_size, microCDRRead);
        result += deserializeUnsignedShortSequence(&ushort_seq_out, &ushort_out_size, microCDRRead);
        result += deserializeIntSequence(&int_seq_out, &int_out_size, microCDRRead);
        result += deserializeUnsignedIntSequence(&uint_seq_out, &uint_out_size, microCDRRead);

        result += deserializeLongSequence(&long_seq_out, &long_out_size, microCDRRead);
        result += deserializeUnsignedLongSequence(&ulong_seq_out, &ulong_out_size, microCDRRead);
        result += deserializeLongLongSequence(&longlong_seq_out, &longlong_out_size, microCDRRead);
        result += deserializeUnsignedLongLongSequence(&ulonglong_seq_out, &ulonglong_out_size, microCDRRead);

        result += deserializeFloatSequence(&float_seq_out, &float_out_size, microCDRRead);
        result += deserializeDoubleSequence(&double_seq_out, &double_out_size, microCDRRead);
        result += deserializeLongDoubleSequence(&longdouble_seq_out, &longdouble_out_size, microCDRRead);
        result += deserializeStringSequence(&string_seq_out, &string_out_size, microCDRRead);

        EXPECT_EQ(result, 0);

        if(result == 0)
        {
            uint32_t comparative = (uint32_t)std::strcmp(string_out, string_t);
            uint32_t comparative_2 = (uint32_t)std::strcmp(string_out_2, emptystring_t);

            EXPECT_EQ(char_out, char_t);
            EXPECT_EQ(octect_out, octet_t);
            EXPECT_EQ(short_out, short_t);
            EXPECT_EQ(ushort_out, ushort_t);
            EXPECT_EQ(long_out, long_t);
            EXPECT_EQ(ulong_out, ulong_t);
            EXPECT_EQ(longlong_out, longlong_t);
            EXPECT_EQ(ulonglong_out, ulonglong_t);
            EXPECT_EQ(longlonglong_out, longlonglong_t);
            EXPECT_EQ(ulonglonglong_out, ulonglonglong_t);
            EXPECT_EQ(float_out, float_tt);
            EXPECT_EQ(double_out, double_tt);
            EXPECT_EQ(longdouble_out, longdouble_t);
            EXPECT_EQ(comparative, 0);
            EXPECT_EQ(length, length_out);
            EXPECT_EQ(comparative_2, 0);
            EXPECT_EQ(length_2, length_out_2);

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(char_array_t[i], char_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(octet_array_t[i], uchar_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(short_array_t[i], short_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ushort_array_t[i], ushort_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(long_array_t[i], int_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulong_array_t[i], uint_array_out[i]);
            }

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlong_array_t[i], long_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglong_array_t[i], ulong_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlonglong_array_t[i], longlong_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglonglong_array_t[i], ulonglong_array_out[i]);
            }

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(float_array_t[i], float_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(double_array_t[i], double_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longdouble_array_t[i], longdouble_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
                int32_t length_out_aux = (uint32_t)std::strlen(string_array_out[i]);
                int32_t comparative_aux = std::strcmp(string_seq_t[i], string_array_out[i]);
                EXPECT_EQ(length_in_aux, length_out_aux);
                EXPECT_EQ(comparative_aux, 0);
                free(string_array_out[i]);
            }
            free(string_array_out);

            EXPECT_EQ(char_out_size, 5);
            EXPECT_EQ(uchar_out_size, 5);
            EXPECT_EQ(short_out_size, 5);
            EXPECT_EQ(ushort_out_size, 5);
            EXPECT_EQ(int_out_size, 5);
            EXPECT_EQ(uint_out_size, 5);

            EXPECT_EQ(long_out_size, 5);
            EXPECT_EQ(ulong_out_size, 5);
            EXPECT_EQ(longlong_out_size, 5);
            EXPECT_EQ(ulonglong_out_size, 5);

            EXPECT_EQ(float_out_size, 5);
            EXPECT_EQ(double_out_size, 5);
            EXPECT_EQ(longdouble_out_size, 5);
            EXPECT_EQ(string_out_size, 5);

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(char_seq_t[i], char_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(octet_seq_t[i], uchar_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(short_seq_t[i], short_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ushort_seq_t[i], ushort_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(long_seq_t[i], int_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulong_seq_t[i], uint_seq_out[i]);
            }

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlong_seq_t[i], long_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglong_seq_t[i], ulong_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlonglong_seq_t[i], longlong_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglonglong_seq_t[i], ulonglong_seq_out[i]);
            }

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(float_seq_t[i], float_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(double_seq_t[i], double_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longdouble_seq_t[i], longdouble_seq_out[i]);
            }

            for(i = 0; i < 5; i++)
            {
                int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
                int32_t length_out_aux = (uint32_t)std::strlen(string_seq_out[i]);
                int32_t comparative_aux = std::strcmp(string_seq_t[i], string_seq_out[i]);
                EXPECT_EQ(length_in_aux, length_out_aux);
                EXPECT_EQ(comparative_aux, 0);
                free(string_seq_out[i]);
            }
            free(string_seq_out);

            free(char_array_out);
            free(uchar_array_out);
            free(short_array_out);
            free(ushort_array_out);
            free(int_array_out);
            free(uint_array_out);

            free(long_array_out);
            free(ulong_array_out);
            free(longlong_array_out);
            free(ulonglong_array_out);

            free(float_array_out);
            free(double_array_out);
            free(longdouble_array_out);

            free(char_seq_out);
            free(uchar_seq_out);
            free(short_seq_out);
            free(ushort_seq_out);
            free(int_seq_out);
            free(uint_seq_out);

            free(long_seq_out);
            free(ulong_seq_out);
            free(longlong_seq_out);
            free(ulonglong_seq_out);

            free(float_seq_out);
            free(double_seq_out);
            free(longdouble_seq_out);

            free(string_out);
            free(string_out_2);

            destroyBuffer(microBuffer);
            free(microCDRWrite);
            free(microCDRRead);
        }
    }
}

TEST(microCDRDynamicAlignedTests, AllEndianness)
{
    //SIMPLE
    char char_out;
    signed char octect_out;
    int16_t short_out;
    uint16_t ushort_out;
    int32_t long_out;
    uint32_t ulong_out;
    int64_t longlong_out;
    uint64_t ulonglong_out;
    long long longlonglong_out;
    unsigned long long ulonglonglong_out;
    float float_out;
    double double_out;
    long double longdouble_out;
    char* string_out;
    char* string_out_2;

    //ARRAYS
    int32_t i;
    char* char_array_out;
    unsigned char* uchar_array_out;
    int16_t* short_array_out;
    uint16_t* ushort_array_out;
    int32_t* int_array_out;
    uint32_t* uint_array_out;
    int64_t* long_array_out;
    uint64_t* ulong_array_out;
    long long* longlong_array_out;
    unsigned long long* ulonglong_array_out;
    float* float_array_out;
    double* double_array_out;
    long double* longdouble_array_out;
    char** string_array_out;

    //SEQUENCES
    char* char_seq_out;
    uint32_t char_out_size;
    unsigned char* uchar_seq_out;
    uint32_t uchar_out_size;
    int16_t* short_seq_out;
    uint32_t short_out_size;
    uint16_t* ushort_seq_out;
    uint32_t ushort_out_size;
    int32_t* int_seq_out;
    uint32_t int_out_size;
    uint32_t* uint_seq_out;
    uint32_t uint_out_size;
    int64_t* long_seq_out;
    uint32_t long_out_size;
    uint64_t* ulong_seq_out;
    uint32_t ulong_out_size;
    long long* longlong_seq_out;
    uint32_t longlong_out_size;
    unsigned long long* ulonglong_seq_out;
    uint32_t ulonglong_out_size;
    float* float_seq_out;
    uint32_t float_out_size;
    double* double_seq_out;
    uint32_t double_out_size;
    long double* longdouble_seq_out;
    uint32_t longdouble_out_size;
    char** string_seq_out;
    uint32_t string_out_size;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    const uint32_t length = (uint32_t)std::strlen(string_t);
    uint32_t length_out;

    int16_t result = 0;

    const uint32_t length_2 = (uint32_t)std::strlen(emptystring_t);
    uint32_t length_out_2;

    // Serialization.
    result += serializeChar(char_t, microCDRWrite);
    result += serializeSignedChar(octet_t, microCDRWrite);
    result += serializeShortEndianness(short_t, endianness, microCDRWrite);
    result += serializeUnsignedShortEndianness(ushort_t, endianness, microCDRWrite);
    result += serializeIntEndianness(long_t, endianness, microCDRWrite);
    result += serializeUnsignedIntEndianness(ulong_t, endianness, microCDRWrite);
    result += serializeLongEndianness(longlong_t, endianness, microCDRWrite);
    result += serializeUnsignedLongEndianness(ulonglong_t, endianness, microCDRWrite);
    result += serializeLongLongEndianness(longlonglong_t, endianness, microCDRWrite);
    result += serializeUnsignedLongLongEndianness(ulonglonglong_t, endianness, microCDRWrite);
    result += serializeFloatEndianness(float_tt, endianness, microCDRWrite);
    result += serializeDoubleEndianness(double_tt, endianness, microCDRWrite);
    result += serializeLongDoubleEndianness(longdouble_t, endianness, microCDRWrite);
    result += serializeStringEndianness(string_t, length, endianness, microCDRWrite);
    result += serializeStringEndianness(emptystring_t, length_2, endianness, microCDRWrite);

    result += serializeCharArray(char_array_t, 5, microCDRWrite);//5
    result += serializeUnsignedCharArray(octet_array_t, 5, microCDRWrite);//5
    result += serializeShortArrayEndianness(short_array_t, 5, endianness, microCDRWrite);//10
    result += serializeUnsignedShortArrayEndianness(ushort_array_t, 5, endianness, microCDRWrite);//10
    result += serializeIntArrayEndianness(long_array_t, 5, endianness, microCDRWrite);//20
    result += serializeUnsignedIntArrayEndianness(ulong_array_t, 5, endianness, microCDRWrite);//20

    result += serializeLongArrayEndianness(longlong_array_t, 5, endianness, microCDRWrite);
    result += serializeUnsignedLongArrayEndianness(ulonglong_array_t, 5, endianness, microCDRWrite);
    result += serializeLongLongArrayEndianness(longlonglong_array_t, 5, endianness, microCDRWrite);
    result += serializeUnsignedLongLongArrayEndianness(ulonglonglong_array_t, 5, endianness, microCDRWrite);

    result += serializeFloatArrayEndianness(float_array_t, 5, endianness, microCDRWrite);//20
    result += serializeDoubleArrayEndianness(double_array_t, 5, endianness, microCDRWrite);//40
    result += serializeLongDoubleArrayEndianness(longdouble_array_t, 5, endianness, microCDRWrite);
    result += serializeStringArrayEndianness(string_seq_t, 5, endianness, microCDRWrite);

    result += serializeCharSequenceEndianness(char_seq_t, 5, endianness, microCDRWrite);//9
    result += serializeUnsignedCharSequenceEndianness(octet_seq_t, 5, endianness, microCDRWrite);//9
    result += serializeShortSequenceEndianness(short_seq_t, 5, endianness, microCDRWrite);//14
    result += serializeUnsignedShortSequenceEndianness(ushort_seq_t, 5, endianness, microCDRWrite);//14
    result += serializeIntSequenceEndianness(long_seq_t, 5, endianness, microCDRWrite);//24
    result += serializeUnsignedIntSequenceEndianness(ulong_seq_t, 5, endianness, microCDRWrite);//24

    result += serializeLongSequenceEndianness(longlong_seq_t, 5, endianness, microCDRWrite);
    result += serializeUnsignedLongSequenceEndianness(ulonglong_seq_t, 5, endianness, microCDRWrite);
    result += serializeLongLongSequenceEndianness(longlonglong_seq_t, 5, endianness, microCDRWrite);
    result += serializeUnsignedLongLongSequenceEndianness(ulonglonglong_seq_t, 5, endianness, microCDRWrite);

    result += serializeFloatSequenceEndianness(float_seq_t, 5, endianness, microCDRWrite);//24
    result += serializeDoubleSequenceEndianness(double_seq_t, 5, endianness, microCDRWrite);//44
    result += serializeLongDoubleSequenceEndianness(longdouble_seq_t, 5, endianness, microCDRWrite);//44
    result += serializeStringSequenceEndianness(string_seq_t, 5, endianness, microCDRWrite);

    //uint32_t serialized = getSerializedDataLength();
    //EXPECT_EQ(serialized, 357);
    EXPECT_EQ(result, 0);

    if(result == 0)
    {
        // Deserialization.
        result += deserializeChar(&char_out, microCDRRead);
        result += deserializeSignedChar(&octect_out, microCDRRead);
        result += deserializeShortEndianness(&short_out, endianness, microCDRRead);
        result += deserializeUnsignedShortEndianness(&ushort_out, endianness, microCDRRead);
        result += deserializeIntEndianness(&long_out, endianness, microCDRRead);
        result += deserializeUnsignedIntEndianness(&ulong_out, endianness, microCDRRead);
        result += deserializeLongEndianness(&longlong_out, endianness, microCDRRead);
        result += deserializeUnsignedLongEndianness(&ulonglong_out, endianness, microCDRRead);
        result += deserializeLongLongEndianness(&longlonglong_out, endianness, microCDRRead);
        result += deserializeUnsignedLongLongEndianness(&ulonglonglong_out, endianness, microCDRRead);
        result += deserializeFloatEndianness(&float_out, endianness, microCDRRead);
        result += deserializeDoubleEndianness(&double_out, endianness, microCDRRead);
        result += deserializeLongDoubleEndianness(&longdouble_out, endianness, microCDRRead);
        result += deserializeStringEndianness(&string_out, &length_out, endianness, microCDRRead);
        result += deserializeStringEndianness(&string_out_2, &length_out_2, endianness, microCDRRead);

        result += deserializeCharArray(&char_array_out, 5, microCDRRead);
        result += deserializeUnsignedCharArray(&uchar_array_out, 5, microCDRRead);
        result += deserializeShortArrayEndianness(&short_array_out, 5, endianness, microCDRRead);
        result += deserializeUnsignedShortArrayEndianness(&ushort_array_out, 5, endianness, microCDRRead);
        result += deserializeIntArrayEndianness(&int_array_out, 5, endianness, microCDRRead);
        result += deserializeUnsignedIntArrayEndianness(&uint_array_out, 5, endianness, microCDRRead);

        result += deserializeLongArrayEndianness(&long_array_out, 5, endianness, microCDRRead);
        result += deserializeUnsignedLongArrayEndianness(&ulong_array_out, 5, endianness, microCDRRead);
        result += deserializeLongLongArrayEndianness(&longlong_array_out, 5, endianness, microCDRRead);
        result += deserializeUnsignedLongLongArrayEndianness(&ulonglong_array_out, 5, endianness, microCDRRead);

        result += deserializeFloatArrayEndianness(&float_array_out, 5, endianness, microCDRRead);
        result += deserializeDoubleArrayEndianness(&double_array_out, 5, endianness, microCDRRead);
        result += deserializeLongDoubleArrayEndianness(&longdouble_array_out, 5, endianness, microCDRRead);
        result += deserializeStringArrayEndianness(&string_array_out, 5, endianness, microCDRRead);

        result += deserializeCharSequenceEndianness(&char_seq_out, &char_out_size, endianness, microCDRRead);
        result += deserializeUnsignedCharSequenceEndianness(&uchar_seq_out, &uchar_out_size, endianness, microCDRRead);
        result += deserializeShortSequenceEndianness(&short_seq_out, &short_out_size, endianness, microCDRRead);
        result += deserializeUnsignedShortSequenceEndianness(&ushort_seq_out, &ushort_out_size, endianness, microCDRRead);
        result += deserializeIntSequenceEndianness(&int_seq_out, &int_out_size, endianness, microCDRRead);
        result += deserializeUnsignedIntSequenceEndianness(&uint_seq_out, &uint_out_size, endianness, microCDRRead);

        result += deserializeLongSequenceEndianness(&long_seq_out, &long_out_size, endianness, microCDRRead);
        result += deserializeUnsignedLongSequenceEndianness(&ulong_seq_out, &ulong_out_size, endianness, microCDRRead);
        result += deserializeLongLongSequenceEndianness(&longlong_seq_out, &longlong_out_size, endianness, microCDRRead);
        result += deserializeUnsignedLongLongSequenceEndianness(&ulonglong_seq_out, &ulonglong_out_size, endianness, microCDRRead);

        result += deserializeFloatSequenceEndianness(&float_seq_out, &float_out_size, endianness, microCDRRead);
        result += deserializeDoubleSequenceEndianness(&double_seq_out, &double_out_size, endianness, microCDRRead);
        result += deserializeLongDoubleSequenceEndianness(&longdouble_seq_out, &longdouble_out_size, endianness, microCDRRead);
        result += deserializeStringSequenceEndianness(&string_seq_out, &string_out_size, endianness, microCDRRead);

        EXPECT_EQ(result, 0);

        if(result == 0)
        {
            uint32_t comparative = (uint32_t)std::strcmp(string_out, string_t);
            uint32_t comparative_2 = (uint32_t)std::strcmp(string_out_2, emptystring_t);

            EXPECT_EQ(char_out, char_t);
            EXPECT_EQ(octect_out, octet_t);
            EXPECT_EQ(short_out, short_t);
            EXPECT_EQ(ushort_out, ushort_t);
            EXPECT_EQ(long_out, long_t);
            EXPECT_EQ(ulong_out, ulong_t);
            EXPECT_EQ(longlong_out, longlong_t);
            EXPECT_EQ(ulonglong_out, ulonglong_t);
            EXPECT_EQ(longlonglong_out, longlonglong_t);
            EXPECT_EQ(ulonglonglong_out, ulonglonglong_t);
            EXPECT_EQ(float_out, float_tt);
            EXPECT_EQ(double_out, double_tt);
            EXPECT_EQ(longdouble_out, longdouble_t);
            EXPECT_EQ(comparative, 0);
            EXPECT_EQ(length, length_out);
            EXPECT_EQ(comparative_2, 0);
            EXPECT_EQ(length_2, length_out_2);

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(char_array_t[i], char_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(octet_array_t[i], uchar_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(short_array_t[i], short_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ushort_array_t[i], ushort_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(long_array_t[i], int_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulong_array_t[i], uint_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlong_array_t[i], long_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglong_array_t[i], ulong_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlonglong_array_t[i], longlong_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglonglong_array_t[i], ulonglong_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(float_array_t[i], float_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(double_array_t[i], double_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longdouble_array_t[i], longdouble_array_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
                int32_t length_out_aux = (uint32_t)std::strlen(string_array_out[i]);
                int32_t comparative_aux = std::strcmp(string_seq_t[i], string_array_out[i]);
                EXPECT_EQ(length_in_aux, length_out_aux);
                EXPECT_EQ(comparative_aux, 0);
                free(string_array_out[i]);
            }
            free(string_array_out);

            EXPECT_EQ(char_out_size, 5);
            EXPECT_EQ(uchar_out_size, 5);
            EXPECT_EQ(short_out_size, 5);
            EXPECT_EQ(ushort_out_size, 5);
            EXPECT_EQ(int_out_size, 5);
            EXPECT_EQ(uint_out_size, 5);

            EXPECT_EQ(long_out_size, 5);
            EXPECT_EQ(ulong_out_size, 5);
            EXPECT_EQ(longlong_out_size, 5);
            EXPECT_EQ(ulonglong_out_size, 5);

            EXPECT_EQ(float_out_size, 5);
            EXPECT_EQ(double_out_size, 5);
            EXPECT_EQ(longdouble_out_size, 5);
            EXPECT_EQ(string_out_size, 5);

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(char_seq_t[i], char_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(octet_seq_t[i], uchar_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(short_seq_t[i], short_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ushort_seq_t[i], ushort_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(long_seq_t[i], int_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulong_seq_t[i], uint_seq_out[i]);
            }

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlong_seq_t[i], long_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglong_seq_t[i], ulong_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longlonglong_seq_t[i], longlong_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(ulonglonglong_seq_t[i], ulonglong_seq_out[i]);
            }

            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(float_seq_t[i], float_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(double_seq_t[i], double_seq_out[i]);
            }
            for(i = 0; i < 5; i++)
            {
                EXPECT_EQ(longdouble_seq_t[i], longdouble_seq_out[i]);
            }

            for(i = 0; i < 5; i++)
            {
                int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
                int32_t length_out_aux = (uint32_t)std::strlen(string_seq_out[i]);
                int32_t comparative_aux = std::strcmp(string_seq_t[i], string_seq_out[i]);
                EXPECT_EQ(length_in_aux, length_out_aux);
                EXPECT_EQ(comparative_aux, 0);
                free(string_seq_out[i]);
            }
            free(string_seq_out);

            free(char_array_out);
            free(uchar_array_out);
            free(short_array_out);
            free(ushort_array_out);
            free(int_array_out);
            free(uint_array_out);

            free(long_array_out);
            free(ulong_array_out);
            free(longlong_array_out);
            free(ulonglong_array_out);

            free(float_array_out);
            free(double_array_out);
            free(longdouble_array_out);

            free(char_seq_out);
            free(uchar_seq_out);
            free(short_seq_out);
            free(ushort_seq_out);
            free(int_seq_out);
            free(uint_seq_out);

            free(long_seq_out);
            free(ulong_seq_out);
            free(longlong_seq_out);
            free(ulonglong_seq_out);

            free(float_seq_out);
            free(double_seq_out);
            free(longdouble_seq_out);

            free(string_out);
            free(string_out_2);

            destroyBuffer(microBuffer);
            free(microCDRWrite);
            free(microCDRRead);
        }
    }
}

TEST(microCDRDynamicAlignedBasicEndiannessTests, Short)
{
    int16_t short_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeShortEndianness(short_t, endianness, microCDRWrite);

    // Deserialization.
    deserializeShortEndianness(&short_out, endianness, microCDRRead);

    EXPECT_EQ(short_out, short_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicEndiannessTests, UnsignedShort)
{
    uint16_t ushort_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedShortEndianness(ushort_t, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedShortEndianness(&ushort_out, endianness, microCDRRead);

    EXPECT_EQ(ushort_out, ushort_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicEndiannessTests, Int)
{
    int32_t long_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeIntEndianness(long_t, endianness, microCDRWrite);

    // Deserialization.
    deserializeIntEndianness(&long_out, endianness, microCDRRead);

    EXPECT_EQ(long_out, long_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicEndiannessTests, UnsignedInt)
{
    uint32_t ulong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedIntEndianness(ulong_t, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedIntEndianness(&ulong_out, endianness, microCDRRead);

    EXPECT_EQ(ulong_out, ulong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicEndiannessTests, Long)
{
    int64_t long_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongEndianness(longlong_t, endianness, microCDRWrite);

    // Deserialization.
    deserializeLongEndianness(&long_out, endianness, microCDRRead);

    EXPECT_EQ(long_out, longlong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicEndiannessTests, uLong)
{
    uint64_t ulong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongEndianness(ulonglong_t, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongEndianness(&ulong_out, endianness, microCDRRead);

    EXPECT_EQ(ulong_out, ulonglong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicEndiannessTests, LongLong)
{
    long long longlong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongLongEndianness(longlonglong_t, endianness, microCDRWrite);

    // Deserialization.
    deserializeLongLongEndianness(&longlong_out, endianness, microCDRRead);

    EXPECT_EQ(longlong_out, longlonglong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicEndiannessTests, uLongLong)
{
    unsigned long long ulonglong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongLongEndianness(ulonglonglong_t, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongLongEndianness(&ulonglong_out, endianness, microCDRRead);

    EXPECT_EQ(ulonglong_out, ulonglonglong_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicEndiannessTests, Float)
{
    float float_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeFloatEndianness(float_tt, endianness, microCDRWrite);

    // Deserialization.
    deserializeFloatEndianness(&float_out, endianness, microCDRRead);

    EXPECT_EQ(float_out, float_tt);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicEndiannessTests, Double)
{
    double double_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeDoubleEndianness(double_tt, endianness, microCDRWrite);

    // Deserialization.
    deserializeDoubleEndianness(&double_out, endianness, microCDRRead);

    EXPECT_EQ(double_out, double_tt);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicEndiannessTests, LongDouble)
{
    long double longdouble_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongDoubleEndianness(longdouble_t, endianness, microCDRWrite);

    // Deserialization.
    deserializeLongDoubleEndianness(&longdouble_out, endianness, microCDRRead);

    EXPECT_EQ(longdouble_out, longdouble_t);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicEndiannessTests, String)
{
    char* string_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    const uint32_t length = (uint32_t)std::strlen(string_t);
    uint32_t length_out;

    // Serialization.
    serializeStringEndianness(string_t, length, endianness, microCDRWrite);

    // Deserialization.
    deserializeStringEndianness(&string_out, &length_out, endianness, microCDRRead);

    uint32_t comparative = std::strcmp(string_out, string_t);

    EXPECT_EQ(comparative, 0);
    EXPECT_EQ(length, length_out);
    free(string_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedBasicEndiannessTests, EmptyString)
{
    char* string_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    const uint32_t length = (uint32_t)std::strlen(emptystring_t);
    uint32_t length_out;

    // Serialization.
    serializeStringEndianness(emptystring_t, length, endianness, microCDRWrite);

    // Deserialization.
    deserializeStringEndianness(&string_out, &length_out, endianness, microCDRRead);

    uint32_t comparative = std::strcmp(string_out, emptystring_t);

    EXPECT_EQ(comparative, 0);
    EXPECT_EQ(length, length_out);
    free(string_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayEndiannessTests, ShortArray)
{
    int16_t* short_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeShortArrayEndianness(short_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeShortArrayEndianness(&short_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(short_array_t[i], short_out[i]);
    }
    free(short_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayEndiannessTests, UnsignedShortArray)
{
    uint16_t* ushort_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedShortArrayEndianness(ushort_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedShortArrayEndianness(&ushort_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ushort_array_t[i], ushort_out[i]);
    }
    free(ushort_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayEndiannessTests, IntArray)
{
    int32_t* int_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeIntArrayEndianness(long_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeIntArrayEndianness(&int_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(long_array_t[i], int_out[i]);
    }
    free(int_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayEndiannessTests, UnsignedIntArray)
{
    uint32_t* uint_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedIntArrayEndianness(ulong_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedIntArrayEndianness(&uint_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulong_array_t[i], uint_out[i]);
    }
    free(uint_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayEndiannessTests, LongArray)
{
    int64_t* long_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongArrayEndianness(longlong_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeLongArrayEndianness(&long_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longlong_array_t[i], long_out[i]);
    }
    free(long_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayEndiannessTests, ULongArray)
{
    uint64_t* ulong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongArrayEndianness(ulonglong_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongArrayEndianness(&ulong_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulonglong_array_t[i], ulong_out[i]);
    }
    free(ulong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayEndiannessTests, LongLongArray)
{
    long long* longlong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongLongArrayEndianness(longlonglong_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeLongLongArrayEndianness(&longlong_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longlonglong_array_t[i], longlong_out[i]);
    }
    free(longlong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayEndiannessTests, ULongLongArray)
{
    unsigned long long* ulonglong_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongLongArrayEndianness(ulonglonglong_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongLongArrayEndianness(&ulonglong_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulonglonglong_array_t[i], ulonglong_out[i]);
    }
    free(ulonglong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayEndiannessTests, FloatArray)
{
    float* float_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeFloatArrayEndianness(float_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeFloatArrayEndianness(&float_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(float_array_t[i], float_out[i]);
    }
    free(float_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayEndiannessTests, DoubleArray)
{
    double* double_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeDoubleArrayEndianness(double_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeDoubleArrayEndianness(&double_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(double_array_t[i], double_out[i]);
    }

    free(double_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayEndiannessTests, LongDoubleArray)
{
    long double* longdouble_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongDoubleArrayEndianness(longdouble_array_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeLongDoubleArrayEndianness(&longdouble_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longdouble_array_t[i], longdouble_out[i]);
    }
    free(longdouble_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedArrayEndiannessTests, StringArray)
{
    char** string_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeStringArrayEndianness(string_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeStringArrayEndianness(&string_out, 5, endianness, microCDRRead);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
        int32_t length_out_aux = (uint32_t)std::strlen(string_out[i]);
        int32_t comparative_aux = std::strcmp(string_seq_t[i], string_out[i]);
        EXPECT_EQ(length_in_aux, length_out_aux);
        EXPECT_EQ(comparative_aux, 0);
        free(string_out[i]);
    }
    free(string_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesEndiannessTests, CharSequence)
{
    char* char_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeCharSequenceEndianness(char_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeCharSequenceEndianness(&char_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(char_seq_t[i], char_out[i]);
    }

    free(char_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesEndiannessTests, UnsignedCharSequence)
{
    unsigned char* char_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedCharSequenceEndianness(octet_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedCharSequenceEndianness(&char_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(octet_seq_t[i], char_out[i]);
    }

    free(char_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesEndiannessTests, ShortSequence)
{
    int16_t* short_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeShortSequenceEndianness(short_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeShortSequenceEndianness(&short_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(short_seq_t[i], short_out[i]);
    }

    free(short_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesEndiannessTests, UnsignedShortSequence)
{
    uint16_t* ushort_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedShortSequenceEndianness(ushort_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedShortSequenceEndianness(&ushort_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ushort_seq_t[i], ushort_out[i]);
    }

    free(ushort_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesEndiannessTests, IntSequence)
{
    int32_t* int_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeIntSequenceEndianness(long_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeIntSequenceEndianness(&int_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(long_seq_t[i], int_out[i]);
    }

    free(int_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesEndiannessTests, UnsignedIntSequence)
{
    uint32_t* uint_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedIntSequenceEndianness(ulong_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedIntSequenceEndianness(&uint_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulong_seq_t[i], uint_out[i]);
    }

    free(uint_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesEndiannessTests, LongSequence)
{
    int64_t* long_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongSequenceEndianness(longlong_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeLongSequenceEndianness(&long_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longlong_seq_t[i], long_out[i]);
    }

    free(long_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesEndiannessTests, ULongSequence)
{
    uint64_t* ulong_out;
    uint32_t size_out;

    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongSequenceEndianness(ulonglong_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongSequenceEndianness(&ulong_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulonglong_seq_t[i], ulong_out[i]);
    }

    free(ulong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesEndiannessTests, LongLongSequence)
{
    long long* longlong_out;
    uint32_t size_out;
    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongLongSequenceEndianness(longlonglong_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeLongLongSequenceEndianness(&longlong_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longlonglong_seq_t[i], longlong_out[i]);
    }

    free(longlong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesEndiannessTests, ULongLongSequence)
{
    unsigned long long* ulonglong_out;
    uint32_t size_out;
    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeUnsignedLongLongSequenceEndianness(ulonglonglong_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeUnsignedLongLongSequenceEndianness(&ulonglong_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(ulonglonglong_seq_t[i], ulonglong_out[i]);
    }

    free(ulonglong_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesEndiannessTests, FloatSequence)
{
    float* float_out;
    uint32_t size_out;
    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeFloatSequenceEndianness(float_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeFloatSequenceEndianness(&float_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(float_seq_t[i], float_out[i]);
    }

    free(float_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesEndiannessTests, DoubleSequence)
{
    double* double_out;
    uint32_t size_out;
    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeDoubleSequenceEndianness(double_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeDoubleSequenceEndianness(&double_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(double_seq_t[i], double_out[i]);
    }

    free(double_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesEndiannessTests, LongDoubleSequence)
{
    long double* longdouble_out;
    uint32_t size_out;
    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeLongDoubleSequenceEndianness(longdouble_seq_t, 5, endianness, microCDRWrite);

    // Deserialization.
    deserializeLongDoubleSequenceEndianness(&longdouble_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        EXPECT_EQ(longdouble_seq_t[i], longdouble_out[i]);
    }

    free(longdouble_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}

TEST(microCDRDynamicAlignedSequencesEndiannessTests, StringSequence)
{
    char** string_out;
    struct microBuffer* microBuffer = NULL;
    struct microCDR* microCDRWrite = NULL;
    struct microCDR* microCDRRead = NULL;

    // Check good case.
    newDynamicAlignedBuffer(&microBuffer);
    newMicroCDR(&microCDRWrite, microBuffer);
    newMicroCDR(&microCDRRead, microBuffer);

    // Serialization.
    serializeStringSequenceEndianness(string_seq_t, 5, endianness, microCDRWrite);

    uint32_t size_out;

    // Deserialization.
    deserializeStringSequenceEndianness(&string_out, &size_out, endianness, microCDRRead);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
        int32_t length_in_aux = (uint32_t)std::strlen(string_seq_t[i]);
        int32_t length_out_aux = (uint32_t)std::strlen(string_out[i]);
        int32_t comparative_aux = std::strcmp(string_seq_t[i], string_out[i]);
        EXPECT_EQ(length_in_aux, length_out_aux);
        EXPECT_EQ(comparative_aux, 0);
        free(string_out[i]);
    }
    free(string_out);

    destroyBuffer(microBuffer);
    free(microCDRWrite);
    free(microCDRRead);
}
