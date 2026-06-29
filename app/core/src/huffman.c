#include "../include/huffman.h"
#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *DecompressBytes(char *data)
{
	return data;
}

char *CompressBytes(char *data)
{
	return data;
}

int CompressFile(const char *file_content, size_t file_size, const char *data_filename, const char *arch_filename)
{
	char full_filename[100];
	snprintf(full_filename, sizeof(full_filename), "%s%s", data_filename, arch_filename);

	FILE *file_out = fopen(full_filename, "w");
	if (file_out == NULL) {
		printf("Error after making file %s\n", full_filename);
		return -1;
	}

	const uint8_t *data = (const uint8_t *)file_content;

	for (int i = 0; i < file_size; ++i) {
		if (putc(file_content[i], file_out) == EOF) {
			fprintf(stderr, "Error writing byte to stream\n");
			fclose(file_out);
			return -1;
		}
	}

	printf("Compress completed\n");

	fclose(file_out);
	return 0;
}

int DecompressFile(const char *file_content, size_t file_size, const char *data_filename, const char *arch_filename)
{
	char full_filename[100];
	snprintf(full_filename, sizeof(full_filename), "%s%s", data_filename, arch_filename);

	FILE *f_out = fopen(full_filename, "w");
	if (f_out == NULL) {
		printf("Error after making file %s\n", full_filename);
		return -1;
	}

	printf("Decompress completed\n");

	fclose(f_out);
	return 0;
}
