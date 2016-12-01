
#ifndef _NANOCDR_NANOCDR_H_
#define _NANOCDR_NANOCDR_H_

#include "nanocdr_dll.h"
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
  nanocdr_DllAPI void newDynamicBuffer ();


  /*!
   * @brief This function creates a static stream of bytes.
   * @param buffer The user's buffer that will be used. This buffer must be deallocated by the user. Cannot be NULL.
   * @param bufferSize The length of user's buffer.
   */
  nanocdr_DllAPI void newStaticBuffer (char * buffer, unsigned int bufferSize);

  /*!
   * @brief This function destroies the nanoBuffer
   */
  nanocdr_DllAPI void destroyBuffer ();

  /*!
  * @brief This function allocates memory.
  * The memory is not initialized.
  * The user will have to free this allocated memory using free() or freeCdr().
  * @param point_t The pointer where the memery will be allocated.
  * @param size Number of bytes that the user wants to allocate.
  */
  nanocdr_DllAPI void mallocCdr (void ** point_t, unsigned int size);

  /*!
  * @brief This function frees the memory pointer by ponint_t.
  * @param point_t Pointer to the allocated memory.
  */
  nanocdr_DllAPI void freeCdr (void ** point_t);


  nanocdr_DllAPI void resetAlignment();

  //char * getBufferPointer ();

  /*!
  * @brief This function returns the length of the serialized data inside the stream.
  * @return The length of the serialized data.
  */
  nanocdr_DllAPI unsigned int getSerializedDataLength ();

  /*!
  * @brief This function resets the current position in the buffer to the begining.
  */
  nanocdr_DllAPI void reset ();


  /*!
  * @brief This function skips a number of bytes in the CDR stream buffer.
  * @param numBytes The number of bytes that will be jumped.
  * @return 0 is returned when the jump operation works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short jump (unsigned short bytes);

  /*!
  * @brief This function returns the current position in the CDR stream.
  * @return Pointer to the current position in the buffer.
  */
  nanocdr_DllAPI char * getCurrentPosition();

  /*!
  * @brief This function change the endianness of the buffer.
  * @param endianness The new endianness for the buffer.
  */
  nanocdr_DllAPI void changeEndianness (Endianness endianness);


  /*!
  * @brief This function resizes the internal buffer. It only applies if the cdrBuffer was created with the dynamic mode.
  * @param minSizeInc Minimun size increase for the internal buffer
  * @return 0 if the resize was succesful, -1 if it was not
  */
  nanocdr_DllAPI short resize (unsigned int minSizeInc);

  /*!
  * @brief This function serializes a character.
  * @param char_t The value of the character that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeChar (const char char_t);

  /*!
  * @brief This function serializes a signed character.
  * @param schar_t The value of the signed character that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeSignedChar (const signed char schar_t);

  /*!
  * @brief This function serializes an unsigned character.
  * @param uchar_t The value of the unsigned character that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedChar (const unsigned char uchar_t);

  /*!
  * @brief This function serializes a string.
  * @param string_t The pointer to the string that will be serialized in the buffer.
  * @param length_t Length of the string that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeString (const char * string_t, const unsigned int length_t);

  /*!
  * @brief This function serializes a string with a different endianness.
  * @param string_t The pointer to the string that will be serialized in the buffer.
  * @param length_t Length of the string that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeStringEndianness (const char * string_t, const unsigned int length_t, Endianness endianness);

  /*!
  * @brief This function deserializes a character.
  * @param char_t The variable that will store the character read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeChar (char * char_t);

  /*!
  * @brief This function deserializes a signed character.
  * @param schar_t The variable that will store the signed character read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeSignedChar (signed char * schar_t);

  /*!
  * @brief This function deserializes an unsigned character.
  * @param uchar_t The variable that will store the unsigned character read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedChar (unsigned char * uchar_t);

  /*!
  * @brief This function deserializes a string.
  * @param string_t The variable that will store the string read from the buffer.
  * @param strlen_t The variable that will store the length of the string.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeString (char ** string_t, unsigned int * strlen_t);

  /*!
  * @brief This function deserializes a string with a different endianness.
  * @param string_t The variable that will store the string read from the buffer.
  * @param strlen_t The variable that will store the length of the string.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeStringEndianness (char ** string_t, unsigned int * strlen_t, Endianness endianness);

  /*!
  * @brief This function serializes a short.
  * @param short_t The value of the short that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeShort (const short short_t);

  /*!
  * @brief This function serializes a short with a different endianness.
  * @param short_t The value of the short that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeShortEndianness (const short short_t, Endianness endianness);

  /*!
  * @brief This function serializes an unsigned short.
  * @param short_t The value of the unsigned short that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedShort (const unsigned short ushort_t);

  /*!
  * @brief This function serializes an unsigned short with a different endianness.
  * @param short_t The value of the unsigned short that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedShortEndianness (const unsigned short ushort_t, Endianness endianness);

  /*!
  * @brief This function serializes an int.
  * @param int_t The value of the integer that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeInt (const int int_t);

  /*!
  * @brief This function serializes an int wiht a different endianness.
  * @param int_t The value of the integer that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeIntEndianness (const int int_t, Endianness endianness);

  /*!
  * @brief This function serializes an unsigne dint.
  * @param uint_t The value of the unsigned int that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedInt (const unsigned int uint_t);

  /*!
  * @brief This function serializes an unsigned int with a different endianness.
  * @param uint_t The value of the unsigned int that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedIntEndianness (const unsigned int uint_t, Endianness endianness);

  /*!
  * @brief This function serializes a long.
  * @param long_t The value of the long that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeLong (const long long_t);

  /*!
  * @brief This function serializes a long with a different endianness.
  * @param long_t The value of the long that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeLongEndianness (const long long_t, Endianness endianness);

  /*!
  * @brief This function serializes an unsigned long.
  * @param ulong_t The value of the unsigned long that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedLong (const unsigned long ulong_t);

  /*!
  * @brief This function serializes an unsigned long with a different endianness.
  * @param ulong_t The value of the unsigned long that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedLongEndianness (const unsigned long ulong_t, Endianness endianness);

  /*!
  * @brief This function serializes a long long .
  * @param longlong_t The value of the long long that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeLongLong (const long long int longlong_t);

  /*!
  * @brief This function serializes a long long with a different endianness.
  * @param longlong_t The value of the long long that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeLongLongEndianness (const long long int longlong_t, Endianness endianness);

  /*!
  * @brief This function serializes an unsigned long long.
  * @param ulonglong_t The value of the unsigned long long that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedLongLong (const unsigned long long int ulonglong_t);

  /*!
  * @brief This function serializes an unsigned long long with a different endianness.
  * @param ulonglong_t The value of the unsigned long long that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedLongLongEndianness (const unsigned long long int ulonglong_t, Endianness endianness);

  /*!
  * @brief This function serializes a float.
  * @param float_t The value of the float that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeFloat (const float float_t);

  /*!
  * @brief This function serializes a float with a different endianness.
  * @param float_t The value of the float that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeFloatEndianness (const float float_t, Endianness endianness);

  /*!
  * @brief This function serializes a double.
  * @param double_t The value of the short that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeDouble (const double double_t);

  /*!
  * @brief This function serializes a double with a different endianness.
  * @param double_t The value of the short that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serrialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeDoubleEndianness (const double double_t, Endianness endianness);

  /*!
  * @brief This function serializes a long double.
  * @param longdouble_t The value of the short that will be serialized in the buffer.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeLongDouble (const long double longdouble_t);

  /*!
  * @brief This function serializes a long double with a different endianness.
  * @param longdouble_t The value of the short that will be serialized in the buffer.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeLongDoubleEndianness (const long double longdouble_t, Endianness endianness);

  /*!
  * @brief This function deserializes a short.
  * @param short_t The variable that will store the short read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeShort (short * short_t);

  /*!
  * @brief This function deserializes a short with a different endianness.
  * @param short_t The variable that will store the short read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeShortEndianness (short * short_t, Endianness endianness);

  /*!
  * @brief This function deserializes an unsigned short.
  * @param ushort_t The variable that will store the unsigned short read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedShort (unsigned short * ushort_t);

  /*!
  * @brief This function deserializes an unsigned short with a different endianness.
  * @param ushort_t The variable that will store the unsigned short read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedShortEndianness (unsigned short * ushort_t, Endianness endianness);

  /*!
  * @brief This function deserializes a int.
  * @param int_t The variable that will store the int read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeInt (int * int_t);

  /*!
  * @brief This function deserializes a int with a different endianness.
  * @param int_t The variable that will store the int read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeIntEndianness (int * int_t, Endianness endianness);

  /*!
  * @brief This function deserializes an unsigned int.
  * @param uint_t The variable that will store the unsigned read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedInt (unsigned int * uint_t);

  /*!
  * @brief This function deserializes an unsigned int with a different endianness.
  * @param uint_t The variable that will store the unsigned read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedIntEndianness (unsigned int * uint_t, Endianness endianness);

  /*!
  * @brief This function deserializes a long.
  * @param long_t The variable that will store the long read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeLong (long * long_t);

  /*!
  * @brief This function deserializes a long with a different endianness.
  * @param long_t The variable that will store the long read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeLongEndianness (long * long_t, Endianness endianness);

  /*!
  * @brief This function deserializes an unsigned long.
  * @param long_t The variable that will store the unsigned long read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedLong (unsigned long * ulong_t);

  /*!
  * @brief This function deserializes an unsigned long with a different endianness.
  * @param long_t The variable that will store the unsigned long read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedLongEndianness (unsigned long * ulong_t, Endianness endianness);

  /*!
  * @brief This function deserializes a long long.
  * @param longlong_t The variable that will store the long long read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeLongLong (long long int * longlong_t);

  /*!
  * @brief This function deserializes a long long with a different endianness.
  * @param longlong_t The variable that will store the long long read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeLongLongEndianness (long long int * longlong_t, Endianness endianness);

  /*!
  * @brief This function deserializes an unsigned long long.
  * @param ulonglong_t The variable that will store the unsigned long long read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedLongLong (unsigned long long int * ulonglong_t);

  /*!
  * @brief This function deserializes an unsigned long long with a different endianness.
  * @param ulonglong_t The variable that will store the unsigned long long read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedLongLongEndianness (unsigned long long int * ulonglong_t, Endianness endianness);

  /*!
  * @brief This function deserializes a float.
  * @param float_t The variable that will store the float read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeFloat (float * float_t);

  /*!
  * @brief This function deserializes a float with a different endianness.
  * @param float_t The variable that will store the float read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeFloatEndianness (float * float_t, Endianness endianness);

  /*!
  * @brief This function deserializes a double.
  * @param double_t The variable that will store the double read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeDouble (double * double_t);

  /*!
  * @brief This function deserializes a double with a different endianness.
  * @param double_t The variable that will store the double read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeDoubleEndianness (double * double_t, Endianness endianness);

  /*!
  * @brief This function deserializes a long double.
  * @param longdouble_t The variable that will store the long double read from the buffer.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeLongDouble (long double * double_t);

  /*!
  * @brief This function deserializes a long double with a different endianness.
  * @param longdouble_t The variable that will store the long double read from the buffer.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeLongDoubleEndianness (long double * double_t, Endianness endianness);


  /*!
  * @brief This function serializes an array of charts.
  * @param chart_t The array of charts that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeCharArray (const char * char_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of unsigned charts.
  * @param uchart_t The array of charts that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedCharArray (const unsigned char * uchar_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of signed charts.
  * @param schart_t The array of charts that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeSignedCharArray (const signed char * schar_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of strings.
  * @param string_t The array of strings that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeStringArray (const char ** string_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of strings with a different endianness.
  * @param string_t The array of strings that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeStringArrayEndianness (const char ** string_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of shorts.
  * @param short_t The array of shorts that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeShortArray (const short * short_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of shorts with a different endianness.
  * @param short_t The array of shorts that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeShortArrayEndianness (const short * short_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of unsigned shorts.
  * @param ushort_t The array of unsigned shorts that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedShortArray (const unsigned short * ushort_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of unsigned shorts with a different endianness.
  * @param ushort_t The array of unsigned shorts that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedShortArrayEndianness (const unsigned short * ushort_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of ints.
  * @param int_t The array of ints that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeIntArray (const int * int_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of ints with a different endianness.
  * @param int_t The array of ints that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeIntArrayEndianness (const int * int_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of unsigned ints.
  * @param uint_t The array of unsigned ints that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedIntArray (const unsigned int * uint_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of unsigned ints with a different endianness.
  * @param uint_t The array of unsigned ints that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedIntArrayEndianness (const unsigned int * uint_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of longs.
  * @param long_t The array of longs that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeLongArray (const long * long_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of longs with a different endianness.
  * @param long_t The array of longs that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeLongArrayEndianness (const long * long_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of unsigned longs.
  * @param ulong_t The array of unsigned longs that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedLongArray (const unsigned long * ulong_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of unsigned longs with a different endianness.
  * @param ulong_t The array of unsigned longs that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedLongArrayEndianness (const unsigned long * ulong_t, const unsigned int numElements, Endianness endiannes);

  /*!
  * @brief This function serializes an array of long longs.
  * @param longlong_t The array of long longs that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeLongLongArray (const long long int * longlong_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of long longs with a different endianness.
  * @param longlong_t The array of long longs that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeLongLongArrayEndianness (const long long int * longlong_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of unsigned long longs.
  * @param ulonglong_t The array of unsigned long longs that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedLongLongArray (const unsigned long long int * ulonglong_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of unsigned long longs with a different endianness.
  * @param ulonglong_t The array of unsigned long longs that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedLongLongArrayEndianness (const unsigned long long int * ulonglong_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of floats.
  * @param float_t The array of floats that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeFloatArray (const float * float_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of floats with a different endianness.
  * @param float_t The array of floats that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeFloatArrayEndianness (const float * float_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of doubles.
  * @param double_t The array of doubles that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeDoubleArray (const double * double_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of doubles with a different endianness.
  * @param double_t The array of doubles that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeDoubleArrayEndianness (const double * double_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes an array of long doubles.
  * @param longdouble_t The array of doubles that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeLongDoubleArray (const long double * longdouble_t, const unsigned int numElements);

  /*!
  * @brief This function serializes an array of long doubles with a different endianness.
  * @param longdouble_t The array of doubles that will be serialized in the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeLongDoubleArrayEndianness (const long double * longdouble_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of chars.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param char_t The variable that will store the array of chars read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeCharArray (char ** char_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of unsigned chars.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param uchar_t The variable that will store the array of chars read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedCharArray (unsigned char ** uchar_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of signed chars.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param schar_t The variable that will store the array of signed chars read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeSignedCharArray (signed char ** schar_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of strings.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param string_t The variable that will store the array of strings read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeStringArray (char *** string_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of strings with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param string_t The variable that will store the array of strings read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeStringArrayEndianness (char *** string_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of shorts.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param short_t The variable that will store the array of shorts read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeShortArray (short ** short_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of shorts with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param short_t The variable that will store the array of shorts read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeShortArrayEndianness (short ** short_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of unsigned shorts.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ushort_t The variable that will store the array of unsigned shorts read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedShortArray (unsigned short ** ushort_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of unsigned shorts with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ushort_t The variable that will store the array of unsigned shorts read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedShortArrayEndianness (unsigned short ** ushort_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of ints.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param int_t The variable that will store the array of ints read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeIntArray (int ** int_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of ints with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param int_t The variable that will store the array of ints read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeIntArrayEndianness (int ** int_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of unsigned ints.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param uint_t The variable that will store the array of unsigned ints read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedIntArray (unsigned int ** int_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of unsigned ints with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param uint_t The variable that will store the array of unsigned ints read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedIntArrayEndianness (unsigned int ** int_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of longs.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param long_t The variable that will store the array of longs read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeLongArray (long ** long_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of longs with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param long_t The variable that will store the array of longs read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeLongArrayEndianness (long ** long_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of unsigned longs.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ulong_t The variable that will store the array of unsigned longs read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedLongArray (unsigned long ** ulong_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of unsigned longs with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ulong_t The variable that will store the array of unsigned longs read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedLongArrayEndianness (unsigned long ** ulong_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of long longs.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param longlong_t The variable that will store the array of long longs read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeLongLongArray (long long int ** longlong_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of long longs with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param longlong_t The variable that will store the array of long longs read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeLongLongArrayEndianness (long long int ** longlong_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of unsigned long longs.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ulonglong_t The variable that will store the array of unsigned long longs read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedLongLongArray (unsigned long long int ** ulonglong_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of unsigned long longs with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ulonglong_t The variable that will store the array of unsigned long longs read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedLongLongArrayEndianness (unsigned long long int ** ulonglong_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of floats.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param float_t The variable that will store the array of floats read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeFloatArray (float ** float_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of floats with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param float_t The variable that will store the array of floats read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeFloatArrayEndianness (float ** float_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of doubles.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param float_t The variable that will store the array of doubles read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeDoubleArray (double ** double_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of doubles with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param float_t The variable that will store the array of doubles read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeDoubleArrayEndianness (double ** double_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function deserializes an array of long doubles.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param longdouble_t The variable that will store the array of long doubles read from the buffer.
  * @param numElements Number of the elements in the array.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeLongDoubleArray (long double ** longdouble_t, const unsigned int numElements);

  /*!
  * @brief This function deserializes an array of long doubles with a different endianness.
  * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param longdouble_t The variable that will store the array of long doubles read from the buffer.
  * @param numElements Number of the elements in the array.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeLongDoubleArrayEndianness (long double ** longdouble_t, const unsigned int numElements, Endianness endianness);


  /*!
  * @brief This function serializes a sequence of chars. The number of elements will be serialized in the buffer.
  * @param char_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeCharSequence (const char * char_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of chars. The number of elements will be serialized in the buffer with a different endianness.
  * @param char_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeCharSequenceEndianness (const char * char_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of unsigned chars. The number of elements will be serialized in the buffer.
  * @param char_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedCharSequence (const unsigned char * uchar_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of unsigned chars. The number of elements will be serialized in the buffer with a different endianness.
  * @param char_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedCharSequenceEndianness (const unsigned char * uchar_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of signed chars. The number of elements will be serialized in the buffer.
  * @param char_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeSignedCharSequence (const signed char * schar_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of signed chars. The number of elements will be serialized in the buffer with a different endianness.
  * @param char_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeSignedCharSequenceEndianness (const signed char * schar_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of strings. The number of elements will be serialized in the buffer.
  * @param string_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeStringSequence (const char ** string_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of strings. The number of elements will be serialized in the buffer with a different endianness.
  * @param string_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeStringSequenceEndianness (const char ** string_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of shorts. The number of elements will be serialized in the buffer.
  * @param short_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeShortSequence (const short * short_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of shorts with a different endianness. The number of elements will be serialized in the buffer.
  * @param short_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeShortSequenceEndianness (const short * short_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of unsigned shorts. The number of elements will be serialized in the buffer.
  * @param short_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedShortSequence (const unsigned short * ushort_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of unsigned shorts with a different endianness. The number of elements will be serialized in the buffer.
  * @param short_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedShortSequenceEndianness (const unsigned short * ushort_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of integers. The number of elements would not be serialized in the buffer.
  * @param int_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeIntSequence (const int * int_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of integers with a different endianness. The number of elements will be serialized in the buffer.
  * @param int_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeIntSequenceEndianness (const int * int_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of unsigned integers. The number of elements will be serialized in the buffer.
  * @param int_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedIntSequence (const unsigned int * uint_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of unsigned integers with a different endianness. The number of elements will be serialized in the buffer.
  * @param int_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedIntSequenceEndianness (const unsigned int * uint_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of longs. The number of elements will be serialized in the buffer.
  * @param long_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeLongSequence (const long * long_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of longs with a different endianness. The number of elements will be serialized in the buffer.
  * @param long_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeLongSequenceEndianness (const long * long_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of unsigned longs. The number of elements will be serialized in the buffer.
  * @param long_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedLongSequence (const unsigned long * ulong_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of unsigned longs with a different endianness. The number of elements will be serialized in the buffer.
  * @param long_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedLongSequenceEndianness (const unsigned long * ulong_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of long longs. The number of elements will be serialized in the buffer.
  * @param longlong_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeLongLongSequence (const long long int * longlong_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of long longs with a different endianness. The number of elements will be serialized in the buffer.
  * @param longlong_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeLongLongSequenceEndianness (const long long int * longlong_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of unsigned long longs. The number of elements will be serialized in the buffer.
  * @param longlong_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedLongLongSequence (const unsigned long long int * ulonglong_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of unsigned long longs with a different endianness. The number of elements will be serialized in the buffer.
  * @param longlong_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeUnsignedLongLongSequenceEndianness (const unsigned long long int * ulonglong_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of floats. The number of elements will be serialized in the buffer.
  * @param float_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeFloatSequence (const float * float_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of floats with a different endianness. The number of elements will be serialized in the buffer.
  * @param float_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeFloatSequenceEndianness (const float * float_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of doubles. The number of elements will be serialized in the buffer.
  * @param double_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeDoubleSequence (const double * double_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of doubles with a different endianness. The number of elements will be serialized in the buffer.
  * @param double_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeDoubleSequenceEndianness (const double * double_t, const unsigned int numElements, Endianness endianness);

  /*!
  * @brief This function serializes a sequence of long doubles. The number of elements will be serialized in the buffer.
  * @param longdouble_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeLongDoubleSequence (const long double * longdouble_t, const unsigned int numElements);

  /*!
  * @brief This function serializes a sequence of long doubles with a different endianness. The number of elements will be serialized in the buffer.
  * @param longdouble_t The sequence that will be serialized in the buffer.
  * @param numElements Number of elements in the sequence.
  * @param endianness Endianness that will be used in the serialization of this value.
  * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short serializeLongDoubleSequenceEndianness (const long double * longdouble_t, const unsigned int numElements, Endianness endianness);


  /*!
  * @brief This function deserializes a sequence of chars.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param char_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeCharSequence (char ** char_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of chars with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param char_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeCharSequenceEndianness (char ** char_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of unsigned chars.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param uchar_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedCharSequence (unsigned char ** uchar_t, unsigned int * numElements);


  /*!
  * @brief This function deserializes a sequence of unsigned chars with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param uchar_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedCharSequenceEndianness (unsigned char ** uchar_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of signed chars.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param schar_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeSignedCharSequence (signed char ** schar_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of signed chars with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param schar_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeSignedCharSequenceEndianness (signed char ** schar_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of strings.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param string_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeStringSequence (char *** string_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of strings with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param string_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeStringSequenceEndianness (char *** string_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of shorts.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param short_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeShortSequence (short ** short_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of shorts with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param short_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeShortSequenceEndianness (short ** short_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of unsigned shorts.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ushort_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedShortSequence (unsigned short ** ushort_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of unsigned shorts with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ushort_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedShortSequenceEndianness (unsigned short ** ushort_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of ints.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param int_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeIntSequence (int ** int_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of ints with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param int_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeIntSequenceEndianness (int ** int_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of unsigned ints.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param uint_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedIntSequence (unsigned int ** uint_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of unsigned ints with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param uint_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedIntSequenceEndianness (unsigned int ** uint_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of longs.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param long_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeLongSequence (long ** long_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of longs with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param long_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeLongSequenceEndianness (long ** long_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of unsigned longs.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ulong_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedLongSequence (unsigned long ** ulong_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of unsigned longs with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ulong_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedLongSequenceEndianness (unsigned long ** ulong_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of long longs.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param longlong_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeLongLongSequence (long long int ** longlong_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of long longs with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param longlong_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeLongLongSequenceEndianness (long long int ** longlong_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of unsigned long longs.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ulonglong_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedLongLongSequence (unsigned long long int ** ulonglong_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of unsigned long longs with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param ulonglong_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeUnsignedLongLongSequenceEndianness (unsigned long long int ** ulonglong_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of floats.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param float_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeFloatSequence (float ** float_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of floats with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param float_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeFloatSequenceEndianness (float ** float_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of doubles.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param double_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeDoubleSequence (double ** double_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of doubles with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param double_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeDoubleSequenceEndianness (double ** double_t, unsigned int * numElements, Endianness endianness);

  /*!
  * @brief This function deserializes a sequence of long doubles.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param longdouble_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeLongDoubleSequence (long double ** longdouble_t, unsigned int * numElements);

  /*!
  * @brief This function deserializes a sequence of long doubles with a different endianness.
  * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
  * The user will have to free this allocated memory using free() or freeCdr()
  * @param longdouble_t The pointer that will store the sequence read from the buffer.
  * @param numElements This variable return the number of elements of the sequence.
  * @param endianness Endianness that will be used in the deserialization of this value.
  * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
  */
  nanocdr_DllAPI short deserializeLongDoubleSequenceEndianness (long double ** longdouble_t, unsigned int * numElements, Endianness endianness);

#endif
