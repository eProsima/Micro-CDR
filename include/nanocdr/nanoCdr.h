
#ifndef _NANOCDR_NANOCDR_H_
#define _NANOCDR_NANOCDR_H_

#include "nanoBuffer.h"

  typedef enum {BIG_ENDIANNESS,LITTLE_ENDIANNESS}Endianness;
  typedef enum {TRUE,FALSE}Bool;

  Bool m_swapBytes;

  Endianness m_endianness;

  struct nanoBuffer * m_cdrBuffer;

  /*!
   * @brief This function creates a dynamic stream of bytes.
   * The stream will be used to serialize.
   */
  void newDynamicBuffer ();


  /*!
   * @brief This function creates a static stream of bytes.
   * @param buffer The user's buffer that will be used. This buffer must be deallocated by the user. Cannot be NULL.
   * @param bufferSize The length of user's buffer.
   */
  void newStaticBuffer (char * buffer, unsigned int bufferSize);

  /*!
   * @brief This function destroies the nanoBuffer
   */
  void destroyBuffer ();

  /*!
  * @brief This function allocates memory.
  * The memory is not initialized.
  * The user will have to free this allocated memory using free() or freeCdr().
  * @param point_t The pointer where the memery will be allocated.
  * @param size Number of bytes that the user wants to allocate.
  */
  void mallocCdr (void ** point_t, unsigned int size);

  /*!
  * @brief This function frees the memory pointer by ponint_t.
  * @param point_t Pointer to the allocated memory.
  */
  void freeCdr (void ** point_t);


  void resetAlignment();

  //char * getBufferPointer ();

  /*!
  * @brief This function returns the length of the serialized data inside the stream.
  * @return The length of the serialized data.
  */
  unsigned int getSerializedDataLength ();

  /*!
  * @brief This function resets the current position in the buffer to the begining.
  */
  void reset ();


  /*!
  * @brief This function skips a number of bytes in the CDR stream buffer.
  * @param numBytes The number of bytes that will be jumped.
  * @return 0 is returned when the jump operation works successfully. Otherwise, -1 is returned.
  */
  short jump (unsigned short bytes);

  /*!
  * @brief This function returns the current position in the CDR stream.
  * @return Pointer to the current position in the buffer.
  */
  char * getCurrentPosition();

  /*!
  * @brief This function change the endianness of the buffer.
  * @param endianness The new endianness for the buffer.
  */
  void changeEndianness (Endianness endianness);


  /*!
  * @brief This function resizes the internal buffer. It only applies if the cdrBuffer was created with the dynamic mode.
  * @param minSizeInc Minimun size increase for the internal buffer
  * @return 0 if the resize was succesful, -1 if it was not
  */
  short resize (unsigned int minSizeInc);

  /*!
  * @brief This function serializes a character.
  * @param char_t The value of the character that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeChar (const char char_t);

  /*!
  * @brief This function serializes a signed character.
  * @param schar_t The value of the signed character that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeSignedChar (const signed char schar_t);

  /*!
  * @brief This function serializes an unsigned character.
  * @param uchar_t The value of the unsigned character that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedChar (const unsigned char uchar_t);

  /*!
  * @brief This function serializes a string.
  * @param string_t The pointer to the string that will be serialized in the buffer.
  * @param length_t Length of the string that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeString (const char * string_t, const unsigned int length_t);

  /*!
  * @brief This function serializes a string with a different endianness.
  * @param string_t The pointer to the string that will be serialized in the buffer.
  * @param length_t Length of the string that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeStringEndianness (const char * string_t, const unsigned int length_t, Endianness endianness);

  /*!
  * @brief This function deserializes a character.
  * @param char_t The variable that will store the character read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeChar (char * char_t);

  /*!
  * @brief This function deserializes a signed character.
  * @param schar_t The variable that will store the signed character read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeSignedChar (signed char * schar_t);

  /*!
  * @brief This function deserializes an unsigned character.
  * @param uchar_t The variable that will store the unsigned character read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedChar (unsigned char * uchar_t);

  /*!
  * @brief This function deserializes a string.
  * @param string_t The variable that will store the string read from the buffer.
  * @param strlen_t The variable that will store the length of the string.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeString (char ** string_t, unsigned int * strlen_t);

  /*!
  * @brief This function deserializes a string with a different endianness.
  * @param string_t The variable that will store the string read from the buffer.
  * @param strlen_t The variable that will store the length of the string.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeStringEndianness (char ** string_t, unsigned int * strlen_t, Endianness endianness);

  /*!
  * @brief This function serializes a short.
  * @param short_t The value of the short that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeShort (const short short_t);

  /*!
  * @brief This function serializes a short with a different endianness.
  * @param short_t The value of the short that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeShortEndianness (const short short_t, Endianness endianness);

  /*!
  * @brief This function serializes an unsigned short.
  * @param short_t The value of the unsigned short that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedShort (const unsigned short ushort_t);

  /*!
  * @brief This function serializes an unsigned short with a different endianness.
  * @param short_t The value of the unsigned short that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedShortEndianness (const unsigned short ushort_t, Endianness endianness);

  /*!
  * @brief This function serializes an int.
  * @param int_t The value of the integer that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeInt (const int int_t);

  /*!
  * @brief This function serializes an int wiht a different endianness.
  * @param int_t The value of the integer that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeIntEndianness (const int int_t, Endianness endianness);

  /*!
  * @brief This function serializes an unsigne dint.
  * @param uint_t The value of the unsigned int that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedInt (const unsigned int uint_t);

  /*!
  * @brief This function serializes an unsigned int with a different endianness.
  * @param uint_t The value of the unsigned int that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedIntEndianness (const unsigned int uint_t, Endianness endianness);

  /*!
  * @brief This function serializes a long.
  * @param long_t The value of the long that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeLong (const long long_t);

  /*!
  * @brief This function serializes a long with a different endianness.
  * @param long_t The value of the long that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeLongEndianness (const long long_t, Endianness endianness);

  /*!
  * @brief This function serializes an unsigned long.
  * @param ulong_t The value of the unsigned long that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedLong (const unsigned long ulong_t);

  /*!
  * @brief This function serializes an unsigned long with a different endianness.
  * @param ulong_t The value of the unsigned long that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedLongEndianness (const unsigned long ulong_t, Endianness endianness);

  /*!
  * @brief This function serializes a long long .
  * @param longlong_t The value of the long long that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeLongLong (const long long int longlong_t);

  /*!
  * @brief This function serializes a long long with a different endianness.
  * @param longlong_t The value of the long long that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeLongLongEndianness (const long long int longlong_t, Endianness endianness);

  /*!
  * @brief This function serializes an unsigned long long.
  * @param ulonglong_t The value of the unsigned long long that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedLongLong (const unsigned long long int ulonglong_t);

  /*!
  * @brief This function serializes an unsigned long long with a different endianness.
  * @param ulonglong_t The value of the unsigned long long that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedLongLongEndianness (const unsigned long long int ulonglong_t, Endianness endianness);

  /*!
  * @brief This function serializes a float.
  * @param float_t The value of the float that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeFloat (const float float_t);

  /*!
  * @brief This function serializes a float with a different endianness.
  * @param float_t The value of the float that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeFloatEndianness (const float float_t, Endianness endianness);

  /*!
  * @brief This function serializes a double.
  * @param double_t The value of the short that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeDouble (const double double_t);

  /*!
  * @brief This function serializes a double with a different endianness.
  * @param double_t The value of the short that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeDoubleEndianness (const double double_t, Endianness endianness);

  /*!
  * @brief This function serializes a long double.
  * @param longdouble_t The value of the short that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeLongDouble (const long double longdouble_t);

  /*!
  * @brief This function serializes a long double with a different endianness.
  * @param longdouble_t The value of the short that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeLongDoubleEndianness (const long double longdouble_t, Endianness endianness);

  /*!
  * @brief This function deserializes a short.
  * @param short_t The variable that will store the short read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeShort (short * short_t);

  /*!
  * @brief This function deserializes a short with a different endianness.
  * @param short_t The variable that will store the short read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeShortEndianness (short * short_t, Endianness endianness);

  /*!
  * @brief This function deserializes an unsigned short.
  * @param ushort_t The variable that will store the unsigned short read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedShort (unsigned short * ushort_t);

  /*!
  * @brief This function deserializes an unsigned short with a different endianness.
  * @param ushort_t The variable that will store the unsigned short read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedShortEndianness (unsigned short * ushort_t, Endianness endianness);

  /*!
  * @brief This function deserializes a int.
  * @param int_t The variable that will store the int read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeInt (int * int_t);

  /*!
  * @brief This function deserializes a int with a different endianness.
  * @param int_t The variable that will store the int read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeIntEndianness (int * int_t, Endianness endianness);

  /*!
  * @brief This function deserializes an unsigned int.
  * @param uint_t The variable that will store the unsigned read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedInt (unsigned int * uint_t);

  /*!
  * @brief This function deserializes an unsigned int with a different endianness.
  * @param uint_t The variable that will store the unsigned read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedIntEndianness (unsigned int * uint_t, Endianness endianness);

  /*!
  * @brief This function deserializes a long.
  * @param long_t The variable that will store the long read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeLong (long * long_t);

  /*!
  * @brief This function deserializes a long with a different endianness.
  * @param long_t The variable that will store the long read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeLongEndianness (long * long_t, Endianness endianness);

  /*!
  * @brief This function deserializes an unsigned long.
  * @param long_t The variable that will store the unsigned long read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedLong (unsigned long * ulong_t);

  /*!
  * @brief This function deserializes an unsigned long with a different endianness.
  * @param long_t The variable that will store the unsigned long read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedLongEndianness (unsigned long * ulong_t, Endianness endianness);

  /*!
  * @brief This function deserializes a long long.
  * @param longlong_t The variable that will store the long long read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeLongLong (long long int * longlong_t);

  /*!
  * @brief This function deserializes a long long with a different endianness.
  * @param longlong_t The variable that will store the long long read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeLongLongEndianness (long long int * longlong_t, Endianness endianness);

  /*!
  * @brief This function deserializes an unsigned long long.
  * @param ulonglong_t The variable that will store the unsigned long long read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedLongLong (unsigned long long int * ulonglong_t);

  /*!
  * @brief This function deserializes an unsigned long long with a different endianness.
  * @param ulonglong_t The variable that will store the unsigned long long read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedLongLongEndianness (unsigned long long int * ulonglong_t, Endianness endianness);

  /*!
  * @brief This function deserializes a float.
  * @param float_t The variable that will store the float read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeFloat (float * float_t);

  /*!
  * @brief This function deserializes a float with a different endianness.
  * @param float_t The variable that will store the float read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeFloatEndianness (float * float_t, Endianness endianness);

  /*!
  * @brief This function deserializes a double.
  * @param double_t The variable that will store the double read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeDouble (double * double_t);

  /*!
  * @brief This function deserializes a double with a different endianness.
  * @param double_t The variable that will store the double read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeDoubleEndianness (double * double_t, Endianness endianness);

  /*!
  * @brief This function deserializes a long double.
  * @param longdouble_t The variable that will store the long double read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeLongDouble (long double * double_t);

  /*!
  * @brief This function deserializes a long double with a different endianness.
  * @param longdouble_t The variable that will store the long double read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  short deserializeLongDoubleEndianness (long double * double_t, Endianness endianness);


  /*!
  * @brief This function serializes an array of charts.
  * @param chart_t The array of charts that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeCharArray (const char * char_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of unsigned charts.
  * @param uchart_t The array of charts that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedCharArray (const unsigned char * uchar_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of signed charts.
  * @param schart_t The array of charts that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeSignedCharArray (const signed char * schar_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of strings.
  * @param string_t The array of strings that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeStringArray (const char ** string_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of strings with a different endianness.
  * @param string_t The array of strings that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeStringArrayEndianness (const char ** string_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of shorts.
  * @param short_t The array of shorts that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeShortArray (const short * short_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of shorts with a different endianness.
  * @param short_t The array of shorts that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeShortArrayEndianness (const short * short_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of unsigned shorts.
  * @param ushort_t The array of unsigned shorts that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedShortArray (const unsigned short * ushort_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of unsigned shorts with a different endianness.
  * @param ushort_t The array of unsigned shorts that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedShortArrayEndianness (const unsigned short * ushort_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of ints.
  * @param int_t The array of ints that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeIntArray (const int * int_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of ints with a different endianness.
  * @param int_t The array of ints that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeIntArrayEndianness (const int * int_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of unsigned ints.
  * @param uint_t The array of unsigned ints that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedIntArray (const unsigned int * uint_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of unsigned ints with a different endianness.
  * @param uint_t The array of unsigned ints that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedIntArrayEndianness (const unsigned int * uint_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of longs.
  * @param long_t The array of longs that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeLongArray (const long * long_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of longs with a different endianness.
  * @param long_t The array of longs that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeLongArrayEndianness (const long * long_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of unsigned longs.
  * @param ulong_t The array of unsigned longs that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedLongArray (const unsigned long * ulong_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of unsigned longs with a different endianness.
  * @param ulong_t The array of unsigned longs that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedLongArrayEndianness (const unsigned long * ulong_t, const unsigned int numElements, Endianness endiannes);

  /*!
  * @brief This function serializes an array of long longs.
  * @param longlong_t The array of long longs that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeLongLongArray (const long long int * longlong_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of long longs with a different endianness.
  * @param longlong_t The array of long longs that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeLongLongArrayEndianness (const long long int * longlong_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of unsigned long longs.
  * @param ulonglong_t The array of unsigned long longs that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedLongLongArray (const unsigned long long int * ulonglong_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of unsigned long longs with a different endianness.
  * @param ulonglong_t The array of unsigned long longs that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedLongLongArrayEndianness (const unsigned long long int * ulonglong_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of floats.
  * @param float_t The array of floats that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeFloatArray (const float * float_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of floats with a different endianness.
  * @param float_t The array of floats that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeFloatArrayEndianness (const float * float_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of doubles.
  * @param double_t The array of doubles that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeDoubleArray (const double * double_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of doubles with a different endianness.
  * @param double_t The array of doubles that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeDoubleArrayEndianness (const double * double_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of long doubles.
  * @param longdouble_t The array of doubles that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeLongDoubleArray (const long double * longdouble_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of long doubles with a different endianness.
  * @param longdouble_t The array of doubles that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeLongDoubleArrayEndianness (const long double * longdouble_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of chars.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param char_t The variable that will store the array of chars read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeCharArray (char ** char_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of unsigned chars.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param uchar_t The variable that will store the array of chars read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedCharArray (unsigned char ** uchar_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of signed chars.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param schar_t The variable that will store the array of signed chars read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeSignedCharArray (signed char ** schar_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of strings.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param string_t The variable that will store the array of strings read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeStringArray (char *** string_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of strings with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param string_t The variable that will store the array of strings read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeStringArrayEndiannes (char *** string_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of shorts.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param short_t The variable that will store the array of shorts read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeShortArray (short ** short_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of shorts with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param short_t The variable that will store the array of shorts read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeShortArrayEndianness (short ** short_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of unsigned shorts.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ushort_t The variable that will store the array of unsigned shorts read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedShortArray (unsigned short ** ushort_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of unsigned shorts with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ushort_t The variable that will store the array of unsigned shorts read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedShortArrayEndianness (unsigned short ** ushort_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of ints.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param int_t The variable that will store the array of ints read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeIntArray (int ** int_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of ints with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param int_t The variable that will store the array of ints read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeIntArrayEndianness (int ** int_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of unsigned ints.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param uint_t The variable that will store the array of unsigned ints read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedIntArray (unsigned int ** int_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of unsigned ints with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param uint_t The variable that will store the array of unsigned ints read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedIntArrayEndianness (unsigned int ** int_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of longs.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param long_t The variable that will store the array of longs read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeLongArray (long ** long_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of longs with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param long_t The variable that will store the array of longs read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeLongArrayEndianness (long ** long_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of unsigned longs.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ulong_t The variable that will store the array of unsigned longs read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedLongArray (unsigned long ** ulong_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of unsigned longs with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ulong_t The variable that will store the array of unsigned longs read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedLongArrayEndiannness (unsigned long ** ulong_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of long longs.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param longlong_t The variable that will store the array of long longs read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeLongLongArray (long long int ** longlong_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of long longs with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param longlong_t The variable that will store the array of long longs read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeLongLongArrayEndianness (long long int ** longlong_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of unsigned long longs.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ulonglong_t The variable that will store the array of unsigned long longs read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedLongLongArray (unsigned long long int ** ulonglong_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of unsigned long longs with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ulonglong_t The variable that will store the array of unsigned long longs read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedLongLongArrayEndianness (unsigned long long int ** ulonglong_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of floats.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param float_t The variable that will store the array of floats read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeFloatArray (float ** float_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of floats with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param float_t The variable that will store the array of floats read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeFloatArrayEndianness (float ** float_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of doubles.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param float_t The variable that will store the array of doubles read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeDoubleArray (double ** double_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of doubles with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param float_t The variable that will store the array of doubles read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeDoubleArrayEndianness (double ** double_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of long doubles.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param longdouble_t The variable that will store the array of long doubles read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeLongDoubleArray (long double ** longdouble_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of long doubles with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param longdouble_t The variable that will store the array of long doubles read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeLongDoubleArrayEndianness (long double ** longdouble_t, const unsigned int numElements, Endianness endianness);


  /*!
  * @brief This function serializes a sequence of chars. The number of elements will be serialized in the buffer.
  * @param char_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeCharSequence (const char * char_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of chars. The number of elements will be serialized in the buffer with a different endianness.
  * @param char_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeCharSequenceEndianness (const char * char_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of unsigned chars. The number of elements will be serialized in the buffer.
  * @param char_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedCharSequence (const unsigned char * uchar_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of unsigned chars. The number of elements will be serialized in the buffer with a different endianness.
  * @param char_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedCharSequenceEndianness (const unsigned char * uchar_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of signed chars. The number of elements will be serialized in the buffer.
  * @param char_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeSignedCharSequence (const signed char * schar_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of signed chars. The number of elements will be serialized in the buffer with a different endianness.
  * @param char_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeSignedCharSequenceEndianness (const signed char * schar_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of strings. The number of elements will be serialized in the buffer.
  * @param string_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeStringSequence (const char ** string_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of strings. The number of elements will be serialized in the buffer with a different endianness.
  * @param string_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeStringSequenceEndianness (const char ** string_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of shorts. The number of elements will be serialized in the buffer.
  * @param short_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeShortSequence (const short * short_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of shorts with a different endianness. The number of elements will be serialized in the buffer.
  * @param short_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeShortSequenceEndianness (const short * short_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of unsigned shorts. The number of elements will be serialized in the buffer.
  * @param short_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedShortSequence (const unsigned short * ushort_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of unsigned shorts with a different endianness. The number of elements will be serialized in the buffer.
  * @param short_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedShortSequenceEndianness (const unsigned short * ushort_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of integers. The number of elements would not be serialized in the buffer.
  * @param int_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeIntSequence (const int * int_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of integers with a different endianness. The number of elements will be serialized in the buffer.
  * @param int_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeIntSequenceEndianness (const int * int_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of unsigned integers. The number of elements will be serialized in the buffer.
  * @param int_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedIntSequence (const unsigned int * uint_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of unsigned integers with a different endianness. The number of elements will be serialized in the buffer.
  * @param int_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedIntSequenceEndianness (const unsigned int * uint_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of longs. The number of elements will be serialized in the buffer.
  * @param long_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeLongSequence (const long * long_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of longs with a different endianness. The number of elements will be serialized in the buffer.
  * @param long_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeLongSequenceEndianness (const long * long_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of unsigned longs. The number of elements will be serialized in the buffer.
  * @param long_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedLongSequence (const unsigned long * ulong_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of unsigned longs with a different endianness. The number of elements will be serialized in the buffer.
  * @param long_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedLongSequenceEndianness (const unsigned long * ulong_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of long longs. The number of elements will be serialized in the buffer.
  * @param longlong_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeLongLongSequence (const long long int * longlong_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of long longs with a different endianness. The number of elements will be serialized in the buffer.
  * @param longlong_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeLongLongSequenceEndianness (const long long int * longlong_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of unsigned long longs. The number of elements will be serialized in the buffer.
  * @param longlong_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedLongLongSequence (const unsigned long long int * ulonglong_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of unsigned long longs with a different endianness. The number of elements will be serialized in the buffer.
  * @param longlong_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeUnsignedLongLongSequenceEndianness (const unsigned long long int * ulonglong_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of floats. The number of elements will be serialized in the buffer.
  * @param float_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeFloatSequence (const float * float_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of floats with a different endianness. The number of elements will be serialized in the buffer.
  * @param float_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeFloatSequenceEndianness (const float * float_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of doubles. The number of elements will be serialized in the buffer.
  * @param double_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeDoubleSequence (const double * double_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of doubles with a different endianness. The number of elements will be serialized in the buffer.
  * @param double_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeDoubleSequenceEndianness (const double * double_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of long doubles. The number of elements will be serialized in the buffer.
  * @param longdouble_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeLongDoubleSequence (const long double * longdouble_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of long doubles with a different endianness. The number of elements will be serialized in the buffer.
  * @param longdouble_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  short serializeLongDoubleSequenceEndianness (const long double * longdouble_t, const unsigned int numElements, Endianness endianness);


  /*!
  * @brief This function deserializes a sequence of chars.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param char_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeCharSequence (char ** char_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of chars with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param char_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeCharSequenceEndianness (char ** char_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of unsigned chars.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param uchar_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedCharSequence (unsigned char ** uchar_t, unsigned int * numElements);


  /*!
  * @brief This function deserializes a sequence of unsigned chars with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param uchar_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedCharSequenceEndianness (unsigned char ** uchar_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of signed chars.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param schar_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeSignedCharSequence (signed char ** schar_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of signed chars with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param schar_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeSignedCharSequenceEndianness (signed char ** schar_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of strings.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param string_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeStringSequence (char *** string_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of strings with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param string_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeStringSequenceEndianness (char *** string_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of shorts.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param short_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeShortSequence (short ** short_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of shorts with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param short_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeShortSequenceEndianness (short ** short_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of unsigned shorts.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ushort_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedShortSequence (unsigned short ** ushort_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of unsigned shorts with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ushort_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedShortSequenceEndianness (unsigned short ** ushort_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of ints.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param int_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeIntSequence (int ** int_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of ints with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param int_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeIntSequenceEndianness (int ** int_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of unsigned ints.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param uint_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedIntSequence (unsigned int ** uint_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of unsigned ints with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param uint_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedIntSequenceEndianness (unsigned int ** uint_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of longs.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param long_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeLongSequence (long ** long_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of longs with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param long_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeLongSequenceEndianness (long ** long_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of unsigned longs.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ulong_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedLongSequence (unsigned long ** ulong_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of unsigned longs with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ulong_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedLongSequenceEndianness (unsigned long ** ulong_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of long longs.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param longlong_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeLongLongSequence (long long int ** longlong_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of long longs with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param longlong_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeLongLongSequenceEndianness (long long int ** longlong_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of unsigned long longs.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ulonglong_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedLongLongSequence (unsigned long long int ** ulonglong_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of unsigned long longs with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ulonglong_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeUnsignedLongLongSequenceEndianness (unsigned long long int ** ulonglong_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of floats.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param float_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeFloatSequence (float ** float_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of floats with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param float_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeFloatSequenceEndianness (float ** float_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of doubles.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param double_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeDoubleSequence (double ** double_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of doubles with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param double_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeDoubleSequenceEndianness (double ** double_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of long doubles.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param longdouble_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeLongDoubleSequence (long double ** longdouble_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of long doubles with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param longdouble_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  short deserializeLongDoubleSequenceEndianness (long double ** longdouble_t, unsigned int * numElements, Endianness endianness);

#endif
