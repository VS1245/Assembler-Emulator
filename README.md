# Assembler-Emulator
Machine Code Generation and Execution (small set of instructions)

## Author Information
- **Name:** Shambhavi Verma
- **Roll No:** 2101CS89
- **Course:** CS209-CS210 Computer Architecture

## Declaration of Authorship
This txt file, `claims.txt`, is part of the assignment of CS209-CS210 at the department of Computer Science and Engineering, IIT Patna.

## Program Structure
The paths of the files used in the code are hardcoded.

### The Assembler:
- Uses a single routine for both passes.
- Detects errors related to nomenclature of labels.
- Consistent and sensible formatting with sensible program structure. 
- Sensible variable, function & type names with explanatory comments.
- Produces a listing file and machine code.
- Assembles test programs.

### The Emulator
- Executes the machine code generated by assembler.
- Produces a record mentioning the value of Reg_A, Reg_B, Stack Pointer, Program Counter.

## What Works:
A) Includes checking for labels and their correct nomenclature (Should not contain number as start, should contain alphanum and _ and nums only)
B) Includes checking for mnemonics and the number of arguments and jumps (incase of labels)
C) Uses map from C++ STL Library (GNU G++14 6.4.0 version) to check for mnemonics and labels.
D) Has custom hashing function to process queries faster and to avoid clashes.
E) Two pass assembler
F) First checks syntactical errors
G) Second checks semantical errors

## Example Cases
1. **test1.asm**
    - with `asm.txt`
    - with `log.txt`
    - with `list.txt`
    - with `emu_o.txt`

2. **test2.asm**
    - with `asm.txt`
    - with `log.txt`
    - with `list.txt`
    - with `emu_o.txt`

3. **test3.asm**
    - with `asm.txt`
    - with `log.txt`
    - with `list.txt`
    - with `emu_o.txt`

4. **test4.asm**
    - with `asm.txt`
    - with `log.txt`
    - with `list.txt`
    - with `emu_o.txt`

5. **test5.asm** (finds sum of n numbers)
    - with `asm.txt`
    - with `log.txt`
    - with `list.txt`
    - with `emu_o.txt`

6. **test6.asm** (find mean of n numbers)
    - with `asm.txt`
    - with `log.txt`
    - with `list.txt`
    - with `emu_o.txt`

7. **test7.asm** (find multiplication of 2 numbers)
    - with `asm.txt`
    - with `log.txt`
    - with `list.txt`
    - with `emu_o.txt`

## Additional Information
- `asm.txt`: Contains machine code.
- `list.txt`: Contains machine code and program counter.
- `emu_o.txt`: Memory dump (records Reg A, Reg B, Stack Pointer, and Program Counter at every instruction).
- `log_o.txt`: Contains all error messages.
- `mem.txt`: Memory block of size 4096.
