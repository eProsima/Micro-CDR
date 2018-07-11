# eProsima microCDR

<a href="http://www.eprosima.com"><img src="https://encrypted-tbn3.gstatic.com/images?q=tbn:ANd9GcSd0PDlVz1U_7MgdTe0FRIWD0Jc9_YH-gGi0ZpLkr-qgCI6ZEoJZ5GBqQ" align="left" hspace="8" vspace="2" width="100" height="100" ></a>

*eProsima microCDR* is a C library implementing the CDR standard serialization methods.
This library is focused on embedded and resource-limited systems.

*microCDR* uses a static buffer, is always aligned, and allow to serialize and deserialize in both, big endianness and little endianness.
For more information about the API of *microCDR* check ...?

## Usage examples
This is a code example showing the serialization and deserialization of a string.
As *microCDR* uses a static buffer, that means the user has to provide a defined buffer and its size during the *MicroBuffer* creation.

```c
    #include <microcdr/microcdr.h>
    #include <stdio.h>

    #define BUFFER_LENGTH 256

    int main(int argc, char** args)
    {
        // Data buffer
        uint8_t buffer[BUFFER_LENGTH];

        // Structs for handle the buffer.
        MicroBuffer writer;
        MicroBuffer reader;

        // Initialize the MicroBuffers for working with an user-managed buffer.
        init_micro_buffer(&writer, buffer, BUFFER_LENGTH);
        init_micro_buffer(&reader, buffer, BUFFER_LENGTH);

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
```

Note: to change the default endianness of functions without the *endian* tag, use the *endianness* member of the *Microbuffer* structure.


## Supported types
The types supported in *microCDR* are presented in the following table. For each of them exists a serialization and a deserialization function.


| Type                 | Endianness |
| -------------------- | ---------- |
| bool                 |            |
| char                 |            |
| uint8                |            |
| int16                |            |
| int16                | endianness |
| uint16               |            |
| uint16               | endianness |
| int32                |            |
| int32                | endianness |
| uint32               |            |
| uint32               | endianness |
| int64                |            |
| int64                | endianness |
| uint64               |            |
| uint64               | endianness |
| float                |            |
| float                | endianness |
| double               |            |
| double               | endianness |
| bool array           |            |
| char array           |            |
| uint8 array          |            |
| int16 array          |            |
| int16 array          | endianness |
| uint16 array         |            |
| uint16 array         | endianness |
| int32 array          |            |
| int32 array          | endianness |
| uint32 array         |            |
| uint32 array         | endianness |
| int64 array          |            |
| int64 array          | endianness |
| uint64 array         |            |
| uint64 array         | endianness |
| float array          |            |
| float array          | endianness |
| double array         |            |
| double array         | endianness |
| bool sequence        |            |
| char sequence        |            |
| uint8 sequence       |            |
| int16 sequence       |            |
| int16 sequence       | endianness |
| uint16 sequence      |            |
| uint16 sequence      | endianness |
| int32 sequence       |            |
| int32 sequence       | endianness |
| uint32 sequence      |            |
| uint32 sequence      | endianness |
| int64 sequence       |            |
| int64 sequence       | endianness |
| uint64 sequence      |            |
| uint64 sequence      | endianness |
| float sequence       |            |
| float sequence       | endianness |
| double sequence      |            |
| double sequence      | endianness |
