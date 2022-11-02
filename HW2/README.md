# Sp4e Assignments

# Homework 2

## Description
Repository containing the second assignment for MATH-611: Scientific Programming for Engineers. The goal of this exercise is to get object oriented programming in cpp.


## Requirements
Minimum requirements and compile options are listed below:
- cmake_minimum_required (VERSION 2.8.11)
- add_compile_options(-std=c++14)

## Visuals
Results for the solution with four techniques of the same problem are presented below.


## Usage
### The HW2 directory contains the following structure:
homework2/
- src/ # contains .hh and .cc files
    - CMakeLists.txt
    - main.cc
    - ComputeArithmetic.cc/.hh
    - ComputePi.cc/.hh
    - DumperSeries.hh
    - PrintSeries.cc/.hh
    - RiemannIntegral.cc/.hh
    - Series.cc/.hh
    - WriteSeries.cc/.hh
- build/ # folder for compilation (not to be commited)
- CMakeLists.txt
- .gitignore
- README.md


### Running the program
Runs the given problem with different choices for maximum iteration, frequency, series type, output option, and separator type.
- Series types are defined as: "arithmetic", "pi"
    - "arithmetic" for arithmetic series
    - "pi" for series converging towards pi
- Output options are defined as: "print", "write"
    - "print" results in printing on terminal
    - "write" results in generating an output file
- Separator types are defined as: "comma", "pipe", "space", "tab"
    - "comma" generates a .csv file
    - "pipe" generates a .psv file
    - "space" and "tab" generates a .txt file

Please change Run>Edit configurations>Program argument within the order of  maximum iteration, frequency, series type, output option, and separator type.
An example set of program arguments for maximum 100 iteration with frequency of 10 for pi series to printing on the screen.
```cpp
"100" "10" "pi" "print" ""
```
An example set of program arguments for maximum 150 iteration with frequency of 20 for pi series to writing to an output file.
```cpp
"150" "20" "pi" "write" "comma"
```

## Authors
Pembe Gizem Özdil, Zeynep Özge Orhan

## Work division 
Since this exercise set questions were a continuation of each other, we thought that division of the work was not that easy. However, we could able to alternate the parts of the exercises among us. For example, one of us takes care of ComputeArithmetic whereas the other takes care of ComputePi. A similar division is valid for WriteSeries and PrintSeries. Similarly, one of us was responsible for documentation while the other was responsible for testing. 


