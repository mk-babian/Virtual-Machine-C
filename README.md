# Stack-Based Virtual Machine

A minimal educational implementation of a stack-based virtual machine in C, featuring a custom assembler and bytecode interpreter.

## Overview

This project demonstrates fundamental concepts in compiler design and virtual machine implementation. It consists of two main components that work together to execute simple programs:

- **Assembler**: Translates human-readable assembly code into compact bytecode
- **Virtual Machine**: Interprets and executes the compiled bytecode using a stack-based architecture

The VM implements a simple instruction set sufficient for arithmetic operations, conditional logic, and basic I/O.

## Features

- ✅ Custom bytecode format with 9 core instructions
- ✅ Stack-based execution model (256-element stack)
- ✅ Arithmetic operations (ADD, SUB, MUL, DIV)
- ✅ Conditional branching (EQ, JZ)
- ✅ Two-pass workflow: assemble → execute

## Project Structure

```
.
├── assembler.c         # Assembler implementation
├── virtual-machine.c   # VM interpreter
├── opcodes.h          # Shared instruction definitions
├── instructions       # Example assembly source (user-created)
└── out.bin           # Compiled bytecode (generated)
```

## Building

### Prerequisites
- GCC or any C99-compatible compiler
- Make (optional)

### Compilation

```bash
# Compile the assembler
gcc -o assembler assembler.c -std=c99 -Wall

# Compile the virtual machine
gcc -o vm virtual-machine.c -std=c99 -Wall
```

Or use the provided Makefile (if you create one):
```bash
make
```

## Quick Start

### 1. Write Your Program

Create a file named `instructions` with your assembly code:

```asm
PUSH 10
PUSH 32
ADD
PRINT
HALT
```

### 2. Assemble the Code

```bash
./assembler
```

Output: `out.bin` (bytecode file)

### 3. Run the Program

```bash
./vm out.bin
```

Output: `42`

## Instruction Set Reference

| Instruction | Opcode | Operand | Stack Effect | Description |
|-------------|--------|---------|--------------|-------------|
| `PUSH n`    | 0x01   | Yes     | `→ n`        | Push immediate value onto stack |
| `ADD`       | 0x02   | No      | `a b → a+b`  | Pop two values and push sum |
| `PRINT`     | 0x03   | No      | `n →`        | Pop and print top value |
| `HALT`      | 0x04   | No      | -            | Terminate execution |
| `SUB`       | 0x05   | No      | `a b → a-b`  | Pop two values and push difference |
| `MUL`       | 0x06   | No      | `a b → a*b`  | Pop two values and push product |
| `DIV`       | 0x07   | No      | `a b → a/b`  | Pop two values and push quotient |
| `EQ`        | 0x08   | No      | `a b → bool` | Compare equality (1 if equal, 0 otherwise) |
| `JZ addr`   | 0x09   | Yes     | `cond →`     | Jump to byte address if top value is zero |

## Example Programs

### Hello World (prints 42)
```asm
PUSH 42
PRINT
HALT
```

### Arithmetic Expression: (15 + 25) * 2
```asm
PUSH 15
PUSH 25
ADD
PUSH 2
MUL
PRINT
HALT
```

### Conditional Execution
```asm
PUSH 10
PUSH 10
EQ          ; Check if equal
JZ 12       ; Skip to HALT if not equal (byte address 12)
PUSH 100    ; Only executes if numbers were equal
PRINT
HALT
```

### Loop Example (countdown from 5)
```asm
PUSH 5      ; Byte 0-1: Initial counter
PUSH 1      ; Byte 2-3: Loop start - push counter for comparison
PUSH 0      ; Byte 4-5: Compare with 0
EQ          ; Byte 6: Check if counter == 0
JZ 16       ; Byte 7-8: If zero, jump to HALT at byte 16
PUSH 1      ; Byte 9-10: Push 1 for subtraction
SUB         ; Byte 11: Decrement counter
JZ 2        ; Byte 12-13: Jump back to loop start (byte 2)
HALT        ; Byte 14
```

*Note: Jump addresses require manual calculation based on bytecode offsets.*

## Technical Details

### Architecture
- **Type**: Stack-based virtual machine
- **Word Size**: 32-bit integers (stack values)
- **Bytecode Width**: 8-bit opcodes and operands
- **Stack Capacity**: 256 elements
- **Memory Model**: Program loaded entirely into RAM

### Bytecode Format
```
[OPCODE (1 byte)] [OPERAND (1 byte, optional)]
```

### Execution Model
1. Program Counter (PC) points to current instruction
2. Instructions are fetched and decoded sequentially
3. Stack Pointer (SP) tracks the top of the stack
4. Operations manipulate the stack according to their semantics

## Known Limitations

This is an educational implementation with intentional simplifications:

- ⚠️ No stack overflow/underflow protection
- ⚠️ No division-by-zero handling
- ⚠️ 8-bit operands only (values 0-255)
- ⚠️ Manual address calculation required for jumps (no label support)
- ⚠️ Assembler reads hardcoded `instructions` file
- ⚠️ Limited error reporting and diagnostics
- ⚠️ `hasOperand` flag not reset in assembler loop (will cause bugs with instruction sequences)

## Learning Objectives

This project demonstrates:

- **Compiler Frontend**: Lexical analysis and parsing of assembly syntax
- **Code Generation**: Translation from text to binary representation
- **VM Design**: Stack-based execution model
- **Instruction Set Architecture**: Opcode design and implementation
- **Control Flow**: Program counter manipulation and conditional branching
- **Memory Management**: Dynamic allocation and file I/O in C

## Future Enhancements

Potential improvements for learning purposes:

- [ ] Add proper error handling and validation
- [ ] Implement label support in assembler
- [ ] Add more instructions (function calls, comparison operators)
- [ ] Implement debugging/tracing mode
- [ ] Add support for larger operands (16-bit, 32-bit)
- [ ] Create a disassembler for bytecode inspection
- [ ] Add comprehensive test suite
- [ ] Support for command-line arguments in assembler

## Contributing

This is an educational project. Feel free to fork and experiment with:
- Additional instructions
- Different stack sizes
- Optimization techniques
- Enhanced error handling
- Better assembler features (labels, macros, etc.)

## License

[Your chosen license - e.g., MIT]

## Author

[Your name/GitHub username]

## Acknowledgments

Built for educational purposes to understand VM implementation and bytecode execution.

---

**Note**: This is a teaching implementation prioritizing clarity over performance or production readiness.
