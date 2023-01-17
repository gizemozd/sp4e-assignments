# Sp4e Assignments

# Homework 4

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
$ python3 main.py --exercise main  --nb_steps 365 --freq 1 --filename ../init.csv --particle_type planet --timestep 1
```
The required arguments to run this exercise:
- ```--exercise```: specify the name of the exercise
    - "main" to ensure the script works for all types of particle 
    - "compute" to compare planet positions
    - "launchsim" to launch simulation with scaled velocity input and compute the error in the trajectory
    - "optimize" to optimize initial velocity input and plot the evolution of the error vs the scaling factor
- ```--nb_steps```: specify the number of steps to perform
- ```--freq```: specify the frequency for dumps
- ```--filename```: start/input filename
- ```--particle_type```: particle type
- ```--timestep```: timestep

Note that this will require a folder called `dumps`, make sure that you create the so-called folder under the cmake folder by running the following:
```bash
mkdir dumps
````

### Exercise 5 - Compute

To run the scripts for Exercise 5:
```bash
$ python3 main.py --exercise compute --planet_name jupiter --directory dumps --directory_ref trajectories
$ python3 main.py --exercise compute --planet_name sun --directory dumps --directory_ref trajectories --plot
$ python3 main.py --exercise compute --planet_name mercury --directory dumps --directory_ref trajectories --plot
```
To plot the trajectories, simple append `--plot` to the command which will save the figure as well.

The required arguments to run this exercise:
- ```--exercise```: specify the name of the exercise
    - "main" to ensure the script works for all types of particle 
    - "compute" to compare planet positions
    - "launchsim" to launch simulation with scaled velocity input and compute the error in the trajectory
    - "optimize" to optimize initial velocity input and plot the evolution of the error vs the scaling factor
- ```--directory```: specify the directory containing the output files
- ```--directory_ref```:  specify the directory containing the reference output files
- ```--plot```: plot the resulting trajectories

Calculated positions and the reference positions for the tJupiter and Mercury is presented in the below figures:
<p align="center" >
<img src="HW4/imgs/jupiter_positions.png" width="600" />
</p>
<p align="center" >
<img src="HW4/imgs/mercury_positions.png" width="600" />
</p>

### Exercise 6 - Launch Simulation

Script to launch simulation with scaled velocity input and compute the error in the trajectory.

Example usage:
```bash
$ python3 main.py --exercise launchsim --planet_name jupiter --filename ../init.csv --nb_steps 365 --freq 1 --scale 1
$ python3 main.py --exercise launchsim --planet_name mercury --filename ../init.csv --nb_steps 365 --freq 1 --scale 100 --plot
```
To plot the trajectories, simple append `--plot` to the command which will save the figure as well.

The required arguments to run this exercise:
- ```--exercise```: specify the name of the exercise
    - "main" to ensure the script works for all types of particle 
    - "compute" to compare planet positions
    - "launchsim" to launch simulation with scaled velocity input and compute the error in the trajectory
    - "optimize" to optimize initial velocity input and plot the evolution of the error vs the scaling factor
- ```--planet_name```: specify the name of the planet
- ```--filename```: start/input filename
- ```--nb_steps```: specify the number of steps to perform
- ```--freq```: specify the frequency for dumps
- ```--scale```: spescale factor for the velocity
- ```--plot```: plot the resulting trajectories

The effect of the scaling factor for the position calculations can be seen as a comparison between the below figures:
<p align="center" >
<img src="HW4/imgs/earthSimulationScale1.png" width="600" />
</p>
<p align="center" >
<img src="HW4/imgs/earthSimulationScale10.png" width="600" />
</p>

### Exercise 7
Script to optimize initial velocity input and plot the evolution of the error vs the scaling factor.

Example usage:
```bash
$ python3 main.py --exercise optimization --planet_name mercury --filename ../init.csv --nb_steps 365 --freq 1 --max_iter 20 --init_guess 5 --plot
```
To plot the trajectories, simple append `--plot` to the command which will save the figure as well.

The required arguments to run this exercise:
- ```--exercise```: specify the name of the exercise
    - "main" to ensure the script works for all types of particle 
    - "compute" to compare planet positions
    - "launchsim" to launch simulation with scaled velocity input and compute the error in the trajectory
    - "optimize" to optimize initial velocity input and plot the evolution of the error vs the scaling factor
- ```--planet_name```: specify the name of the planet
- ```--filename```: start/input filename
- ```--nb_steps```: specify the number of steps to perform
- ```--freq```: specify the frequency for dumps
- ```--max_iter```: maximum iteration for the optimization
- ```--init_guess```: initial guess for the optimization
- ```--plot```: plot the resulting trajectories

Mercury positions are plotted with given initial velocity as shown in the below figure.
<p align="center" >
<img src="HW4/imgs/mercuryPositionsbeforeOpt.png" width="600" />
</p>
<p align="center" >

After running the optimization routine, mercury positions are calculated to verify the optimization result. By using optimization result as initial velocity, the calculated mercury positions are presented in the below figure:
<img src="HW4/imgs/mercuryPositionsafterOpt.png" width="600" />
</p>

The calculated scaling factors during the optimization for the initial velocity can be presented as:
<p align="center" >
<img src="HW4/imgs/optimizationSteps.png" width="400" />
</p>
------

## Authors
Pembe Gizem Özdil, Zeynep Özge Orhan
