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
### Executing particles code
```python
cd cmake-build-debug
./hw3 10 1 ../heat_file.csv material_point 0.0001
```

### Executing heat_distribution.py
```python
python heat_distribution.py --xlim -1 1 --ylim -1 1 --pn_x 8 --pn_y 8 --radius 0.5 --filename heat_file_input.csv
```
where
- ```xlim```: shows lower and upper limit of x coordinates
- ```ylim```: shows lower and upper limit of y coordinates
- ```pn_x```: shows the number of particles in x direction
- ```pn_y```: shows the number of particles in y direction
- ```radius```: shows the radius of the heat distribution
- ```filename```: shows the name of the output file and its path


### Interface Implementation
FFTW wrapping interface has been implemented and tests are prepared to verify the results.

**Executing test of FFTW implementation:**
```cpp
cd cmake-build-debug
./test_fft
```

### Solver Implementation
A solver for a transient heat equation is implemented and tests are prepared to verify the results.

**Executing test of temperature computation implementation:**
```cpp
cd cmake-build-debug
./test_temp
```
------
## Answers to the questions

**Exercise 1.1:** 
_Describe in your README how the particles are organized in the various objects?_
<p align="center" >
<img src="HW3/figures/classHierarchy3.png" width="800" />
</p>
MaterialPointsFactory and MaterialPoint are the child classes of ParticlesFactoryInterface and Particle classes, respectively. Three different type of objects are inherited from each of these two base clasess.



**Exercise 4.5:** 
_Implement a python script to generate a heat distribution within a provided radius as given in Equation 5.Explain in the README how you integrate this condition within the existing code._

A circular heat distribution is generated with $`x^2 + y^2 < R`$ formula. As a result a CSV file for the heat distribution is generated with the information of positions, velocity, force, masses, temperature, ad heat rate. Generated CSV file is utilized as an input file for the simulation through Paraview. 

In the exercise a boundary condition for temperature field is given such that it should be zero at the boundry of the domain and not evolve with time. To integrate this boundry condition ```isBoundary``` is declared in ```material_point``` as a boolean. Through this boolean member, temperature is set to zero to enforce this condition while computing the temperatures at the boundries. 

**Exercise 4.6:** 
_Describe how to launch such a stimulation which will produce dumps observable with Paraview for a grid of 512 × 512 particles._

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
<img src="HW3/figures/rendering.png" width="1000" />
</p>
----

## Authors
Pembe Gizem Özdil, Zeynep Özge Orhan

