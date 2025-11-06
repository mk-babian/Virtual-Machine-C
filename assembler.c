#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "opcodes.h"

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
    const char *delimiters = " ";
    
    char *instruction;
    char *operand;

    uint8_t opcode;
    int hasOperand = 0; 
    // TODO: Parse the text from the text file

    // Use sscanf
    // Check how many items successfully read
    
    // Go through each line of the file
    while (fgets(line, 256, file) != NULL){
        // Find the next instruction
        instruction = strtok(line, delimiters);
        operand = strtok(NULL, delimiters);

        if (strcmp(instruction, "PUSH") == 0) {
            opcode = PUSH;
            hasOperand = 1;
        }else if (strcmp(instruction, "JZ") == 0){
            opcode = JZ;
            hasOperand = 1;
        }else if (strcmp(instruction, "SUB") == 0){
            opcode = SUB;
            hasOperand = 0;
        }else if (strcmp(instruction, "ADD") == 0){
            opcode = ADD;
            hasOperand = 0;
        }else if (strcmp(instruction, "PRINT") == 0){
            opcode = PRINT;
            hasOperand = 0;
        }else if (strcmp(instruction, "DIV") == 0){
            opcode = DIV;
            hasOperand = 0;
        }else if (strcmp(instruction, "MUL") == 0){
            opcode = MUL;
            hasOperand = 0;
        }else if (strcmp(instruction, "EQ") == 0){
            opcode = EQ;
            hasOperand = 0;
        }else if (strcmp(instruction, "HALT") == 0){
            opcode = HALT;
            hasOperand = 0;
        }
        
        fwrite(&opcode, sizeof(uint8_t), 1, outFile);
        
        if (hasOperand && operand != NULL){
            int op = atoi(operand);
            fwrite(&op, sizeof(int), 1, outFile);

            // DEBUG
            printf("%s %d\n", instruction, op);
        }else{
            printf("%s", instruction);
        }
    }   

    fclose(file);
    fclose(outFile);
    return 0;
}
