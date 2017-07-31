#ifndef _MICROCDR_MICROBUFFER_H_
#define _MICROCDR_MICROBUFFER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

//const char MICRO_DYNAMIC = '1';
//const char MICRO_STATIC = '0';

//typedef enum {TRUE,FALSE}Bool;

typedef struct microBuffer
{
    //! @brief Pointer to the beginning of stream.
    char * m_buffer;

    //! @brief The total size of the user's buffer.
    uint32_t m_bufferSize;

    //! @brief This variable indicates if the managed buffer is internal or is from the user.
    char m_internalBuffer;

    //! @brief The size of the serialized/unserialized data in the stream.
    uint32_t m_serializedBuffer;

    //!@ brief This variable indicates if the managed buffer stream is aligned or not
    uint8_t m_alingData;

} microBuffer;

#ifdef __cplusplus
}
#endif

#endif
