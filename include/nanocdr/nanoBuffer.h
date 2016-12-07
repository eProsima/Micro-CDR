

#ifndef _NANOCDR_NANOBUFFER_H_
#define _NANOCDR_NANOBUFFER_H_

#include <stdint.h>

//const char NANO_DYNAMIC = '1';
//const char NANO_STATIC = '0';

	typedef enum {BIG_ENDIANNESS,LITTLE_ENDIANNESS}Endianness;
	typedef enum {TRUE,FALSE}Bool;

	struct nanoBuffer
	{
		//! @brief Pointer to the beginning of stream.
		char * m_buffer;

		//! @brief The position in the buffer when the state was created.
		char * m_currentPosition;

		//! @brief The total size of the user's buffer.
		uint32_t m_bufferSize;

		//! @brief This variable indicates if the managed buffer is internal or is from the user.
		char m_internalBuffer;

		//! @brief This variable indicates the actual position in the stream.
		uint32_t m_iterator;

		//! @brief The size of the serialized/unserialized data in the stream.
		uint32_t m_serializedBuffer;

		//! @brief
		char * m_alignPosition;

		//! @brief Endianness of the buffer
		Endianness m_endianness;

		//! @brief This variable indicates if the library must swap the words.
		Bool m_swapBytes;

	}nanoBuffer;
#endif
