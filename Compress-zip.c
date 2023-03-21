#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

#define CHUNK_SIZE 16384

int main(int argc, char *argv[]) {
    FILE *source_file, *dest_file;
    char buffer[CHUNK_SIZE];
    int bytes_read;
    z_stream stream;

    if (argc != 3) {
        printf("Usage: compress <source file> <destination file>\n");
        exit(1);
    }

    source_file = fopen(argv[1], "rb");
    if (source_file == NULL) {
        printf("Unable to open source file %s\n", argv[1]);
        exit(1);
    }

    dest_file = fopen(argv[2], "wb");
    if (dest_file == NULL) {
        printf("Unable to create destination file %s\n", argv[2]);
        exit(1);
    }

    // Initialize the zlib stream
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    deflateInit(&stream, Z_DEFAULT_COMPRESSION);

    // Compress the data
    do {
        bytes_read = fread(buffer, 1, CHUNK_SIZE, source_file);
        stream.avail_in = bytes_read;
        stream.next_in = (Bytef *)buffer;
        do {
            stream.avail_out = CHUNK_SIZE;
            stream.next_out = (Bytef *)buffer;
            deflate(&stream, Z_FINISH);
            fwrite(buffer, 1, CHUNK_SIZE - stream.avail_out, dest_file);
        } while (stream.avail_out == 0);
    } while (bytes_read == CHUNK_SIZE);

    // Clean up
    deflateEnd(&stream);
    fclose(source_file);
    fclose(dest_file);

    return 0;
}
