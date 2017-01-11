eProsima nanoCDR
================

.. image:: https://encrypted-tbn3.gstatic.com/images?q=tbn:ANd9GcSd0PDlVz1U_7MgdTe0FRIWD0Jc9_YH-gGi0ZpLkr-qgCI6ZEoJZ5GBqQ
    :height: 100px
    :width: 100px
    :align: left
    :alt: eProsima
    :target: http://www.eprosima.com

*eProsima nanoCDR* is a C library implementing the CDR standard serialization methods. Additionally it expands its capabilities, making *nanoCDR* compatible with aligned and non-aligned data streams.

This library is based on *eProsima Fast CDR* and it is focused on embedded and resource-limited systems.

Usage examples
--------------

*nanoCDR* provides different buffer configurations for reading and writing data. This is a code example showing the serialization and deserialization of a variable. In this case it has been used static user-defined buffers. That means that the user has to provide a defined buffer and its size during the *nanoBuffer* creation. To write inside this buffer its needed an static *nanoBuffer*. For reading, it is needed a deserialized *nanoBuffer*. Each of them will need an associated *nanoCDR* instance for managing its content.

.. code-block:: C

    #include <stdlib.h>
    #include <nanocdr/nanoCdr.h>

    #define BUFFER_LENGTH 200

    int main(){
        // A user defined buffer
        char buffer[BUFFER_LENGTH];

        // nanoBuffers using the user defined buffer
        struct nanoBuffer * nanoBufferWriter = NULL;
        struct nanoBuffer * nanoBufferReader = NULL;
        newStaticAlignedBuffer(buffer, BUFFER_LENGTH, &nanoBufferWriter);
        newDeserializedAlignedBuffer(buffer, BUFFER_LENGTH, &nanoBufferReader);

        // nanoCDR structs for managing the nanoBuffers
        struct nanoCDR * nanoCDRWriter = NULL;
        struct nanoCDR * nanoCDRReader = NULL;
        newNanoCDR(&nanoCDRWriter, nanoBufferWriter);
        newNanoCDR(&nanoCDRReader, nanoBufferReader);

        char input = 'X';
        char output;

        // Serialization of input data
        serializeChar(input, nanoCDRWriter);

        //Deserialization of data in output
        deserializeChar(&output, nanoCDRReader);

        free(nanoBufferWriter);
        free(nanoBufferReader);
        free(nanoCDRWriter);
        free(nanoCDRReader);
    }

Another option is using dynamic *nanoBuffers*, which will create their own internal buffer. Dynamic *nanoBuffers* have the capability of resizing its internal buffer to make the allocation of streams with different sizes.

.. code-block:: C

    #include <stdlib.h>
    #include <nanocdr/nanoCdr.h>

    #define BUFFER_LENGTH 200

    int main(){
        // Empty nanoBuffer
        struct nanoBuffer * nanoBufferRW = NULL;
        newDynamicAlignedBuffer(&nanoBufferRW);

        // nanoCDR structs for managing the nanoBuffer
        struct nanoCDR * nanoCDRWriter = NULL;
        struct nanoCDR * nanoCDRReader = NULL;
        newNanoCDR(&nanoCDRWriter, nanoBufferRW);
        newNanoCDR(&nanoCDRReader, nanoBufferRW);

        char input = 'X';
        char output;

        // Serialization
        serializeChar(input, nanoCDRWriter);

        // Deserialization
        deserializeChar(&output, nanoCDRReader);

        free(nanoBufferRW);
        free(nanoCDRWriter);
        free(nanoCDRReader);
    }

In both code examples, *nanoBuffers* can be created as aligned or non-aligned buffers. For example, the function **newDynamicAlignedBuffer** (as well as the other *nanoBuffer* creation functions) has a paralell function named **newDynamicNonAlignedBuffer** for this purpouse. For more information about the API of *nanoCDR* check ...?

Supported types
---------------

The types supported in *nanoCDR* are presented in the following table. For each of them exists a serialization and a deserialization function.



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
