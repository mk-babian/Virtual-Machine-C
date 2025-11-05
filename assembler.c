#include <stdio.h>
#include <stdint.h>

#include "opcodes.h"

typedef uint8_t BYTE;

int main() {
	// Open a text file containing instructions
	FILE *file = fopen("instructions", "r");
	if (!file){
		printf("ERR | Error opening file\n");
		return 1;
	}
	// Write to a binary file those same instructions
	FILE *outFile = fopen("out.bin", "wb");
	if (!outFile){
		printf("ERR | Error opening output file\n");
		return 4;
	}
	
	// Find the file size
	fseek(file, 0, SEEK_END); // Set the file cursor to the end
	long fileSize = ftell(file);
	if (fileSize == -1L){
		printf("ERR | ftell failed");
		fclose(file);
		return 2;
	}
	fseek(file, 0, SEEK_SET); // Set the file cursor to the beginning
	
	char line[256]; // Buffer for one line of text	
	char *res;



	fclose(file);
	fclose(outFile);
	return 0;
}
