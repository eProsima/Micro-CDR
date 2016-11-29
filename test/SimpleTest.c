#include <nanocdr/nanoCdr.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_LENGTH 2000

int main (int argc, const char* argv[])
{
  signed char octet_t = 32;
  const char char_t =  'Z';

  unsigned short ushort_t = 65500;
  short short_t = -32700;
  unsigned int ulong_t = 4294967200;
  int long_t = -2147483600;
  unsigned long ulonglong_t = 18446744073709551600u;
  long longlong_t = -9223372036800;

  float float_tt = FLT_MIN;
  double double_tt = DBL_MIN;

  //TODO bool
  //static const bool bool_t = true;

  char * string_t = "Hola a todos, esto es un test";
  char * emptystring_t = "";
  unsigned char octet_array_t[5] = {1, 2, 3, 4, 5};

  unsigned char octet_array_2_t[5] = {5, 4, 3, 2, 1};
  char char_array_t[5] = {'A', 'B', 'C', 'D', 'E'};
  char char_array_2_t[5] = {'E', 'D', 'C', 'B', 'A'};

  unsigned short ushort_array_t [5] = {65500, 65501, 65502, 65503, 65504};
  unsigned short ushort_array_2_t[5] = {65504, 65503, 65502, 65501, 65500};

  short short_array_t[5] = {-32700, -32701, -32702, -32703, -32704};
  short short_array_2_t[5] = {-32704, -32703, -32702, -32701, -32700};
  unsigned int ulong_array_t[5] = {4294967200, 4294967201, 4294967202, 4294967203, 4294967204};
  unsigned int ulong_array_2_t[5] = {4294967204, 4294967203, 4294967202, 4294967201, 4294967200};

  int long_array_t[5] = {-2147483600, -2147483601, -2147483602, -2147483603, -2147483604};
  int long_array_2_t[5] = {-2147483604, -2147483603, -2147483602, -2147483601, -2147483600};

  unsigned long ulonglong_array_t[5] = {18446744073709551600u, 18446744073709551601u, 18446744073709551602u, 18446744073709551603u, 18446744073709551604u};
  unsigned long ulonglong_array_2_t[5] = {18446744073709551604u, 18446744073709551603u, 18446744073709551602u, 18446744073709551601u, 18446744073709551600u};
  long  longlong_array_t[5] = {-9223372036800, -9223372036801, -9223372036802, -9223372036803, -9223372036804};
  long longlong_array_2_t[5] = {-9223372036804, -9223372036803, -9223372036802, -9223372036801, -9223372036800};

  float float_array_t[5] = {float_tt, float_tt + 1, float_tt + 2, float_tt + 3, float_tt + 4};
  float float_array_2_t[5] = {float_tt + 4, float_tt + 3, float_tt + 2, float_tt + 1, float_tt};

  double double_array_t[5] = {double_tt, double_tt + 1, double_tt + 2, double_tt + 3, double_tt + 4};
  double double_array_2_t[5] = {double_tt + 4, double_tt + 3, double_tt + 2, double_tt + 1, double_tt};

  //TODO bool
  //static const std::array<bool, 5> bool_array_t = {{true, false, true, false, true}};
  //static const bool bool_array_2_t[5] = {false, true, false, true, false};

  char * string_array_t[5];
  string_array_t[0] = "HOLA";
  string_array_t[1] = "ADIOS";
  string_array_t[2] = "HELLO";
  string_array_t[3] = "BYE";
  string_array_t[4] ="GOODBYE";

  char * string_array_2_t[5];
  string_array_t[0] = "HOLA";
  string_array_t[1] = "ADIOS";
  string_array_t[2] = "HELLO";
  string_array_t[3] = "BYE";
  string_array_t[4] = "GOODBYE";

  /*static const unsigned char octet_vector_t[] = {octet_array_2_t, octet_array_2_t + sizeof(octet_array_2_t) / sizeof(unsigned char)};
  static const std::vector<char> char_vector_t(char_array_2_t, char_array_2_t + sizeof(char_array_2_t) / sizeof(char));
  static const std::vector<uint16_t> ushort_vector_t(ushort_array_2_t, ushort_array_2_t + sizeof(ushort_array_2_t) / sizeof(uint16_t));
  static const std::vector<int16_t> short_vector_t(short_array_2_t, short_array_2_t + sizeof(short_array_2_t) / sizeof(int16_t));
  static const std::vector<uint32_t> ulong_vector_t(ulong_array_2_t, ulong_array_2_t + sizeof(ulong_array_2_t) / sizeof(uint32_t));
  static const std::vector<int32_t> long_vector_t(long_array_2_t, long_array_2_t + sizeof(long_array_2_t) / sizeof(int32_t));
  static const std::vector<uint64_t> ulonglong_vector_t(ulonglong_array_2_t, ulonglong_array_2_t + sizeof(ulonglong_array_2_t) / sizeof(uint64_t));
  static const std::vector<int64_t> longlong_vector_t(longlong_array_2_t, longlong_array_2_t + sizeof(longlong_array_2_t) / sizeof(int64_t));
  static const std::vector<float> float_vector_t(float_array_2_t, float_array_2_t + sizeof(float_array_2_t) / sizeof(float));
  static const std::vector<double> double_vector_t(double_array_2_t, double_array_2_t + sizeof(double_array_2_t) / sizeof(double));
  static const std::vector<bool> bool_vector_t(bool_array_2_t, bool_array_2_t + sizeof(bool_array_2_t) / sizeof(bool));
  static const std::vector<std::string> string_vector_t(string_array_2_t, string_array_2_t + sizeof(string_array_2_t) / sizeof(std::string));
  static const std::array<std::array<std::array<uint32_t, 3>, 2>, 2> triple_ulong_array_t = {{ {{ {{1, 2, 3}}, {{4, 5, 6}} }}, {{ {{7, 8, 9}}, {{10, 11, 12}} }} }};*/

  // Added because error 336.
  unsigned char octet_seq_t[5] = {5, 4, 3, 2, 1};
  char char_seq_t[5] = {'E', 'D', 'C', 'B', 'A'};
  unsigned short ushort_seq_t[5] = {65504, 65503, 65502, 65501, 65500};
  short short_seq_t[5] = {-32704, -32703, -32702, -32701, -32700};
  unsigned int ulong_seq_t[5] = {4294967204, 4294967203, 4294967202, 4294967201, 4294967200};
  int long_seq_t[5] = {-2147483604, -2147483603, -2147483602, -2147483601, -2147483600};
  unsigned long ulonglong_seq_t[5] = {18446744073709551604u, 18446744073709551603u, 18446744073709551602u, 18446744073709551601u, 18446744073709551600u};
  long longlong_seq_t[5] = {-9223372036804, -9223372036803, -9223372036802, -9223372036801, -9223372036800};
  float float_seq_t[5] = {float_tt + 4, float_tt + 3, float_tt + 2, float_tt + 1, float_tt};
  double double_seq_t[5] = {double_tt + 4, double_tt + 3, double_tt + 2, double_tt + 1, double_tt};

  //static const bool bool_seq_t[5] = {true, true, false, false, true};

  char * string_seq_t[5] = {"HELLO", "BYE", "GOODBYE", "HOLA", "ADIOS"};
  // Added because error 337
  char * c_string_t = "HOLA";
}
