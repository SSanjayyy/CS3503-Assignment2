# CS 3503 – Assignment 2: Advanced Data Representation

## Author
Sanjay Ravikumar

## Description
This project extends the base conversion work from Assignment 1 by adding direct mapping functions between number systems and signed int representations. These cool new functions include:

- `oct_to_bin` — Oct to Binary (3-bit mapping per digit)  
- `oct_to_hex` — Oct to Hexa (via binary grouping)  
- `hex_to_bin` — Hexa to Binary (4-bit mapping, case-insensitive)  
- `to_sign_magnitude` — Signed int stored with MSB as the sign bit  
- `to_ones_complement` — Signed int stored with all bits flipped for negatives  
- `to_twos_complement` — Signed int stored in standard two’s complement form  

## Notes:
Biggest challenge: Figuring out how to actually structure the functions and coding it up

## Build Instructions
To compile and run on Windows using **MinGW (gcc)**:

## In other words:
Assignment 1 focused on implementing base conversion using division and subtraction algorithms along with a bit manipulation demo. This assignment builds on that foundation with direct mappings and signed number representations.

```bash
# Compile both source files
gcc -std=c11 -Wall -Wextra -o convert.exe convert.c main.c

# Run with the Assignment 2 test cases and redirect results
.\convert.exe a2_test.txt > output.txt
