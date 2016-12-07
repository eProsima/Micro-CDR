#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cstring>

#include <gtest/gtest.h>

extern "C" {
  #include <nanocdr/nanoCdr.h>
}

const signed char octet_t = 32;
const char char_t =  'Z';

const unsigned short ushort_t = 65500;
const short short_t = -32700;
const unsigned int ulong_t = 4294967200;
const int long_t = -2147483600;

const unsigned long ulonglong_t = (unsigned long)18446744073709551600u;
const long longlong_t = (long)-9223372036800;

const unsigned long long ulonglonglong_t = 18446744073709551600u;
const long long longlonglong_t = -9223372036800;

const float float_tt = FLT_MIN;
const double double_tt = DBL_MIN;
const long double longdouble_t = DBL_MIN;

//TODO bool
//static const bool bool_t = true;

const char * string_t = "Hola a todos, esto es un test";
const char * emptystring_t = "";

const unsigned char octet_array_t[5] = {1, 2, 3, 4, 5};
const char char_array_t[5] = {'A', 'B', 'C', 'D', 'E'};

const unsigned short ushort_array_t [5] = {65500, 65501, 65502, 65503, 65504};
const short short_array_t[5] = {-32700, -32701, -32702, -32703, -32704};

const unsigned int ulong_array_t[5] = {4294967200, 4294967201, 4294967202, 4294967203, 4294967204};
const int long_array_t[5] = {-2147483600, -2147483601, -2147483602, -2147483603, -2147483604};


const unsigned long ulonglong_array_t[5] = {(unsigned long)18446744073709551600u, (unsigned long)18446744073709551601u, (unsigned long)18446744073709551602u, (unsigned long)18446744073709551603u, (unsigned long)18446744073709551604u};
const long  longlong_array_t[5] = {(long)-9223372036800, (long)-9223372036801, (long)-9223372036802, (long)-9223372036803, (long)-9223372036804};

const unsigned long long ulonglonglong_array_t[5] = {18446744073709551600u, 18446744073709551601u, 18446744073709551602u, 18446744073709551603u, 18446744073709551604u};
const long long longlonglong_array_t[5] = {-9223372036800, -9223372036801, -9223372036802, -9223372036803, -9223372036804};

const float float_array_t[5] = {float_tt, float_tt + 1, float_tt + 2, float_tt + 3, float_tt + 4};
const double double_array_t[5] = {double_tt, double_tt + 1, double_tt + 2, double_tt + 3, double_tt + 4};
const long double longdouble_array_t[5] = {longdouble_t, longdouble_t + 1, longdouble_t + 2, longdouble_t + 3, longdouble_t + 4};

//TODO bool
//static const std::array<bool, 5> bool_array_t = {{true, false, true, false, true}};
//static const bool bool_array_2_t[5] = {false, true, false, true, false};

// Added because error 336.
const unsigned char octet_seq_t[5] = {5, 4, 3, 2, 1};
const char char_seq_t[5] = {'E', 'D', 'C', 'B', 'A'};
const unsigned short ushort_seq_t[5] = {65504, 65503, 65502, 65501, 65500};
const short short_seq_t[5] = {-32704, -32703, -32702, -32701, -32700};
const unsigned int ulong_seq_t[5] = {4294967204, 4294967203, 4294967202, 4294967201, 4294967200};
const int long_seq_t[5] = {-2147483604, -2147483603, -2147483602, -2147483601, -2147483600};

const unsigned long ulonglong_seq_t[5] = {(unsigned long)18446744073709551600u, (unsigned long)18446744073709551601u, (unsigned long)18446744073709551602u, (unsigned long)18446744073709551603u, (unsigned long)18446744073709551604u};
const long  longlong_seq_t[5] = {(long)-9223372036800, (long)-9223372036801, (long)-9223372036802, (long)-9223372036803, (long)-9223372036804};

const unsigned long long ulonglonglong_seq_t[5] = {18446744073709551600u, 18446744073709551601u, 18446744073709551602u, 18446744073709551603u, 18446744073709551604u};
const long long longlonglong_seq_t[5] = {-9223372036800, -9223372036801, -9223372036802, -9223372036803, -9223372036804};


const float float_seq_t[5] = {float_tt + 4, float_tt + 3, float_tt + 2, float_tt + 1, float_tt};
const double double_seq_t[5] = {double_tt + 4, double_tt + 3, double_tt + 2, double_tt + 1, double_tt};
const long double longdouble_seq_t[5] = {longdouble_t, longdouble_t + 1, longdouble_t + 2, longdouble_t + 3, longdouble_t + 4};

//static const bool bool_seq_t[5] = {true, true, false, false, true};

const char * string_seq_t[5] = {"HELLO", "BYE", "GOODBYE", "HOLA", "ADIOS"};
// Added because error 337
const char * c_string_t = "HOLA";

Endianness endianness = LITTLE_ENDIANNESS;

TEST(nanoCDRBasicTests, Char)
{
    char char_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeChar(char_t, nanoCDR);

    // Deseriazliation.
    deserializeChar(&char_out, nanoCDR);

    EXPECT_EQ(char_out, char_t);

    destroyBuffer(nanoCDR);
}

TEST(nanoCDRBasicTests, SignedChar)
{
    signed char octect_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeSignedChar(octet_t, nanoCDR);

    // Deseriazliation.
    deserializeSignedChar(&octect_out, nanoCDR);

    EXPECT_EQ(octect_out, octet_t);
}

TEST(nanoCDRBasicTests, Short)
{
    int16_t short_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeShort(short_t, nanoCDR);

    // Deseriazliation.
    deserializeShort(&short_out, nanoCDR);

    EXPECT_EQ(short_out, short_t);
}

TEST(nanoCDRBasicTests, UnsignedShort)
{
    uint16_t ushort_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedShort(ushort_t, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedShort(&ushort_out, nanoCDR);

    EXPECT_EQ(ushort_out, ushort_t);
}

TEST(nanoCDRBasicTests, Int)
{
    int32_t long_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeInt(long_t, nanoCDR);

    // Deseriazliation.
    deserializeInt(&long_out, nanoCDR);

    EXPECT_EQ(long_out, long_t);
}

TEST(nanoCDRBasicTests, UnsignedInt)
{
    uint32_t ulong_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedInt(ulong_t, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedInt(&ulong_out, nanoCDR);

    EXPECT_EQ(ulong_out, ulong_t);
}

TEST(nanoCDRBasicTests, Long)
{
    int64_t long_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeLong(longlong_t, nanoCDR);

    // Deseriazliation.
    deserializeLong(&long_out, nanoCDR);

    EXPECT_EQ(long_out, longlong_t);
}

TEST(nanoCDRBasicTests, uLong)
{
    uint64_t ulong_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedLong(ulonglong_t, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedLong(&ulong_out, nanoCDR);

    EXPECT_EQ(ulong_out, ulonglong_t);
}

TEST(nanoCDRBasicTests, LongLong)
{
    long long longlong_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeLongLong(longlonglong_t, nanoCDR);

    // Deseriazliation.
    deserializeLongLong(&longlong_out, nanoCDR);

    EXPECT_EQ(longlong_out, longlonglong_t);
}

TEST(nanoCDRBasicTests, uLongLong)
{
    unsigned long long ulonglong_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedLongLong(ulonglonglong_t, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedLongLong(&ulonglong_out, nanoCDR);

    EXPECT_EQ(ulonglong_out, ulonglonglong_t);
}

TEST(nanoCDRBasicTests, Float)
{
    float float_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeFloat(float_tt, nanoCDR);

    // Deseriazliation.
    deserializeFloat(&float_out, nanoCDR);

    EXPECT_EQ(float_out, float_tt);
}

TEST(nanoCDRBasicTests, Double)
{
    double double_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeDouble(double_tt, nanoCDR);

    // Deseriazliation.
    deserializeDouble(&double_out, nanoCDR);

    EXPECT_EQ(double_out, double_tt);
}

TEST(nanoCDRBasicTests, LongDouble)
{
    long double longdouble_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeLongDouble(longdouble_t, nanoCDR);

    // Deseriazliation.
    deserializeLongDouble(&longdouble_out, nanoCDR);

    EXPECT_EQ(longdouble_out, longdouble_t);
}

TEST(nanoCDRBasicTests, String)
{
    char * string_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    const uint32_t length = (uint32_t)std::strlen(string_t);
    uint32_t length_out;

    // Serialization.
    serializeString(string_t, length, nanoCDR);

    // Deseriazliation.
    deserializeString(&string_out, &length_out, nanoCDR);

    uint32_t comparative = std::strcmp(string_out, string_t);

    EXPECT_EQ(comparative, 0);
    EXPECT_EQ(length, length_out);
    free(string_out);
}

TEST(nanoCDRBasicTests, EmptyString)
{
    char * string_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    const uint32_t length = (uint32_t)std::strlen(emptystring_t);
    uint32_t length_out;

    // Serialization.
    serializeString(emptystring_t, length, nanoCDR);

    // Deseriazliation.
    deserializeString(&string_out, &length_out, nanoCDR);

    uint32_t comparative = std::strcmp(string_out, emptystring_t);

    EXPECT_EQ(comparative, 0);
    EXPECT_EQ(length, length_out);
    free(string_out);
}

TEST(nanoCDRArrayTests, CharArray)
{
    char * char_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeCharArray(char_array_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeCharArray(&char_out, 5, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(char_array_t[i], char_out[i]);
    }
    free(char_out);
}

TEST(nanoCDRArrayTests, UnsignedCharArray)
{
    unsigned char * char_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedCharArray(octet_array_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedCharArray(&char_out, 5, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(octet_array_t[i], char_out[i]);
    }
    free(char_out);
}

TEST(nanoCDRArrayTests, ShortArray)
{
    int16_t * short_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeShortArray(short_array_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeShortArray(&short_out, 5, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(short_array_t[i], short_out[i]);
    }
    free(short_out);
}

TEST(nanoCDRArrayTests, UnsignedShortArray)
{
    uint16_t * ushort_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedShortArray(ushort_array_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedShortArray(&ushort_out, 5, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(ushort_array_t[i], ushort_out[i]);
    }
    free(ushort_out);
}

TEST(nanoCDRArrayTests, IntArray)
{
    int32_t * int_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeIntArray(long_array_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeIntArray(&int_out, 5, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(long_array_t[i], int_out[i]);
    }
    free(int_out);
}

TEST(nanoCDRArrayTests, UnsignedIntArray)
{
    uint32_t * uint_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedIntArray(ulong_array_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedIntArray(&uint_out, 5, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(ulong_array_t[i], uint_out[i]);
    }
    free(uint_out);
}

TEST(nanoCDRArrayTests, LongArray)
{
    int64_t * long_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeLongArray(longlong_array_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeLongArray(&long_out, 5, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(longlong_array_t[i], long_out[i]);
    }
    free(long_out);
}

TEST(nanoCDRArrayTests, ULongArray)
{
    uint64_t * ulong_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedLongArray(ulonglong_array_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedLongArray(&ulong_out, 5, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(ulonglong_array_t[i], ulong_out[i]);
    }
    free(ulong_out);
}

TEST(nanoCDRArrayTests, LongLongArray)
{
    long long * longlong_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeLongLongArray(longlonglong_array_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeLongLongArray(&longlong_out, 5, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(longlonglong_array_t[i], longlong_out[i]);
    }
    free(longlong_out);
}

TEST(nanoCDRArrayTests, ULongLongArray)
{
    unsigned long long * ulonglong_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedLongLongArray(ulonglonglong_array_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedLongLongArray(&ulonglong_out, 5, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(ulonglonglong_array_t[i], ulonglong_out[i]);
    }
    free(ulonglong_out);
}

TEST(nanoCDRArrayTests, FloatArray)
{
    float * float_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeFloatArray(float_array_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeFloatArray(&float_out, 5, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(float_array_t[i], float_out[i]);
    }
    free(float_out);
}

TEST(nanoCDRArrayTests, DoubleArray)
{
    double * double_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeDoubleArray(double_array_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeDoubleArray(&double_out, 5, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(double_array_t[i], double_out[i]);
    }

    free(double_out);
}

TEST(nanoCDRArrayTests, LongDoubleArray)
{
    long double * longdouble_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeLongDoubleArray(longdouble_array_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeLongDoubleArray(&longdouble_out, 5, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(longdouble_array_t[i], longdouble_out[i]);
    }
    free(longdouble_out);
}

TEST(nanoCDRArrayTests, StringArray)
{
    char ** string_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeStringArray(string_seq_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeStringArray(&string_out, 5, nanoCDR);

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
}

TEST(nanoCDRSequencesTests, CharSequence)
{
    char * char_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeCharSequence(char_seq_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeCharSequence(&char_out, &size_out, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(char_seq_t[i], char_out[i]);
    }

    free(char_out);
}

TEST(nanoCDRSequencesTests, UnsignedCharSequence)
{
    unsigned char * char_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedCharSequence(octet_seq_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedCharSequence(&char_out, &size_out, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(octet_seq_t[i], char_out[i]);
    }

    free(char_out);
}

TEST(nanoCDRSequencesTests, ShortSequence)
{
    int16_t * short_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeShortSequence(short_seq_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeShortSequence(&short_out, &size_out, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(short_seq_t[i], short_out[i]);
    }

    free(short_out);
}

TEST(nanoCDRSequencesTests, UnsignedShortSequence)
{
    uint16_t * ushort_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedShortSequence(ushort_seq_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedShortSequence(&ushort_out, &size_out, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(ushort_seq_t[i], ushort_out[i]);
    }

    free(ushort_out);
}

TEST(nanoCDRSequencesTests, IntSequence)
{
    int32_t * int_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeIntSequence(long_seq_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeIntSequence(&int_out, &size_out, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(long_seq_t[i], int_out[i]);
    }

    free(int_out);
}

TEST(nanoCDRSequencesTests, UnsignedIntSequence)
{
    uint32_t * uint_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedIntSequence(ulong_seq_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedIntSequence(&uint_out, &size_out, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(ulong_seq_t[i], uint_out[i]);
    }

    free(uint_out);
}

TEST(nanoCDRSequencesTests, LongSequence)
{
    int64_t * long_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeLongSequence(longlong_seq_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeLongSequence(&long_out, &size_out, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(longlong_seq_t[i], long_out[i]);
    }

    free(long_out);
}

TEST(nanoCDRSequencesTests, ULongSequence)
{
    uint64_t * ulong_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedLongSequence(ulonglong_seq_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedLongSequence(&ulong_out, &size_out, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(ulonglong_seq_t[i], ulong_out[i]);
    }

    free(ulong_out);
}

TEST(nanoCDRSequencesTests, LongLongSequence)
{
    long long * longlong_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeLongLongSequence(longlonglong_seq_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeLongLongSequence(&longlong_out, &size_out, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(longlonglong_seq_t[i], longlong_out[i]);
    }

    free(longlong_out);
}

TEST(nanoCDRSequencesTests, ULongLongSequence)
{
    unsigned long long * ulonglong_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedLongLongSequence(ulonglonglong_seq_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedLongLongSequence(&ulonglong_out, &size_out, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(ulonglonglong_seq_t[i], ulonglong_out[i]);
    }

    free(ulonglong_out);
}

TEST(nanoCDRSequencesTests, FloatSequence)
{
    float * float_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeFloatSequence(float_seq_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeFloatSequence(&float_out, &size_out, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(float_seq_t[i], float_out[i]);
    }

    free(float_out);
}

TEST(nanoCDRSequencesTests, DoubleSequence)
{
    double * double_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeDoubleSequence(double_seq_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeDoubleSequence(&double_out, &size_out, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(double_seq_t[i], double_out[i]);
    }

    free(double_out);
}

TEST(nanoCDRSequencesTests, LongDoubleSequence)
{
    long double * longdouble_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);
    // Serialization.
    serializeLongDoubleSequence(longdouble_seq_t, 5, nanoCDR);

    // Deseriazliation.
    deserializeLongDoubleSequence(&longdouble_out, &size_out, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(longdouble_seq_t[i], longdouble_out[i]);
    }

    free(longdouble_out);
}

TEST(nanoCDRSequencesTests, StringSequence)
{
    char ** string_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeStringSequence(string_seq_t, 5, nanoCDR);

    uint32_t size_out;

    // Deseriazliation.
    deserializeStringSequence(&string_out, &size_out, nanoCDR);

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
}

TEST(nanoCDRTests, SimpleVar)
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
  char * string_out;
  char * string_out_2;

  // Check good case.
  struct nanoBuffer * nanoCDR = NULL;
  // Check good case.
  newDynamicBuffer(&nanoCDR);

  const uint32_t length = (uint32_t)std::strlen(string_t);
  uint32_t length_out;

  const uint32_t length_2 = (uint32_t)std::strlen(emptystring_t);
  uint32_t length_out_2;

  // Serialization.
  serializeChar(char_t, nanoCDR);
  serializeSignedChar(octet_t, nanoCDR);
  serializeShort(short_t, nanoCDR);
  serializeUnsignedShort(ushort_t, nanoCDR);
  serializeInt(long_t, nanoCDR);
  serializeUnsignedInt(ulong_t, nanoCDR);
  serializeLong(longlong_t, nanoCDR);
  serializeUnsignedLong(ulonglong_t, nanoCDR);
  serializeLongLong(longlonglong_t, nanoCDR);
  serializeUnsignedLongLong(ulonglonglong_t, nanoCDR);
  serializeFloat(float_tt, nanoCDR);
  serializeDouble(double_tt, nanoCDR);
  serializeLongDouble(longdouble_t, nanoCDR);
  serializeString(string_t, length, nanoCDR);
  serializeString(emptystring_t, length_2, nanoCDR);

  // Deseriazliation.
  deserializeChar(&char_out, nanoCDR);
  deserializeSignedChar(&octect_out, nanoCDR);
  deserializeShort(&short_out, nanoCDR);
  deserializeUnsignedShort(&ushort_out, nanoCDR);
  deserializeInt(&long_out, nanoCDR);
  deserializeUnsignedInt(&ulong_out, nanoCDR);
  deserializeLong(&longlong_out, nanoCDR);
  deserializeUnsignedLong(&ulonglong_out, nanoCDR);
  deserializeLongLong(&longlonglong_out, nanoCDR);
  deserializeUnsignedLongLong(&ulonglonglong_out, nanoCDR);
  deserializeFloat(&float_out, nanoCDR);
  deserializeDouble(&double_out, nanoCDR);
  deserializeLongDouble(&longdouble_out, nanoCDR);
  deserializeString(&string_out, &length_out, nanoCDR);
  deserializeString(&string_out_2, &length_out_2, nanoCDR);

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
}

TEST(nanoCDRTests, Arrays)
{
  int32_t i;
  char * char_out;
  unsigned char * uchar_out;
  int16_t * short_out;
  uint16_t * ushort_out;
  int32_t * int_out;
  uint32_t * uint_out;
  int64_t * long_out;
  uint64_t * ulong_out;
  long long * longlong_out;
  unsigned long long * ulonglong_out;
  float * float_out;
  double * double_out;
  long double * longdouble_out;
  char ** string_out;

  // Check good case.
  struct nanoBuffer * nanoCDR = NULL;
  // Check good case.
  newDynamicBuffer(&nanoCDR);

  int16_t result = 0;

  // Serialization.
  result += serializeCharArray(char_array_t, 5, nanoCDR); //5
  result += serializeUnsignedCharArray(octet_array_t, 5, nanoCDR); //5
  result += serializeShortArray(short_array_t, 5, nanoCDR); //10
  result += serializeUnsignedShortArray(ushort_array_t, 5, nanoCDR); //10
  result += serializeIntArray(long_array_t, 5, nanoCDR); //20
  result += serializeUnsignedIntArray(ulong_array_t, 5, nanoCDR); //20
  result += serializeLongArray(longlong_array_t, 5, nanoCDR); //20
  result += serializeUnsignedLongArray(ulonglong_array_t, 5, nanoCDR); //20
  result += serializeLongLongArray(longlonglong_array_t, 5, nanoCDR); //20
  result += serializeUnsignedLongLongArray(ulonglonglong_array_t, 5, nanoCDR); //20
  result += serializeFloatArray(float_array_t, 5, nanoCDR); //20
  result += serializeDoubleArray(double_array_t, 5, nanoCDR); //40
  result += serializeLongDoubleArray(longdouble_array_t, 5, nanoCDR); //40
  result += serializeStringArray(string_seq_t, 5, nanoCDR);

  //uint32_t serialized = getSerializedDataLength();

  EXPECT_EQ(result, 0);
  //EXPECT_EQ(serialized, 130);

  if(result == 0){
    // Deseriazliation.
    result += deserializeCharArray(&char_out, 5, nanoCDR);
    result += deserializeUnsignedCharArray(&uchar_out, 5, nanoCDR);
    result += deserializeShortArray(&short_out, 5, nanoCDR);
    result += deserializeUnsignedShortArray(&ushort_out, 5, nanoCDR);
    result += deserializeIntArray(&int_out, 5, nanoCDR);
    result += deserializeUnsignedIntArray(&uint_out, 5, nanoCDR);
    result += deserializeLongArray(&long_out, 5, nanoCDR);
    result += deserializeUnsignedLongArray(&ulong_out, 5, nanoCDR);
    result += deserializeLongLongArray(&longlong_out, 5, nanoCDR);
    result += deserializeUnsignedLongLongArray(&ulonglong_out, 5, nanoCDR);
    result += deserializeFloatArray(&float_out, 5, nanoCDR);
    result += deserializeDoubleArray(&double_out, 5, nanoCDR);
    result += deserializeLongDoubleArray(&longdouble_out, 5, nanoCDR);
    result += deserializeStringArray(&string_out, 5, nanoCDR);

    EXPECT_EQ(result, 0);

    if(result == 0){
      for(i = 0; i < 5; i++){
        EXPECT_EQ(char_array_t[i], char_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(octet_array_t[i], uchar_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(short_array_t[i], short_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ushort_array_t[i], ushort_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(long_array_t[i], int_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ulong_array_t[i], uint_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(longlong_array_t[i], long_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ulonglong_array_t[i], ulong_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(longlonglong_array_t[i], longlong_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ulonglonglong_array_t[i], ulonglong_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(float_array_t[i], float_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(double_array_t[i], double_out[i]);
      }
      for(i = 0; i < 5; i++){
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
    }
  }
}

TEST(nanoCDRTests, Sequences)
{
  int32_t i;
  char * char_out;
  uint32_t char_out_size;
  unsigned char * uchar_out;
  uint32_t uchar_out_size;
  int16_t * short_out;
  uint32_t short_out_size;
  uint16_t * ushort_out;
  uint32_t ushort_out_size;
  int32_t * int_out;
  uint32_t int_out_size;
  uint32_t * uint_out;
  uint32_t uint_out_size;
  int64_t * long_out;
  uint32_t long_out_size;
  uint64_t * ulong_out;
  uint32_t ulong_out_size;
  long long * longlong_out;
  uint32_t longlong_out_size;
  unsigned long long * ulonglong_out;
  uint32_t ulonglong_out_size;
  float * float_out;
  uint32_t float_out_size;
  double * double_out;
  uint32_t double_out_size;
  long double * longdouble_out;
  uint32_t longdouble_out_size;
  char ** string_out;
  uint32_t string_out_size;

  int16_t result = 0;


  // Check good case.
  struct nanoBuffer * nanoCDR = NULL;
  // Check good case.
  newDynamicBuffer(&nanoCDR);

  // Serialization.
  result += serializeCharSequence(char_seq_t, 5, nanoCDR); //9
  result += serializeUnsignedCharSequence(octet_seq_t, 5, nanoCDR); //9
  result += serializeShortSequence(short_seq_t, 5, nanoCDR);//14
  result += serializeUnsignedShortSequence(ushort_seq_t, 5, nanoCDR);//14
  result += serializeIntSequence(long_seq_t, 5, nanoCDR);//24
  result += serializeUnsignedIntSequence(ulong_seq_t, 5, nanoCDR);//24
  result += serializeLongSequence(longlong_seq_t, 5, nanoCDR);//24
  result += serializeUnsignedLongSequence(ulonglong_seq_t, 5, nanoCDR);//24
  result += serializeLongLongSequence(longlonglong_seq_t, 5, nanoCDR);//24
  result += serializeUnsignedLongLongSequence(ulonglonglong_seq_t, 5, nanoCDR);//24
  result += serializeFloatSequence(float_seq_t, 5, nanoCDR);//24
  result += serializeDoubleSequence(double_seq_t, 5, nanoCDR);//44
  result += serializeLongDoubleSequence(longdouble_seq_t, 5, nanoCDR);//44
  result += serializeStringSequence(string_seq_t, 5, nanoCDR);

  //uint32_t serialized = getSerializedDataLength();
  //EXPECT_EQ(serialized, 162);

  EXPECT_EQ(result, 0);

  if(result == 0){
    // Deseriazliation.
    result += deserializeCharSequence(&char_out, &char_out_size, nanoCDR);
    result += deserializeUnsignedCharSequence(&uchar_out, &uchar_out_size, nanoCDR);
    result += deserializeShortSequence(&short_out, &short_out_size, nanoCDR);
    result += deserializeUnsignedShortSequence(&ushort_out, &ushort_out_size, nanoCDR);
    result += deserializeIntSequence(&int_out, &int_out_size, nanoCDR);
    result += deserializeUnsignedIntSequence(&uint_out, &uint_out_size, nanoCDR);
    result += deserializeLongSequence(&long_out, &long_out_size, nanoCDR);
    result += deserializeUnsignedLongSequence(&ulong_out, &ulong_out_size, nanoCDR);
    result += deserializeLongLongSequence(&longlong_out, &longlong_out_size, nanoCDR);
    result += deserializeUnsignedLongLongSequence(&ulonglong_out, &ulonglong_out_size, nanoCDR);
    result += deserializeFloatSequence(&float_out, &float_out_size, nanoCDR);
    result += deserializeDoubleSequence(&double_out, &double_out_size, nanoCDR);
    result += deserializeLongDoubleSequence(&longdouble_out, &longdouble_out_size, nanoCDR);
    result += deserializeStringSequence(&string_out, &string_out_size, nanoCDR);

    EXPECT_EQ(result, 0);

    if(result == 0){
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

      for(i = 0; i < 5; i++){
        EXPECT_EQ(char_seq_t[i], char_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(octet_seq_t[i], uchar_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(short_seq_t[i], short_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ushort_seq_t[i], ushort_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(long_seq_t[i], int_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ulong_seq_t[i], uint_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(longlong_seq_t[i], long_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ulonglong_seq_t[i], ulong_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(longlonglong_seq_t[i], longlong_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ulonglonglong_seq_t[i], ulonglong_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(float_seq_t[i], float_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(double_seq_t[i], double_out[i]);
      }
      for(i = 0; i < 5; i++){
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
    }
  }
}

TEST(nanoCDRTests, All)
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
  char * string_out;
  char * string_out_2;

  //ARRAYS
  int32_t i;
  char * char_array_out;
  unsigned char * uchar_array_out;
  int16_t * short_array_out;
  uint16_t * ushort_array_out;
  int32_t * int_array_out;
  uint32_t * uint_array_out;
  int64_t * long_array_out;
  uint64_t * ulong_array_out;
  long long * longlong_array_out;
  unsigned long long * ulonglong_array_out;
  float * float_array_out;
  double * double_array_out;
  long double * longdouble_array_out;
  char ** string_array_out;

  //SEQUENCES
  char * char_seq_out;
  uint32_t char_out_size;
  unsigned char * uchar_seq_out;
  uint32_t uchar_out_size;
  int16_t * short_seq_out;
  uint32_t short_out_size;
  uint16_t * ushort_seq_out;
  uint32_t ushort_out_size;
  int32_t * int_seq_out;
  uint32_t int_out_size;
  uint32_t * uint_seq_out;
  uint32_t uint_out_size;
  int64_t * long_seq_out;
  uint32_t long_out_size;
  uint64_t * ulong_seq_out;
  uint32_t ulong_out_size;
  long long * longlong_seq_out;
  uint32_t longlong_out_size;
  unsigned long long * ulonglong_seq_out;
  uint32_t ulonglong_out_size;
  float * float_seq_out;
  uint32_t float_out_size;
  double * double_seq_out;
  uint32_t double_out_size;
  long double * longdouble_seq_out;
  uint32_t longdouble_out_size;
  char ** string_seq_out;
  uint32_t string_out_size;


  // Check good case.
  struct nanoBuffer * nanoCDR = NULL;
  // Check good case.
  newDynamicBuffer(&nanoCDR);

  const uint32_t length = (uint32_t)std::strlen(string_t);
  uint32_t length_out;

  int16_t result = 0;

  const uint32_t length_2 = (uint32_t)std::strlen(emptystring_t);
  uint32_t length_out_2;

  // Serialization.
  result += serializeChar(char_t, nanoCDR);
  result += serializeSignedChar(octet_t, nanoCDR);
  result += serializeShort(short_t, nanoCDR);
  result += serializeUnsignedShort(ushort_t, nanoCDR);
  result += serializeInt(long_t, nanoCDR);
  result += serializeUnsignedInt(ulong_t, nanoCDR);
  result += serializeLong(longlong_t, nanoCDR);
  result += serializeUnsignedLong(ulonglong_t, nanoCDR);
  result += serializeLongLong(longlonglong_t, nanoCDR);
  result += serializeUnsignedLongLong(ulonglonglong_t, nanoCDR);
  result += serializeFloat(float_tt, nanoCDR);
  result += serializeDouble(double_tt, nanoCDR);
  result += serializeLongDouble(longdouble_t, nanoCDR);
  result += serializeString(string_t, length, nanoCDR);
  result += serializeString(emptystring_t, length_2, nanoCDR);

  result += serializeCharArray(char_array_t, 5, nanoCDR); //5
  result += serializeUnsignedCharArray(octet_array_t, 5, nanoCDR); //5
  result += serializeShortArray(short_array_t, 5, nanoCDR); //10
  result += serializeUnsignedShortArray(ushort_array_t, 5, nanoCDR); //10
  result += serializeIntArray(long_array_t, 5, nanoCDR); //20
  result += serializeUnsignedIntArray(ulong_array_t, 5, nanoCDR); //20

  result += serializeLongArray(longlong_array_t, 5, nanoCDR);
  result += serializeUnsignedLongArray(ulonglong_array_t, 5, nanoCDR);
  result += serializeLongLongArray(longlonglong_array_t, 5, nanoCDR);
  result += serializeUnsignedLongLongArray(ulonglonglong_array_t, 5, nanoCDR);

  result += serializeFloatArray(float_array_t, 5, nanoCDR); //20
  result += serializeDoubleArray(double_array_t, 5, nanoCDR); //40
  result += serializeLongDoubleArray(longdouble_array_t, 5, nanoCDR);
  result += serializeStringArray(string_seq_t, 5, nanoCDR);

  result += serializeCharSequence(char_seq_t, 5, nanoCDR); //9
  result += serializeUnsignedCharSequence(octet_seq_t, 5, nanoCDR); //9
  result += serializeShortSequence(short_seq_t, 5, nanoCDR);//14
  result += serializeUnsignedShortSequence(ushort_seq_t, 5, nanoCDR);//14
  result += serializeIntSequence(long_seq_t, 5, nanoCDR);//24
  result += serializeUnsignedIntSequence(ulong_seq_t, 5, nanoCDR);//24

  result += serializeLongSequence(longlong_seq_t, 5, nanoCDR);
  result += serializeUnsignedLongSequence(ulonglong_seq_t, 5, nanoCDR);
  result += serializeLongLongSequence(longlonglong_seq_t, 5, nanoCDR);
  result += serializeUnsignedLongLongSequence(ulonglonglong_seq_t, 5, nanoCDR);

  result += serializeFloatSequence(float_seq_t, 5, nanoCDR);//24
  result += serializeDoubleSequence(double_seq_t, 5, nanoCDR);//44
  result += serializeLongDoubleSequence(longdouble_seq_t, 5, nanoCDR);//44
  result += serializeStringSequence(string_seq_t, 5, nanoCDR);

  //uint32_t serialized = getSerializedDataLength();
  //EXPECT_EQ(serialized, 357);
  EXPECT_EQ(result, 0);

  if(result == 0){
  // Deseriazliation.
    result += deserializeChar(&char_out, nanoCDR);
    result += deserializeSignedChar(&octect_out, nanoCDR);
    result += deserializeShort(&short_out, nanoCDR);
    result += deserializeUnsignedShort(&ushort_out, nanoCDR);
    result += deserializeInt(&long_out, nanoCDR);
    result += deserializeUnsignedInt(&ulong_out, nanoCDR);
    result += deserializeLong(&longlong_out, nanoCDR);
    result += deserializeUnsignedLong(&ulonglong_out, nanoCDR);
    result += deserializeLongLong(&longlonglong_out, nanoCDR);
    result += deserializeUnsignedLongLong(&ulonglonglong_out, nanoCDR);
    result += deserializeFloat(&float_out, nanoCDR);
    result += deserializeDouble(&double_out, nanoCDR);
    result += deserializeLongDouble(&longdouble_out, nanoCDR);
    result += deserializeString(&string_out, &length_out, nanoCDR);
    result += deserializeString(&string_out_2, &length_out_2, nanoCDR);

    result += deserializeCharArray(&char_array_out, 5, nanoCDR);
    result += deserializeUnsignedCharArray(&uchar_array_out, 5, nanoCDR);
    result += deserializeShortArray(&short_array_out, 5, nanoCDR);
    result += deserializeUnsignedShortArray(&ushort_array_out, 5, nanoCDR);
    result += deserializeIntArray(&int_array_out, 5, nanoCDR);
    result += deserializeUnsignedIntArray(&uint_array_out, 5, nanoCDR);

    result += deserializeLongArray(&long_array_out, 5, nanoCDR);
    result += deserializeUnsignedLongArray(&ulong_array_out, 5, nanoCDR);
    result += deserializeLongLongArray(&longlong_array_out, 5, nanoCDR);
    result += deserializeUnsignedLongLongArray(&ulonglong_array_out, 5, nanoCDR);

    result += deserializeFloatArray(&float_array_out, 5, nanoCDR);
    result += deserializeDoubleArray(&double_array_out, 5, nanoCDR);
    result += deserializeLongDoubleArray(&longdouble_array_out, 5, nanoCDR);
    result += deserializeStringArray(&string_array_out, 5, nanoCDR);

    result += deserializeCharSequence(&char_seq_out, &char_out_size, nanoCDR);
    result += deserializeUnsignedCharSequence(&uchar_seq_out, &uchar_out_size, nanoCDR);
    result += deserializeShortSequence(&short_seq_out, &short_out_size, nanoCDR);
    result += deserializeUnsignedShortSequence(&ushort_seq_out, &ushort_out_size, nanoCDR);
    result += deserializeIntSequence(&int_seq_out, &int_out_size, nanoCDR);
    result += deserializeUnsignedIntSequence(&uint_seq_out, &uint_out_size, nanoCDR);

    result += deserializeLongSequence(&long_seq_out, &long_out_size, nanoCDR);
    result += deserializeUnsignedLongSequence(&ulong_seq_out, &ulong_out_size, nanoCDR);
    result += deserializeLongLongSequence(&longlong_seq_out, &longlong_out_size, nanoCDR);
    result += deserializeUnsignedLongLongSequence(&ulonglong_seq_out, &ulonglong_out_size, nanoCDR);

    result += deserializeFloatSequence(&float_seq_out, &float_out_size, nanoCDR);
    result += deserializeDoubleSequence(&double_seq_out, &double_out_size, nanoCDR);
    result += deserializeLongDoubleSequence(&longdouble_seq_out, &longdouble_out_size, nanoCDR);
    result += deserializeStringSequence(&string_seq_out, &string_out_size, nanoCDR);

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

      for(i = 0; i < 5; i++){
        EXPECT_EQ(char_array_t[i], char_array_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(octet_array_t[i], uchar_array_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(short_array_t[i], short_array_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ushort_array_t[i], ushort_array_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(long_array_t[i], int_array_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ulong_array_t[i], uint_array_out[i]);
      }

      for(i = 0; i < 5; i++){
        EXPECT_EQ(longlong_array_t[i], long_array_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ulonglong_array_t[i], ulong_array_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(longlonglong_array_t[i], longlong_array_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ulonglonglong_array_t[i], ulonglong_array_out[i]);
      }

      for(i = 0; i < 5; i++){
        EXPECT_EQ(float_array_t[i], float_array_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(double_array_t[i], double_array_out[i]);
      }
      for(i = 0; i < 5; i++){
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

      for(i = 0; i < 5; i++){
        EXPECT_EQ(char_seq_t[i], char_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(octet_seq_t[i], uchar_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(short_seq_t[i], short_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ushort_seq_t[i], ushort_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(long_seq_t[i], int_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ulong_seq_t[i], uint_seq_out[i]);
      }

      for(i = 0; i < 5; i++){
        EXPECT_EQ(longlong_seq_t[i], long_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ulonglong_seq_t[i], ulong_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(longlonglong_seq_t[i], longlong_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ulonglonglong_seq_t[i], ulonglong_seq_out[i]);
      }

      for(i = 0; i < 5; i++){
        EXPECT_EQ(float_seq_t[i], float_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(double_seq_t[i], double_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
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
    }
  }
}

TEST(nanoCDRTests, AllEndianness)
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
  char * string_out;
  char * string_out_2;

  //ARRAYS
  int32_t i;
  char * char_array_out;
  unsigned char * uchar_array_out;
  int16_t * short_array_out;
  uint16_t * ushort_array_out;
  int32_t * int_array_out;
  uint32_t * uint_array_out;
  int64_t * long_array_out;
  uint64_t * ulong_array_out;
  long long * longlong_array_out;
  unsigned long long * ulonglong_array_out;
  float * float_array_out;
  double * double_array_out;
  long double * longdouble_array_out;
  char ** string_array_out;

  //SEQUENCES
  char * char_seq_out;
  uint32_t char_out_size;
  unsigned char * uchar_seq_out;
  uint32_t uchar_out_size;
  int16_t * short_seq_out;
  uint32_t short_out_size;
  uint16_t * ushort_seq_out;
  uint32_t ushort_out_size;
  int32_t * int_seq_out;
  uint32_t int_out_size;
  uint32_t * uint_seq_out;
  uint32_t uint_out_size;
  int64_t * long_seq_out;
  uint32_t long_out_size;
  uint64_t * ulong_seq_out;
  uint32_t ulong_out_size;
  long long * longlong_seq_out;
  uint32_t longlong_out_size;
  unsigned long long * ulonglong_seq_out;
  uint32_t ulonglong_out_size;
  float * float_seq_out;
  uint32_t float_out_size;
  double * double_seq_out;
  uint32_t double_out_size;
  long double * longdouble_seq_out;
  uint32_t longdouble_out_size;
  char ** string_seq_out;
  uint32_t string_out_size;


  // Check good case.
  struct nanoBuffer * nanoCDR = NULL;
  // Check good case.
  newDynamicBuffer(&nanoCDR);

  const uint32_t length = (uint32_t)std::strlen(string_t);
  uint32_t length_out;

  int16_t result = 0;

  const uint32_t length_2 = (uint32_t)std::strlen(emptystring_t);
  uint32_t length_out_2;

  // Serialization.
  result += serializeChar(char_t, nanoCDR);
  result += serializeSignedChar(octet_t, nanoCDR);
  result += serializeShortEndianness(short_t, endianness, nanoCDR);
  result += serializeUnsignedShortEndianness(ushort_t, endianness, nanoCDR);
  result += serializeIntEndianness(long_t, endianness, nanoCDR);
  result += serializeUnsignedIntEndianness(ulong_t, endianness, nanoCDR);
  result += serializeLongEndianness(longlong_t, endianness, nanoCDR);
  result += serializeUnsignedLongEndianness(ulonglong_t, endianness, nanoCDR);
  result += serializeLongLongEndianness(longlonglong_t, endianness, nanoCDR);
  result += serializeUnsignedLongLongEndianness(ulonglonglong_t, endianness, nanoCDR);
  result += serializeFloatEndianness(float_tt, endianness, nanoCDR);
  result += serializeDoubleEndianness(double_tt, endianness, nanoCDR);
  result += serializeLongDoubleEndianness(longdouble_t, endianness, nanoCDR);
  result += serializeStringEndianness(string_t, length, endianness, nanoCDR);
  result += serializeStringEndianness(emptystring_t, length_2, endianness, nanoCDR);

  result += serializeCharArray(char_array_t, 5, nanoCDR); //5
  result += serializeUnsignedCharArray(octet_array_t, 5, nanoCDR); //5
  result += serializeShortArrayEndianness(short_array_t, 5, endianness, nanoCDR); //10
  result += serializeUnsignedShortArrayEndianness(ushort_array_t, 5, endianness, nanoCDR); //10
  result += serializeIntArrayEndianness(long_array_t, 5, endianness, nanoCDR); //20
  result += serializeUnsignedIntArrayEndianness(ulong_array_t, 5, endianness, nanoCDR); //20

  result += serializeLongArrayEndianness(longlong_array_t, 5, endianness, nanoCDR);
  result += serializeUnsignedLongArrayEndianness(ulonglong_array_t, 5, endianness, nanoCDR);
  result += serializeLongLongArrayEndianness(longlonglong_array_t, 5, endianness, nanoCDR);
  result += serializeUnsignedLongLongArrayEndianness(ulonglonglong_array_t, 5, endianness, nanoCDR);

  result += serializeFloatArrayEndianness(float_array_t, 5, endianness, nanoCDR); //20
  result += serializeDoubleArrayEndianness(double_array_t, 5, endianness, nanoCDR); //40
  result += serializeLongDoubleArrayEndianness(longdouble_array_t, 5, endianness, nanoCDR);
  result += serializeStringArrayEndianness(string_seq_t, 5, endianness, nanoCDR);

  result += serializeCharSequenceEndianness(char_seq_t, 5, endianness, nanoCDR); //9
  result += serializeUnsignedCharSequenceEndianness(octet_seq_t, 5, endianness, nanoCDR); //9
  result += serializeShortSequenceEndianness(short_seq_t, 5, endianness, nanoCDR);//14
  result += serializeUnsignedShortSequenceEndianness(ushort_seq_t, 5, endianness, nanoCDR);//14
  result += serializeIntSequenceEndianness(long_seq_t, 5, endianness, nanoCDR);//24
  result += serializeUnsignedIntSequenceEndianness(ulong_seq_t, 5, endianness, nanoCDR);//24

  result += serializeLongSequenceEndianness(longlong_seq_t, 5, endianness, nanoCDR);
  result += serializeUnsignedLongSequenceEndianness(ulonglong_seq_t, 5, endianness, nanoCDR);
  result += serializeLongLongSequenceEndianness(longlonglong_seq_t, 5, endianness, nanoCDR);
  result += serializeUnsignedLongLongSequenceEndianness(ulonglonglong_seq_t, 5, endianness, nanoCDR);

  result += serializeFloatSequenceEndianness(float_seq_t, 5, endianness, nanoCDR);//24
  result += serializeDoubleSequenceEndianness(double_seq_t, 5, endianness, nanoCDR);//44
  result += serializeLongDoubleSequenceEndianness(longdouble_seq_t, 5, endianness, nanoCDR);//44
  result += serializeStringSequenceEndianness(string_seq_t, 5, endianness, nanoCDR);

  //uint32_t serialized = getSerializedDataLength();
  //EXPECT_EQ(serialized, 357);
  EXPECT_EQ(result, 0);

  if(result == 0){
  // Deseriazliation.
    result += deserializeChar(&char_out, nanoCDR);
    result += deserializeSignedChar(&octect_out, nanoCDR);
    result += deserializeShortEndianness(&short_out, endianness, nanoCDR);
    result += deserializeUnsignedShortEndianness(&ushort_out, endianness, nanoCDR);
    result += deserializeIntEndianness(&long_out, endianness, nanoCDR);
    result += deserializeUnsignedIntEndianness(&ulong_out, endianness, nanoCDR);
    result += deserializeLongEndianness(&longlong_out, endianness, nanoCDR);
    result += deserializeUnsignedLongEndianness(&ulonglong_out, endianness, nanoCDR);
    result += deserializeLongLongEndianness(&longlonglong_out, endianness, nanoCDR);
    result += deserializeUnsignedLongLongEndianness(&ulonglonglong_out, endianness, nanoCDR);
    result += deserializeFloatEndianness(&float_out, endianness, nanoCDR);
    result += deserializeDoubleEndianness(&double_out, endianness, nanoCDR);
    result += deserializeLongDoubleEndianness(&longdouble_out, endianness, nanoCDR);
    result += deserializeStringEndianness(&string_out, &length_out, endianness, nanoCDR);
    result += deserializeStringEndianness(&string_out_2, &length_out_2, endianness, nanoCDR);

    result += deserializeCharArray(&char_array_out, 5, nanoCDR);
    result += deserializeUnsignedCharArray(&uchar_array_out, 5, nanoCDR);
    result += deserializeShortArrayEndianness(&short_array_out, 5, endianness, nanoCDR);
    result += deserializeUnsignedShortArrayEndianness(&ushort_array_out, 5, endianness, nanoCDR);
    result += deserializeIntArrayEndianness(&int_array_out, 5, endianness, nanoCDR);
    result += deserializeUnsignedIntArrayEndianness(&uint_array_out, 5, endianness, nanoCDR);

    result += deserializeLongArrayEndianness(&long_array_out, 5, endianness, nanoCDR);
    result += deserializeUnsignedLongArrayEndianness(&ulong_array_out, 5, endianness, nanoCDR);
    result += deserializeLongLongArrayEndianness(&longlong_array_out, 5, endianness, nanoCDR);
    result += deserializeUnsignedLongLongArrayEndianness(&ulonglong_array_out, 5, endianness, nanoCDR);

    result += deserializeFloatArrayEndianness(&float_array_out, 5, endianness, nanoCDR);
    result += deserializeDoubleArrayEndianness(&double_array_out, 5, endianness, nanoCDR);
    result += deserializeLongDoubleArrayEndianness(&longdouble_array_out, 5, endianness, nanoCDR);
    result += deserializeStringArrayEndianness(&string_array_out, 5, endianness, nanoCDR);

    result += deserializeCharSequenceEndianness(&char_seq_out, &char_out_size, endianness, nanoCDR);
    result += deserializeUnsignedCharSequenceEndianness(&uchar_seq_out, &uchar_out_size, endianness, nanoCDR);
    result += deserializeShortSequenceEndianness(&short_seq_out, &short_out_size, endianness, nanoCDR);
    result += deserializeUnsignedShortSequenceEndianness(&ushort_seq_out, &ushort_out_size, endianness, nanoCDR);
    result += deserializeIntSequenceEndianness(&int_seq_out, &int_out_size, endianness, nanoCDR);
    result += deserializeUnsignedIntSequenceEndianness(&uint_seq_out, &uint_out_size, endianness, nanoCDR);

    result += deserializeLongSequenceEndianness(&long_seq_out, &long_out_size, endianness, nanoCDR);
    result += deserializeUnsignedLongSequenceEndianness(&ulong_seq_out, &ulong_out_size, endianness, nanoCDR);
    result += deserializeLongLongSequenceEndianness(&longlong_seq_out, &longlong_out_size, endianness, nanoCDR);
    result += deserializeUnsignedLongLongSequenceEndianness(&ulonglong_seq_out, &ulonglong_out_size, endianness, nanoCDR);

    result += deserializeFloatSequenceEndianness(&float_seq_out, &float_out_size, endianness, nanoCDR);
    result += deserializeDoubleSequenceEndianness(&double_seq_out, &double_out_size, endianness, nanoCDR);
    result += deserializeLongDoubleSequenceEndianness(&longdouble_seq_out, &longdouble_out_size, endianness, nanoCDR);
    result += deserializeStringSequenceEndianness(&string_seq_out, &string_out_size, endianness, nanoCDR);

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

      for(i = 0; i < 5; i++){
        EXPECT_EQ(char_array_t[i], char_array_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(octet_array_t[i], uchar_array_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(short_array_t[i], short_array_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ushort_array_t[i], ushort_array_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(long_array_t[i], int_array_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ulong_array_t[i], uint_array_out[i]);
      }

      for(i = 0; i < 5; i++){
        EXPECT_EQ(longlong_array_t[i], long_array_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ulonglong_array_t[i], ulong_array_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(longlonglong_array_t[i], longlong_array_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ulonglonglong_array_t[i], ulonglong_array_out[i]);
      }

      for(i = 0; i < 5; i++){
        EXPECT_EQ(float_array_t[i], float_array_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(double_array_t[i], double_array_out[i]);
      }
      for(i = 0; i < 5; i++){
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

      for(i = 0; i < 5; i++){
        EXPECT_EQ(char_seq_t[i], char_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(octet_seq_t[i], uchar_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(short_seq_t[i], short_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ushort_seq_t[i], ushort_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(long_seq_t[i], int_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ulong_seq_t[i], uint_seq_out[i]);
      }

      for(i = 0; i < 5; i++){
        EXPECT_EQ(longlong_seq_t[i], long_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ulonglong_seq_t[i], ulong_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(longlonglong_seq_t[i], longlong_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(ulonglonglong_seq_t[i], ulonglong_seq_out[i]);
      }

      for(i = 0; i < 5; i++){
        EXPECT_EQ(float_seq_t[i], float_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(double_seq_t[i], double_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
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
    }
  }
}

TEST(nanoCDRBasicEndiannessTests, Short)
{
    int16_t short_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeShortEndianness(short_t, endianness, nanoCDR);

    // Deseriazliation.
    deserializeShortEndianness(&short_out, endianness, nanoCDR);

    EXPECT_EQ(short_out, short_t);
}

TEST(nanoCDRBasicEndiannessTests, UnsignedShort)
{
    uint16_t ushort_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedShortEndianness(ushort_t, endianness, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedShortEndianness(&ushort_out, endianness, nanoCDR);

    EXPECT_EQ(ushort_out, ushort_t);
}


TEST(nanoCDRBasicEndiannessTests, Int)
{
    int32_t long_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeIntEndianness(long_t, endianness, nanoCDR);

    // Deseriazliation.
    deserializeIntEndianness(&long_out, endianness, nanoCDR);

    EXPECT_EQ(long_out, long_t);
}

TEST(nanoCDRBasicEndiannessTests, UnsignedInt)
{
    uint32_t ulong_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedIntEndianness(ulong_t, endianness, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedIntEndianness(&ulong_out, endianness, nanoCDR);

    EXPECT_EQ(ulong_out, ulong_t);
}

TEST(nanoCDRBasicEndiannessTests, Long)
{
    int64_t long_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeLongEndianness(longlong_t, endianness, nanoCDR);

    // Deseriazliation.
    deserializeLongEndianness(&long_out, endianness, nanoCDR);

    EXPECT_EQ(long_out, longlong_t);
}

TEST(nanoCDRBasicEndiannessTests, uLong)
{
    uint64_t ulong_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedLongEndianness(ulonglong_t, endianness, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedLongEndianness(&ulong_out, endianness, nanoCDR);

    EXPECT_EQ(ulong_out, ulonglong_t);
}

TEST(nanoCDRBasicEndiannessTests, LongLong)
{
    long long longlong_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeLongLongEndianness(longlonglong_t, endianness, nanoCDR);

    // Deseriazliation.
    deserializeLongLongEndianness(&longlong_out, endianness, nanoCDR);

    EXPECT_EQ(longlong_out, longlonglong_t);
}

TEST(nanoCDRBasicEndiannessTests, uLongLong)
{
    unsigned long long ulonglong_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedLongLongEndianness(ulonglonglong_t, endianness, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedLongLongEndianness(&ulonglong_out, endianness, nanoCDR);

    EXPECT_EQ(ulonglong_out, ulonglonglong_t);
}

TEST(nanoCDRBasicEndiannessTests, Float)
{
    float float_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeFloatEndianness(float_tt, endianness, nanoCDR);

    // Deseriazliation.
    deserializeFloatEndianness(&float_out, endianness, nanoCDR);

    EXPECT_EQ(float_out, float_tt);
}

TEST(nanoCDRBasicEndiannessTests, Double)
{
    double double_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeDoubleEndianness(double_tt, endianness, nanoCDR);

    // Deseriazliation.
    deserializeDoubleEndianness(&double_out, endianness, nanoCDR);

    EXPECT_EQ(double_out, double_tt);
}

TEST(nanoCDRBasicEndiannessTests, LongDouble)
{
    long double longdouble_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeLongDoubleEndianness(longdouble_t, endianness, nanoCDR);

    // Deseriazliation.
    deserializeLongDoubleEndianness(&longdouble_out, endianness, nanoCDR);

    EXPECT_EQ(longdouble_out, longdouble_t);
}

TEST(nanoCDRBasicEndiannessTests, String)
{
    char * string_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    const uint32_t length = (uint32_t)std::strlen(string_t);
    uint32_t length_out;

    // Serialization.
    serializeStringEndianness(string_t, length, endianness, nanoCDR);

    // Deseriazliation.
    deserializeStringEndianness(&string_out, &length_out, endianness, nanoCDR);

    uint32_t comparative = std::strcmp(string_out, string_t);

    EXPECT_EQ(comparative, 0);
    EXPECT_EQ(length, length_out);
    free(string_out);
}

TEST(nanoCDRBasicEndiannessTests, EmptyString)
{
    char * string_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    const uint32_t length = (uint32_t)std::strlen(emptystring_t);
    uint32_t length_out;

    // Serialization.
    serializeStringEndianness(emptystring_t, length, endianness, nanoCDR);

    // Deseriazliation.
    deserializeStringEndianness(&string_out, &length_out, endianness, nanoCDR);

    uint32_t comparative = std::strcmp(string_out, emptystring_t);

    EXPECT_EQ(comparative, 0);
    EXPECT_EQ(length, length_out);
    free(string_out);
}

TEST(nanoCDRArrayEndiannessTests, ShortArray)
{
    int16_t * short_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeShortArrayEndianness(short_array_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeShortArrayEndianness(&short_out, 5, endianness, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(short_array_t[i], short_out[i]);
    }
    free(short_out);
}

TEST(nanoCDRArrayEndiannessTests, UnsignedShortArray)
{
    uint16_t * ushort_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedShortArrayEndianness(ushort_array_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedShortArrayEndianness(&ushort_out, 5, endianness, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(ushort_array_t[i], ushort_out[i]);
    }
    free(ushort_out);
}

TEST(nanoCDRArrayEndiannessTests, IntArray)
{
    int32_t * int_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeIntArrayEndianness(long_array_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeIntArrayEndianness(&int_out, 5, endianness, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(long_array_t[i], int_out[i]);
    }
    free(int_out);
}

TEST(nanoCDRArrayEndiannessTests, UnsignedIntArray)
{
    uint32_t * uint_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedIntArrayEndianness(ulong_array_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedIntArrayEndianness(&uint_out, 5, endianness, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(ulong_array_t[i], uint_out[i]);
    }
    free(uint_out);
}

TEST(nanoCDRArrayEndiannessTests, LongArray)
{
    int64_t * long_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeLongArrayEndianness(longlong_array_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeLongArrayEndianness(&long_out, 5, endianness, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(longlong_array_t[i], long_out[i]);
    }
    free(long_out);
}

TEST(nanoCDRArrayEndiannessTests, ULongArray)
{
    uint64_t * ulong_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedLongArrayEndianness(ulonglong_array_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedLongArrayEndianness(&ulong_out, 5, endianness, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(ulonglong_array_t[i], ulong_out[i]);
    }
    free(ulong_out);
}

TEST(nanoCDRArrayEndiannessTests, LongLongArray)
{
    long long * longlong_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeLongLongArrayEndianness(longlonglong_array_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeLongLongArrayEndianness(&longlong_out, 5, endianness, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(longlonglong_array_t[i], longlong_out[i]);
    }
    free(longlong_out);
}

TEST(nanoCDRArrayEndiannessTests, ULongLongArray)
{
    unsigned long long * ulonglong_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedLongLongArrayEndianness(ulonglonglong_array_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedLongLongArrayEndianness(&ulonglong_out, 5, endianness, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(ulonglonglong_array_t[i], ulonglong_out[i]);
    }
    free(ulonglong_out);
}

TEST(nanoCDRArrayEndiannessTests, FloatArray)
{
    float * float_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeFloatArrayEndianness(float_array_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeFloatArrayEndianness(&float_out, 5, endianness, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(float_array_t[i], float_out[i]);
    }
    free(float_out);
}

TEST(nanoCDRArrayEndiannessTests, DoubleArray)
{
    double * double_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeDoubleArrayEndianness(double_array_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeDoubleArrayEndianness(&double_out, 5, endianness, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(double_array_t[i], double_out[i]);
    }

    free(double_out);
}

TEST(nanoCDRArrayEndiannessTests, LongDoubleArray)
{
    long double * longdouble_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeLongDoubleArrayEndianness(longdouble_array_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeLongDoubleArrayEndianness(&longdouble_out, 5, endianness, nanoCDR);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(longdouble_array_t[i], longdouble_out[i]);
    }
    free(longdouble_out);
}

TEST(nanoCDRArrayEndiannessTests, StringArray)
{
    char ** string_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeStringArrayEndianness(string_seq_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeStringArrayEndianness(&string_out, 5, endianness, nanoCDR);

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
}

TEST(nanoCDRSequencesEndiannessTests, CharSequence)
{
    char * char_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeCharSequenceEndianness(char_seq_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeCharSequenceEndianness(&char_out, &size_out, endianness, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(char_seq_t[i], char_out[i]);
    }

    free(char_out);
}

TEST(nanoCDRSequencesEndiannessTests, UnsignedCharSequence)
{
    unsigned char * char_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedCharSequenceEndianness(octet_seq_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedCharSequenceEndianness(&char_out, &size_out, endianness, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(octet_seq_t[i], char_out[i]);
    }

    free(char_out);
}

TEST(nanoCDRSequencesEndiannessTests, ShortSequence)
{
    int16_t * short_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeShortSequenceEndianness(short_seq_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeShortSequenceEndianness(&short_out, &size_out, endianness, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(short_seq_t[i], short_out[i]);
    }

    free(short_out);
}

TEST(nanoCDRSequencesEndiannessTests, UnsignedShortSequence)
{
    uint16_t * ushort_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedShortSequenceEndianness(ushort_seq_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedShortSequenceEndianness(&ushort_out, &size_out, endianness, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(ushort_seq_t[i], ushort_out[i]);
    }

    free(ushort_out);
}

TEST(nanoCDRSequencesEndiannessTests, IntSequence)
{
    int32_t * int_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeIntSequenceEndianness(long_seq_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeIntSequenceEndianness(&int_out, &size_out, endianness, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(long_seq_t[i], int_out[i]);
    }

    free(int_out);
}

TEST(nanoCDRSequencesEndiannessTests, UnsignedIntSequence)
{
    uint32_t * uint_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedIntSequenceEndianness(ulong_seq_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedIntSequenceEndianness(&uint_out, &size_out, endianness, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(ulong_seq_t[i], uint_out[i]);
    }

    free(uint_out);
}

TEST(nanoCDRSequencesEndiannessTests, LongSequence)
{
    int64_t * long_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeLongSequenceEndianness(longlong_seq_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeLongSequenceEndianness(&long_out, &size_out, endianness, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(longlong_seq_t[i], long_out[i]);
    }

    free(long_out);
}

TEST(nanoCDRSequencesEndiannessTests, ULongSequence)
{
    uint64_t * ulong_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedLongSequenceEndianness(ulonglong_seq_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedLongSequenceEndianness(&ulong_out, &size_out, endianness, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(ulonglong_seq_t[i], ulong_out[i]);
    }

    free(ulong_out);
}

TEST(nanoCDRSequencesEndiannessTests, LongLongSequence)
{
    long long * longlong_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeLongLongSequenceEndianness(longlonglong_seq_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeLongLongSequenceEndianness(&longlong_out, &size_out, endianness, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(longlonglong_seq_t[i], longlong_out[i]);
    }

    free(longlong_out);
}

TEST(nanoCDRSequencesEndiannessTests, ULongLongSequence)
{
    unsigned long long * ulonglong_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeUnsignedLongLongSequenceEndianness(ulonglonglong_seq_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeUnsignedLongLongSequenceEndianness(&ulonglong_out, &size_out, endianness, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(ulonglonglong_seq_t[i], ulonglong_out[i]);
    }

    free(ulonglong_out);
}

TEST(nanoCDRSequencesEndiannessTests, FloatSequence)
{
    float * float_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeFloatSequenceEndianness(float_seq_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeFloatSequenceEndianness(&float_out, &size_out, endianness, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(float_seq_t[i], float_out[i]);
    }

    free(float_out);
}

TEST(nanoCDRSequencesEndiannessTests, DoubleSequence)
{
    double * double_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeDoubleSequenceEndianness(double_seq_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeDoubleSequenceEndianness(&double_out, &size_out, endianness, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(double_seq_t[i], double_out[i]);
    }

    free(double_out);
}

TEST(nanoCDRSequencesEndiannessTests, LongDoubleSequence)
{
    long double * longdouble_out;
    uint32_t size_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);
    // Serialization.
    serializeLongDoubleSequenceEndianness(longdouble_seq_t, 5, endianness, nanoCDR);

    // Deseriazliation.
    deserializeLongDoubleSequenceEndianness(&longdouble_out, &size_out, endianness, nanoCDR);

    EXPECT_EQ(size_out, 5);

    int32_t i;
    for(i = 0; i < 5; i++)
    {
      EXPECT_EQ(longdouble_seq_t[i], longdouble_out[i]);
    }

    free(longdouble_out);
}

TEST(nanoCDRSequencesEndiannessTests, StringSequence)
{
    char ** string_out;
    // Check good case.
    struct nanoBuffer * nanoCDR = NULL;
    // Check good case.
    newDynamicBuffer(&nanoCDR);

    // Serialization.
    serializeStringSequenceEndianness(string_seq_t, 5, endianness, nanoCDR);

    uint32_t size_out;

    // Deseriazliation.
    deserializeStringSequenceEndianness(&string_out, &size_out, endianness, nanoCDR);

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
}
