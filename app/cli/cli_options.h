#ifndef CLI_OPTIONS_H
#define CLI_OPTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include <string.h>

#if defined _WIN32 || defined _WIN64
    #define MAX_PATH_LEN 32767
#elif defined PATH_MAX
    #define MAX_PATH_LEN PATH_MAX
#else
    #define MAX_PATH_LEN 1024
#endif

typedef struct {
    char input_file[MAX_PATH_LEN];
    char output_file[MAX_PATH_LEN];
    int is_compress;
    int verbose;
    int print_table;
    int show_help;
    int invalid;
    int output_explicit;
    size_t input_file_size;
} CliOptions;

void print_help(void);
CliOptions cli_options_default(void);
CliOptions parse_cli_options(int argc, char *argv[]);

#endif
