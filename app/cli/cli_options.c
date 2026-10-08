#include "cli_options.h"

void print_help(void) {
    printf("Huffman Archiver - cli\n");
    printf("Usage: ./build/huffman-cli [options] <input_file>\n\n");
    printf("Options:\n");
    printf("  -o, --output <file>  Specify output file path\n");
    printf("  -d, --decompress     Decompress file\n");
    printf("  -c, --compress       Compress file (default)\n");
    printf("  -t, --table          Display symbol frequency table\n");
    printf("  -v, --verbose        Display detailed progress logs\n");
    printf("  -h, --help           Display this help screen\n\n");
}

CliOptions cli_options_default(void) {
    CliOptions options;
    options.input_file[0] = '\0';
    options.output_file[0] = '\0';
    options.is_compress = 1;
    options.verbose = 0;
    options.print_table = 0;
    options.show_help = 0;
    options.invalid = 0;
    options.output_explicit = 0;
    options.input_file_size = 0;
    return options;
}

static int find_last_dot(const char *path) {
    const char *slash = strrchr(path, '/');
    const char *base;

    if (slash) {
        base = slash + 1;
    } else {
        base = path;
    }

    const char *dot = strrchr(base, '.');
    if (!dot || dot == base) {
        return -1;
    }
    return (int)(dot - path);
}

CliOptions parse_cli_options(int argc, char *argv[]) {
    CliOptions options = cli_options_default();

    if (argc < 2) {
        options.invalid = 1;
        return options;
    }

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            options.show_help = 1;
            return options;
        }
        else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            if (i + 1 < argc) {
                snprintf(options.output_file, sizeof(options.output_file), "%s", argv[++i]);
                options.output_explicit = 1;
            } else {
                fprintf(stderr, "Error: Option %s requires a filename\n", argv[i]);
                options.invalid = 1;
                return options;
            }
        }
        else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--decompress") == 0) {
            options.is_compress = 0;
        }
        else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--compress") == 0) {
            options.is_compress = 1;
        }
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            options.verbose = 1;
        }
        else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--table") == 0) {
            options.print_table = 1;
        }
        else if (argv[i][0] != '-') {
            snprintf(options.input_file, sizeof(options.input_file), "%s", argv[i]);
        }
        else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            options.invalid = 1;
            return options;
        }
    }

    if (options.input_file[0] == '\0') {
        fprintf(stderr, "Error: no input file given\n");
        options.invalid = 1;
        return options;
    }

    // automatically select output filename if -o is not provided
    if (!options.output_explicit) {
        size_t in_len = strlen(options.input_file);
        static const char HUFF_SUFFIX[] = ".huff";

        if (options.is_compress) {
            int dot_pos = find_last_dot(options.input_file);
            int base_len;
            if (dot_pos >= 0) {
                base_len = dot_pos;
            } else {
                base_len = (int)in_len;
            }

            size_t suffix_size = sizeof(HUFF_SUFFIX);
            if ((size_t)base_len + suffix_size >= sizeof(options.output_file)) {
                fprintf(stderr, "Error: resulting filename too long\n");
                options.invalid = 1;
                return options;
            }

            snprintf(options.output_file, sizeof(options.output_file),
                     "%.*s.huff", base_len, options.input_file);
        } else {
            size_t suffix_len = sizeof(HUFF_SUFFIX) - 1;
            size_t base_len = in_len;
            if (in_len > suffix_len) {
                const char *tail = options.input_file + in_len - suffix_len;
                if (strcmp(tail, HUFF_SUFFIX) == 0) {
                    base_len = in_len - suffix_len;
                }
            }

            if (base_len + 1 >= sizeof(options.output_file)) {
                fprintf(stderr, "Error: resulting filename too long\n");
                options.invalid = 1;
                return options;
            }

            snprintf(options.output_file, sizeof(options.output_file),
                     "%.*s", (int)base_len, options.input_file);
        }
    }

    return options;
}
