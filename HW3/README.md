# Sp4e Assignments

# Homework 3

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
### The HW3 directory contains the following structure:
<p align="center" >
<img src="HW3/figures/classHierarchy2.png" width="600" />
</p>
Doxyfile is included in the directory, therefore the documentation can be generated using doxywizard.

### Running the program
Build the program as the following: 
```
cd sp4e-assignments/HW3
mkdir build
cd build 
cmake ..
make
```
### Executing generate_input.py

### Executing heat_distribution.py


### Interface Implementation


### Solver Implementation


------
## Answers to the questions

**Exercise 1.1:** 
_Describe in your README how the particles are organized in the various objects?_
<p align="center" >
<img src="HW3/figures/classHierarchy3.png" width="600" />
</p>
MaterialPointsFactory and MaterialPoint are the child classes of ParticlesFactoryInterface and Particle classes, respectively. Three different type of objects are inherited from each of these two base clasess.


**Exercise 4.5:** 
_Implement a python script to generate a heat distribution within a provided radius as given in Equation
5.Explain in the README how you integrate this condition within the existing code._



**Exercise 4.6:** 
_Describe how to launch such a stimulation which will produce dumps observable with Paraview for a
grid of 512 × 512 particles._
Required steps to launch the simulation with Paraview:
1. File > Open > 'heat_file_input.csv' > Open Data With CSV Reader
2. In the Properties window
    - Deselect 'Have Headers'
    - Change 'Field Delimiter Characters' to space as ' '
    - Click on Apply
3. On the menu, go to Filters > Search and search for 'Table to Points' and press enter
4. In the Properties window 
    - Choose X,Y, and Z columns as Field 0, Field 1, and Field 2, respectively
    - Select 2D points
    - Click Apply
    - Under Display (GeometryRepresentation) change Coloring to Field 10 for temperature visulatization, Field 11 for the heat visualization
    - Click show/hide color legend for the legend

Sample results from with random temperature field rendering is presented below:
<p align="center" >
<img src="HW3/figures/rendering.png" width="600" />
</p>
----

## Authors
Pembe Gizem Özdil, Zeynep Özge Orhan

