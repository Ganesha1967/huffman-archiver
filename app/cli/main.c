#include "cli_options.h"
#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    CliOptions options = parse_cli_options(argc, argv);

    if (options.show_help) {
        print_help();
        return 0;
    }

    if (options.invalid) {
        fprintf(stderr, "Invalid arguments.\n\n");
        print_help();
        return 1;
    }

    HuffmanOptions huf_options = {
        .input_file = options.input_file,
        .output_file = options.output_file,
        .print_table = options.print_table,
        .verbose = options.verbose,
        .explicit_output = options.output_explicit,
    };

    if (options.is_compress) {
        if (options.verbose) {
            printf("Mode: COMPRESSION\n");
            printf("Input file:  %s\n", options.input_file);
            printf("Output file: %s\n", options.output_file);
            printf("Building Huffman Tree and encoding stream...\n");
        }

        int result = compress_file(&huf_options);
        if (result != 0) {
            fprintf(stderr, "Error: failed to compress file '%s'\n", options.input_file);
            return 1;
        }

        if (options.verbose) {
            printf("Compression finished successfully -> %s\n", options.output_file);
        } else {
            printf("Compressed successfully -> %s\n", options.output_file);
        }
    }
    else {
        char resolved_output[MAX_PATH_LEN];
        resolved_output[0] = '\0';

        if (options.verbose) {
            printf("Mode: DECOMPRESSION\n");
            printf("Input file:  %s\n", options.input_file);
            printf("Reading header and decoding stream...\n");
        }

        int result = decompress_file(&huf_options, resolved_output, sizeof(resolved_output));
        if (result != 0) {
            fprintf(stderr, "Error: failed to decompress file '%s'\n", options.input_file);
            return 1;
        }

        if (options.verbose) {
            printf("Decompression finished successfully -> %s\n", resolved_output);
        } else {
            printf("Decompressed successfully -> %s\n", resolved_output);
        }
    }

    return 0;
}
