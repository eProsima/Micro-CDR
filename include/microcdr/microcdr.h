#ifndef _MICROCDR_MICRO_CDR_H_
#define _MICROCDR_MICRO_CDR_H_

#define LITTLE_ENDIAN_MACHINE 1

#ifdef __cplusplus
extern "C"
{
#endif

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
    uint8_t* buffer;
    uint8_t* final;
    uint8_t* iterator;

    uint32_t last_data_size;

} MicroBuffer;


// -------------------------------------------------------------------
//                         MICRO BUFFER FUNCTIONS
// -------------------------------------------------------------------

void init_micro_buffer(MicroBuffer* micro_buffer, uint8_t* buffer, uint32_t size);
void reset_micro_buffer(MicroBuffer* micro_buffer);

void make_alignment(MicroBuffer* micro_buffer, uint32_t aligment);


// -------------------------------------------------------------------
//                        SERIALIZATION FUNCTIONS
// -------------------------------------------------------------------

// Basics
int serialize_char         (MicroBuffer* micro_buffer, char     value);
int serialize_bool         (MicroBuffer* micro_buffer, bool     value);
int serialize_uint8        (MicroBuffer* micro_buffer, uint8_t  value);
int serialize_uint16       (MicroBuffer* micro_buffer, uint16_t value);
int serialize_uint32       (MicroBuffer* micro_buffer, uint32_t value);
int serialize_uint64       (MicroBuffer* micro_buffer, uint64_t value);
int serialize_int16        (MicroBuffer* micro_buffer, int16_t  value);
int serialize_int32        (MicroBuffer* micro_buffer, int32_t  value);
int serialize_int64        (MicroBuffer* micro_buffer, int64_t  value);
int serialize_float        (MicroBuffer* micro_buffer, float    value);
int serialize_double       (MicroBuffer* micro_buffer, double   value);

int deserialize_char       (MicroBuffer* micro_buffer, char*     value);
int deserialize_bool       (MicroBuffer* micro_buffer, bool*     value);
int deserialize_uint8      (MicroBuffer* micro_buffer, uint8_t*  value);
int deserialize_uint16     (MicroBuffer* micro_buffer, uint16_t* value);
int deserialize_uint32     (MicroBuffer* micro_buffer, uint32_t* value);
int deserialize_uint64     (MicroBuffer* micro_buffer, uint64_t* value);
int deserialize_int16      (MicroBuffer* micro_buffer, int16_t*  value);
int deserialize_int32      (MicroBuffer* micro_buffer, int32_t*  value);
int deserialize_int64      (MicroBuffer* micro_buffer, int64_t*  value);
int deserialize_float      (MicroBuffer* micro_buffer, float*    value);
int deserialize_double     (MicroBuffer* micro_buffer, double*   value);

// Arrays
int serialize_array_char      (MicroBuffer* micro_buffer, char*     array, uint32_t size);
int serialize_array_bool      (MicroBuffer* micro_buffer, bool*     array, uint32_t size);
int serialize_array_uint8     (MicroBuffer* micro_buffer, uint8_t*  array, uint32_t size);
int serialize_array_uint16    (MicroBuffer* micro_buffer, uint16_t* array, uint32_t size);
int serialize_array_uint32    (MicroBuffer* micro_buffer, uint32_t* array, uint32_t size);
int serialize_array_uint64    (MicroBuffer* micro_buffer, uint64_t* array, uint32_t size);
int serialize_array_int16     (MicroBuffer* micro_buffer, int16_t*  array, uint32_t size);
int serialize_array_int32     (MicroBuffer* micro_buffer, int32_t*  array, uint32_t size);
int serialize_array_int64     (MicroBuffer* micro_buffer, int64_t*  array, uint32_t size);
int serialize_array_float     (MicroBuffer* micro_buffer, float*    array, uint32_t size);
int serialize_array_double    (MicroBuffer* micro_buffer, double*   array, uint32_t size);

int deserialize_array_char    (MicroBuffer* micro_buffer, char*     array, uint32_t size);
int deserialize_array_bool    (MicroBuffer* micro_buffer, bool*     array, uint32_t size);
int deserialize_array_uint8   (MicroBuffer* micro_buffer, uint8_t*  array, uint32_t size);
int deserialize_array_uint16  (MicroBuffer* micro_buffer, uint16_t* array, uint32_t size);
int deserialize_array_uint32  (MicroBuffer* micro_buffer, uint32_t* array, uint32_t size);
int deserialize_array_uint64  (MicroBuffer* micro_buffer, uint64_t* array, uint32_t size);
int deserialize_array_int16   (MicroBuffer* micro_buffer, int16_t*  array, uint32_t size);
int deserialize_array_int32   (MicroBuffer* micro_buffer, int32_t*  array, uint32_t size);
int deserialize_array_int64   (MicroBuffer* micro_buffer, int64_t*  array, uint32_t size);
int deserialize_array_float   (MicroBuffer* micro_buffer, float*    array, uint32_t size);
int deserialize_array_double  (MicroBuffer* micro_buffer, double*   array, uint32_t size);

// Sequence
int serialize_sequence_char     (MicroBuffer* micro_buffer, char*     sequence, uint32_t size);
int serialize_sequence_bool     (MicroBuffer* micro_buffer, bool*     sequence, uint32_t size);
int serialize_sequence_uint8    (MicroBuffer* micro_buffer, uint8_t*  sequence, uint32_t size);
int serialize_sequence_uint16   (MicroBuffer* micro_buffer, uint16_t* sequence, uint32_t size);
int serialize_sequence_uint32   (MicroBuffer* micro_buffer, uint32_t* sequence, uint32_t size);
int serialize_sequence_uint64   (MicroBuffer* micro_buffer, uint64_t* sequence, uint32_t size);
int serialize_sequence_int16    (MicroBuffer* micro_buffer, int16_t* sequence, uint32_t size);
int serialize_sequence_int32    (MicroBuffer* micro_buffer, int32_t* sequence, uint32_t size);
int serialize_sequence_int64    (MicroBuffer* micro_buffer, int64_t* sequence, uint32_t size);
int serialize_sequence_float    (MicroBuffer* micro_buffer, float*    sequence, uint32_t size);
int serialize_sequence_double   (MicroBuffer* micro_buffer, double*   sequence, uint32_t size);

int deserialize_sequence_char   (MicroBuffer* micro_buffer, char*     sequence, uint32_t* size);
int deserialize_sequence_bool   (MicroBuffer* micro_buffer, bool*     sequence, uint32_t* size);
int deserialize_sequence_uint8  (MicroBuffer* micro_buffer, uint8_t*  sequence, uint32_t* size);
int deserialize_sequence_uint16 (MicroBuffer* micro_buffer, uint16_t* sequence, uint32_t* size);
int deserialize_sequence_uint32 (MicroBuffer* micro_buffer, uint32_t* sequence, uint32_t* size);
int deserialize_sequence_uint64 (MicroBuffer* micro_buffer, uint64_t* sequence, uint32_t* size);
int deserialize_sequence_int16  (MicroBuffer* micro_buffer, int16_t* sequence, uint32_t* size);
int deserialize_sequence_int32  (MicroBuffer* micro_buffer, int32_t* sequence, uint32_t* size);
int deserialize_sequence_int64  (MicroBuffer* micro_buffer, int64_t* sequence, uint32_t* size);
int deserialize_sequence_float  (MicroBuffer* micro_buffer, float*    sequence, uint32_t* size);
int deserialize_sequence_double (MicroBuffer* micro_buffer, double*   sequence, uint32_t* size);


// -------------------------------------------------------------------
//                  SERIALIZATION FUNCTIONS - ENDIAN
// -------------------------------------------------------------------

// Basics
int serialize_endian_uint16  (MicroBuffer* micro_buffer, Endianness endianness, uint16_t   value);
int serialize_endian_uint32  (MicroBuffer* micro_buffer, Endianness endianness, uint32_t   value);
int serialize_endian_uint64  (MicroBuffer* micro_buffer, Endianness endianness, uint64_t   value);
int serialize_endian_int16   (MicroBuffer* micro_buffer, Endianness endianness, int16_t   value);
int serialize_endian_int32   (MicroBuffer* micro_buffer, Endianness endianness, int32_t   value);
int serialize_endian_int64   (MicroBuffer* micro_buffer, Endianness endianness, int64_t   value);
int serialize_endian_float   (MicroBuffer* micro_buffer, Endianness endianness, float      value);
int serialize_endian_double  (MicroBuffer* micro_buffer, Endianness endianness, double     value);

int deserialize_endian_uint16  (MicroBuffer* micro_buffer, Endianness endianness, uint16_t* value);
int deserialize_endian_uint32  (MicroBuffer* micro_buffer, Endianness endianness, uint32_t* value);
int deserialize_endian_uint64  (MicroBuffer* micro_buffer, Endianness endianness, uint64_t* value);
int deserialize_endian_int16   (MicroBuffer* micro_buffer, Endianness endianness, int16_t*  value);
int deserialize_endian_int32   (MicroBuffer* micro_buffer, Endianness endianness, int32_t*  value);
int deserialize_endian_int64   (MicroBuffer* micro_buffer, Endianness endianness, int64_t*  value);
int deserialize_endian_float   (MicroBuffer* micro_buffer, Endianness endianness, float*    value);
int deserialize_endian_double  (MicroBuffer* micro_buffer, Endianness endianness, double*   value);

// Array
int serialize_array_endian_uint16 (MicroBuffer* micro_buffer, Endianness endianness, uint16_t* array, uint32_t size);
int serialize_array_endian_uint32 (MicroBuffer* micro_buffer, Endianness endianness, uint32_t* array, uint32_t size);
int serialize_array_endian_uint64 (MicroBuffer* micro_buffer, Endianness endianness, uint64_t* array, uint32_t size);
int serialize_array_endian_int16  (MicroBuffer* micro_buffer, Endianness endianness, int16_t*  array, uint32_t size);
int serialize_array_endian_int32  (MicroBuffer* micro_buffer, Endianness endianness, int32_t*  array, uint32_t size);
int serialize_array_endian_int64  (MicroBuffer* micro_buffer, Endianness endianness, int64_t*  array, uint32_t size);
int serialize_array_endian_float  (MicroBuffer* micro_buffer, Endianness endianness, float*    array, uint32_t size);
int serialize_array_endian_double (MicroBuffer* micro_buffer, Endianness endianness, double*   array, uint32_t size);

int deserialize_array_endian_uint16 (MicroBuffer* micro_buffer, Endianness endianness, uint16_t* array, uint32_t size);
int deserialize_array_endian_uint32 (MicroBuffer* micro_buffer, Endianness endianness, uint32_t* array, uint32_t size);
int deserialize_array_endian_uint64 (MicroBuffer* micro_buffer, Endianness endianness, uint64_t* array, uint32_t size);
int deserialize_array_endian_int16  (MicroBuffer* micro_buffer, Endianness endianness, int16_t* array, uint32_t size);
int deserialize_array_endian_int32  (MicroBuffer* micro_buffer, Endianness endianness, int32_t* array, uint32_t size);
int deserialize_array_endian_int64  (MicroBuffer* micro_buffer, Endianness endianness, int64_t* array, uint32_t size);
int deserialize_array_endian_float  (MicroBuffer* micro_buffer, Endianness endianness, float*    array, uint32_t size);
int deserialize_array_endian_double (MicroBuffer* micro_buffer, Endianness endianness, double*   array, uint32_t size);

// Sequence
int serialize_sequence_endian_uint16 (MicroBuffer* micro_buffer, Endianness endianness, uint16_t* sequence, uint32_t size);
int serialize_sequence_endian_uint32 (MicroBuffer* micro_buffer, Endianness endianness, uint32_t* sequence, uint32_t size);
int serialize_sequence_endian_uint64 (MicroBuffer* micro_buffer, Endianness endianness, uint64_t* sequence, uint32_t size);
int serialize_sequence_endian_int16  (MicroBuffer* micro_buffer, Endianness endianness, int16_t*  sequence, uint32_t size);
int serialize_sequence_endian_int32  (MicroBuffer* micro_buffer, Endianness endianness, int32_t*  sequence, uint32_t size);
int serialize_sequence_endian_int64  (MicroBuffer* micro_buffer, Endianness endianness, int64_t*  sequence, uint32_t size);
int serialize_sequence_endian_float  (MicroBuffer* micro_buffer, Endianness endianness, float*    sequence, uint32_t size);
int serialize_sequence_endian_double (MicroBuffer* micro_buffer, Endianness endianness, double*   sequence, uint32_t size);

int deserialize_sequence_endian_uint16 (MicroBuffer* micro_buffer, Endianness endianness, uint16_t* sequence, uint32_t* size);
int deserialize_sequence_endian_uint32 (MicroBuffer* micro_buffer, Endianness endianness, uint32_t* sequence, uint32_t* size);
int deserialize_sequence_endian_uint64 (MicroBuffer* micro_buffer, Endianness endianness, uint64_t* sequence, uint32_t* size);
int deserialize_sequence_endian_int16  (MicroBuffer* micro_buffer, Endianness endianness, int16_t*  sequence, uint32_t* size);
int deserialize_sequence_endian_int32  (MicroBuffer* micro_buffer, Endianness endianness, int32_t*  sequence, uint32_t* size);
int deserialize_sequence_endian_int64  (MicroBuffer* micro_buffer, Endianness endianness, int64_t*  sequence, uint32_t* size);
int deserialize_sequence_endian_float  (MicroBuffer* micro_buffer, Endianness endianness, float*    sequence, uint32_t* size);
int deserialize_sequence_endian_double (MicroBuffer* micro_buffer, Endianness endianness, double*   sequence, uint32_t* size);

#ifdef __cplusplus
}
#endif

#endif //_MICROCDR_MICRO_CDR_H_