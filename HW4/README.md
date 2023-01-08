# Sp4e Assignments

# Homework 4

## Description
Repository containing the third assignment for MATH-611: Scientific Programming for Engineers. The goal of this exercise is to use an external library made for scientific computing and adapt it to our needs through a wrapping interface. FFTW library is used to code a heat equation solver.

## Requirements
Minimum requirements and compile options are listed below:
For C++:
- cmake_minimum_required (VERSION 2.8.11)
- add_compile_options(-std=c++14)
- FFTW version 3.3.10
- GoogleTest v1.12.1

For Python:
- numpy v.1.23.4
- matplotlib v.3.6.1
- csv v.1.0

## Usage
### The HW4 directory contains the following structure:
<p align="center" >
<img src="HW4/figures/classHierarchy2.png" width="600" />
</p>
Doxyfile is included in the directory, therefore the documentation can be generated using doxywizard. Generated files will be placed in /html directory.

### Running the program
Build the program as the following: 
```
cd sp4e-assignments/HW3
mkdir build
cd build 
cmake ..
make
```

------

## Authors
Pembe Gizem Özdil, Zeynep Özge Orhan

