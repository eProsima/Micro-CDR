

#ifndef _NANOCDR_NANOBUFFER_H_
#define _NANOCDR_NANOBUFFER_H_

#include <stdint.h>

//const char NANO_DYNAMIC = '1';
//const char NANO_STATIC = '0';

//typedef enum {TRUE,FALSE}Bool;

	typedef struct nanoBuffer
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

	}nanoBuffer;
#endif
