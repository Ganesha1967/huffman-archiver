#include "../core/include/huffman.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	// implement command-line argument validation and corresponding error handling
	// define conditions to call the appropriate function based on command-line arguments

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
		return -1;
	}

	char *input_filename = argv[1];

	FILE *file = fopen(input_filename, "rb");
	if (file == NULL) {
		fprintf(stderr, "Erroe with open file\n");
		return -1;
	}

	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	if (file_size == 0) {
		fprintf(stderr, "File is empty\n");
		fclose(file);
		return -1;
	}

	char *buffer = (char *)malloc(file_size + 1);
	if (buffer == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		fclose(file);
		return -1;
	}

	size_t bytes_read = fread(buffer, 1, file_size, file);
	buffer[bytes_read] = '\0';

	fclose(file);

	char data_filename[] = "example.txt";
	char arch_filename[] = ".huffman";
	if (CompressFile(buffer, file_size, data_filename, arch_filename) != 0) {
		fclose(file);
		return -1;
	};

	if (DecompressFile(buffer, file_size, data_filename, arch_filename) != 0) {
		fclose(file);
		return -1;
	};

	free(buffer);
	return 0;
}
