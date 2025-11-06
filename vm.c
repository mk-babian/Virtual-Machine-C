#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "opcodes.h"

typedef uint8_t BYTE;

int main() {
    // Open the "out.bin" file ine "rb" mode (read & binary)
    FILE *file = fopen("out.bin", "rb");
    if (!file) {
        printf("ERR | Error opening file\n");
        return 1;
    }

    int stack[256];
    int stackPointer = 0;       // Stack pointer (top of stack)
    int programCounter = 0;     // Program counter (which instruction)

    fseek(file, 0, SEEK_END);   // Put the file pointer at EOF (end of file)
    long fileSize = ftell(file);    // Store the current cursor position using ftell
    if (fileSize == -1L) {
        printf("ERR | ftell failed\n");
        fclose(file);
        return 2;
    }
    fseek(file, 0, SEEK_SET); // Put the file pointer back to the start

    BYTE *program = malloc(fileSize);
    if (!program) {
        printf("ERR | malloc failed\n");
        fclose(file);
        return 3; // Added error handling for malloc
    }
    fread(program, sizeof(BYTE), fileSize, file);

    // Exec
    while (1) {
        uint8_t instruction = program[programCounter++];

        // The PUSH function
        if (instruction == PUSH) {
            int value = program[programCounter++];
            stack[stackPointer++] = value;
        }
        // Adding numbers
        else if (instruction == ADD) {
            int b = stack[--stackPointer]; 
            int a = stack[--stackPointer]; 
            stack[stackPointer++] = a + b;
        }
        // Subtracting numbers
        else if (instruction == SUB) {
            int b = stack[--stackPointer]; 
            int a = stack[--stackPointer]; 
            stack[stackPointer++] = a - b;
        }
        // Multiplying numbers
        else if (instruction == MUL) {
            int b = stack[--stackPointer]; 
            int a = stack[--stackPointer]; 
            stack[stackPointer++] = a * b;
        }
        // Dividing numbers
        else if (instruction == DIV) {
            int b = stack[--stackPointer]; 
            int a = stack[--stackPointer]; 
            stack[stackPointer++] = a / b;
        }
        // Check if equal
        else if (instruction == EQ) {
            int b = stack[--stackPointer]; 
            int a = stack[--stackPointer]; 
            stack[stackPointer++] = (a == b) ? 1 : 0; // Push 1 if equal, 0 if not
        }
        else if (instruction == JZ) {
            int address = program[programCounter++]; // Where to jump to
            int condition = stack[--stackPointer]; 
            if (condition == 0) {
                programCounter = address; // Jump by changing program counter
            }
        }
        // Print the thingy bagingy
        else if (instruction == PRINT) {
            printf("%d\n", stack[--stackPointer]); 
        }
        // Stop right there, criminal scum!
        else if (instruction == HALT) {
            break;
        }
    }

    free(program);
    fclose(file);
    return 0;
}
