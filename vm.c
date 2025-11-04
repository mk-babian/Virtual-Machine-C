#include <stdio.h>
#include <stdint.h>

// Instructions
#define PUSH 1 // Push number on top of stack
#define ADD 2 // Add
#define PRINT 3 // pint?
#define HALT 4 // Stop right there, criminal scum!
#define SUB 5 // Subtract
#define MUL 6 // Multiply
#define DIV 7 // Divide
#define EQ 8 // Check if equal
#define JZ 9 // Jump if zero

int main(){

	// TODO:
	//
	// Open file in binary read mode [DONE]
	// Figure out how big the file is [DONE]
	// Allocate memory to hold that many bytes []
	// Read the file contents into that memory []
	// Close the file []
	// Use that memory as the program array (instead of hardcoded one) []
	// Free the memory []

	// Unsigned 8 bit int "program" that defines what instructions the VM uses
	uint8_t program[] = {PUSH, 5, PUSH, 5, EQ, JZ, 10,
                     PUSH, 99, PRINT, HALT, PUSH, 0, PRINT, HALT};
	// Open the "test.bin" file ine "rb" mode (read & binary)	
	FILE *file = fopen("test.bin", "rb");
	if (!file){
		printf("ERR | Error opening file\n");
		return 1;
	}

	int stack[256];			// Number holder
	int stackPointer = 0;		// Stack pointer (top of stack)
	int programCounter = 0;		// Program counter (which instruction)

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);	

	// Exec
	while (1){
		uint8_t instruction = program[programCounter++];
		
		// The PUSH function puts the next byte on top of the stack 
		if (instruction == PUSH){
			int value = program[programCounter++];
			stack[stackPointer++] = value;

			// stack[stackPointer++] = value is basically:
			// stack[stackPointer] = value;
			// stackPointer = stackPointer + 1;
		}
		// Adding numbers
		else if (instruction == ADD){
			int b = stack[--stackPointer];
			int a = stack[--stackPointer];
			stack[stackPointer++] = a + b;
		}
		// Subtracting numbers
		else if (instruction == SUB){
			int b = stack[--stackPointer];
			int a = stack[--stackPointer];
			stack[stackPointer++] = a - b;
		}
		// Multiplying numbers
		else if (instruction == MUL){
			int b = stack[--stackPointer];
			int a = stack[--stackPointer];
			stack[stackPointer++] = a * b;
		}
		// Dividing numbers
		else if (instruction == DIV){
			int b = stack[--stackPointer];
			int a = stack[--stackPointer];
			stack[stackPointer++] = a / b;
		}
		// Check if equal
		else if (instruction == EQ){
			int b = stack[--stackPointer];
			int a = stack[--stackPointer];
			stack[stackPointer++] = (a == b) ? 1 : 0; // Push 1 if equal, 0 if not
		}
		else if (instruction == JZ){
			int address = program[programCounter++]; // Where to jump to
			int condition = stack[--stackPointer]; 
			if (condition == 0){
				programCounter = address; // Jump by changing program counter
			}
		}
		// Print the thingy bagingy
		else if (instruction == PRINT){
			printf("%d\n", stack[--stackPointer]);
		}
		// Stop right there, criminal scum!
		else if (instruction == HALT) {
			break;
		}
	}
		
	fclose(file);

	return 0;
}

