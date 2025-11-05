#include <stdio.h>
#include <stdint.h>

// Instructions
#define PUSH 1  // Push number on top of stack
#define ADD 2   // Add
#define PRINT 3 // pint?
#define HALT 4  // Stop right there, criminal scum!
#define SUB 5   // Subtract
#define MUL 6   // Multiply
#define DIV 7   // Divide
#define EQ 8    // Check if equal
#define JZ 9    // Jump if zero

typedef uint8_t BYTE;

int main() {
	// Open two files, one for reading the instructions
	// from a text file, and the other for writing to
	// a binary file
	FILE *file = fopen("instructions", "r");
	if (!file){
		printf("ERR | Error opening file\n");
		return 1;
	}
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

	while (fgets(line, sizeof(line), file)){
		res = strtok(line, " ");	
	}			

	fclose(file);
	fclose(outFile);
	return 0;
}
