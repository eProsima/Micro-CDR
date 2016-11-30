

#ifndef _NANOCDR_NANOBUFFER_H_
#define _NANOCDR_NANOBUFFER_H_

//const char NANO_DYNAMIC = '1';
//const char NANO_STATIC = '0';

	struct nanoBuffer
	{
		//! @brief Pointer to the beginning of stream.
		char * m_buffer;

		//! @brief The position in the buffer when the state was created.
		char * m_currentPosition;

		//! @brief The total size of the user's buffer.
		unsigned int m_bufferSize;

		//! @brief This variable indicates if the managed buffer is internal or is from the user.
		char m_internalBuffer;

		//! @brief This variable indicates the actual position in the stream.
		unsigned int m_iterator;

		//! @brief The size of the serialized/unserialized data in the stream.
		unsigned int m_serializedBuffer;

		//! @brief
		char * m_alignPosition;

	}nanoBuffer;
#endif
