// Copyright 2017 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#ifndef _MICROCDR_MICRO_CDR_H_
#define _MICROCDR_MICRO_CDR_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "microcdr_dll.h"

#include <stdint.h>
#include <stdbool.h>

// -------------------------------------------------------------------
//                         MICRO CDR STRUCTURES
// -------------------------------------------------------------------

typedef enum Endianness
{
    BIG_ENDIANNESS,
    LITTLE_ENDIANNESS,
} Endianness;

extern const Endianness MACHINE_ENDIANNESS;

typedef struct MicroState
{
    uint8_t* position;
    uint32_t last_data_size;

} MicroState;

typedef struct MicroBuffer
{
    uint8_t* init;
    uint8_t* final;
    uint8_t* iterator;

    Endianness endianness;
    uint32_t last_data_size;

    bool internal_buffer_management;

} MicroBuffer;


// -------------------------------------------------------------------
//                         MICRO BUFFER FUNCTIONS
// -------------------------------------------------------------------

microcdr_DllAPI void init_external_buffer(MicroBuffer* buffer, uint8_t* data, uint32_t size);
microcdr_DllAPI void init_internal_buffer(MicroBuffer* buffer, uint32_t initial_size);
microcdr_DllAPI void free_internal_buffer(MicroBuffer* buffer);
microcdr_DllAPI void reset_buffer(MicroBuffer* buffer);

microcdr_DllAPI MicroState get_micro_state(MicroBuffer* buffer);
microcdr_DllAPI void restore_micro_state(MicroBuffer* buffer, MicroState state);
microcdr_DllAPI void align_to(MicroBuffer* buffer, uint32_t size);

// -------------------------------------------------------------------
//                        SERIALIZATION FUNCTIONS
// -------------------------------------------------------------------

// Basics
microcdr_DllAPI void serialize_char         (MicroBuffer* buffer, char     value);
microcdr_DllAPI void serialize_bool         (MicroBuffer* buffer, bool     value);
microcdr_DllAPI void serialize_uint8_t        (MicroBuffer* buffer, uint8_t  value);
microcdr_DllAPI void serialize_uint16_t       (MicroBuffer* buffer, uint16_t value);
microcdr_DllAPI void serialize_uint32_t       (MicroBuffer* buffer, uint32_t value);
microcdr_DllAPI void serialize_uint64_t       (MicroBuffer* buffer, uint64_t value);
microcdr_DllAPI void serialize_int16_t        (MicroBuffer* buffer, int16_t  value);
microcdr_DllAPI void serialize_int32_t        (MicroBuffer* buffer, int32_t  value);
microcdr_DllAPI void serialize_int64_t        (MicroBuffer* buffer, int64_t  value);
microcdr_DllAPI void serialize_float        (MicroBuffer* buffer, float    value);
microcdr_DllAPI void serialize_double       (MicroBuffer* buffer, double   value);

microcdr_DllAPI void deserialize_char       (MicroBuffer* buffer, char*     value);
microcdr_DllAPI void deserialize_bool       (MicroBuffer* buffer, bool*     value);
microcdr_DllAPI void deserialize_uint8_t      (MicroBuffer* buffer, uint8_t*  value);
microcdr_DllAPI void deserialize_uint16_t     (MicroBuffer* buffer, uint16_t* value);
microcdr_DllAPI void deserialize_uint32_t     (MicroBuffer* buffer, uint32_t* value);
microcdr_DllAPI void deserialize_uint64_t     (MicroBuffer* buffer, uint64_t* value);
microcdr_DllAPI void deserialize_int16_t      (MicroBuffer* buffer, int16_t*  value);
microcdr_DllAPI void deserialize_int32_t      (MicroBuffer* buffer, int32_t*  value);
microcdr_DllAPI void deserialize_int64_t      (MicroBuffer* buffer, int64_t*  value);
microcdr_DllAPI void deserialize_float      (MicroBuffer* buffer, float*    value);
microcdr_DllAPI void deserialize_double     (MicroBuffer* buffer, double*   value);

// Arrays
microcdr_DllAPI void serialize_array_char      (MicroBuffer* buffer, const char*     array, uint32_t size);
microcdr_DllAPI void serialize_array_bool      (MicroBuffer* buffer, const bool*     array, uint32_t size);
microcdr_DllAPI void serialize_array_uint8_t     (MicroBuffer* buffer, const uint8_t*  array, uint32_t size);
microcdr_DllAPI void serialize_array_uint16_t    (MicroBuffer* buffer, const uint16_t* array, uint32_t size);
microcdr_DllAPI void serialize_array_uint32_t    (MicroBuffer* buffer, const uint32_t* array, uint32_t size);
microcdr_DllAPI void serialize_array_uint64_t    (MicroBuffer* buffer, const uint64_t* array, uint32_t size);
microcdr_DllAPI void serialize_array_int16_t     (MicroBuffer* buffer, const int16_t*  array, uint32_t size);
microcdr_DllAPI void serialize_array_int32_t     (MicroBuffer* buffer, const int32_t*  array, uint32_t size);
microcdr_DllAPI void serialize_array_int64_t     (MicroBuffer* buffer, const int64_t*  array, uint32_t size);
microcdr_DllAPI void serialize_array_float     (MicroBuffer* buffer, const float*    array, uint32_t size);
microcdr_DllAPI void serialize_array_double    (MicroBuffer* buffer, const double*   array, uint32_t size);

microcdr_DllAPI void deserialize_array_char    (MicroBuffer* buffer, char*     array, uint32_t size);
microcdr_DllAPI void deserialize_array_bool    (MicroBuffer* buffer, bool*     array, uint32_t size);
microcdr_DllAPI void deserialize_array_uint8_t   (MicroBuffer* buffer, uint8_t*  array, uint32_t size);
microcdr_DllAPI void deserialize_array_uint16_t  (MicroBuffer* buffer, uint16_t* array, uint32_t size);
microcdr_DllAPI void deserialize_array_uint32_t  (MicroBuffer* buffer, uint32_t* array, uint32_t size);
microcdr_DllAPI void deserialize_array_uint64_t  (MicroBuffer* buffer, uint64_t* array, uint32_t size);
microcdr_DllAPI void deserialize_array_int16_t   (MicroBuffer* buffer, int16_t*  array, uint32_t size);
microcdr_DllAPI void deserialize_array_int32_t   (MicroBuffer* buffer, int32_t*  array, uint32_t size);
microcdr_DllAPI void deserialize_array_int64_t   (MicroBuffer* buffer, int64_t*  array, uint32_t size);
microcdr_DllAPI void deserialize_array_float   (MicroBuffer* buffer, float*    array, uint32_t size);
microcdr_DllAPI void deserialize_array_double  (MicroBuffer* buffer, double*   array, uint32_t size);

// -------------------------------------------------------------------
//                  SERIALIZATION FUNCTIONS - ENDIAN
// -------------------------------------------------------------------

// Basics
microcdr_DllAPI void serialize_endian_uint16_t  (MicroBuffer* buffer, Endianness endianness, uint16_t   value);
microcdr_DllAPI void serialize_endian_uint32_t  (MicroBuffer* buffer, Endianness endianness, uint32_t   value);
microcdr_DllAPI void serialize_endian_uint64_t  (MicroBuffer* buffer, Endianness endianness, uint64_t   value);
microcdr_DllAPI void serialize_endian_int16_t   (MicroBuffer* buffer, Endianness endianness, int16_t   value);
microcdr_DllAPI void serialize_endian_int32_t   (MicroBuffer* buffer, Endianness endianness, int32_t   value);
microcdr_DllAPI void serialize_endian_int64_t   (MicroBuffer* buffer, Endianness endianness, int64_t   value);
microcdr_DllAPI void serialize_endian_float   (MicroBuffer* buffer, Endianness endianness, float      value);
microcdr_DllAPI void serialize_endian_double  (MicroBuffer* buffer, Endianness endianness, double     value);

microcdr_DllAPI void deserialize_endian_uint16_t  (MicroBuffer* buffer, Endianness endianness, uint16_t* value);
microcdr_DllAPI void deserialize_endian_uint32_t  (MicroBuffer* buffer, Endianness endianness, uint32_t* value);
microcdr_DllAPI void deserialize_endian_uint64_t  (MicroBuffer* buffer, Endianness endianness, uint64_t* value);
microcdr_DllAPI void deserialize_endian_int16_t   (MicroBuffer* buffer, Endianness endianness, int16_t*  value);
microcdr_DllAPI void deserialize_endian_int32_t   (MicroBuffer* buffer, Endianness endianness, int32_t*  value);
microcdr_DllAPI void deserialize_endian_int64_t   (MicroBuffer* buffer, Endianness endianness, int64_t*  value);
microcdr_DllAPI void deserialize_endian_float   (MicroBuffer* buffer, Endianness endianness, float*    value);
microcdr_DllAPI void deserialize_endian_double  (MicroBuffer* buffer, Endianness endianness, double*   value);

// Array
microcdr_DllAPI void serialize_endian_array_uint16_t (MicroBuffer* buffer, Endianness endianness, const uint16_t* array, uint32_t size);
microcdr_DllAPI void serialize_endian_array_uint32_t (MicroBuffer* buffer, Endianness endianness, const uint32_t* array, uint32_t size);
microcdr_DllAPI void serialize_endian_array_uint64_t (MicroBuffer* buffer, Endianness endianness, const uint64_t* array, uint32_t size);
microcdr_DllAPI void serialize_endian_array_int16_t  (MicroBuffer* buffer, Endianness endianness, const int16_t*  array, uint32_t size);
microcdr_DllAPI void serialize_endian_array_int32_t  (MicroBuffer* buffer, Endianness endianness, const int32_t*  array, uint32_t size);
microcdr_DllAPI void serialize_endian_array_int64_t  (MicroBuffer* buffer, Endianness endianness, const int64_t*  array, uint32_t size);
microcdr_DllAPI void serialize_endian_array_float  (MicroBuffer* buffer, Endianness endianness, const float*    array, uint32_t size);
microcdr_DllAPI void serialize_endian_array_double (MicroBuffer* buffer, Endianness endianness, const double*   array, uint32_t size);

microcdr_DllAPI void deserialize_endian_array_uint16_t (MicroBuffer* buffer, Endianness endianness, uint16_t* array, uint32_t size);
microcdr_DllAPI void deserialize_endian_array_uint32_t (MicroBuffer* buffer, Endianness endianness, uint32_t* array, uint32_t size);
microcdr_DllAPI void deserialize_endian_array_uint64_t (MicroBuffer* buffer, Endianness endianness, uint64_t* array, uint32_t size);
microcdr_DllAPI void deserialize_endian_array_int16_t  (MicroBuffer* buffer, Endianness endianness, int16_t* array, uint32_t size);
microcdr_DllAPI void deserialize_endian_array_int32_t  (MicroBuffer* buffer, Endianness endianness, int32_t* array, uint32_t size);
microcdr_DllAPI void deserialize_endian_array_int64_t  (MicroBuffer* buffer, Endianness endianness, int64_t* array, uint32_t size);
microcdr_DllAPI void deserialize_endian_array_float  (MicroBuffer* buffer, Endianness endianness, float*    array, uint32_t size);
microcdr_DllAPI void deserialize_endian_array_double (MicroBuffer* buffer, Endianness endianness, double*   array, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_MICRO_CDR_H_