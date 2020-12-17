# Assembler for verilog machine #

Program used to create a pseudo assembler for handmade microc on verilog, since writing machine code directly is a pain

## Program usage ##

```
Usage: sim -n NLINES -i INSTR_FILE -o OUTFILE -p ASM_PROGRAM

 - n: Set the max number of lines of the program file
 - i: Set the instruction Set filename
 - o: Set the output filename
 - p: Set the input assembler program file

example: bin/sim -n 1024 -i resources/instr_set.is -o outfile -p resources/test
```

## Instruction set encoding ##

```
REG   BITS_TO_ENCODE_NUM_OF_REGISTER
INM   INMEDIATE_VALUES_SIZE
DIR   ADDRESSING_SPACE
PORT  NUM_OF_PORTS
-
NUM_OF_INSTRUCTIONS_IN_SET
INSTRUCTION_LABEL NS/S NUM_OF_OPERATORS OPCODE PARAM1 PARAM2 ....

```

### Example ###
```
REG   4
INM   8
DIR   10
PORT  2
-
17
MOV   NS  2   0000               REG    REG
NOT   NS  2   0001               REG    REG
ADD   NS  3   0010               REG    REG   REG
SUB   NS  3   0011               REG    REG   REG
AND   NS  3   0100               REG    REG   REG
OR    NS  3   0101               REG    REG   REG
NEG1  NS  2   0110               REG    REG
NEG2  NS  2   0111               REG    REG
LI    NS  2   1000               REG    INM
JUMP  S   1   100100             DIR
BEZ   S   1   100101             DIR
BNZ   S   1   100110             DIR
LOAD  NS  2   100111             PORT   REG
STRE  NS  2   101000             PORT   REG
STRI  NS  2   101001             PORT   INM
JAL   S   1   101010             DIR
RET   NS  0   1010110000000000
```

## Todo ##

- Fill instructions if size is not reached by parameters + opcode
- Add way to include fillers for specific instr
- Fx instr file not ending in blank line hanging app
- Format output for progfile.dat xxxx_xxxx_xxxx_xxxx