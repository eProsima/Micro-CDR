#ifndef _MICROCDR_MICRO_CDR_H_
#define _MICROCDR_MICRO_CDR_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define microcdr_DllAPI

#include <stdint.h>
#include <stdbool.h>

// -------------------------------------------------------------------
//                         MICRO CDR STRUCTURES
// -------------------------------------------------------------------

typedef enum Endianness
{
    BIG_ENDIANNESS, LITTLE_ENDIANNESS

} Endianness;

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

microcdr_DllAPI inline uint32_t get_alignment_offset(MicroBuffer* buffer, uint32_t data_size);
microcdr_DllAPI inline bool check_size(MicroBuffer* buffer, uint32_t bytes);

// -------------------------------------------------------------------
//                        SERIALIZATION FUNCTIONS
// -------------------------------------------------------------------

// Basics
microcdr_DllAPI void serialize_char         (MicroBuffer* buffer, char     value);
microcdr_DllAPI void serialize_bool         (MicroBuffer* buffer, bool     value);
microcdr_DllAPI void serialize_uint8        (MicroBuffer* buffer, uint8_t  value);
microcdr_DllAPI void serialize_uint16       (MicroBuffer* buffer, uint16_t value);
microcdr_DllAPI void serialize_uint32       (MicroBuffer* buffer, uint32_t value);
microcdr_DllAPI void serialize_uint64       (MicroBuffer* buffer, uint64_t value);
microcdr_DllAPI void serialize_int16        (MicroBuffer* buffer, int16_t  value);
microcdr_DllAPI void serialize_int32        (MicroBuffer* buffer, int32_t  value);
microcdr_DllAPI void serialize_int64        (MicroBuffer* buffer, int64_t  value);
microcdr_DllAPI void serialize_float        (MicroBuffer* buffer, float    value);
microcdr_DllAPI void serialize_double       (MicroBuffer* buffer, double   value);

microcdr_DllAPI void deserialize_char       (MicroBuffer* buffer, char*     value);
microcdr_DllAPI void deserialize_bool       (MicroBuffer* buffer, bool*     value);
microcdr_DllAPI void deserialize_uint8      (MicroBuffer* buffer, uint8_t*  value);
microcdr_DllAPI void deserialize_uint16     (MicroBuffer* buffer, uint16_t* value);
microcdr_DllAPI void deserialize_uint32     (MicroBuffer* buffer, uint32_t* value);
microcdr_DllAPI void deserialize_uint64     (MicroBuffer* buffer, uint64_t* value);
microcdr_DllAPI void deserialize_int16      (MicroBuffer* buffer, int16_t*  value);
microcdr_DllAPI void deserialize_int32      (MicroBuffer* buffer, int32_t*  value);
microcdr_DllAPI void deserialize_int64      (MicroBuffer* buffer, int64_t*  value);
microcdr_DllAPI void deserialize_float      (MicroBuffer* buffer, float*    value);
microcdr_DllAPI void deserialize_double     (MicroBuffer* buffer, double*   value);

// Arrays
microcdr_DllAPI void serialize_array_char      (MicroBuffer* buffer, char*     array, uint32_t size);
microcdr_DllAPI void serialize_array_bool      (MicroBuffer* buffer, bool*     array, uint32_t size);
microcdr_DllAPI void serialize_array_uint8     (MicroBuffer* buffer, uint8_t*  array, uint32_t size);
microcdr_DllAPI void serialize_array_uint16    (MicroBuffer* buffer, uint16_t* array, uint32_t size);
microcdr_DllAPI void serialize_array_uint32    (MicroBuffer* buffer, uint32_t* array, uint32_t size);
microcdr_DllAPI void serialize_array_uint64    (MicroBuffer* buffer, uint64_t* array, uint32_t size);
microcdr_DllAPI void serialize_array_int16     (MicroBuffer* buffer, int16_t*  array, uint32_t size);
microcdr_DllAPI void serialize_array_int32     (MicroBuffer* buffer, int32_t*  array, uint32_t size);
microcdr_DllAPI void serialize_array_int64     (MicroBuffer* buffer, int64_t*  array, uint32_t size);
microcdr_DllAPI void serialize_array_float     (MicroBuffer* buffer, float*    array, uint32_t size);
microcdr_DllAPI void serialize_array_double    (MicroBuffer* buffer, double*   array, uint32_t size);

microcdr_DllAPI void deserialize_array_char    (MicroBuffer* buffer, char*     array, uint32_t size);
microcdr_DllAPI void deserialize_array_bool    (MicroBuffer* buffer, bool*     array, uint32_t size);
microcdr_DllAPI void deserialize_array_uint8   (MicroBuffer* buffer, uint8_t*  array, uint32_t size);
microcdr_DllAPI void deserialize_array_uint16  (MicroBuffer* buffer, uint16_t* array, uint32_t size);
microcdr_DllAPI void deserialize_array_uint32  (MicroBuffer* buffer, uint32_t* array, uint32_t size);
microcdr_DllAPI void deserialize_array_uint64  (MicroBuffer* buffer, uint64_t* array, uint32_t size);
microcdr_DllAPI void deserialize_array_int16   (MicroBuffer* buffer, int16_t*  array, uint32_t size);
microcdr_DllAPI void deserialize_array_int32   (MicroBuffer* buffer, int32_t*  array, uint32_t size);
microcdr_DllAPI void deserialize_array_int64   (MicroBuffer* buffer, int64_t*  array, uint32_t size);
microcdr_DllAPI void deserialize_array_float   (MicroBuffer* buffer, float*    array, uint32_t size);
microcdr_DllAPI void deserialize_array_double  (MicroBuffer* buffer, double*   array, uint32_t size);

// Sequence
microcdr_DllAPI void serialize_sequence_char     (MicroBuffer* buffer, char*     sequence, uint32_t size);
microcdr_DllAPI void serialize_sequence_bool     (MicroBuffer* buffer, bool*     sequence, uint32_t size);
microcdr_DllAPI void serialize_sequence_uint8    (MicroBuffer* buffer, uint8_t*  sequence, uint32_t size);
microcdr_DllAPI void serialize_sequence_uint16   (MicroBuffer* buffer, uint16_t* sequence, uint32_t size);
microcdr_DllAPI void serialize_sequence_uint32   (MicroBuffer* buffer, uint32_t* sequence, uint32_t size);
microcdr_DllAPI void serialize_sequence_uint64   (MicroBuffer* buffer, uint64_t* sequence, uint32_t size);
microcdr_DllAPI void serialize_sequence_int16    (MicroBuffer* buffer, int16_t* sequence, uint32_t size);
microcdr_DllAPI void serialize_sequence_int32    (MicroBuffer* buffer, int32_t* sequence, uint32_t size);
microcdr_DllAPI void serialize_sequence_int64    (MicroBuffer* buffer, int64_t* sequence, uint32_t size);
microcdr_DllAPI void serialize_sequence_float    (MicroBuffer* buffer, float*    sequence, uint32_t size);
microcdr_DllAPI void serialize_sequence_double   (MicroBuffer* buffer, double*   sequence, uint32_t size);

microcdr_DllAPI void deserialize_sequence_char   (MicroBuffer* buffer, char*     sequence, uint32_t* size);
microcdr_DllAPI void deserialize_sequence_bool   (MicroBuffer* buffer, bool*     sequence, uint32_t* size);
microcdr_DllAPI void deserialize_sequence_uint8  (MicroBuffer* buffer, uint8_t*  sequence, uint32_t* size);
microcdr_DllAPI void deserialize_sequence_uint16 (MicroBuffer* buffer, uint16_t* sequence, uint32_t* size);
microcdr_DllAPI void deserialize_sequence_uint32 (MicroBuffer* buffer, uint32_t* sequence, uint32_t* size);
microcdr_DllAPI void deserialize_sequence_uint64 (MicroBuffer* buffer, uint64_t* sequence, uint32_t* size);
microcdr_DllAPI void deserialize_sequence_int16  (MicroBuffer* buffer, int16_t* sequence, uint32_t* size);
microcdr_DllAPI void deserialize_sequence_int32  (MicroBuffer* buffer, int32_t* sequence, uint32_t* size);
microcdr_DllAPI void deserialize_sequence_int64  (MicroBuffer* buffer, int64_t* sequence, uint32_t* size);
microcdr_DllAPI void deserialize_sequence_float  (MicroBuffer* buffer, float*    sequence, uint32_t* size);
microcdr_DllAPI void deserialize_sequence_double (MicroBuffer* buffer, double*   sequence, uint32_t* size);


// -------------------------------------------------------------------
//                  SERIALIZATION FUNCTIONS - ENDIAN
// -------------------------------------------------------------------

// Basics
microcdr_DllAPI void serialize_endian_uint16  (MicroBuffer* buffer, Endianness endianness, uint16_t   value);
microcdr_DllAPI void serialize_endian_uint32  (MicroBuffer* buffer, Endianness endianness, uint32_t   value);
microcdr_DllAPI void serialize_endian_uint64  (MicroBuffer* buffer, Endianness endianness, uint64_t   value);
microcdr_DllAPI void serialize_endian_int16   (MicroBuffer* buffer, Endianness endianness, int16_t   value);
microcdr_DllAPI void serialize_endian_int32   (MicroBuffer* buffer, Endianness endianness, int32_t   value);
microcdr_DllAPI void serialize_endian_int64   (MicroBuffer* buffer, Endianness endianness, int64_t   value);
microcdr_DllAPI void serialize_endian_float   (MicroBuffer* buffer, Endianness endianness, float      value);
microcdr_DllAPI void serialize_endian_double  (MicroBuffer* buffer, Endianness endianness, double     value);

microcdr_DllAPI void deserialize_endian_uint16  (MicroBuffer* buffer, Endianness endianness, uint16_t* value);
microcdr_DllAPI void deserialize_endian_uint32  (MicroBuffer* buffer, Endianness endianness, uint32_t* value);
microcdr_DllAPI void deserialize_endian_uint64  (MicroBuffer* buffer, Endianness endianness, uint64_t* value);
microcdr_DllAPI void deserialize_endian_int16   (MicroBuffer* buffer, Endianness endianness, int16_t*  value);
microcdr_DllAPI void deserialize_endian_int32   (MicroBuffer* buffer, Endianness endianness, int32_t*  value);
microcdr_DllAPI void deserialize_endian_int64   (MicroBuffer* buffer, Endianness endianness, int64_t*  value);
microcdr_DllAPI void deserialize_endian_float   (MicroBuffer* buffer, Endianness endianness, float*    value);
microcdr_DllAPI void deserialize_endian_double  (MicroBuffer* buffer, Endianness endianness, double*   value);

// Array
microcdr_DllAPI void serialize_array_endian_uint16 (MicroBuffer* buffer, Endianness endianness, uint16_t* array, uint32_t size);
microcdr_DllAPI void serialize_array_endian_uint32 (MicroBuffer* buffer, Endianness endianness, uint32_t* array, uint32_t size);
microcdr_DllAPI void serialize_array_endian_uint64 (MicroBuffer* buffer, Endianness endianness, uint64_t* array, uint32_t size);
microcdr_DllAPI void serialize_array_endian_int16  (MicroBuffer* buffer, Endianness endianness, int16_t*  array, uint32_t size);
microcdr_DllAPI void serialize_array_endian_int32  (MicroBuffer* buffer, Endianness endianness, int32_t*  array, uint32_t size);
microcdr_DllAPI void serialize_array_endian_int64  (MicroBuffer* buffer, Endianness endianness, int64_t*  array, uint32_t size);
microcdr_DllAPI void serialize_array_endian_float  (MicroBuffer* buffer, Endianness endianness, float*    array, uint32_t size);
microcdr_DllAPI void serialize_array_endian_double (MicroBuffer* buffer, Endianness endianness, double*   array, uint32_t size);

microcdr_DllAPI void deserialize_array_endian_uint16 (MicroBuffer* buffer, Endianness endianness, uint16_t* array, uint32_t size);
microcdr_DllAPI void deserialize_array_endian_uint32 (MicroBuffer* buffer, Endianness endianness, uint32_t* array, uint32_t size);
microcdr_DllAPI void deserialize_array_endian_uint64 (MicroBuffer* buffer, Endianness endianness, uint64_t* array, uint32_t size);
microcdr_DllAPI void deserialize_array_endian_int16  (MicroBuffer* buffer, Endianness endianness, int16_t* array, uint32_t size);
microcdr_DllAPI void deserialize_array_endian_int32  (MicroBuffer* buffer, Endianness endianness, int32_t* array, uint32_t size);
microcdr_DllAPI void deserialize_array_endian_int64  (MicroBuffer* buffer, Endianness endianness, int64_t* array, uint32_t size);
microcdr_DllAPI void deserialize_array_endian_float  (MicroBuffer* buffer, Endianness endianness, float*    array, uint32_t size);
microcdr_DllAPI void deserialize_array_endian_double (MicroBuffer* buffer, Endianness endianness, double*   array, uint32_t size);

// Sequence
microcdr_DllAPI void serialize_sequence_endian_uint16 (MicroBuffer* buffer, Endianness endianness, uint16_t* sequence, uint32_t size);
microcdr_DllAPI void serialize_sequence_endian_uint32 (MicroBuffer* buffer, Endianness endianness, uint32_t* sequence, uint32_t size);
microcdr_DllAPI void serialize_sequence_endian_uint64 (MicroBuffer* buffer, Endianness endianness, uint64_t* sequence, uint32_t size);
microcdr_DllAPI void serialize_sequence_endian_int16  (MicroBuffer* buffer, Endianness endianness, int16_t*  sequence, uint32_t size);
microcdr_DllAPI void serialize_sequence_endian_int32  (MicroBuffer* buffer, Endianness endianness, int32_t*  sequence, uint32_t size);
microcdr_DllAPI void serialize_sequence_endian_int64  (MicroBuffer* buffer, Endianness endianness, int64_t*  sequence, uint32_t size);
microcdr_DllAPI void serialize_sequence_endian_float  (MicroBuffer* buffer, Endianness endianness, float*    sequence, uint32_t size);
microcdr_DllAPI void serialize_sequence_endian_double (MicroBuffer* buffer, Endianness endianness, double*   sequence, uint32_t size);

microcdr_DllAPI void deserialize_sequence_endian_uint16 (MicroBuffer* buffer, Endianness endianness, uint16_t* sequence, uint32_t* size);
microcdr_DllAPI void deserialize_sequence_endian_uint32 (MicroBuffer* buffer, Endianness endianness, uint32_t* sequence, uint32_t* size);
microcdr_DllAPI void deserialize_sequence_endian_uint64 (MicroBuffer* buffer, Endianness endianness, uint64_t* sequence, uint32_t* size);
microcdr_DllAPI void deserialize_sequence_endian_int16  (MicroBuffer* buffer, Endianness endianness, int16_t*  sequence, uint32_t* size);
microcdr_DllAPI void deserialize_sequence_endian_int32  (MicroBuffer* buffer, Endianness endianness, int32_t*  sequence, uint32_t* size);
microcdr_DllAPI void deserialize_sequence_endian_int64  (MicroBuffer* buffer, Endianness endianness, int64_t*  sequence, uint32_t* size);
microcdr_DllAPI void deserialize_sequence_endian_float  (MicroBuffer* buffer, Endianness endianness, float*    sequence, uint32_t* size);
microcdr_DllAPI void deserialize_sequence_endian_double (MicroBuffer* buffer, Endianness endianness, double*   sequence, uint32_t* size);

#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_MICRO_CDR_H_