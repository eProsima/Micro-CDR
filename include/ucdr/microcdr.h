// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef MICROCDR_MICRO_CDR_H_
#define MICROCDR_MICRO_CDR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ucdr/visibility.h>
#include <ucdr/config.h>

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define UCDR_BIG_ENDIANNESS     0
#define UCDR_LITTLE_ENDIANNESS  1

// ------------------------------------------------
//                      Types
// ------------------------------------------------

typedef bool ucdrEndianness;

/**
 * @brief
 */
typedef struct ucdrBufferInfo
{
    size_t origin;
    size_t size;
    uint8_t* data;

    void* next;
    void* prev;

} ucdrBufferInfo;

/**
 * @brief
 */
typedef struct ucdrStream
{
    size_t offset;
    uint8_t* iterator;
    size_t size;

    ucdrEndianness endianness;

    bool error;

    ucdrBufferInfo buffer_info;

} ucdrStream;

// ------------------------------------------------
//                 Main functions
// ------------------------------------------------

/**
 * @brief Initializes a ucdrStream from a buffer.
 * @param us        A pointer to the ucdrStream to be initialized.
 * @param buffer    The buffer which will be associated with the ucdrStream.
 * @param size      The size of the buffer.
 */
UCDRDLLAPI void ucdr_init_stream(
        ucdrStream* us,
        uint8_t* buffer,
        size_t size);

/**
 * @brief Initializes a ucdrStream from a buffer with a offset.
 * @param us        A pointer to the ucdrStream to initialize.
 * @param buffer    The buffer which will be associated with the ucdrStream.
 * @param size      The size of the buffer.
 * @param offset    The initial offset of the ucdrStream.
 */
UCDRDLLAPI void ucdr_init_stream_offset(
        ucdrStream* us,
        uint8_t* data,
        size_t size,
        size_t offset);

/**
 * @brief Initializes a ucdrStream from a buffer with a offset and an endianness.
 * @param us            A pointer to the ucdrStream to initialize.
 * @param buffer        A pointer to the buffer which will be associated with the ucdrStream.
 * @param size          The size of the buffer.
 * @param offset        The initial offset of the ucdrStream.
 * @param endianness    The endianness of the ucdrStream.
 */
UCDRDLLAPI void ucdr_init_stream_offset_endian(
        ucdrStream* us,
        uint8_t* data,
        size_t size,
        size_t offset,
        ucdrEndianness endianness);

/**
 * @brief Copies the de/serialized data of a ucdrStream into a new one.
 * @param us_dest   A pointer to the ucdrStream to copy to.
 * @param us_source A pointer to the ucdrStream to copy from.
 */
UCDRDLLAPI void ucdr_copy_stream(
        ucdrStream* us_dest,
        const ucdrStream* us_source);

/**
 * @brief Links a buffer to the ucdrStream. Multiple buffer can be linked forming a doubly linked list of buffers.
 * @param us        A pointer to the ucdrStream to which the buffer will be linked.
 * @param buffer    A pointer to the buffer to be linked.
 * @param size      The size of the buffer.
 * @return  true in case of successful buffer linking, and false in other case.
 */
UCDRDLLAPI bool ucdr_link_buffer(
        ucdrStream* us,
        uint8_t* data,
        size_t size);

/**
 * @brief Resets a ucdrStream.
 * @param ub    A pointer to the ucdrStream to reset.
 */
UCDRDLLAPI void ucdr_reset_stream(
        ucdrStream* us);

/**
 * @brief Advances the XCDR stream to achieve a desired alignment.
 * @param us        A pointer to the ucdrStream to align.
 * @param type_size Size of the type to be aligned.
 */
UCDRDLLAPI void ucdr_align(
        ucdrStream* us,
        size_t type_size);

/**
 * @brief Computes the total size of the ucdrStream, that is, the sum of the linked buffers' effective size.
 * @param us    A pointer to the ucdrStream.
 * @return      The total size of the ucdrStream.
 */
UCDRDLLAPI size_t ucdr_size(
        const ucdrStream* us);

/**
 * @brief Computes the remaining size of the ucdrStream.
 * @param us    A pointer to the ucdrStream.
 * @return      The total size of the ucdrStream.
 */
UCDRDLLAPI size_t ucdr_remaining_size(
        const ucdrStream* us);

/**
 * @brief Computes the used size of the ucdrStream.
 * @param us    A pointer to the ucdrStream.
 * @return      The used size of the ucdrStream.
 */
UCDRDLLAPI size_t ucdr_used_size(
        const ucdrStream* us);

/**
 * @brief Returns the endianness of the ucdrStream.
 * @param ub    A pointer to the ucdrStream.
 * @return      The endianness of the ucdrStream.
 */
UCDRDLLAPI ucdrEndianness ucdr_endianness(
        const ucdrStream* ub);

/**
 * @brief Indicates whether the ucdrStream has an error.
 * @param us    A pointer to the ucdrStream.
 * @return      The error state of the ucdrStream.
 */
UCDRDLLAPI bool ucdr_has_error(
        const ucdrStream* us);

// -------------------------------------------------------------------
//              PUBLIC DE-SERIALIZATION DECLARATIONS
// -------------------------------------------------------------------

#define UCDR_BASIC_TYPE_DECLARATIONS(SUFFIX, TYPE) \
    UCDRDLLAPI bool ucdr_serialize ## SUFFIX(ucdrStream* us, TYPE value); \
    UCDRDLLAPI bool ucdr_serialize_endian ## SUFFIX(ucdrStream* us, ucdrEndianness endianness, TYPE value); \
    UCDRDLLAPI bool ucdr_deserialize ## SUFFIX(ucdrStream* us, TYPE* value); \
    UCDRDLLAPI bool ucdr_deserialize_endian ## SUFFIX(ucdrStream* us, ucdrEndianness endianness, TYPE* value); \

#define UCDR_ARRAY_DECLARATIONS(SUFFIX, TYPE) \
    UCDRDLLAPI bool ucdr_serialize_array ## SUFFIX(ucdrStream* us, const TYPE* array, size_t size); \
    UCDRDLLAPI bool ucdr_serialize_endian_array ## SUFFIX(ucdrStream* us, ucdrEndianness endianness, const TYPE* array, size_t size); \
    UCDRDLLAPI bool ucdr_deserialize_array ## SUFFIX(ucdrStream* us, TYPE* array, size_t size); \
    UCDRDLLAPI bool ucdr_deserialize_endian_array ## SUFFIX(ucdrStream* us, ucdrEndianness endianness, TYPE* array, size_t size); \

#define UCDR_SEQUENCE_DECLARATIONS(SUFFIX, TYPE) \
    UCDRDLLAPI bool ucdr_serialize_sequence ## SUFFIX(ucdrStream* us, const TYPE* array, uint32_t length); \
    UCDRDLLAPI bool ucdr_serialize_endian_sequence ## SUFFIX(ucdrStream* us, ucdrEndianness endianness, const TYPE* array, uint32_t length); \
    UCDRDLLAPI bool ucdr_deserialize_sequence ## SUFFIX(ucdrStream* us, TYPE* array, size_t array_capacity, uint32_t* length); \
    UCDRDLLAPI bool ucdr_deserialize_endian_sequence ## SUFFIX(ucdrStream* us, ucdrEndianness endianness, TYPE* array, size_t array_capacity, uint32_t* length); \

UCDRDLLAPI bool ucdr_serialize_string(ucdrStream* us, const char* string);
UCDRDLLAPI bool ucdr_serialize_endian_string(ucdrStream* us, ucdrEndianness endianness, const char* string);
UCDRDLLAPI bool ucdr_deserialize_string(ucdrStream* us, char* string, size_t string_capacity);
UCDRDLLAPI bool ucdr_deserialize_endian_string(ucdrStream* us, ucdrEndianness endianness, char* string, size_t string_capacity);

// -------------------------------------------------------------------
//               VALID TYPES DECLARATIONS
// -------------------------------------------------------------------

UCDR_BASIC_TYPE_DECLARATIONS(_char, char)
UCDR_BASIC_TYPE_DECLARATIONS(_bool, bool)
UCDR_BASIC_TYPE_DECLARATIONS(_uint8_t, uint8_t)
UCDR_BASIC_TYPE_DECLARATIONS(_uint16_t, uint16_t)
UCDR_BASIC_TYPE_DECLARATIONS(_uint32_t, uint32_t)
UCDR_BASIC_TYPE_DECLARATIONS(_uint64_t, uint64_t)
UCDR_BASIC_TYPE_DECLARATIONS(_int8_t, int8_t)
UCDR_BASIC_TYPE_DECLARATIONS(_int16_t, int16_t)
UCDR_BASIC_TYPE_DECLARATIONS(_int32_t, int32_t)
UCDR_BASIC_TYPE_DECLARATIONS(_int64_t, int64_t)
UCDR_BASIC_TYPE_DECLARATIONS(_float, float)
UCDR_BASIC_TYPE_DECLARATIONS(_double, double)

UCDR_ARRAY_DECLARATIONS(_char, char)
UCDR_ARRAY_DECLARATIONS(_bool, bool)
UCDR_ARRAY_DECLARATIONS(_uint8_t, uint8_t)
UCDR_ARRAY_DECLARATIONS(_uint16_t, uint16_t)
UCDR_ARRAY_DECLARATIONS(_uint32_t, uint32_t)
UCDR_ARRAY_DECLARATIONS(_uint64_t, uint64_t)
UCDR_ARRAY_DECLARATIONS(_int8_t, int8_t)
UCDR_ARRAY_DECLARATIONS(_int16_t, int16_t)
UCDR_ARRAY_DECLARATIONS(_int32_t, int32_t)
UCDR_ARRAY_DECLARATIONS(_int64_t, int64_t)
UCDR_ARRAY_DECLARATIONS(_float, float)
UCDR_ARRAY_DECLARATIONS(_double, double)

UCDR_SEQUENCE_DECLARATIONS(_char, char)
UCDR_SEQUENCE_DECLARATIONS(_bool, bool)
UCDR_SEQUENCE_DECLARATIONS(_uint8_t, uint8_t)
UCDR_SEQUENCE_DECLARATIONS(_uint16_t, uint16_t)
UCDR_SEQUENCE_DECLARATIONS(_uint32_t, uint32_t)
UCDR_SEQUENCE_DECLARATIONS(_uint64_t, uint64_t)
UCDR_SEQUENCE_DECLARATIONS(_int8_t, int8_t)
UCDR_SEQUENCE_DECLARATIONS(_int16_t, int16_t)
UCDR_SEQUENCE_DECLARATIONS(_int32_t, int32_t)
UCDR_SEQUENCE_DECLARATIONS(_int64_t, int64_t)
UCDR_SEQUENCE_DECLARATIONS(_float, float)
UCDR_SEQUENCE_DECLARATIONS(_double, double)

#ifdef __cplusplus
}
#endif

#endif // MICROCDR_MICRO_CDR_H_
