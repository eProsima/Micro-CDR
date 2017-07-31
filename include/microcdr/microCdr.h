#ifndef _MICROCDR_MICROCDR_H_
#define _MICROCDR_MICROCDR_H_

#include "microcdr_dll.h"
#include "microBuffer.h"
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define MICROCDR_INIT_BUF_LENGTH 200

typedef enum
{
    BIG_ENDIANNESS, LITTLE_ENDIANNESS
} Endianness;

#define NCDR_TRUE 0
#define NCDR_FALSE 1

typedef struct microCDR
{

    struct microBuffer * m_microBuffer;

    //! @brief The position in the buffer when the state was created.
    char * m_currentPosition;

    //! @brief This variable indicates the actual position in the stream.
    uint32_t m_iterator;

    //! @brief Pointer to the align position.
    char * m_alignPosition;

    //! @brief Endianness of the buffer
    Endianness m_endianness;

    //! @brief This variable indicates if the library must swap the words.
    uint8_t m_swapBytes;

    //! @brief Stores the last datasize serialized/deserialized when the state was created.
    uint32_t m_lastDataSize;

    //! @brief Coppy of internal buffer.
    char * m_buffer;

} microCDR;

/*!
 * @brief This function creates a microCDR with the passed microBuffer.
 * @param m_cdrBuffer Pointer to allocate the new microCDR.
 * @param microBuffer Buffer to create microCDR.
 */
microcdr_DllAPI void newMicroCDR(struct microCDR ** m_cdrBuffer, struct microBuffer * m_microBuffer);

/*!
 * @brief This function initialize already created microCDR with the passed microBuffer.
 * @param m_cdrBuffer Pointer to a microCDR object to be initialized.
 * @param microBuffer Buffer to create microCDR.
 */
microcdr_DllAPI void initMicroCDR(struct microCDR *m_microCDR, struct microBuffer *m_microBuffer);

/*!
 * @brief Resets a microCDR object for serialization purposes.
 * @param m_microCDR Pointer to an existing microCDR.
 */
microcdr_DllAPI void resetStaticMicroCDRForSerialize(struct microCDR *m_microCDR);

/*!
 * @brief Resets a microCDR object for deserialization purposes.
 * @param m_microCDR Pointer to an existing microCDR.
 */
microcdr_DllAPI void resetStaticMicroCDRForDeserialize(struct microCDR *m_microCDR);

/*!
 * @brief This function creates a static non aligned stream of bytes to deserialize.
 * @param buffer The user's buffer that will be used. This buffer must be deallocated by the user. Cannot be NULL.
 * @param bufferSize The length of user's buffer.
 * @param m_microBuffer Final microBuffer.
 */
microcdr_DllAPI void newDeserializedNonAlignedBuffer(char *buffer, uint32_t bufferSize,
        struct microBuffer **m_microBuffer);

/*!
 * @brief This function initialize a already created microBuffer as non aligned stream of bytes to deserialize.
 * @param buffer The user's buffer that will be used. This buffer must be deallocated by the user. Cannot be NULL.
 * @param bufferSize The length of user's buffer.
 * @param m_microBuffer Pointer to already allocated microBuffer.
 */
microcdr_DllAPI void initDeserializedNonAlignedBuffer(char *buffer, uint32_t bufferSize,
        struct microBuffer *m_microBuffer);

/*!
 * @brief This function creates a static aligned stream of bytes.
 * @param buffer The user's buffer that will be used. This buffer must be deallocated by the user. Cannot be NULL.
 * @param bufferSize The length of user's buffer.
 * @param m_microBuffer Final microBuffer.
 */
microcdr_DllAPI void newDeserializedAlignedBuffer(char * buffer, uint32_t bufferSize,
        struct microBuffer ** m_microBuffer);

/*!
 * @brief This function initialize a already created microBuffer as a static aligned stream of bytes.
 * @param buffer The user's buffer that will be used. This buffer must be deallocated by the user. Cannot be NULL.
 * @param bufferSize The length of user's buffer.
 * @param m_microBuffer Pointer to already allocated microBuffer.
 */
microcdr_DllAPI void initDeserializedAlignedBuffer(char *buffer, uint32_t bufferSize,
        struct microBuffer *m_microBuffer);

/*!
 * @brief This function creates a dynamic aligned stream of bytes.
 * @param m_microBuffer Final microBuffer.
 */
microcdr_DllAPI void newDynamicAlignedBuffer(struct microBuffer ** m_cdrBuffer);

/*!
 * @brief This function creates a static stream of bytes.
 * @param buffer The user's buffer that will be used. This buffer must be deallocated by the user. Cannot be NULL.
 * @param bufferSize The length of user's buffer.
 */
microcdr_DllAPI void newStaticAlignedBuffer(char * buffer, uint32_t bufferSize, struct microBuffer ** m_cdrBuffer);

/*!
 * @brief This function initialize a already created microBuffer as a static stream of bytes.
 * @param buffer The user's buffer that will be used. This buffer must be deallocated by the user. Cannot be NULL.
 * @param bufferSize The length of user's buffer.
 * @param m_microBuffer Pointer to already allocated microBuffer.
 */
microcdr_DllAPI void initStaticAlignedBuffer(char *buffer, uint32_t bufferSize, struct microBuffer *m_microBuffer);

/*!
 * @brief This function creates a dynamic aligned stream of bytes.
 * @param m_microBuffer Final microBuffer.
 */
microcdr_DllAPI void newDynamicNonAlignedBuffer(struct microBuffer ** m_cdrBuffer);

/*!
 * @brief This function creates a static stream of bytes.
 * @param buffer The user's buffer that will be used. This buffer must be deallocated by the user. Cannot be NULL.
 * @param bufferSize The length of user's buffer.
 */
microcdr_DllAPI void newStaticNonAlignedBuffer(char * buffer, uint32_t bufferSize, struct microBuffer ** m_cdrBuffer);

/*!
 * @brief This function initialize a already created microBuffer as a non aligned static stream of bytes.
 * @param buffer The user's buffer that will be used. This buffer must be deallocated by the user. Cannot be NULL.
 * @param bufferSize The length of user's buffer.
 * @param m_microBuffer Pointer to already allocated microBuffer.
 */
microcdr_DllAPI void initStaticNonAlignedBuffer(char * buffer, uint32_t bufferSize, struct microBuffer *m_microBuffer);

/*!
 * @brief This function destroies the microBuffer
 */
microcdr_DllAPI void destroyBuffer(struct microBuffer * m_cdrBuffer);

/*!
 * @brief This function allocates memory.
 * The memory is not initialized.
 * The user will have to free this allocated memory using free() or freeCdr().
 * @param point_t The pointer where the memery will be allocated.
 * @param size Number of bytes that the user wants to allocate.
 */
microcdr_DllAPI void mallocCdr(void ** point_t, uint32_t size);

/*!
 * @brief This function frees the memory pointer by ponint_t.
 * @param point_t Pointer to the allocated memory.
 */
microcdr_DllAPI void freeCdr(void ** point_t);

microcdr_DllAPI void resetAlignment(struct microCDR * m_cdrBuffer);

/*!
 * @brief This function returns the extra bytes regarding the allignment.
 * @param dataSize The size of the data that will be serialized.
 * @return The size needed for the aligment.
 */
microcdr_DllAPI uint32_t alignment(uint32_t dataSize, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function jumps the number of bytes of the alignment. These bytes should be calculated with the function alignment.
 * @param align The number of bytes to be skipped.
 */
microcdr_DllAPI void makeAlign(uint32_t align, struct microCDR * m_cdrBuffer);

//char * getBufferPointer ();

/*!
 * @brief This function returns the length of the serialized data inside the stream.
 * @return The length of the serialized data.
 */
microcdr_DllAPI uint32_t getSerializedDataLength(struct microCDR * m_cdrBuffer);

/*!
 * @brief TODO
 */
microcdr_DllAPI char * getBufferPointer(struct microCDR * m_cdrBuffer);

/*!
 * @brief This function resets the current position in the buffer to the begining.
 */
microcdr_DllAPI void reset(struct microCDR * m_cdrBuffer);

/*!
 * @brief This function skips a number of bytes in the CDR stream buffer.
 * @param numBytes The number of bytes that will be jumped.
 * @return 0 is returned when the jump operation works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t jump(uint16_t bytes, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function returns the current position in the CDR stream.
 * @return Pointer to the current position in the buffer.
 */
microcdr_DllAPI char * getCurrentPosition(struct microCDR * m_cdrBuffer);

/*!
 * @brief This function change the endianness of the buffer.
 * @param endianness The new endianness for the buffer.
 */
microcdr_DllAPI void changeEndianness(Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief
 * @param
 */
microcdr_DllAPI void updateCurrentPosition(struct microCDR * m_cdrBuffer);

/*!
 * @brief This function resizes the internal buffer. It only applies if the cdrBuffer was created with the dynamic mode.
 * @param minSizeInc Minimun size increase for the internal buffer
 * @return 0 if the resize was succesful, -1 if it was not
 */
microcdr_DllAPI int8_t resize(uint32_t minSizeInc, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a character.
 * @param char_t The value of the character that will be serialized in the buffer.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeChar(const char char_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a signed character.
 * @param schar_t The value of the signed character that will be serialized in the buffer.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeSignedChar(const signed char schar_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an unsigned character.
 * @param uchar_t The value of the unsigned character that will be serialized in the buffer.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedChar(const unsigned char uchar_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a bool.
 * @param bool_t The value of the bool that will be serialized in the buffer.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeBool(const bool bool_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a string.
 * @param string_t The pointer to the string that will be serialized in the buffer.
 * @param length_t Length of the string that will be serialized in the buffer.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeString(const char * string_t, const uint32_t length_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a string with a different endianness.
 * @param string_t The pointer to the string that will be serialized in the buffer.
 * @param length_t Length of the string that will be serialized in the buffer.
 * @param endianness Endianness that will be used in the serialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeStringEndianness(const char * string_t, const uint32_t length_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a character.
 * @param char_t The variable that will store the character read from the buffer.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeChar(char * char_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a signed character.
 * @param schar_t The variable that will store the signed character read from the buffer.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeSignedChar(signed char * schar_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an unsigned character.
 * @param uchar_t The variable that will store the unsigned character read from the buffer.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedChar(unsigned char * uchar_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a bool.
 * @param bool_t The variable that will store the bool read from the buffer.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeBool(bool * bool_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a string.
 * @param string_t The variable that will store the string read from the buffer.
 * @param strlen_t The variable that will store the length of the string.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeString(char ** string_t, uint32_t * strlen_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a string with a different endianness.
 * @param string_t The variable that will store the string read from the buffer.
 * @param strlen_t The variable that will store the length of the string.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeStringEndianness(char ** string_t, uint32_t * strlen_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a short.
 * @param short_t The value of the short that will be serialized in the buffer.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeShort(const int16_t short_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a short with a different endianness.
 * @param short_t The value of the short that will be serialized in the buffer.
 * @param endianness Endianness that will be used in the serrialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeShortEndianness(const int16_t short_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an unsigned short.
 * @param short_t The value of the unsigned short that will be serialized in the buffer.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedShort(const uint16_t ushort_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an unsigned short with a different endianness.
 * @param short_t The value of the unsigned short that will be serialized in the buffer.
 * @param endianness Endianness that will be used in the serrialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedShortEndianness(const uint16_t ushort_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an int.
 * @param int_t The value of the integer that will be serialized in the buffer.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeInt(const int32_t int_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an int wiht a different endianness.
 * @param int_t The value of the integer that will be serialized in the buffer.
 * @param endianness Endianness that will be used in the serrialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeIntEndianness(const int32_t int_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an unsigne dint.
 * @param uint_t The value of the unsigned int that will be serialized in the buffer.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedInt(const uint32_t uint_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an unsigned int with a different endianness.
 * @param uint_t The value of the unsigned int that will be serialized in the buffer.
 * @param endianness Endianness that will be used in the serrialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedIntEndianness(const uint32_t uint_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a long.
 * @param long_t The value of the long that will be serialized in the buffer.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeLong(const int64_t long_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a long with a different endianness.
 * @param long_t The value of the long that will be serialized in the buffer.
 * @param endianness Endianness that will be used in the serrialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeLongEndianness(const int64_t long_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an unsigned long.
 * @param ulong_t The value of the unsigned long that will be serialized in the buffer.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedLong(const uint64_t ulong_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an unsigned long with a different endianness.
 * @param ulong_t The value of the unsigned long that will be serialized in the buffer.
 * @param endianness Endianness that will be used in the serrialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedLongEndianness(const uint64_t ulong_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a long long .
 * @param longlong_t The value of the long long that will be serialized in the buffer.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeLongLong(const long long int longlong_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a long long with a different endianness.
 * @param longlong_t The value of the long long that will be serialized in the buffer.
 * @param endianness Endianness that will be used in the serrialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeLongLongEndianness(const long long int longlong_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an unsigned long long.
 * @param ulonglong_t The value of the unsigned long long that will be serialized in the buffer.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedLongLong(const unsigned long long int ulonglong_t,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an unsigned long long with a different endianness.
 * @param ulonglong_t The value of the unsigned long long that will be serialized in the buffer.
 * @param endianness Endianness that will be used in the serrialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedLongLongEndianness(const unsigned long long int ulonglong_t,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a float.
 * @param float_t The value of the float that will be serialized in the buffer.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeFloat(const float float_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a float with a different endianness.
 * @param float_t The value of the float that will be serialized in the buffer.
 * @param endianness Endianness that will be used in the serrialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeFloatEndianness(const float float_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a double.
 * @param double_t The value of the short that will be serialized in the buffer.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeDouble(const double double_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a double with a different endianness.
 * @param double_t The value of the short that will be serialized in the buffer.
 * @param endianness Endianness that will be used in the serrialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeDoubleEndianness(const double double_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a long double.
 * @param longdouble_t The value of the short that will be serialized in the buffer.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeLongDouble(const long double longdouble_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a long double with a different endianness.
 * @param longdouble_t The value of the short that will be serialized in the buffer.
 * @param endianness Endianness that will be used in the serialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeLongDoubleEndianness(const long double longdouble_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a short.
 * @param short_t The variable that will store the short read from the buffer.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeShort(int16_t * short_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a short with a different endianness.
 * @param short_t The variable that will store the short read from the buffer.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeShortEndianness(int16_t * short_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an unsigned short.
 * @param ushort_t The variable that will store the unsigned short read from the buffer.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedShort(uint16_t * ushort_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an unsigned short with a different endianness.
 * @param ushort_t The variable that will store the unsigned short read from the buffer.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedShortEndianness(uint16_t * ushort_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a int.
 * @param int_t The variable that will store the int read from the buffer.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeInt(int32_t * int_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a int with a different endianness.
 * @param int_t The variable that will store the int read from the buffer.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeIntEndianness(int32_t * int_t, Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an unsigned int.
 * @param uint_t The variable that will store the unsigned read from the buffer.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedInt(uint32_t * uint_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an unsigned int with a different endianness.
 * @param uint_t The variable that will store the unsigned read from the buffer.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedIntEndianness(uint32_t * uint_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a long.
 * @param long_t The variable that will store the long read from the buffer.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeLong(int64_t * long_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a long with a different endianness.
 * @param long_t The variable that will store the long read from the buffer.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeLongEndianness(int64_t * long_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an unsigned long.
 * @param long_t The variable that will store the unsigned long read from the buffer.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedLong(uint64_t * ulong_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an unsigned long with a different endianness.
 * @param long_t The variable that will store the unsigned long read from the buffer.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedLongEndianness(uint64_t * ulong_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a long long.
 * @param longlong_t The variable that will store the long long read from the buffer.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeLongLong(long long int * longlong_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a long long with a different endianness.
 * @param longlong_t The variable that will store the long long read from the buffer.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeLongLongEndianness(long long int * longlong_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an unsigned long long.
 * @param ulonglong_t The variable that will store the unsigned long long read from the buffer.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedLongLong(unsigned long long int * ulonglong_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an unsigned long long with a different endianness.
 * @param ulonglong_t The variable that will store the unsigned long long read from the buffer.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedLongLongEndianness(unsigned long long int * ulonglong_t,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a float.
 * @param float_t The variable that will store the float read from the buffer.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeFloat(float * float_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a float with a different endianness.
 * @param float_t The variable that will store the float read from the buffer.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeFloatEndianness(float * float_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a double.
 * @param double_t The variable that will store the double read from the buffer.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeDouble(double * double_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a double with a different endianness.
 * @param double_t The variable that will store the double read from the buffer.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeDoubleEndianness(double * double_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a long double.
 * @param longdouble_t The variable that will store the long double read from the buffer.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeLongDouble(long double * double_t, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a long double with a different endianness.
 * @param longdouble_t The variable that will store the long double read from the buffer.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialized works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeLongDoubleEndianness(long double * double_t, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of charts.
 * @param chart_t The array of charts that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeCharArray(const char * char_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of unsigned charts.
 * @param uchart_t The array of charts that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedCharArray(const unsigned char * uchar_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of signed charts.
 * @param schart_t The array of charts that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeSignedCharArray(const signed char * schar_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of bools.
 * @param bool_t The array of bools that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeBoolArray(const bool * bool_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of strings.
 * @param string_t The array of strings that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeStringArray(const char ** string_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of strings with a different endianness.
 * @param string_t The array of strings that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the serialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeStringArrayEndianness(const char ** string_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of shorts.
 * @param short_t The array of shorts that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeShortArray(const int16_t * short_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of shorts with a different endianness.
 * @param short_t The array of shorts that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the serialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeShortArrayEndianness(const int16_t * short_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of unsigned shorts.
 * @param ushort_t The array of unsigned shorts that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedShortArray(const uint16_t * ushort_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of unsigned shorts with a different endianness.
 * @param ushort_t The array of unsigned shorts that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the serialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedShortArrayEndianness(const uint16_t * ushort_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of ints.
 * @param int_t The array of ints that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeIntArray(const int32_t * int_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of ints with a different endianness.
 * @param int_t The array of ints that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the serialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeIntArrayEndianness(const int32_t * int_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of unsigned ints.
 * @param uint_t The array of unsigned ints that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedIntArray(const uint32_t * uint_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of unsigned ints with a different endianness.
 * @param uint_t The array of unsigned ints that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the serialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedIntArrayEndianness(const uint32_t * uint_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of longs.
 * @param long_t The array of longs that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeLongArray(const int64_t * long_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of longs with a different endianness.
 * @param long_t The array of longs that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the serialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeLongArrayEndianness(const int64_t * long_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of unsigned longs.
 * @param ulong_t The array of unsigned longs that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedLongArray(const uint64_t * ulong_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of unsigned longs with a different endianness.
 * @param ulong_t The array of unsigned longs that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the serialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedLongArrayEndianness(const uint64_t * ulong_t, const uint32_t numElements,
        Endianness endiannes, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of long longs.
 * @param longlong_t The array of long longs that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeLongLongArray(const long long int * longlong_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of long longs with a different endianness.
 * @param longlong_t The array of long longs that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the serialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeLongLongArrayEndianness(const long long int * longlong_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of unsigned long longs.
 * @param ulonglong_t The array of unsigned long longs that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedLongLongArray(const unsigned long long int * ulonglong_t,
        const uint32_t numElements, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of unsigned long longs with a different endianness.
 * @param ulonglong_t The array of unsigned long longs that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the serialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedLongLongArrayEndianness(const unsigned long long int * ulonglong_t,
        const uint32_t numElements, Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of floats.
 * @param float_t The array of floats that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeFloatArray(const float * float_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of floats with a different endianness.
 * @param float_t The array of floats that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the serialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeFloatArrayEndianness(const float * float_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of doubles.
 * @param double_t The array of doubles that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeDoubleArray(const double * double_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of doubles with a different endianness.
 * @param double_t The array of doubles that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the serialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeDoubleArrayEndianness(const double * double_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of long doubles.
 * @param longdouble_t The array of doubles that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeLongDoubleArray(const long double * longdouble_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes an array of long doubles with a different endianness.
 * @param longdouble_t The array of doubles that will be serialized in the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the serialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeLongDoubleArrayEndianness(const long double * longdouble_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of chars.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param char_t The variable that will store the array of chars read from the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeCharArray(char ** char_t, const uint32_t numElements, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of unsigned chars.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param uchar_t The variable that will store the array of chars read from the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedCharArray(unsigned char ** uchar_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of signed chars.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param schar_t The variable that will store the array of signed chars read from the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeSignedCharArray(signed char ** schar_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of bools.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param bool_t The variable that will store the array of bools read from the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeBoolArray(bool ** bool_t, const uint32_t numElements, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of strings.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param string_t The variable that will store the array of strings read from the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeStringArray(char *** string_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of strings with a different endianness.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param string_t The variable that will store the array of strings read from the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeStringArrayEndianness(char *** string_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of shorts.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param short_t The variable that will store the array of shorts read from the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeShortArray(int16_t ** short_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of shorts with a different endianness.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param short_t The variable that will store the array of shorts read from the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeShortArrayEndianness(int16_t ** short_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of unsigned shorts.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param ushort_t The variable that will store the array of unsigned shorts read from the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedShortArray(uint16_t ** ushort_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of unsigned shorts with a different endianness.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param ushort_t The variable that will store the array of unsigned shorts read from the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedShortArrayEndianness(uint16_t ** ushort_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of ints.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param int_t The variable that will store the array of ints read from the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeIntArray(int32_t ** int_t, const uint32_t numElements, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of ints with a different endianness.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param int_t The variable that will store the array of ints read from the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeIntArrayEndianness(int32_t ** int_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of unsigned ints.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param uint_t The variable that will store the array of unsigned ints read from the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedIntArray(uint32_t ** int_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of unsigned ints with a different endianness.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param uint_t The variable that will store the array of unsigned ints read from the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedIntArrayEndianness(uint32_t ** int_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of longs.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param long_t The variable that will store the array of longs read from the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeLongArray(int64_t ** long_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of longs with a different endianness.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param long_t The variable that will store the array of longs read from the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeLongArrayEndianness(int64_t ** long_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of unsigned longs.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param ulong_t The variable that will store the array of unsigned longs read from the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedLongArray(uint64_t ** ulong_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of unsigned longs with a different endianness.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param ulong_t The variable that will store the array of unsigned longs read from the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedLongArrayEndianness(uint64_t ** ulong_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of long longs.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param longlong_t The variable that will store the array of long longs read from the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeLongLongArray(long long int ** longlong_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of long longs with a different endianness.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param longlong_t The variable that will store the array of long longs read from the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeLongLongArrayEndianness(long long int ** longlong_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of unsigned long longs.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param ulonglong_t The variable that will store the array of unsigned long longs read from the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedLongLongArray(unsigned long long int ** ulonglong_t,
        const uint32_t numElements, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of unsigned long longs with a different endianness.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param ulonglong_t The variable that will store the array of unsigned long longs read from the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedLongLongArrayEndianness(unsigned long long int ** ulonglong_t,
        const uint32_t numElements, Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of floats.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param float_t The variable that will store the array of floats read from the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeFloatArray(float ** float_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of floats with a different endianness.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param float_t The variable that will store the array of floats read from the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeFloatArrayEndianness(float ** float_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of doubles.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param float_t The variable that will store the array of doubles read from the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeDoubleArray(double ** double_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of doubles with a different endianness.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param float_t The variable that will store the array of doubles read from the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeDoubleArrayEndianness(double ** double_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of long doubles.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param longdouble_t The variable that will store the array of long doubles read from the buffer.
 * @param numElements Number of the elements in the array.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeLongDoubleArray(long double ** longdouble_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes an array of long doubles with a different endianness.
 * This function allocates memory to store the array. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param longdouble_t The variable that will store the array of long doubles read from the buffer.
 * @param numElements Number of the elements in the array.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeLongDoubleArrayEndianness(long double ** longdouble_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of chars. The number of elements will be serialized in the buffer.
 * @param char_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeCharSequence(const char * char_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of chars. The number of elements will be serialized in the buffer with a different endianness.
 * @param char_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @param endianness Endianness that will be used in the serialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeCharSequenceEndianness(const char * char_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of unsigned chars. The number of elements will be serialized in the buffer.
 * @param char_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedCharSequence(const unsigned char * uchar_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of unsigned chars. The number of elements will be serialized in the buffer with a different endianness.
 * @param char_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedCharSequenceEndianness(const unsigned char * uchar_t,
        const uint32_t numElements, Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of signed chars. The number of elements will be serialized in the buffer.
 * @param char_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeSignedCharSequence(const signed char * schar_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of signed chars. The number of elements will be serialized in the buffer with a different endianness.
 * @param char_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeSignedCharSequenceEndianness(const signed char * schar_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of strings. The number of elements will be serialized in the buffer.
 * @param string_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeStringSequence(const char ** string_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of strings. The number of elements will be serialized in the buffer with a different endianness.
 * @param string_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeStringSequenceEndianness(const char ** string_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of shorts. The number of elements will be serialized in the buffer.
 * @param short_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeShortSequence(const int16_t * short_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of shorts with a different endianness. The number of elements will be serialized in the buffer.
 * @param short_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeShortSequenceEndianness(const int16_t * short_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of unsigned shorts. The number of elements will be serialized in the buffer.
 * @param short_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedShortSequence(const uint16_t * ushort_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of unsigned shorts with a different endianness. The number of elements will be serialized in the buffer.
 * @param short_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedShortSequenceEndianness(const uint16_t * ushort_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of integers. The number of elements would not be serialized in the buffer.
 * @param int_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeIntSequence(const int32_t * int_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of integers with a different endianness. The number of elements will be serialized in the buffer.
 * @param int_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeIntSequenceEndianness(const int32_t * int_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of unsigned integers. The number of elements will be serialized in the buffer.
 * @param int_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedIntSequence(const uint32_t * uint_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of unsigned integers with a different endianness. The number of elements will be serialized in the buffer.
 * @param int_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedIntSequenceEndianness(const uint32_t * uint_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of longs. The number of elements will be serialized in the buffer.
 * @param long_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeLongSequence(const int64_t * long_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of longs with a different endianness. The number of elements will be serialized in the buffer.
 * @param long_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeLongSequenceEndianness(const int64_t * long_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of unsigned longs. The number of elements will be serialized in the buffer.
 * @param long_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedLongSequence(const uint64_t * ulong_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of unsigned longs with a different endianness. The number of elements will be serialized in the buffer.
 * @param long_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedLongSequenceEndianness(const uint64_t * ulong_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of long longs. The number of elements will be serialized in the buffer.
 * @param longlong_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeLongLongSequence(const long long int * longlong_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of long longs with a different endianness. The number of elements will be serialized in the buffer.
 * @param longlong_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeLongLongSequenceEndianness(const long long int * longlong_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of unsigned long longs. The number of elements will be serialized in the buffer.
 * @param longlong_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedLongLongSequence(const unsigned long long int * ulonglong_t,
        const uint32_t numElements, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of unsigned long longs with a different endianness. The number of elements will be serialized in the buffer.
 * @param longlong_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @param endianness Endianness that will be used in the serialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeUnsignedLongLongSequenceEndianness(const unsigned long long int * ulonglong_t,
        const uint32_t numElements, Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of floats. The number of elements will be serialized in the buffer.
 * @param float_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeFloatSequence(const float * float_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of floats with a different endianness. The number of elements will be serialized in the buffer.
 * @param float_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @param endianness Endianness that will be used in the serialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeFloatSequenceEndianness(const float * float_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of doubles. The number of elements will be serialized in the buffer.
 * @param double_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeDoubleSequence(const double * double_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of doubles with a different endianness. The number of elements will be serialized in the buffer.
 * @param double_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @param endianness Endianness that will be used in the serialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeDoubleSequenceEndianness(const double * double_t, const uint32_t numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of long doubles. The number of elements will be serialized in the buffer.
 * @param longdouble_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeLongDoubleSequence(const long double * longdouble_t, const uint32_t numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function serializes a sequence of long doubles with a different endianness. The number of elements will be serialized in the buffer.
 * @param longdouble_t The sequence that will be serialized in the buffer.
 * @param numElements Number of elements in the sequence.
 * @param endianness Endianness that will be used in the serialization of this value.
 * @return 0 is returned when the serialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t serializeLongDoubleSequenceEndianness(const long double * longdouble_t,
        const uint32_t numElements, Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of chars.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param char_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeCharSequence(char ** char_t, uint32_t * numElements, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of chars with a different endianness.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param char_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeCharSequenceEndianness(char ** char_t, uint32_t * numElements, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of unsigned chars.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param uchar_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedCharSequence(unsigned char ** uchar_t, uint32_t * numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of unsigned chars with a different endianness.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param uchar_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedCharSequenceEndianness(unsigned char ** uchar_t, uint32_t * numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of signed chars.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param schar_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeSignedCharSequence(signed char ** schar_t, uint32_t * numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of signed chars with a different endianness.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param schar_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeSignedCharSequenceEndianness(signed char ** schar_t, uint32_t * numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of strings.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param string_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeStringSequence(char *** string_t, uint32_t * numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of strings with a different endianness.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param string_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeStringSequenceEndianness(char *** string_t, uint32_t * numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of shorts.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param short_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeShortSequence(int16_t ** short_t, uint32_t * numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of shorts with a different endianness.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param short_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeShortSequenceEndianness(int16_t ** short_t, uint32_t * numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of unsigned shorts.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param ushort_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedShortSequence(uint16_t ** ushort_t, uint32_t * numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of unsigned shorts with a different endianness.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param ushort_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedShortSequenceEndianness(uint16_t ** ushort_t, uint32_t * numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of ints.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param int_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeIntSequence(int32_t ** int_t, uint32_t * numElements, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of ints with a different endianness.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param int_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeIntSequenceEndianness(int32_t ** int_t, uint32_t * numElements, Endianness endianness,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of unsigned ints.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param uint_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedIntSequence(uint32_t ** uint_t, uint32_t * numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of unsigned ints with a different endianness.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param uint_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedIntSequenceEndianness(uint32_t ** uint_t, uint32_t * numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of longs.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param long_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeLongSequence(int64_t ** long_t, uint32_t * numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of longs with a different endianness.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param long_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeLongSequenceEndianness(int64_t ** long_t, uint32_t * numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of unsigned longs.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param ulong_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedLongSequence(uint64_t ** ulong_t, uint32_t * numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of unsigned longs with a different endianness.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param ulong_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedLongSequenceEndianness(uint64_t ** ulong_t, uint32_t * numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of long longs.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param longlong_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeLongLongSequence(long long int ** longlong_t, uint32_t * numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of long longs with a different endianness.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param longlong_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeLongLongSequenceEndianness(long long int ** longlong_t, uint32_t * numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of unsigned long longs.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param ulonglong_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedLongLongSequence(unsigned long long int ** ulonglong_t,
        uint32_t * numElements, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of unsigned long longs with a different endianness.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param ulonglong_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeUnsignedLongLongSequenceEndianness(unsigned long long int ** ulonglong_t,
        uint32_t * numElements, Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of floats.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param float_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeFloatSequence(float ** float_t, uint32_t * numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of floats with a different endianness.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param float_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeFloatSequenceEndianness(float ** float_t, uint32_t * numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of doubles.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param double_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeDoubleSequence(double ** double_t, uint32_t * numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of doubles with a different endianness.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param double_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeDoubleSequenceEndianness(double ** double_t, uint32_t * numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of long doubles.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param longdouble_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeLongDoubleSequence(long double ** longdouble_t, uint32_t * numElements,
        struct microCDR * m_cdrBuffer);

/*!
 * @brief This function deserializes a sequence of long doubles with a different endianness.
 * This function allocates memory to store the sequence. The user pointer will be set to point this allocated memory.
 * The user will have to free this allocated memory using free() or freeCdr()
 * @param longdouble_t The pointer that will store the sequence read from the buffer.
 * @param numElements This variable return the number of elements of the sequence.
 * @param endianness Endianness that will be used in the deserialization of this value.
 * @return 0 is returned when the deserialezed works successfully. Otherwise, -1 is returned.
 */
microcdr_DllAPI int8_t deserializeLongDoubleSequenceEndianness(long double ** longdouble_t, uint32_t * numElements,
        Endianness endianness, struct microCDR * m_cdrBuffer);

#ifdef __cplusplus
}
#endif

#endif
