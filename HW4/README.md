# Sp4e Assignments

# Homework 4
# TO-DO
* Check if ex 6 is working as expected. Check the locations of input output folders and pypart imports or not.
* Exercise 7.
* Read me.

## Description
Repository containing the third assignment for MATH-611: Scientific Programming for Engineers. The goal of this exercise is to use an external library Pybind11 to create Python bindingd of the C++ Particles' code.

## Requirements
Minimum requirements and compile options are listed below:
For C++:
- cmake_minimum_required (VERSION 2.8.11)
- add_compile_options(-std=c++14)
- FFTW version 3.3.10
- GoogleTest v1.12.1
- Pybind11 v2.10.3

For Python:
- numpy v.1.23.4
- matplotlib v.3.6.1
- csv v.1.0
- scipy v1.10.0

## Usage
### The HW4 directory contains the following structure:
<p align="center" >
<img src="HW4/imgs/classHierarchy.png" width="600" />
</p>
Doxyfile is included in the directory, therefore the documentation can be generated using doxywizard. Generated files will be placed in /html directory.

### Running the program
Build the program as the following:
```
cd sp4e-assignments/HW4
mkdir build
cd build
cmake ..
make
```
------
### Exercise 1

2. Overloading process allows to use the same function multiple times by passing different number of arguments.

### Exercise 2

2. The references to the Compute objects type are correctly can be managed by taking advantage of the return value policy annotations provided by Pybind11. These annotations can be passed to the module_::def() and class_::def() functions. As also suggested in the Pybind11 documentation, smart pointers can be an alternative method to manage the memory. The use of smart pointers eliminates the necessity of return value policy.

### Exercise 4

To simulate the planet trajectories for 365 days with a timestep of 1 day, run the following:
```bash
$ python3 main.py 365 1 ../init.csv planet 1
```

Note that this will require a folder called `dumps`, make sure that you create the so-called folder under the cmake folder by running the following:
```bash
mkdir dumps
````

### Exercise 5

To run the scripts for Exercise 5:
```bash
$ python exercise5.py --planet_name jupiter --directory ../dumps --directory_ref ../trajectories
$ python exercise5.py --planet_name sun --directory ../dumps --directory_ref ../trajectories --plot
$ python exercise5.py --planet_name mercury --directory ../dumps --directory_ref ../trajectories --plot
```

To plot the trajectories, simple append `--plot` to the command which will save the figure as well.

:warning: ADD SOME FIGURES HERE :warning:
<p align="center" >
<img src="HW4/imgs/eart_positions.png" width="600" />
</p>
<p align="center" >
<img src="HW4/imgs/jupiter_positions.png" width="600" />
</p>
<p align="center" >
<img src="HW4/imgs/mercury_positions.png" width="600" />
</p>

### Exercise 6

Script to launch simulation with scaled velocity input and compute the error in the trajectory.

Example usage:
```bash
$ python exercise6.py --planet_name jupiter --filename ../init_scaled.csv --nsteps 1000 --freq 10 --scale 1000
```

To plot the trajectories, simple append `--plot` to the command which will save the figure as well.

:warning: WARNING ABOUT THE DIRECTORY :warning:

### Exercise 7
Script to optimize initial velocity input and plot the evolution of the error vs the scaling factor.

Example usage:
```bash
$ python exercise7.py --planet_name mercury --filename ../init.csv --nsteps 1000 --freq 10 --scale 1000
```

:warning: WARNING ABOUT THE DIRECTORY :warning:

------

## Authors
Pembe Gizem Özdil, Zeynep Özge Orhan


