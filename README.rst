eProsima microCDR
================

.. image:: https://encrypted-tbn3.gstatic.com/images?q=tbn:ANd9GcSd0PDlVz1U_7MgdTe0FRIWD0Jc9_YH-gGi0ZpLkr-qgCI6ZEoJZ5GBqQ
    :height: 100px
    :width: 100px
    :align: left
    :alt: eProsima
    :target: http://www.eprosima.com

*eProsima microCDR* is a C library implementing the CDR standard serialization methods. Additionally it expands its capabilities, making *microCDR* compatible with aligned and non-aligned data streams.

This library is based on *eProsima Fast CDR* and it is focused on embedded and resource-limited systems.

Usage examples
--------------

*microCDR* provides different buffer configurations for reading and writing data. This is a code example showing the serialization and deserialization of a variable. In this case it has been used static buffer. That means that the user has to provide a defined buffer and its size during the *MicroBuffer* creation.

.. code-block:: C

    #include <microcdr/microcdr.h>
    #include <stdio.h>

    #define BUFFER_LENGTH 256

    uint8_t buffer[BUFFER_LENGTH];

    int main(int argc, char** args)
    {
        // Structs for handle the buffer.
        MicroBuffer writer;
        MicroBuffer reader;

        // Initialize the MicroBuffers for working with an user-managed buffer.
        init_external_buffer(&writer, buffer, BUFFER_LENGTH);
        init_external_buffer(&reader, buffer, BUFFER_LENGTH);

        // Serialize data
        char input[16] = "Hello microCDR!"; //16 characters
        serialize_array_char(&writer, input, 16);

        // Deserialize data
        char output[16];
        deserialize_array_char(&reader, output, 16);

        printf("Input: %s\n", input);
        printf("Output: %s\n", output);

        return 0;
    }

Another option is using a dynamic *MicroBuffer*, which will create their own internal buffer. Dynamic *MicroBuffers* have the capability of resizing its internal buffer to make the allocation of streams with different sizes.

.. code-block:: C

    #include <microcdr/microcdr.h>
    #include <stdio.h>

    #define BUFFER_LENGTH 256
    #define INITIAL_BUFFER_LENGTH 8

    uint8_t buffer[BUFFER_LENGTH];

    int main(int argc, char** args)
    {
        // Structs for handle the buffer.
        MicroBuffer writer;
        MicroBuffer reader;

        // The writer will be managed dynamically by the library.
        init_internal_buffer(&writer, INITIAL_BUFFER_LENGTH);

        // Serialize data
        char input[16] = "Hello microCDR!"; //16 characters
        serialize_array_char(&writer, input, 16);


        // The reader will read from the writer-managed buffer.
        init_external_buffer(&reader, writer.init, BUFFER_LENGTH);

        // Deserialize data
        char output[16];
        deserialize_array_char(&reader, output, 16);

        // Free internal buffer of the writer.
        free_internal_buffer(writer);

        printf("Input: %s\n", input);
        printf("Output: %s\n", output);

        return 0;
    }

Note: to change the default endianness of funcions without the *endian* tag, use the *endianness* member of the *Microbuffer* structure.

*microCDR* is always aligned. For more information about the API of *microCDR* check ...?

Supported types
---------------

The types supported in *microCDR* are presented in the following table. For each of them exists a serialization and a deserialization function.


+----------------------+------------+
| Type                 | Endianness |
+======================+============+
| bool                 |            |
+----------------------+------------+
| char                 |            |
+----------------------+------------+
| uint8_t              |            |
+----------------------+------------+
| int16                |            |
+----------------------+------------+
| int16                | endianness |
+----------------------+------------+
| uint16               |            |
+----------------------+------------+
| uint16               | endianness |
+----------------------+------------+
| int32                |            |
+----------------------+------------+
| int32                | endianness |
+----------------------+------------+
| uint32               |            |
+----------------------+------------+
| uint32               | endianness |
+----------------------+------------+
| int64                |            |
+----------------------+------------+
| int64                | endianness |
+----------------------+------------+
| uint64               |            |
+----------------------+------------+
| uint64               | endianness |
+----------------------+------------+
| float                |            |
+----------------------+------------+
| float                | endianness |
+----------------------+------------+
| double               |            |
+----------------------+------------+
| double               | endianness |
+----------------------+------------+
| bool array           |            |
+----------------------+------------+
| char array           |            |
+----------------------+------------+
| uint8_t array        |            |
+----------------------+------------+
| int16 array          |            |
+----------------------+------------+
| int16 array          | endianness |
+----------------------+------------+
| uint16 array         |            |
+----------------------+------------+
| uint16 array         | endianness |
+----------------------+------------+
| int32 array          |            |
+----------------------+------------+
| int32 array          | endianness |
+----------------------+------------+
| uint32 array         |            |
+----------------------+------------+
| uint32 array         | endianness |
+----------------------+------------+
| int64 array          |            |
+----------------------+------------+
| int64 array          | endianness |
+----------------------+------------+
| uint64 array         |            |
+----------------------+------------+
| uint64 array         | endianness |
+----------------------+------------+
| float array          |            |
+----------------------+------------+
| float array          | endianness |
+----------------------+------------+
| double array         |            |
+----------------------+------------+
| double array         | endianness |
+----------------------+------------+
| bool sequence        |            |
+----------------------+------------+
| char sequence        |            |
+----------------------+------------+
| uint8_t sequence     |            |
+----------------------+------------+
| int16 sequence       |            |
+----------------------+------------+
| int16 sequence       | endianness |
+----------------------+------------+
| uint16 sequence      |            |
+----------------------+------------+
| uint16 sequence      | endianness |
+----------------------+------------+
| int32 sequence       |            |
+----------------------+------------+
| int32 sequence       | endianness |
+----------------------+------------+
| uint32 sequence      |            |
+----------------------+------------+
| uint32 sequence      | endianness |
+----------------------+------------+
| int64 sequence       |            |
+----------------------+------------+
| int64 sequence       | endianness |
+----------------------+------------+
| uint64 sequence      |            |
+----------------------+------------+
| uint64 sequence      | endianness |
+----------------------+------------+
| float sequence       |            |
+----------------------+------------+
| float sequence       | endianness |
+----------------------+------------+
| double sequence      |            |
+----------------------+------------+
| double sequence      | endianness |
+----------------------+------------+