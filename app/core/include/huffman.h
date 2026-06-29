#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int CompressFile(const char *file_content, size_t file_size, const char *data_filename, const char *arch_filename);
int DecompressFile(const char *file_content, size_t file_size, const char *data_filename, const char *arch_filename);
char *DecompressBytes(char *data);
char *CompressBytes(char *data);

#endif
