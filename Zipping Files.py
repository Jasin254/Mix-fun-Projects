import zlib

CHUNK_SIZE = 16384

def compress_file(source_file, dest_file):
    with open(source_file, 'rb') as f_in, open(dest_file, 'wb') as f_out:
        # Initialize the zlib compressor
        compressor = zlib.compressobj()

        while True:
            # Read a chunk of data from the source file
            chunk = f_in.read(CHUNK_SIZE)
            if not chunk:
                # End of file
                break

            # Compress the chunk of data
            compressed_chunk = compressor.compress(chunk)

            # Write the compressed data to the output file
            f_out.write(compressed_chunk)

        # Flush the compressor and write any remaining compressed data to the output file
        remaining_data = compressor.flush()
        f_out.write(remaining_data)
        //compress_file('example.txt', 'example.txt.gz')
