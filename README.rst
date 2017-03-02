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

*microCDR* provides different buffer configurations for reading and writing data. This is a code example showing the serialization and deserialization of a variable. In this case it has been used static user-defined buffers. That means that the user has to provide a defined buffer and its size during the *microBuffer* creation. To write inside this buffer its needed an static *microBuffer*. For reading, it is needed a deserialized *microBuffer*. Each of them will need an associated *microCDR* instance for managing its content.

.. code-block:: C

    #include <stdlib.h>
    #include <microcdr/microCdr.h>

    #define BUFFER_LENGTH 200

    int main(){
        // A user defined buffer
        char buffer[BUFFER_LENGTH];

        // microBuffers using the user defined buffer
        struct microBuffer * microBufferWriter = NULL;
        struct microBuffer * microBufferReader = NULL;
        newStaticAlignedBuffer(buffer, BUFFER_LENGTH, &microBufferWriter);
        newDeserializedAlignedBuffer(buffer, BUFFER_LENGTH, &microBufferReader);

        // microCDR structs for managing the microBuffers
        struct microCDR * microCDRWriter = NULL;
        struct microCDR * microCDRReader = NULL;
        newMicroCDR(&microCDRWriter, microBufferWriter);
        newMicroCDR(&microCDRReader, microBufferReader);

        char input = 'X';
        char output;

        // Serialization of input data
        serializeChar(input, microCDRWriter);

        //Deserialization of data in output
        deserializeChar(&output, microCDRReader);

        free(microBufferWriter);
        free(microBufferReader);
        free(microCDRWriter);
        free(microCDRReader);
    }

Another option is using dynamic *microBuffers*, which will create their own internal buffer. Dynamic *microBuffers* have the capability of resizing its internal buffer to make the allocation of streams with different sizes.

.. code-block:: C

    #include <stdlib.h>
    #include <microcdr/microCdr.h>

    #define BUFFER_LENGTH 200

    int main(){
        // Empty microBuffer
        struct microBuffer * microBufferRW = NULL;
        newDynamicAlignedBuffer(&microBufferRW);

        // microCDR structs for managing the microBuffer
        struct microCDR * microCDRWriter = NULL;
        struct microCDR * microCDRReader = NULL;
        newMicroCDR(&microCDRWriter, microBufferRW);
        newMicroCDR(&microCDRReader, microBufferRW);

        char input = 'X';
        char output;

        // Serialization
        serializeChar(input, microCDRWriter);

        // Deserialization
        deserializeChar(&output, microCDRReader);

        free(microBufferRW);
        free(microCDRWriter);
        free(microCDRReader);
    }

In both code examples, *microBuffers* can be created as aligned or non-aligned buffers. For example, the function **newDynamicAlignedBuffer** (as well as the other *microBuffer* creation functions) has a paralell function named **newDynamicNonAlignedBuffer** for this purpouse. For more information about the API of *microCDR* check ...?

Supported types
---------------

The types supported in *microCDR* are presented in the following table. For each of them exists a serialization and a deserialization function.



+----------+----------------------+------------+
| Sign     | Type                 | Endianness |
+==========+======================+============+
|          | char                 |            |
+----------+----------------------+------------+
| signed   | char                 |            |
+----------+----------------------+------------+
| unsigned | char                 |            |
+----------+----------------------+------------+
|          | string               |            |
+----------+----------------------+------------+
|          | string               | endianness |
+----------+----------------------+------------+
|          | short                |            |
+----------+----------------------+------------+
|          | short                | endianness |
+----------+----------------------+------------+
| unsigned | short                |            |
+----------+----------------------+------------+
| unsigned | short                | endianness |
+----------+----------------------+------------+
|          | int                  |            |
+----------+----------------------+------------+
|          | int                  | endianness |
+----------+----------------------+------------+
| unsigned | int                  |            |
+----------+----------------------+------------+
| unsigned | int                  | endianness |
+----------+----------------------+------------+
|          | long                 |            |
+----------+----------------------+------------+
|          | long                 | endianness |
+----------+----------------------+------------+
| unsigned | long                 |            |
+----------+----------------------+------------+
| unsigned | long                 | endianness |
+----------+----------------------+------------+
|          | long long            |            |
+----------+----------------------+------------+
|          | long long            | endianness |
+----------+----------------------+------------+
| unsigned | long long            |            |
+----------+----------------------+------------+
| unsigned | long long            | endianness |
+----------+----------------------+------------+
|          | float                |            |
+----------+----------------------+------------+
|          | float                | endianness |
+----------+----------------------+------------+
|          | double               |            |
+----------+----------------------+------------+
|          | double               | endiannes  |
+----------+----------------------+------------+
|          | long double          |            |
+----------+----------------------+------------+
|          | long double          | endiannes  |
+----------+----------------------+------------+
|          | char array           |            |
+----------+----------------------+------------+
| signed   | char array           |            |
+----------+----------------------+------------+
| unsigned | char array           |            |
+----------+----------------------+------------+
|          | string array         |            |
+----------+----------------------+------------+
|          | string array         | endianness |
+----------+----------------------+------------+
|          | short array          |            |
+----------+----------------------+------------+
|          | short array          | endianness |
+----------+----------------------+------------+
| unsigned | short array          |            |
+----------+----------------------+------------+
| unsigned | short array          | endianness |
+----------+----------------------+------------+
|          | int array            |            |
+----------+----------------------+------------+
|          | int array            | endianness |
+----------+----------------------+------------+
| unsigned | int array            |            |
+----------+----------------------+------------+
| unsigned | int array            | endianness |
+----------+----------------------+------------+
|          | long array           |            |
+----------+----------------------+------------+
|          | long array           | endianness |
+----------+----------------------+------------+
| unsigned | long array           |            |
+----------+----------------------+------------+
| unsigned | long array           | endianness |
+----------+----------------------+------------+
|          | long long array      |            |
+----------+----------------------+------------+
|          | long long array      | endianness |
+----------+----------------------+------------+
| unsigned | long long array      |            |
+----------+----------------------+------------+
| unsigned | long long array      | endianness |
+----------+----------------------+------------+
|          | float array          |            |
+----------+----------------------+------------+
|          | float array          | endianness |
+----------+----------------------+------------+
|          | double array         |            |
+----------+----------------------+------------+
|          | double array         | endiannes  |
+----------+----------------------+------------+
|          | long double array    |            |
+----------+----------------------+------------+
|          | long double array    | endiannes  |
+----------+----------------------+------------+
|          | char sequence        |            |
+----------+----------------------+------------+
| signed   | char sequence        |            |
+----------+----------------------+------------+
| unsigned | char sequence        |            |
+----------+----------------------+------------+
|          | string sequence      |            |
+----------+----------------------+------------+
|          | string sequence      | endianness |
+----------+----------------------+------------+
|          | short sequence       |            |
+----------+----------------------+------------+
|          | short sequence       | endianness |
+----------+----------------------+------------+
| unsigned | short sequence       |            |
+----------+----------------------+------------+
| unsigned | short sequence       | endianness |
+----------+----------------------+------------+
|          | int sequence         |            |
+----------+----------------------+------------+
|          | int sequence         | endianness |
+----------+----------------------+------------+
| unsigned | int sequence         |            |
+----------+----------------------+------------+
| unsigned | int sequence         | endianness |
+----------+----------------------+------------+
|          | long sequence        |            |
+----------+----------------------+------------+
|          | long sequence        | endianness |
+----------+----------------------+------------+
| unsigned | long sequence        |            |
+----------+----------------------+------------+
| unsigned | long sequence        | endianness |
+----------+----------------------+------------+
|          | long long sequence   |            |
+----------+----------------------+------------+
|          | long long sequence   | endianness |
+----------+----------------------+------------+
| unsigned | long long sequence   |            |
+----------+----------------------+------------+
| unsigned | long long sequence   | endianness |
+----------+----------------------+------------+
|          | float sequence       |            |
+----------+----------------------+------------+
|          | float sequence       | endianness |
+----------+----------------------+------------+
|          | double sequence      |            |
+----------+----------------------+------------+
|          | double sequence      | endiannes  |
+----------+----------------------+------------+
|          | long double sequence |            |
+----------+----------------------+------------+
|          | long double sequence | endiannes  |
+----------+----------------------+------------+
