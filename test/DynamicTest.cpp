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

  const float float_tt = FLT_MIN;
  const double double_tt = DBL_MIN;

  //TODO bool
  //static const bool bool_t = true;

  const char * string_t = "Hola a todos, esto es un test";
  const char * emptystring_t = "";

  const unsigned char octet_array_t[5] = {1, 2, 3, 4, 5};
  const unsigned char octet_array_2_t[5] = {5, 4, 3, 2, 1};
  const char char_array_t[5] = {'A', 'B', 'C', 'D', 'E'};
  const char char_array_2_t[5] = {'E', 'D', 'C', 'B', 'A'};

  const unsigned short ushort_array_t [5] = {65500, 65501, 65502, 65503, 65504};
  const unsigned short ushort_array_2_t[5] = {65504, 65503, 65502, 65501, 65500};
  const short short_array_t[5] = {-32700, -32701, -32702, -32703, -32704};
  const short short_array_2_t[5] = {-32704, -32703, -32702, -32701, -32700};

  const unsigned int ulong_array_t[5] = {4294967200, 4294967201, 4294967202, 4294967203, 4294967204};
  const unsigned int ulong_array_2_t[5] = {4294967204, 4294967203, 4294967202, 4294967201, 4294967200};
  const int long_array_t[5] = {-2147483600, -2147483601, -2147483602, -2147483603, -2147483604};
  const int long_array_2_t[5] = {-2147483604, -2147483603, -2147483602, -2147483601, -2147483600};


  const unsigned long ulonglong_array_t[5] = {18446744073709551600u, 18446744073709551601u, 18446744073709551602u, 18446744073709551603u, 18446744073709551604u};
  const unsigned long ulonglong_array_2_t[5] = {18446744073709551604u, 18446744073709551603u, 18446744073709551602u, 18446744073709551601u, 18446744073709551600u};
  const long  longlong_array_t[5] = {-9223372036800, -9223372036801, -9223372036802, -9223372036803, -9223372036804};
  const long longlong_array_2_t[5] = {-9223372036804, -9223372036803, -9223372036802, -9223372036801, -9223372036800};


  const float float_array_t[5] = {float_tt, float_tt + 1, float_tt + 2, float_tt + 3, float_tt + 4};
  const float float_array_2_t[5] = {float_tt + 4, float_tt + 3, float_tt + 2, float_tt + 1, float_tt};

  const double double_array_t[5] = {double_tt, double_tt + 1, double_tt + 2, double_tt + 3, double_tt + 4};
  const double double_array_2_t[5] = {double_tt + 4, double_tt + 3, double_tt + 2, double_tt + 1, double_tt};

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

  const float float_seq_t[5] = {float_tt + 4, float_tt + 3, float_tt + 2, float_tt + 1, float_tt};
  const double double_seq_t[5] = {double_tt + 4, double_tt + 3, double_tt + 2, double_tt + 1, double_tt};

  //static const bool bool_seq_t[5] = {true, true, false, false, true};

  const char * string_seq_t[5] = {"HELLO", "BYE", "GOODBYE", "HOLA", "ADIOS"};
  // Added because error 337
  const char * c_string_t = "HOLA";


  TEST(nanoCDRDynamicTests, Char)
  {
      char char_out;
      //char buffer[BUFFER_LENGTH];
      // Check good case.
      newDynamicBuffer();

      // Serialization.
      serializeChar(char_t);

      // Deseriazliation.
      deserializeChar(&char_out);

      EXPECT_EQ(char_out, char_t);
  }

  TEST(nanoCDRDynamicTests, SignedChar)
  {
      signed char octect_out;
      // Check good case.
      newDynamicBuffer();

      // Serialization.
      serializeSignedChar(octet_t);

      // Deseriazliation.
      deserializeSignedChar(&octect_out);

      EXPECT_EQ(octect_out, octet_t);

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, Short)
  {
      short short_out;
      // Check good case.
      newDynamicBuffer();

      // Serialization.
      serializeShort(short_t);

      // Deseriazliation.
      deserializeShort(&short_out);

      EXPECT_EQ(short_out, short_t);

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, UnsignedShort)
  {
      unsigned short ushort_out;
      // Check good case.
      newDynamicBuffer();

      // Serialization.
      serializeUnsignedShort(ushort_t);

      // Deseriazliation.
      deserializeUnsignedShort(&ushort_out);

      EXPECT_EQ(ushort_out, ushort_t);

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, Int)
  {
      int long_out;
      // Check good case.
      newDynamicBuffer();

      // Serialization.
      serializeInt(long_t);

      // Deseriazliation.
      deserializeInt(&long_out);

      EXPECT_EQ(long_out, long_t);

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, UnsignedInt)
  {
      unsigned int ulong_out;
      // Check good case.
      newDynamicBuffer();

      // Serialization.
      serializeUnsignedInt(ulong_t);

      // Deseriazliation.
      deserializeUnsignedInt(&ulong_out);

      EXPECT_EQ(ulong_out, ulong_t);

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, Float)
  {
      float float_out;
      // Check good case.
      newDynamicBuffer();

      // Serialization.
      serializeFloat(float_tt);

      // Deseriazliation.
      deserializeFloat(&float_out);

      EXPECT_EQ(float_out, float_tt);

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, Double)
  {
      double double_out;
      // Check good case.
      newDynamicBuffer();

      // Serialization.
      serializeDouble(double_tt);

      // Deseriazliation.
      deserializeDouble(&double_out);

      EXPECT_EQ(double_out, double_tt);

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, String)
  {
      char * string_out;
      // Check good case.
      newDynamicBuffer();

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

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, EmptyString)
  {
      char * string_out;
      // Check good case.
      newDynamicBuffer();

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

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, CharArray)
  {
      char * char_out;
      // Check good case.
      newDynamicBuffer();

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

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, UnsignedCharArray)
  {
      unsigned char * char_out;
      // Check good case.
      newDynamicBuffer();

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

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, ShortArray)
  {
      short * short_out;
      // Check good case.
      newDynamicBuffer();

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

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, UnsignedShortArray)
  {
      unsigned short * ushort_out;
      // Check good case.
      newDynamicBuffer();

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

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, IntArray)
  {
      int * int_out;
      // Check good case.
      newDynamicBuffer();

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

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, UnsignedIntArray)
  {
      unsigned int * uint_out;
      // Check good case.
      newDynamicBuffer();

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

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, FloatArray)
  {
      float * float_out;
      // Check good case.
      newDynamicBuffer();

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

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, DoubleArray)
  {
      double * double_out;
      // Check good case.
      newDynamicBuffer();

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

      destroyBuffer();
  }

/*
  TEST(nanoCDRDynamicTests, StringArray)
  {
      char ** string_out;
      // Check good case.
      newDynamicBuffer();

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

      destroyBuffer();
  }
*/
  TEST(nanoCDRDynamicTests, CharSequence)
  {
      char * char_out;
      unsigned int size_out;
      // Check good case.
      newDynamicBuffer();

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

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, UnsignedCharSequence)
  {
      unsigned char * char_out;
      unsigned int size_out;
      // Check good case.
      newDynamicBuffer();

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

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, ShortSequence)
  {
      short * short_out;
      unsigned int size_out;
      // Check good case.
      newDynamicBuffer();

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

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, UnsignedShortSequence)
  {
      unsigned short * ushort_out;
      unsigned int size_out;
      // Check good case.
      newDynamicBuffer();

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

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, IntSequence)
  {
      int * int_out;
      unsigned int size_out;
      // Check good case.
      newDynamicBuffer();

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

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, UnsignedIntSequence)
  {
      unsigned int * uint_out;
      unsigned int size_out;
      // Check good case.
      newDynamicBuffer();

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

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, FloatSequence)
  {
      float * float_out;
      unsigned int size_out;
      // Check good case.
      newDynamicBuffer();

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

      destroyBuffer();
  }

  TEST(nanoCDRDynamicTests, DoubleSequence)
  {
      double * double_out;
      unsigned int size_out;
      // Check good case.
      newDynamicBuffer();

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

      destroyBuffer();
  }

/*
  TEST(nanoCDRDynamicTests, StringSequence)
  {
      char ** string_out;
      // Check good case.
      newDynamicBuffer();

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
      }

      destroyBuffer();
  }
*/

TEST(nanoCDRDynamicTests, SimpleVar)
{
  char char_out;
  signed char octect_out;
  short short_out;
  unsigned short ushort_out;
  int long_out;
  unsigned int ulong_out;
  float float_out;
  double double_out;
  char * string_out;
  char * string_out_2;

  newDynamicBuffer();

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
  serializeFloat(float_tt);
  serializeDouble(double_tt);
  serializeString(string_t, length);
  serializeString(emptystring_t, length_2);

  // Deseriazliation.
  deserializeChar(&char_out);
  deserializeSignedChar(&octect_out);
  deserializeShort(&short_out);
  deserializeUnsignedShort(&ushort_out);
  deserializeInt(&long_out);
  deserializeUnsignedInt(&ulong_out);
  deserializeFloat(&float_out);
  deserializeDouble(&double_out);
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
  EXPECT_EQ(float_out, float_tt);
  EXPECT_EQ(double_out, double_tt);
  EXPECT_EQ(comparative, 0);
  EXPECT_EQ(length, length_out);
  EXPECT_EQ(comparative_2, 0);
  EXPECT_EQ(length_2, length_out_2);

  destroyBuffer();
}

TEST(nanoCDRDynamicTests, Arrays)
{
  int i;
  char * char_out;
  unsigned char * uchar_out;
  short * short_out;
  unsigned short * ushort_out;
  int * int_out;
  unsigned int * uint_out;
  float * float_out;
  double * double_out;
  //char ** string_out;

  newDynamicBuffer();

  short result = 0;

  // Serialization.
  result += serializeCharArray(char_array_t, 5); //5
  result += serializeUnsignedCharArray(octet_array_t, 5); //5
  result += serializeShortArray(short_array_t, 5); //10
  result += serializeUnsignedShortArray(ushort_array_t, 5); //10
  result += serializeIntArray(long_array_t, 5); //20
  result += serializeUnsignedIntArray(ulong_array_t, 5); //20
  result += serializeFloatArray(float_array_t, 5); //20
  result += serializeDoubleArray(double_array_t, 5); //40
  //result += serializeStringArray(string_seq_t, 5);

  unsigned int serialized = getSerializedDataLength();

  EXPECT_EQ(result, 0);
  EXPECT_EQ(serialized, 130);

  if(result == 0){
    // Deseriazliation.
    result += deserializeCharArray(&char_out, 5);
    result += deserializeUnsignedCharArray(&uchar_out, 5);
    result += deserializeShortArray(&short_out, 5);
    result += deserializeUnsignedShortArray(&ushort_out, 5);
    result += deserializeIntArray(&int_out, 5);
    result += deserializeUnsignedIntArray(&uint_out, 5);
    result += deserializeFloatArray(&float_out, 5);
    result += deserializeDoubleArray(&double_out, 5);
    //result += deserializeStringArray(&string_out, 5);

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
        EXPECT_EQ(float_array_t[i], float_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(double_array_t[i], double_out[i]);
      }
      /*for(i = 0; i < 5; i++)
      {
        int length_in = std::strlen(string_seq_t[i]);
        int length_out = std::strlen(string_out[i]);
        int comparative = std::strcmp(string_seq_t[i], string_out[i]);
        EXPECT_EQ(length_in, length_out);
        EXPECT_EQ(comparative, 0);
      }*/

      free(char_out);
      free(uchar_out);
      free(short_out);
      free(ushort_out);
      free(int_out);
      free(uint_out);
      free(float_out);
      free(double_out);

      destroyBuffer();
    }
  }
}

TEST(nanoCDRDynamicTests, Sequences)
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
  float * float_out;
  unsigned int float_out_size;
  double * double_out;
  unsigned int double_out_size;
  //char ** string_out;

  short result = 0;

  newDynamicBuffer();

  // Serialization.
  result += serializeCharSequence(char_seq_t, 5); //9
  result += serializeUnsignedCharSequence(octet_seq_t, 5); //9
  result += serializeShortSequence(short_seq_t, 5);//14
  result += serializeUnsignedShortSequence(ushort_seq_t, 5);//14
  result += serializeIntSequence(long_seq_t, 5);//24
  result += serializeUnsignedIntSequence(ulong_seq_t, 5);//24
  result += serializeFloatSequence(float_seq_t, 5);//24
  result += serializeDoubleSequence(double_seq_t, 5);//44
  //result += serializeStringArray(string_seq_t, 5);

  unsigned int serialized = getSerializedDataLength();
  EXPECT_EQ(serialized, 162);

  EXPECT_EQ(result, 0);

  if(result == 0){
    // Deseriazliation.
    result += deserializeCharSequence(&char_out, &char_out_size);
    result += deserializeUnsignedCharSequence(&uchar_out, &uchar_out_size);
    result += deserializeShortSequence(&short_out, &short_out_size);
    result += deserializeUnsignedShortSequence(&ushort_out, &ushort_out_size);
    result += deserializeIntSequence(&int_out, &int_out_size);
    result += deserializeUnsignedIntSequence(&uint_out, &uint_out_size);
    result += deserializeFloatSequence(&float_out, &float_out_size);
    result += deserializeDoubleSequence(&double_out, &double_out_size);
    //result += deserializeStringArray(&string_out, 5);

    EXPECT_EQ(result, 0);

    if(result == 0){
      EXPECT_EQ(char_out_size, 5);
      EXPECT_EQ(uchar_out_size, 5);
      EXPECT_EQ(short_out_size, 5);
      EXPECT_EQ(ushort_out_size, 5);
      EXPECT_EQ(int_out_size, 5);
      EXPECT_EQ(uint_out_size, 5);
      EXPECT_EQ(float_out_size, 5);
      EXPECT_EQ(double_out_size, 5);

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
        EXPECT_EQ(float_seq_t[i], float_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(double_seq_t[i], double_out[i]);
      }
      /*for(i = 0; i < 5; i++)
      {
        int length_in = std::strlen(string_seq_t[i]);
        int length_out = std::strlen(string_out[i]);
        int comparative = std::strcmp(string_seq_t[i], string_out[i]);
        EXPECT_EQ(length_in, length_out);
        EXPECT_EQ(comparative, 0);
      }*/

      free(char_out);
      free(uchar_out);
      free(short_out);
      free(ushort_out);
      free(int_out);
      free(uint_out);
      free(float_out);
      free(double_out);

      destroyBuffer();
    }
  }
}

TEST(nanoCDRDynamicTests, All)
{
  //SIMPLE
  char char_out;
  signed char octect_out;
  short short_out;
  unsigned short ushort_out;
  int long_out;
  unsigned int ulong_out;
  float float_out;
  double double_out;
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
  float * float_array_out;
  double * double_array_out;

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
  float * float_seq_out;
  unsigned int float_out_size;
  double * double_seq_out;
  unsigned int double_out_size;

  newDynamicBuffer();

  const unsigned int length = std::strlen(string_t);
  unsigned int length_out;

  short result = 0;

  const unsigned int length_2 = std::strlen(emptystring_t);
  unsigned int length_out_2;

  // Serialization.
  result += serializeChar(char_t); //1
  result += serializeSignedChar(octet_t); //1
  result += serializeShort(short_t); //2
  result += serializeUnsignedShort(ushort_t); //2
  result += serializeInt(long_t); //4
  result += serializeUnsignedInt(ulong_t); //4
  result += serializeFloat(float_tt); //4
  result += serializeDouble(double_tt); //8
  result += serializeString(string_t, length); //4 + 30
  result += serializeString(emptystring_t, length_2); //4 + 1

  result += serializeCharArray(char_array_t, 5); //5
  result += serializeUnsignedCharArray(octet_array_t, 5); //5
  result += serializeShortArray(short_array_t, 5); //10
  result += serializeUnsignedShortArray(ushort_array_t, 5); //10
  result += serializeIntArray(long_array_t, 5); //20
  result += serializeUnsignedIntArray(ulong_array_t, 5); //20
  result += serializeFloatArray(float_array_t, 5); //20
  result += serializeDoubleArray(double_array_t, 5); //40
  //result += serializeStringArray(string_seq_t, 5);

  result += serializeCharSequence(char_seq_t, 5); //9
  result += serializeUnsignedCharSequence(octet_seq_t, 5); //9
  result += serializeShortSequence(short_seq_t, 5);//14
  result += serializeUnsignedShortSequence(ushort_seq_t, 5);//14
  result += serializeIntSequence(long_seq_t, 5);//24
  result += serializeUnsignedIntSequence(ulong_seq_t, 5);//24
  result += serializeFloatSequence(float_seq_t, 5);//24
  result += serializeDoubleSequence(double_seq_t, 5);//44

  unsigned int serialized = getSerializedDataLength();
  EXPECT_EQ(serialized, 357);
  EXPECT_EQ(result, 0);

  if(result == 0){
  // Deseriazliation.
    result += deserializeChar(&char_out);
    result += deserializeSignedChar(&octect_out);
    result += deserializeShort(&short_out);
    result += deserializeUnsignedShort(&ushort_out);
    result += deserializeInt(&long_out);
    result += deserializeUnsignedInt(&ulong_out);
    result += deserializeFloat(&float_out);
    result += deserializeDouble(&double_out);
    result += deserializeString(&string_out, &length_out);
    result += deserializeString(&string_out_2, &length_out_2);

    result += deserializeCharArray(&char_array_out, 5);
    result += deserializeUnsignedCharArray(&uchar_array_out, 5);
    result += deserializeShortArray(&short_array_out, 5);
    result += deserializeUnsignedShortArray(&ushort_array_out, 5);
    result += deserializeIntArray(&int_array_out, 5);
    result += deserializeUnsignedIntArray(&uint_array_out, 5);
    result += deserializeFloatArray(&float_array_out, 5);
    result += deserializeDoubleArray(&double_array_out, 5);
    //result += deserializeStringArray(&string_out, 5);

    result += deserializeCharSequence(&char_seq_out, &char_out_size);
    result += deserializeUnsignedCharSequence(&uchar_seq_out, &uchar_out_size);
    result += deserializeShortSequence(&short_seq_out, &short_out_size);
    result += deserializeUnsignedShortSequence(&ushort_seq_out, &ushort_out_size);
    result += deserializeIntSequence(&int_seq_out, &int_out_size);
    result += deserializeUnsignedIntSequence(&uint_seq_out, &uint_out_size);
    result += deserializeFloatSequence(&float_seq_out, &float_out_size);
    result += deserializeDoubleSequence(&double_seq_out, &double_out_size);

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
      EXPECT_EQ(float_out, float_tt);
      EXPECT_EQ(double_out, double_tt);
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
        EXPECT_EQ(float_array_t[i], float_array_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(double_array_t[i], double_array_out[i]);
      }
      /*for(i = 0; i < 5; i++)
      {
        int length_in = std::strlen(string_seq_t[i]);
        int length_out = std::strlen(string_out[i]);
        int comparative = std::strcmp(string_seq_t[i], string_out[i]);
        EXPECT_EQ(length_in, length_out);
        EXPECT_EQ(comparative, 0);
      }*/

      EXPECT_EQ(char_out_size, 5);
      EXPECT_EQ(uchar_out_size, 5);
      EXPECT_EQ(short_out_size, 5);
      EXPECT_EQ(ushort_out_size, 5);
      EXPECT_EQ(int_out_size, 5);
      EXPECT_EQ(uint_out_size, 5);
      EXPECT_EQ(float_out_size, 5);
      EXPECT_EQ(double_out_size, 5);

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
        EXPECT_EQ(float_seq_t[i], float_seq_out[i]);
      }
      for(i = 0; i < 5; i++){
        EXPECT_EQ(double_seq_t[i], double_seq_out[i]);
      }

      /*for(i = 0; i < 5; i++)
      {
        int length_in = std::strlen(string_seq_t[i]);
        int length_out = std::strlen(string_out[i]);
        int comparative = std::strcmp(string_seq_t[i], string_out[i]);
        EXPECT_EQ(length_in, length_out);
        EXPECT_EQ(comparative, 0);
      }*/

      free(char_array_out);
      free(uchar_array_out);
      free(short_array_out);
      free(ushort_array_out);
      free(int_array_out);
      free(uint_array_out);
      free(float_array_out);
      free(double_array_out);

      free(char_seq_out);
      free(uchar_seq_out);
      free(short_seq_out);
      free(ushort_seq_out);
      free(int_seq_out);
      free(uint_seq_out);
      free(float_seq_out);
      free(double_seq_out);

      destroyBuffer();
    }
  }
}
