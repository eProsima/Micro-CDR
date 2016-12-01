#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cstring>

#include <gtest/gtest.h>

extern "C" {
  #include <nanocdr/nanoCdr.h>
}

  #define BUFFER_LENGTH 2000

  const signed char octet_t = 32;
  const char char_t =  'Z';

  const unsigned short ushort_t = 65500;
  const short short_t = -32700;
  const unsigned int ulong_t = 4294967200;
  const int long_t = -2147483600;

  const unsigned long ulonglong_t = 18446744073709551600u;
  const long longlong_t = -9223372036800;

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


  const unsigned long ulonglong_array_t[5] = {18446744073709551600u, 18446744073709551601u, 18446744073709551602u, 18446744073709551603u, 18446744073709551604u};
  const long  longlong_array_t[5] = {-9223372036800, -9223372036801, -9223372036802, -9223372036803, -9223372036804};

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

  const unsigned long ulonglong_seq_t[5] = {18446744073709551604u, 18446744073709551603u, 18446744073709551602u, 18446744073709551601u, 18446744073709551600u};
  const long longlong_seq_t[5] = {-9223372036804, -9223372036803, -9223372036802, -9223372036801, -9223372036800};

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
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeChar(char_t);

      // Deseriazliation.
      deserializeChar(&char_out);

      EXPECT_EQ(char_out, char_t);
  }

  TEST(nanoCDRBasicTests, SignedChar)
  {
      signed char octect_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeSignedChar(octet_t);

      // Deseriazliation.
      deserializeSignedChar(&octect_out);

      EXPECT_EQ(octect_out, octet_t);
  }

  TEST(nanoCDRBasicTests, Short)
  {
      short short_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeShort(short_t);

      // Deseriazliation.
      deserializeShort(&short_out);

      EXPECT_EQ(short_out, short_t);
  }

  TEST(nanoCDRBasicTests, UnsignedShort)
  {
      unsigned short ushort_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedShort(ushort_t);

      // Deseriazliation.
      deserializeUnsignedShort(&ushort_out);

      EXPECT_EQ(ushort_out, ushort_t);
  }

  TEST(nanoCDRBasicTests, Int)
  {
      int long_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeInt(long_t);

      // Deseriazliation.
      deserializeInt(&long_out);

      EXPECT_EQ(long_out, long_t);
  }

  TEST(nanoCDRBasicTests, UnsignedInt)
  {
      unsigned int ulong_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedInt(ulong_t);

      // Deseriazliation.
      deserializeUnsignedInt(&ulong_out);

      EXPECT_EQ(ulong_out, ulong_t);
  }

  TEST(nanoCDRBasicTests, Long)
  {
      long long_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeLong(longlong_t);

      // Deseriazliation.
      deserializeLong(&long_out);

      EXPECT_EQ(long_out, longlong_t);
  }

  TEST(nanoCDRBasicTests, uLong)
  {
      unsigned long ulong_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedLong(ulonglong_t);

      // Deseriazliation.
      deserializeUnsignedLong(&ulong_out);

      EXPECT_EQ(ulong_out, ulonglong_t);
  }

  TEST(nanoCDRBasicTests, LongLong)
  {
      long long longlong_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeLongLong(longlonglong_t);

      // Deseriazliation.
      deserializeLongLong(&longlong_out);

      EXPECT_EQ(longlong_out, longlonglong_t);
  }

  TEST(nanoCDRBasicTests, uLongLong)
  {
      unsigned long long ulonglong_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedLongLong(ulonglonglong_t);

      // Deseriazliation.
      deserializeUnsignedLongLong(&ulonglong_out);

      EXPECT_EQ(ulonglong_out, ulonglonglong_t);
  }

  TEST(nanoCDRBasicTests, Float)
  {
      float float_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeFloat(float_tt);

      // Deseriazliation.
      deserializeFloat(&float_out);

      EXPECT_EQ(float_out, float_tt);
  }

  TEST(nanoCDRBasicTests, Double)
  {
      double double_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeDouble(double_tt);

      // Deseriazliation.
      deserializeDouble(&double_out);

      EXPECT_EQ(double_out, double_tt);
  }

  TEST(nanoCDRBasicTests, LongDouble)
  {
      long double longdouble_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeLongDouble(longdouble_t);

      // Deseriazliation.
      deserializeLongDouble(&longdouble_out);

      EXPECT_EQ(longdouble_out, longdouble_t);
  }

  TEST(nanoCDRBasicTests, String)
  {
      char * string_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      const unsigned int length = std::strlen(string_t);
      unsigned int length_out;

      // Serialization.
      serializeString(string_t, length);

      // Deseriazliation.
      deserializeString(&string_out, &length_out);

      unsigned int comparative = std::strcmp(string_out, string_t);

      EXPECT_EQ(comparative, 0);
      EXPECT_EQ(length, length_out);
      free(string_out);
  }

  TEST(nanoCDRBasicTests, EmptyString)
  {
      char * string_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      const unsigned int length = std::strlen(emptystring_t);
      unsigned int length_out;

      // Serialization.
      serializeString(emptystring_t, length);

      // Deseriazliation.
      deserializeString(&string_out, &length_out);

      unsigned int comparative = std::strcmp(string_out, emptystring_t);

      EXPECT_EQ(comparative, 0);
      EXPECT_EQ(length, length_out);
      free(string_out);
  }

  TEST(nanoCDRArrayTests, CharArray)
  {
      char * char_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeCharArray(char_array_t, 5);

      // Deseriazliation.
      deserializeCharArray(&char_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(char_array_t[i], char_out[i]);
      }
      free(char_out);
  }

  TEST(nanoCDRArrayTests, UnsignedCharArray)
  {
      unsigned char * char_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedCharArray(octet_array_t, 5);

      // Deseriazliation.
      deserializeUnsignedCharArray(&char_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(octet_array_t[i], char_out[i]);
      }
      free(char_out);
  }

  TEST(nanoCDRArrayTests, ShortArray)
  {
      short * short_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeShortArray(short_array_t, 5);

      // Deseriazliation.
      deserializeShortArray(&short_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(short_array_t[i], short_out[i]);
      }
      free(short_out);
  }

  TEST(nanoCDRArrayTests, UnsignedShortArray)
  {
      unsigned short * ushort_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedShortArray(ushort_array_t, 5);

      // Deseriazliation.
      deserializeUnsignedShortArray(&ushort_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(ushort_array_t[i], ushort_out[i]);
      }
      free(ushort_out);
  }

  TEST(nanoCDRArrayTests, IntArray)
  {
      int * int_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeIntArray(long_array_t, 5);

      // Deseriazliation.
      deserializeIntArray(&int_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(long_array_t[i], int_out[i]);
      }
      free(int_out);
  }

  TEST(nanoCDRArrayTests, UnsignedIntArray)
  {
      unsigned int * uint_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedIntArray(ulong_array_t, 5);

      // Deseriazliation.
      deserializeUnsignedIntArray(&uint_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(ulong_array_t[i], uint_out[i]);
      }
      free(uint_out);
  }

  TEST(nanoCDRArrayTests, LongArray)
  {
      long * long_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeLongArray(longlong_array_t, 5);

      // Deseriazliation.
      deserializeLongArray(&long_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(longlong_array_t[i], long_out[i]);
      }
      free(long_out);
  }

  TEST(nanoCDRArrayTests, ULongArray)
  {
      unsigned long * ulong_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedLongArray(ulonglong_array_t, 5);

      // Deseriazliation.
      deserializeUnsignedLongArray(&ulong_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(ulonglong_array_t[i], ulong_out[i]);
      }
      free(ulong_out);
  }

  TEST(nanoCDRArrayTests, LongLongArray)
  {
      long long * longlong_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeLongLongArray(longlonglong_array_t, 5);

      // Deseriazliation.
      deserializeLongLongArray(&longlong_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(longlonglong_array_t[i], longlong_out[i]);
      }
      free(longlong_out);
  }

  TEST(nanoCDRArrayTests, ULongLongArray)
  {
      unsigned long long * ulonglong_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedLongLongArray(ulonglonglong_array_t, 5);

      // Deseriazliation.
      deserializeUnsignedLongLongArray(&ulonglong_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(ulonglonglong_array_t[i], ulonglong_out[i]);
      }
      free(ulonglong_out);
  }

  TEST(nanoCDRArrayTests, FloatArray)
  {
      float * float_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeFloatArray(float_array_t, 5);

      // Deseriazliation.
      deserializeFloatArray(&float_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(float_array_t[i], float_out[i]);
      }
      free(float_out);
  }

  TEST(nanoCDRArrayTests, DoubleArray)
  {
      double * double_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeDoubleArray(double_array_t, 5);

      // Deseriazliation.
      deserializeDoubleArray(&double_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(double_array_t[i], double_out[i]);
      }

      free(double_out);
  }

  TEST(nanoCDRArrayTests, LongDoubleArray)
  {
      long double * longdouble_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeLongDoubleArray(longdouble_array_t, 5);

      // Deseriazliation.
      deserializeLongDoubleArray(&longdouble_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(longdouble_array_t[i], longdouble_out[i]);
      }
      free(longdouble_out);
  }

  TEST(nanoCDRArrayTests, StringArray)
  {
      char ** string_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeStringArray(string_seq_t, 5);

      // Deseriazliation.
      deserializeStringArray(&string_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        int length_in = std::strlen(string_seq_t[i]);
        int length_out = std::strlen(string_out[i]);
        int comparative = std::strcmp(string_seq_t[i], string_out[i]);
        EXPECT_EQ(length_in, length_out);
        EXPECT_EQ(comparative, 0);
        free(string_out[i]);
      }
      free(string_out);
  }

  TEST(nanoCDRSequencesTests, CharSequence)
  {
      char * char_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeCharSequence(char_seq_t, 5);

      // Deseriazliation.
      deserializeCharSequence(&char_out, &size_out);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(char_seq_t[i], char_out[i]);
      }

      free(char_out);
  }

  TEST(nanoCDRSequencesTests, UnsignedCharSequence)
  {
      unsigned char * char_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedCharSequence(octet_seq_t, 5);

      // Deseriazliation.
      deserializeUnsignedCharSequence(&char_out, &size_out);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(octet_seq_t[i], char_out[i]);
      }

      free(char_out);
  }

  TEST(nanoCDRSequencesTests, ShortSequence)
  {
      short * short_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeShortSequence(short_seq_t, 5);

      // Deseriazliation.
      deserializeShortSequence(&short_out, &size_out);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(short_seq_t[i], short_out[i]);
      }

      free(short_out);
  }

  TEST(nanoCDRSequencesTests, UnsignedShortSequence)
  {
      unsigned short * ushort_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedShortSequence(ushort_seq_t, 5);

      // Deseriazliation.
      deserializeUnsignedShortSequence(&ushort_out, &size_out);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(ushort_seq_t[i], ushort_out[i]);
      }

      free(ushort_out);
  }

  TEST(nanoCDRSequencesTests, IntSequence)
  {
      int * int_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeIntSequence(long_seq_t, 5);

      // Deseriazliation.
      deserializeIntSequence(&int_out, &size_out);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(long_seq_t[i], int_out[i]);
      }

      free(int_out);
  }

  TEST(nanoCDRSequencesTests, UnsignedIntSequence)
  {
      unsigned int * uint_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedIntSequence(ulong_seq_t, 5);

      // Deseriazliation.
      deserializeUnsignedIntSequence(&uint_out, &size_out);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(ulong_seq_t[i], uint_out[i]);
      }

      free(uint_out);
  }

  TEST(nanoCDRSequencesTests, LongSequence)
  {
      long * long_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeLongSequence(longlong_seq_t, 5);

      // Deseriazliation.
      deserializeLongSequence(&long_out, &size_out);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(longlong_seq_t[i], long_out[i]);
      }

      free(long_out);
  }

  TEST(nanoCDRSequencesTests, ULongSequence)
  {
      unsigned long * ulong_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedLongSequence(ulonglong_seq_t, 5);

      // Deseriazliation.
      deserializeUnsignedLongSequence(&ulong_out, &size_out);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(ulonglong_seq_t[i], ulong_out[i]);
      }

      free(ulong_out);
  }

  TEST(nanoCDRSequencesTests, LongLongSequence)
  {
      long long * longlong_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeLongLongSequence(longlonglong_seq_t, 5);

      // Deseriazliation.
      deserializeLongLongSequence(&longlong_out, &size_out);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(longlonglong_seq_t[i], longlong_out[i]);
      }

      free(longlong_out);
  }

  TEST(nanoCDRSequencesTests, ULongLongSequence)
  {
      unsigned long long * ulonglong_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedLongLongSequence(ulonglonglong_seq_t, 5);

      // Deseriazliation.
      deserializeUnsignedLongLongSequence(&ulonglong_out, &size_out);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(ulonglonglong_seq_t[i], ulonglong_out[i]);
      }

      free(ulonglong_out);
  }

  TEST(nanoCDRSequencesTests, FloatSequence)
  {
      float * float_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeFloatSequence(float_seq_t, 5);

      // Deseriazliation.
      deserializeFloatSequence(&float_out, &size_out);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(float_seq_t[i], float_out[i]);
      }

      free(float_out);
  }

  TEST(nanoCDRSequencesTests, DoubleSequence)
  {
      double * double_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeDoubleSequence(double_seq_t, 5);

      // Deseriazliation.
      deserializeDoubleSequence(&double_out, &size_out);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(double_seq_t[i], double_out[i]);
      }

      free(double_out);
  }

  TEST(nanoCDRSequencesTests, LongDoubleSequence)
  {
      long double * longdouble_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeLongDoubleSequence(longdouble_seq_t, 5);

      // Deseriazliation.
      deserializeLongDoubleSequence(&longdouble_out, &size_out);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(longdouble_seq_t[i], longdouble_out[i]);
      }

      free(longdouble_out);
  }

  TEST(nanoCDRSequencesTests, StringSequence)
  {
      char ** string_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeStringSequence(string_seq_t, 5);

      unsigned int size_out;

      // Deseriazliation.
      deserializeStringSequence(&string_out, &size_out);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        int length_in = std::strlen(string_seq_t[i]);
        int length_out = std::strlen(string_out[i]);
        int comparative = std::strcmp(string_seq_t[i], string_out[i]);
        EXPECT_EQ(length_in, length_out);
        EXPECT_EQ(comparative, 0);
        free(string_out[i]);
      }
      free(string_out);
  }

  TEST(nanoCDRTests, SimpleVar)
  {
    char char_out;
    signed char octect_out;
    short short_out;
    unsigned short ushort_out;
    int long_out;
    unsigned int ulong_out;
    long longlong_out;
    unsigned long ulonglong_out;
    long long longlonglong_out;
    unsigned long long ulonglonglong_out;
    float float_out;
    double double_out;
    long double longdouble_out;
    char * string_out;
    char * string_out_2;

    char buffer[BUFFER_LENGTH];
    // Check good case.
    newStaticBuffer(buffer, BUFFER_LENGTH);

    const unsigned int length = std::strlen(string_t);
    unsigned int length_out;

    const unsigned int length_2 = std::strlen(emptystring_t);
    unsigned int length_out_2;

    // Serialization.
    serializeChar(char_t);
    serializeSignedChar(octet_t);
    serializeShort(short_t);
    serializeUnsignedShort(ushort_t);
    serializeInt(long_t);
    serializeUnsignedInt(ulong_t);
    serializeLong(longlong_t);
    serializeUnsignedLong(ulonglong_t);
    serializeLongLong(longlonglong_t);
    serializeUnsignedLongLong(ulonglonglong_t);
    serializeFloat(float_tt);
    serializeDouble(double_tt);
    serializeLongDouble(longdouble_t);
    serializeString(string_t, length);
    serializeString(emptystring_t, length_2);

    // Deseriazliation.
    deserializeChar(&char_out);
    deserializeSignedChar(&octect_out);
    deserializeShort(&short_out);
    deserializeUnsignedShort(&ushort_out);
    deserializeInt(&long_out);
    deserializeUnsignedInt(&ulong_out);
    deserializeLong(&longlong_out);
    deserializeUnsignedLong(&ulonglong_out);
    deserializeLongLong(&longlonglong_out);
    deserializeUnsignedLongLong(&ulonglonglong_out);
    deserializeFloat(&float_out);
    deserializeDouble(&double_out);
    deserializeLongDouble(&longdouble_out);
    deserializeString(&string_out, &length_out);
    deserializeString(&string_out_2, &length_out_2);

    unsigned int comparative = std::strcmp(string_out, string_t);
    unsigned int comparative_2 = std::strcmp(string_out_2, emptystring_t);

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
    int i;
    char * char_out;
    unsigned char * uchar_out;
    short * short_out;
    unsigned short * ushort_out;
    int * int_out;
    unsigned int * uint_out;
    long * long_out;
    unsigned long * ulong_out;
    long long * longlong_out;
    unsigned long long * ulonglong_out;
    float * float_out;
    double * double_out;
    long double * longdouble_out;
    char ** string_out;


    char buffer[BUFFER_LENGTH];
    // Check good case.
    newStaticBuffer(buffer, BUFFER_LENGTH);

    short result = 0;

    // Serialization.
    result += serializeCharArray(char_array_t, 5); //5
    result += serializeUnsignedCharArray(octet_array_t, 5); //5
    result += serializeShortArray(short_array_t, 5); //10
    result += serializeUnsignedShortArray(ushort_array_t, 5); //10
    result += serializeIntArray(long_array_t, 5); //20
    result += serializeUnsignedIntArray(ulong_array_t, 5); //20
    result += serializeLongArray(longlong_array_t, 5); //20
    result += serializeUnsignedLongArray(ulonglong_array_t, 5); //20
    result += serializeLongLongArray(longlonglong_array_t, 5); //20
    result += serializeUnsignedLongLongArray(ulonglonglong_array_t, 5); //20
    result += serializeFloatArray(float_array_t, 5); //20
    result += serializeDoubleArray(double_array_t, 5); //40
    result += serializeLongDoubleArray(longdouble_array_t, 5); //40
    result += serializeStringArray(string_seq_t, 5);

    //unsigned int serialized = getSerializedDataLength();

    EXPECT_EQ(result, 0);
    //EXPECT_EQ(serialized, 130);

    if(result == 0){
      // Deseriazliation.
      result += deserializeCharArray(&char_out, 5);
      result += deserializeUnsignedCharArray(&uchar_out, 5);
      result += deserializeShortArray(&short_out, 5);
      result += deserializeUnsignedShortArray(&ushort_out, 5);
      result += deserializeIntArray(&int_out, 5);
      result += deserializeUnsignedIntArray(&uint_out, 5);
      result += deserializeLongArray(&long_out, 5);
      result += deserializeUnsignedLongArray(&ulong_out, 5);
      result += deserializeLongLongArray(&longlong_out, 5);
      result += deserializeUnsignedLongLongArray(&ulonglong_out, 5);
      result += deserializeFloatArray(&float_out, 5);
      result += deserializeDoubleArray(&double_out, 5);
      result += deserializeLongDoubleArray(&longdouble_out, 5);
      result += deserializeStringArray(&string_out, 5);

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
          int length_in = std::strlen(string_seq_t[i]);
          int length_out = std::strlen(string_out[i]);
          int comparative = std::strcmp(string_seq_t[i], string_out[i]);
          EXPECT_EQ(length_in, length_out);
          EXPECT_EQ(comparative, 0);
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
    int i;
    char * char_out;
    unsigned int char_out_size;
    unsigned char * uchar_out;
    unsigned int uchar_out_size;
    short * short_out;
    unsigned int short_out_size;
    unsigned short * ushort_out;
    unsigned int ushort_out_size;
    int * int_out;
    unsigned int int_out_size;
    unsigned int * uint_out;
    unsigned int uint_out_size;
    long * long_out;
    unsigned int long_out_size;
    unsigned long * ulong_out;
    unsigned int ulong_out_size;
    long long * longlong_out;
    unsigned int longlong_out_size;
    unsigned long long * ulonglong_out;
    unsigned int ulonglong_out_size;
    float * float_out;
    unsigned int float_out_size;
    double * double_out;
    unsigned int double_out_size;
    long double * longdouble_out;
    unsigned int longdouble_out_size;
    char ** string_out;
    unsigned int string_out_size;

    short result = 0;


    char buffer[BUFFER_LENGTH];
    // Check good case.
    newStaticBuffer(buffer, BUFFER_LENGTH);

    // Serialization.
    result += serializeCharSequence(char_seq_t, 5); //9
    result += serializeUnsignedCharSequence(octet_seq_t, 5); //9
    result += serializeShortSequence(short_seq_t, 5);//14
    result += serializeUnsignedShortSequence(ushort_seq_t, 5);//14
    result += serializeIntSequence(long_seq_t, 5);//24
    result += serializeUnsignedIntSequence(ulong_seq_t, 5);//24
    result += serializeLongSequence(longlong_seq_t, 5);//24
    result += serializeUnsignedLongSequence(ulonglong_seq_t, 5);//24
    result += serializeLongLongSequence(longlonglong_seq_t, 5);//24
    result += serializeUnsignedLongLongSequence(ulonglonglong_seq_t, 5);//24
    result += serializeFloatSequence(float_seq_t, 5);//24
    result += serializeDoubleSequence(double_seq_t, 5);//44
    result += serializeLongDoubleSequence(longdouble_seq_t, 5);//44
    result += serializeStringSequence(string_seq_t, 5);

    //unsigned int serialized = getSerializedDataLength();
    //EXPECT_EQ(serialized, 162);

    EXPECT_EQ(result, 0);

    if(result == 0){
      // Deseriazliation.
      result += deserializeCharSequence(&char_out, &char_out_size);
      result += deserializeUnsignedCharSequence(&uchar_out, &uchar_out_size);
      result += deserializeShortSequence(&short_out, &short_out_size);
      result += deserializeUnsignedShortSequence(&ushort_out, &ushort_out_size);
      result += deserializeIntSequence(&int_out, &int_out_size);
      result += deserializeUnsignedIntSequence(&uint_out, &uint_out_size);
      result += deserializeLongSequence(&long_out, &long_out_size);
      result += deserializeUnsignedLongSequence(&ulong_out, &ulong_out_size);
      result += deserializeLongLongSequence(&longlong_out, &longlong_out_size);
      result += deserializeUnsignedLongLongSequence(&ulonglong_out, &ulonglong_out_size);
      result += deserializeFloatSequence(&float_out, &float_out_size);
      result += deserializeDoubleSequence(&double_out, &double_out_size);
      result += deserializeLongDoubleSequence(&longdouble_out, &longdouble_out_size);
      result += deserializeStringSequence(&string_out, &string_out_size);

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
          int length_in = std::strlen(string_seq_t[i]);
          int length_out = std::strlen(string_out[i]);
          int comparative = std::strcmp(string_seq_t[i], string_out[i]);
          EXPECT_EQ(length_in, length_out);
          EXPECT_EQ(comparative, 0);
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
    short short_out;
    unsigned short ushort_out;
    int long_out;
    unsigned int ulong_out;
    long longlong_out;
    unsigned long ulonglong_out;
    long long longlonglong_out;
    unsigned long long ulonglonglong_out;
    float float_out;
    double double_out;
    long double longdouble_out;
    char * string_out;
    char * string_out_2;

    //ARRAYS
    int i;
    char * char_array_out;
    unsigned char * uchar_array_out;
    short * short_array_out;
    unsigned short * ushort_array_out;
    int * int_array_out;
    unsigned int * uint_array_out;
    long * long_array_out;
    unsigned long * ulong_array_out;
    long long * longlong_array_out;
    unsigned long long * ulonglong_array_out;
    float * float_array_out;
    double * double_array_out;
    long double * longdouble_array_out;
    char ** string_array_out;

    //SEQUENCES
    char * char_seq_out;
    unsigned int char_out_size;
    unsigned char * uchar_seq_out;
    unsigned int uchar_out_size;
    short * short_seq_out;
    unsigned int short_out_size;
    unsigned short * ushort_seq_out;
    unsigned int ushort_out_size;
    int * int_seq_out;
    unsigned int int_out_size;
    unsigned int * uint_seq_out;
    unsigned int uint_out_size;
    long * long_seq_out;
    unsigned int long_out_size;
    unsigned long * ulong_seq_out;
    unsigned int ulong_out_size;
    long long * longlong_seq_out;
    unsigned int longlong_out_size;
    unsigned long long * ulonglong_seq_out;
    unsigned int ulonglong_out_size;
    float * float_seq_out;
    unsigned int float_out_size;
    double * double_seq_out;
    unsigned int double_out_size;
    long double * longdouble_seq_out;
    unsigned int longdouble_out_size;
    char ** string_seq_out;
    unsigned int string_out_size;


    char buffer[BUFFER_LENGTH];
    // Check good case.
    newStaticBuffer(buffer, BUFFER_LENGTH);

    const unsigned int length = std::strlen(string_t);
    unsigned int length_out;

    short result = 0;

    const unsigned int length_2 = std::strlen(emptystring_t);
    unsigned int length_out_2;

    // Serialization.
    result += serializeChar(char_t);
    result += serializeSignedChar(octet_t);
    result += serializeShort(short_t);
    result += serializeUnsignedShort(ushort_t);
    result += serializeInt(long_t);
    result += serializeUnsignedInt(ulong_t);
    result += serializeLong(longlong_t);
    result += serializeUnsignedLong(ulonglong_t);
    result += serializeLongLong(longlonglong_t);
    result += serializeUnsignedLongLong(ulonglonglong_t);
    result += serializeFloat(float_tt);
    result += serializeDouble(double_tt);
    result += serializeLongDouble(longdouble_t);
    result += serializeString(string_t, length);
    result += serializeString(emptystring_t, length_2);

    result += serializeCharArray(char_array_t, 5); //5
    result += serializeUnsignedCharArray(octet_array_t, 5); //5
    result += serializeShortArray(short_array_t, 5); //10
    result += serializeUnsignedShortArray(ushort_array_t, 5); //10
    result += serializeIntArray(long_array_t, 5); //20
    result += serializeUnsignedIntArray(ulong_array_t, 5); //20

    result += serializeLongArray(longlong_array_t, 5);
    result += serializeUnsignedLongArray(ulonglong_array_t, 5);
    result += serializeLongLongArray(longlonglong_array_t, 5);
    result += serializeUnsignedLongLongArray(ulonglonglong_array_t, 5);

    result += serializeFloatArray(float_array_t, 5); //20
    result += serializeDoubleArray(double_array_t, 5); //40
    result += serializeLongDoubleArray(longdouble_array_t, 5);
    result += serializeStringArray(string_seq_t, 5);

    result += serializeCharSequence(char_seq_t, 5); //9
    result += serializeUnsignedCharSequence(octet_seq_t, 5); //9
    result += serializeShortSequence(short_seq_t, 5);//14
    result += serializeUnsignedShortSequence(ushort_seq_t, 5);//14
    result += serializeIntSequence(long_seq_t, 5);//24
    result += serializeUnsignedIntSequence(ulong_seq_t, 5);//24

    result += serializeLongSequence(longlong_seq_t, 5);
    result += serializeUnsignedLongSequence(ulonglong_seq_t, 5);
    result += serializeLongLongSequence(longlonglong_seq_t, 5);
    result += serializeUnsignedLongLongSequence(ulonglonglong_seq_t, 5);

    result += serializeFloatSequence(float_seq_t, 5);//24
    result += serializeDoubleSequence(double_seq_t, 5);//44
    result += serializeLongDoubleSequence(longdouble_seq_t, 5);//44
    result += serializeStringSequence(string_seq_t, 5);

    //unsigned int serialized = getSerializedDataLength();
    //EXPECT_EQ(serialized, 357);
    EXPECT_EQ(result, 0);

    if(result == 0){
    // Deseriazliation.
      result += deserializeChar(&char_out);
      result += deserializeSignedChar(&octect_out);
      result += deserializeShort(&short_out);
      result += deserializeUnsignedShort(&ushort_out);
      result += deserializeInt(&long_out);
      result += deserializeUnsignedInt(&ulong_out);
      result += deserializeLong(&longlong_out);
      result += deserializeUnsignedLong(&ulonglong_out);
      result += deserializeLongLong(&longlonglong_out);
      result += deserializeUnsignedLongLong(&ulonglonglong_out);
      result += deserializeFloat(&float_out);
      result += deserializeDouble(&double_out);
      result += deserializeLongDouble(&longdouble_out);
      result += deserializeString(&string_out, &length_out);
      result += deserializeString(&string_out_2, &length_out_2);

      result += deserializeCharArray(&char_array_out, 5);
      result += deserializeUnsignedCharArray(&uchar_array_out, 5);
      result += deserializeShortArray(&short_array_out, 5);
      result += deserializeUnsignedShortArray(&ushort_array_out, 5);
      result += deserializeIntArray(&int_array_out, 5);
      result += deserializeUnsignedIntArray(&uint_array_out, 5);

      result += deserializeLongArray(&long_array_out, 5);
      result += deserializeUnsignedLongArray(&ulong_array_out, 5);
      result += deserializeLongLongArray(&longlong_array_out, 5);
      result += deserializeUnsignedLongLongArray(&ulonglong_array_out, 5);

      result += deserializeFloatArray(&float_array_out, 5);
      result += deserializeDoubleArray(&double_array_out, 5);
      result += deserializeLongDoubleArray(&longdouble_array_out, 5);
      result += deserializeStringArray(&string_array_out, 5);

      result += deserializeCharSequence(&char_seq_out, &char_out_size);
      result += deserializeUnsignedCharSequence(&uchar_seq_out, &uchar_out_size);
      result += deserializeShortSequence(&short_seq_out, &short_out_size);
      result += deserializeUnsignedShortSequence(&ushort_seq_out, &ushort_out_size);
      result += deserializeIntSequence(&int_seq_out, &int_out_size);
      result += deserializeUnsignedIntSequence(&uint_seq_out, &uint_out_size);

      result += deserializeLongSequence(&long_seq_out, &long_out_size);
      result += deserializeUnsignedLongSequence(&ulong_seq_out, &ulong_out_size);
      result += deserializeLongLongSequence(&longlong_seq_out, &longlong_out_size);
      result += deserializeUnsignedLongLongSequence(&ulonglong_seq_out, &ulonglong_out_size);

      result += deserializeFloatSequence(&float_seq_out, &float_out_size);
      result += deserializeDoubleSequence(&double_seq_out, &double_out_size);
      result += deserializeLongDoubleSequence(&longdouble_seq_out, &longdouble_out_size);
      result += deserializeStringSequence(&string_seq_out, &string_out_size);

      EXPECT_EQ(result, 0);

      if(result == 0)
      {
        unsigned int comparative = std::strcmp(string_out, string_t);
        unsigned int comparative_2 = std::strcmp(string_out_2, emptystring_t);

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
          int length_in = std::strlen(string_seq_t[i]);
          int length_out = std::strlen(string_array_out[i]);
          int comparative = std::strcmp(string_seq_t[i], string_array_out[i]);
          EXPECT_EQ(length_in, length_out);
          EXPECT_EQ(comparative, 0);
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
          int length_in = std::strlen(string_seq_t[i]);
          int length_out = std::strlen(string_seq_out[i]);
          int comparative = std::strcmp(string_seq_t[i], string_seq_out[i]);
          EXPECT_EQ(length_in, length_out);
          EXPECT_EQ(comparative, 0);
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
    short short_out;
    unsigned short ushort_out;
    int long_out;
    unsigned int ulong_out;
    long longlong_out;
    unsigned long ulonglong_out;
    long long longlonglong_out;
    unsigned long long ulonglonglong_out;
    float float_out;
    double double_out;
    long double longdouble_out;
    char * string_out;
    char * string_out_2;

    //ARRAYS
    int i;
    char * char_array_out;
    unsigned char * uchar_array_out;
    short * short_array_out;
    unsigned short * ushort_array_out;
    int * int_array_out;
    unsigned int * uint_array_out;
    long * long_array_out;
    unsigned long * ulong_array_out;
    long long * longlong_array_out;
    unsigned long long * ulonglong_array_out;
    float * float_array_out;
    double * double_array_out;
    long double * longdouble_array_out;
    char ** string_array_out;

    //SEQUENCES
    char * char_seq_out;
    unsigned int char_out_size;
    unsigned char * uchar_seq_out;
    unsigned int uchar_out_size;
    short * short_seq_out;
    unsigned int short_out_size;
    unsigned short * ushort_seq_out;
    unsigned int ushort_out_size;
    int * int_seq_out;
    unsigned int int_out_size;
    unsigned int * uint_seq_out;
    unsigned int uint_out_size;
    long * long_seq_out;
    unsigned int long_out_size;
    unsigned long * ulong_seq_out;
    unsigned int ulong_out_size;
    long long * longlong_seq_out;
    unsigned int longlong_out_size;
    unsigned long long * ulonglong_seq_out;
    unsigned int ulonglong_out_size;
    float * float_seq_out;
    unsigned int float_out_size;
    double * double_seq_out;
    unsigned int double_out_size;
    long double * longdouble_seq_out;
    unsigned int longdouble_out_size;
    char ** string_seq_out;
    unsigned int string_out_size;


    char buffer[BUFFER_LENGTH];
    // Check good case.
    newStaticBuffer(buffer, BUFFER_LENGTH);

    const unsigned int length = std::strlen(string_t);
    unsigned int length_out;

    short result = 0;

    const unsigned int length_2 = std::strlen(emptystring_t);
    unsigned int length_out_2;

    // Serialization.
    result += serializeChar(char_t);
    result += serializeSignedChar(octet_t);
    result += serializeShortEndianness(short_t, endianness);
    result += serializeUnsignedShortEndianness(ushort_t, endianness);
    result += serializeIntEndianness(long_t, endianness);
    result += serializeUnsignedIntEndianness(ulong_t, endianness);
    result += serializeLongEndianness(longlong_t, endianness);
    result += serializeUnsignedLongEndianness(ulonglong_t, endianness);
    result += serializeLongLongEndianness(longlonglong_t, endianness);
    result += serializeUnsignedLongLongEndianness(ulonglonglong_t, endianness);
    result += serializeFloatEndianness(float_tt, endianness);
    result += serializeDoubleEndianness(double_tt, endianness);
    result += serializeLongDoubleEndianness(longdouble_t, endianness);
    result += serializeStringEndianness(string_t, length, endianness);
    result += serializeStringEndianness(emptystring_t, length_2, endianness);

    result += serializeCharArray(char_array_t, 5); //5
    result += serializeUnsignedCharArray(octet_array_t, 5); //5
    result += serializeShortArrayEndianness(short_array_t, 5, endianness); //10
    result += serializeUnsignedShortArrayEndianness(ushort_array_t, 5, endianness); //10
    result += serializeIntArrayEndianness(long_array_t, 5, endianness); //20
    result += serializeUnsignedIntArrayEndianness(ulong_array_t, 5, endianness); //20

    result += serializeLongArrayEndianness(longlong_array_t, 5, endianness);
    result += serializeUnsignedLongArrayEndianness(ulonglong_array_t, 5, endianness);
    result += serializeLongLongArrayEndianness(longlonglong_array_t, 5, endianness);
    result += serializeUnsignedLongLongArrayEndianness(ulonglonglong_array_t, 5, endianness);

    result += serializeFloatArrayEndianness(float_array_t, 5, endianness); //20
    result += serializeDoubleArrayEndianness(double_array_t, 5, endianness); //40
    result += serializeLongDoubleArrayEndianness(longdouble_array_t, 5, endianness);
    result += serializeStringArrayEndianness(string_seq_t, 5, endianness);

    result += serializeCharSequenceEndianness(char_seq_t, 5, endianness); //9
    result += serializeUnsignedCharSequenceEndianness(octet_seq_t, 5, endianness); //9
    result += serializeShortSequenceEndianness(short_seq_t, 5, endianness);//14
    result += serializeUnsignedShortSequenceEndianness(ushort_seq_t, 5, endianness);//14
    result += serializeIntSequenceEndianness(long_seq_t, 5, endianness);//24
    result += serializeUnsignedIntSequenceEndianness(ulong_seq_t, 5, endianness);//24

    result += serializeLongSequenceEndianness(longlong_seq_t, 5, endianness);
    result += serializeUnsignedLongSequenceEndianness(ulonglong_seq_t, 5, endianness);
    result += serializeLongLongSequenceEndianness(longlonglong_seq_t, 5, endianness);
    result += serializeUnsignedLongLongSequenceEndianness(ulonglonglong_seq_t, 5, endianness);

    result += serializeFloatSequenceEndianness(float_seq_t, 5, endianness);//24
    result += serializeDoubleSequenceEndianness(double_seq_t, 5, endianness);//44
    result += serializeLongDoubleSequenceEndianness(longdouble_seq_t, 5, endianness);//44
    result += serializeStringSequenceEndianness(string_seq_t, 5, endianness);

    //unsigned int serialized = getSerializedDataLength();
    //EXPECT_EQ(serialized, 357);
    EXPECT_EQ(result, 0);

    if(result == 0){
    // Deseriazliation.
      result += deserializeChar(&char_out);
      result += deserializeSignedChar(&octect_out);
      result += deserializeShortEndianness(&short_out, endianness);
      result += deserializeUnsignedShortEndianness(&ushort_out, endianness);
      result += deserializeIntEndianness(&long_out, endianness);
      result += deserializeUnsignedIntEndianness(&ulong_out, endianness);
      result += deserializeLongEndianness(&longlong_out, endianness);
      result += deserializeUnsignedLongEndianness(&ulonglong_out, endianness);
      result += deserializeLongLongEndianness(&longlonglong_out, endianness);
      result += deserializeUnsignedLongLongEndianness(&ulonglonglong_out, endianness);
      result += deserializeFloatEndianness(&float_out, endianness);
      result += deserializeDoubleEndianness(&double_out, endianness);
      result += deserializeLongDoubleEndianness(&longdouble_out, endianness);
      result += deserializeStringEndianness(&string_out, &length_out, endianness);
      result += deserializeStringEndianness(&string_out_2, &length_out_2, endianness);

      result += deserializeCharArray(&char_array_out, 5);
      result += deserializeUnsignedCharArray(&uchar_array_out, 5);
      result += deserializeShortArrayEndianness(&short_array_out, 5, endianness);
      result += deserializeUnsignedShortArrayEndianness(&ushort_array_out, 5, endianness);
      result += deserializeIntArrayEndianness(&int_array_out, 5, endianness);
      result += deserializeUnsignedIntArrayEndianness(&uint_array_out, 5, endianness);

      result += deserializeLongArrayEndianness(&long_array_out, 5, endianness);
      result += deserializeUnsignedLongArrayEndianness(&ulong_array_out, 5, endianness);
      result += deserializeLongLongArrayEndianness(&longlong_array_out, 5, endianness);
      result += deserializeUnsignedLongLongArrayEndianness(&ulonglong_array_out, 5, endianness);

      result += deserializeFloatArrayEndianness(&float_array_out, 5, endianness);
      result += deserializeDoubleArrayEndianness(&double_array_out, 5, endianness);
      result += deserializeLongDoubleArrayEndianness(&longdouble_array_out, 5, endianness);
      result += deserializeStringArrayEndianness(&string_array_out, 5, endianness);

      result += deserializeCharSequenceEndianness(&char_seq_out, &char_out_size, endianness);
      result += deserializeUnsignedCharSequenceEndianness(&uchar_seq_out, &uchar_out_size, endianness);
      result += deserializeShortSequenceEndianness(&short_seq_out, &short_out_size, endianness);
      result += deserializeUnsignedShortSequenceEndianness(&ushort_seq_out, &ushort_out_size, endianness);
      result += deserializeIntSequenceEndianness(&int_seq_out, &int_out_size, endianness);
      result += deserializeUnsignedIntSequenceEndianness(&uint_seq_out, &uint_out_size, endianness);

      result += deserializeLongSequenceEndianness(&long_seq_out, &long_out_size, endianness);
      result += deserializeUnsignedLongSequenceEndianness(&ulong_seq_out, &ulong_out_size, endianness);
      result += deserializeLongLongSequenceEndianness(&longlong_seq_out, &longlong_out_size, endianness);
      result += deserializeUnsignedLongLongSequenceEndianness(&ulonglong_seq_out, &ulonglong_out_size, endianness);

      result += deserializeFloatSequenceEndianness(&float_seq_out, &float_out_size, endianness);
      result += deserializeDoubleSequenceEndianness(&double_seq_out, &double_out_size, endianness);
      result += deserializeLongDoubleSequenceEndianness(&longdouble_seq_out, &longdouble_out_size, endianness);
      result += deserializeStringSequenceEndianness(&string_seq_out, &string_out_size, endianness);

      EXPECT_EQ(result, 0);

      if(result == 0)
      {
        unsigned int comparative = std::strcmp(string_out, string_t);
        unsigned int comparative_2 = std::strcmp(string_out_2, emptystring_t);

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
          int length_in = std::strlen(string_seq_t[i]);
          int length_out = std::strlen(string_array_out[i]);
          int comparative = std::strcmp(string_seq_t[i], string_array_out[i]);
          EXPECT_EQ(length_in, length_out);
          EXPECT_EQ(comparative, 0);
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
          int length_in = std::strlen(string_seq_t[i]);
          int length_out = std::strlen(string_seq_out[i]);
          int comparative = std::strcmp(string_seq_t[i], string_seq_out[i]);
          EXPECT_EQ(length_in, length_out);
          EXPECT_EQ(comparative, 0);
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
      short short_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeShortEndianness(short_t, endianness);

      // Deseriazliation.
      deserializeShortEndianness(&short_out, endianness);

      EXPECT_EQ(short_out, short_t);
  }

  TEST(nanoCDRBasicEndiannessTests, UnsignedShort)
  {
      unsigned short ushort_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedShortEndianness(ushort_t, endianness);

      // Deseriazliation.
      deserializeUnsignedShortEndianness(&ushort_out, endianness);

      EXPECT_EQ(ushort_out, ushort_t);
  }


  TEST(nanoCDRBasicEndiannessTests, Int)
  {
      int long_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeIntEndianness(long_t, endianness);

      // Deseriazliation.
      deserializeIntEndianness(&long_out, endianness);

      EXPECT_EQ(long_out, long_t);
  }

  TEST(nanoCDRBasicEndiannessTests, UnsignedInt)
  {
      unsigned int ulong_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedIntEndianness(ulong_t, endianness);

      // Deseriazliation.
      deserializeUnsignedIntEndianness(&ulong_out, endianness);

      EXPECT_EQ(ulong_out, ulong_t);
  }

  TEST(nanoCDRBasicEndiannessTests, Long)
  {
      long long_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeLongEndianness(longlong_t, endianness);

      // Deseriazliation.
      deserializeLongEndianness(&long_out, endianness);

      EXPECT_EQ(long_out, longlong_t);
  }

  TEST(nanoCDRBasicEndiannessTests, uLong)
  {
      unsigned long ulong_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedLongEndianness(ulonglong_t, endianness);

      // Deseriazliation.
      deserializeUnsignedLongEndianness(&ulong_out, endianness);

      EXPECT_EQ(ulong_out, ulonglong_t);
  }

  TEST(nanoCDRBasicEndiannessTests, LongLong)
  {
      long long longlong_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeLongLongEndianness(longlonglong_t, endianness);

      // Deseriazliation.
      deserializeLongLongEndianness(&longlong_out, endianness);

      EXPECT_EQ(longlong_out, longlonglong_t);
  }

  TEST(nanoCDRBasicEndiannessTests, uLongLong)
  {
      unsigned long long ulonglong_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedLongLongEndianness(ulonglonglong_t, endianness);

      // Deseriazliation.
      deserializeUnsignedLongLongEndianness(&ulonglong_out, endianness);

      EXPECT_EQ(ulonglong_out, ulonglonglong_t);
  }

  TEST(nanoCDRBasicEndiannessTests, Float)
  {
      float float_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeFloatEndianness(float_tt, endianness);

      // Deseriazliation.
      deserializeFloatEndianness(&float_out, endianness);

      EXPECT_EQ(float_out, float_tt);
  }

  TEST(nanoCDRBasicEndiannessTests, Double)
  {
      double double_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeDoubleEndianness(double_tt, endianness);

      // Deseriazliation.
      deserializeDoubleEndianness(&double_out, endianness);

      EXPECT_EQ(double_out, double_tt);
  }

  TEST(nanoCDRBasicEndiannessTests, LongDouble)
  {
      long double longdouble_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeLongDoubleEndianness(longdouble_t, endianness);

      // Deseriazliation.
      deserializeLongDoubleEndianness(&longdouble_out, endianness);

      EXPECT_EQ(longdouble_out, longdouble_t);
  }

  TEST(nanoCDRBasicEndiannessTests, String)
  {
      char * string_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      const unsigned int length = std::strlen(string_t);
      unsigned int length_out;

      // Serialization.
      serializeStringEndianness(string_t, length, endianness);

      // Deseriazliation.
      deserializeStringEndianness(&string_out, &length_out, endianness);

      unsigned int comparative = std::strcmp(string_out, string_t);

      EXPECT_EQ(comparative, 0);
      EXPECT_EQ(length, length_out);
      free(string_out);
  }

  TEST(nanoCDRBasicEndiannessTests, EmptyString)
  {
      char * string_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      const unsigned int length = std::strlen(emptystring_t);
      unsigned int length_out;

      // Serialization.
      serializeStringEndianness(emptystring_t, length, endianness);

      // Deseriazliation.
      deserializeStringEndianness(&string_out, &length_out, endianness);

      unsigned int comparative = std::strcmp(string_out, emptystring_t);

      EXPECT_EQ(comparative, 0);
      EXPECT_EQ(length, length_out);
      free(string_out);
  }

  TEST(nanoCDRArrayEndiannessTests, ShortArray)
  {
      short * short_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeShortArrayEndianness(short_array_t, 5, endianness);

      // Deseriazliation.
      deserializeShortArrayEndianness(&short_out, 5, endianness);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(short_array_t[i], short_out[i]);
      }
      free(short_out);
  }

  TEST(nanoCDRArrayEndiannessTests, UnsignedShortArray)
  {
      unsigned short * ushort_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedShortArrayEndianness(ushort_array_t, 5, endianness);

      // Deseriazliation.
      deserializeUnsignedShortArrayEndianness(&ushort_out, 5, endianness);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(ushort_array_t[i], ushort_out[i]);
      }
      free(ushort_out);
  }

  TEST(nanoCDRArrayEndiannessTests, IntArray)
  {
      int * int_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeIntArrayEndianness(long_array_t, 5, endianness);

      // Deseriazliation.
      deserializeIntArrayEndianness(&int_out, 5, endianness);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(long_array_t[i], int_out[i]);
      }
      free(int_out);
  }

  TEST(nanoCDRArrayEndiannessTests, UnsignedIntArray)
  {
      unsigned int * uint_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedIntArrayEndianness(ulong_array_t, 5, endianness);

      // Deseriazliation.
      deserializeUnsignedIntArrayEndianness(&uint_out, 5, endianness);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(ulong_array_t[i], uint_out[i]);
      }
      free(uint_out);
  }

  TEST(nanoCDRArrayEndiannessTests, LongArray)
  {
      long * long_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeLongArrayEndianness(longlong_array_t, 5, endianness);

      // Deseriazliation.
      deserializeLongArrayEndianness(&long_out, 5, endianness);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(longlong_array_t[i], long_out[i]);
      }
      free(long_out);
  }

  TEST(nanoCDRArrayEndiannessTests, ULongArray)
  {
      unsigned long * ulong_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedLongArrayEndianness(ulonglong_array_t, 5, endianness);

      // Deseriazliation.
      deserializeUnsignedLongArrayEndianness(&ulong_out, 5, endianness);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(ulonglong_array_t[i], ulong_out[i]);
      }
      free(ulong_out);
  }

  TEST(nanoCDRArrayEndiannessTests, LongLongArray)
  {
      long long * longlong_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeLongLongArrayEndianness(longlonglong_array_t, 5, endianness);

      // Deseriazliation.
      deserializeLongLongArrayEndianness(&longlong_out, 5, endianness);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(longlonglong_array_t[i], longlong_out[i]);
      }
      free(longlong_out);
  }

  TEST(nanoCDRArrayEndiannessTests, ULongLongArray)
  {
      unsigned long long * ulonglong_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedLongLongArrayEndianness(ulonglonglong_array_t, 5, endianness);

      // Deseriazliation.
      deserializeUnsignedLongLongArrayEndianness(&ulonglong_out, 5, endianness);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(ulonglonglong_array_t[i], ulonglong_out[i]);
      }
      free(ulonglong_out);
  }

  TEST(nanoCDRArrayEndiannessTests, FloatArray)
  {
      float * float_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeFloatArrayEndianness(float_array_t, 5, endianness);

      // Deseriazliation.
      deserializeFloatArrayEndianness(&float_out, 5, endianness);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(float_array_t[i], float_out[i]);
      }
      free(float_out);
  }

  TEST(nanoCDRArrayEndiannessTests, DoubleArray)
  {
      double * double_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeDoubleArrayEndianness(double_array_t, 5, endianness);

      // Deseriazliation.
      deserializeDoubleArrayEndianness(&double_out, 5, endianness);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(double_array_t[i], double_out[i]);
      }

      free(double_out);
  }

  TEST(nanoCDRArrayEndiannessTests, LongDoubleArray)
  {
      long double * longdouble_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeLongDoubleArrayEndianness(longdouble_array_t, 5, endianness);

      // Deseriazliation.
      deserializeLongDoubleArrayEndianness(&longdouble_out, 5, endianness);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(longdouble_array_t[i], longdouble_out[i]);
      }
      free(longdouble_out);
  }

  TEST(nanoCDRArrayEndiannessTests, StringArray)
  {
      char ** string_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeStringArrayEndianness(string_seq_t, 5, endianness);

      // Deseriazliation.
      deserializeStringArrayEndianness(&string_out, 5, endianness);

      int i;
      for(i = 0; i < 5; i++)
      {
        int length_in = std::strlen(string_seq_t[i]);
        int length_out = std::strlen(string_out[i]);
        int comparative = std::strcmp(string_seq_t[i], string_out[i]);
        EXPECT_EQ(length_in, length_out);
        EXPECT_EQ(comparative, 0);
        free(string_out[i]);
      }
      free(string_out);
  }

  TEST(nanoCDRSequencesEndiannessTests, CharSequence)
  {
      char * char_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeCharSequenceEndianness(char_seq_t, 5, endianness);

      // Deseriazliation.
      deserializeCharSequenceEndianness(&char_out, &size_out, endianness);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(char_seq_t[i], char_out[i]);
      }

      free(char_out);
  }

  TEST(nanoCDRSequencesEndiannessTests, UnsignedCharSequence)
  {
      unsigned char * char_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedCharSequenceEndianness(octet_seq_t, 5, endianness);

      // Deseriazliation.
      deserializeUnsignedCharSequenceEndianness(&char_out, &size_out, endianness);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(octet_seq_t[i], char_out[i]);
      }

      free(char_out);
  }

  TEST(nanoCDRSequencesEndiannessTests, ShortSequence)
  {
      short * short_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeShortSequenceEndianness(short_seq_t, 5, endianness);

      // Deseriazliation.
      deserializeShortSequenceEndianness(&short_out, &size_out, endianness);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(short_seq_t[i], short_out[i]);
      }

      free(short_out);
  }

  TEST(nanoCDRSequencesEndiannessTests, UnsignedShortSequence)
  {
      unsigned short * ushort_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedShortSequenceEndianness(ushort_seq_t, 5, endianness);

      // Deseriazliation.
      deserializeUnsignedShortSequenceEndianness(&ushort_out, &size_out, endianness);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(ushort_seq_t[i], ushort_out[i]);
      }

      free(ushort_out);
  }

  TEST(nanoCDRSequencesEndiannessTests, IntSequence)
  {
      int * int_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeIntSequenceEndianness(long_seq_t, 5, endianness);

      // Deseriazliation.
      deserializeIntSequenceEndianness(&int_out, &size_out, endianness);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(long_seq_t[i], int_out[i]);
      }

      free(int_out);
  }

  TEST(nanoCDRSequencesEndiannessTests, UnsignedIntSequence)
  {
      unsigned int * uint_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedIntSequenceEndianness(ulong_seq_t, 5, endianness);

      // Deseriazliation.
      deserializeUnsignedIntSequenceEndianness(&uint_out, &size_out, endianness);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(ulong_seq_t[i], uint_out[i]);
      }

      free(uint_out);
  }

  TEST(nanoCDRSequencesEndiannessTests, LongSequence)
  {
      long * long_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeLongSequenceEndianness(longlong_seq_t, 5, endianness);

      // Deseriazliation.
      deserializeLongSequenceEndianness(&long_out, &size_out, endianness);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(longlong_seq_t[i], long_out[i]);
      }

      free(long_out);
  }

  TEST(nanoCDRSequencesEndiannessTests, ULongSequence)
  {
      unsigned long * ulong_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedLongSequenceEndianness(ulonglong_seq_t, 5, endianness);

      // Deseriazliation.
      deserializeUnsignedLongSequenceEndianness(&ulong_out, &size_out, endianness);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(ulonglong_seq_t[i], ulong_out[i]);
      }

      free(ulong_out);
  }

  TEST(nanoCDRSequencesEndiannessTests, LongLongSequence)
  {
      long long * longlong_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeLongLongSequenceEndianness(longlonglong_seq_t, 5, endianness);

      // Deseriazliation.
      deserializeLongLongSequenceEndianness(&longlong_out, &size_out, endianness);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(longlonglong_seq_t[i], longlong_out[i]);
      }

      free(longlong_out);
  }

  TEST(nanoCDRSequencesEndiannessTests, ULongLongSequence)
  {
      unsigned long long * ulonglong_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeUnsignedLongLongSequenceEndianness(ulonglonglong_seq_t, 5, endianness);

      // Deseriazliation.
      deserializeUnsignedLongLongSequenceEndianness(&ulonglong_out, &size_out, endianness);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(ulonglonglong_seq_t[i], ulonglong_out[i]);
      }

      free(ulonglong_out);
  }

  TEST(nanoCDRSequencesEndiannessTests, FloatSequence)
  {
      float * float_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeFloatSequenceEndianness(float_seq_t, 5, endianness);

      // Deseriazliation.
      deserializeFloatSequenceEndianness(&float_out, &size_out, endianness);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(float_seq_t[i], float_out[i]);
      }

      free(float_out);
  }

  TEST(nanoCDRSequencesEndiannessTests, DoubleSequence)
  {
      double * double_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeDoubleSequenceEndianness(double_seq_t, 5, endianness);

      // Deseriazliation.
      deserializeDoubleSequenceEndianness(&double_out, &size_out, endianness);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(double_seq_t[i], double_out[i]);
      }

      free(double_out);
  }

  TEST(nanoCDRSequencesEndiannessTests, LongDoubleSequence)
  {
      long double * longdouble_out;
      unsigned int size_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeLongDoubleSequenceEndianness(longdouble_seq_t, 5, endianness);

      // Deseriazliation.
      deserializeLongDoubleSequenceEndianness(&longdouble_out, &size_out, endianness);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        EXPECT_EQ(longdouble_seq_t[i], longdouble_out[i]);
      }

      free(longdouble_out);
  }

  TEST(nanoCDRSequencesEndiannessTests, StringSequence)
  {
      char ** string_out;
      char buffer[BUFFER_LENGTH];
      // Check good case.
      newStaticBuffer(buffer, BUFFER_LENGTH);

      // Serialization.
      serializeStringSequenceEndianness(string_seq_t, 5, endianness);

      unsigned int size_out;

      // Deseriazliation.
      deserializeStringSequenceEndianness(&string_out, &size_out, endianness);

      EXPECT_EQ(size_out, 5);

      int i;
      for(i = 0; i < 5; i++)
      {
        int length_in = std::strlen(string_seq_t[i]);
        int length_out = std::strlen(string_out[i]);
        int comparative = std::strcmp(string_seq_t[i], string_out[i]);
        EXPECT_EQ(length_in, length_out);
        EXPECT_EQ(comparative, 0);
        free(string_out[i]);
      }
      free(string_out);
  }
