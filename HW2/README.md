# Sp4e Assignments

## HW2

## Description
Folder containing the first assignment for MATH-611: Scientific Programming for Engineers. The goal of this exercise is to ...

In the first exercise, ....

## Visuals
Results for the solution with three techniques of the same problem are presented below.


<p align="center">
<img src="HW1/figures/BFGS.png" width="200" />
</p>

## Installation
External packages are used in this project as listed below:
- numpy v.1.23.4
- matplotlib v.3.6.1

## Usage
### The HW2 directory contains the following files:
- exercise1.py contains the main function for the exercise1
- exercise2.py contains the main function for the exercise2
- optimizer.py contains the minimizers used in exercise 1
- plotting.py contains plotting routines
- GMRES.py contains the GMRES method implementation


### Running the program
Exercise 1: Runs the given optimization problem with three different methods: lgmres, BFGS, and Nelder-Mead. Please change the metrices A, b, and initial condition x0 to run the optimization for other matrices.
Exercise 2: Runs the chosen optimizer with the given A matrix and vector.
Example usage:
```
python exercise2.py --matrixdata_A  8 1 1 3 --nrows_A 2 --vectordata_b 2 4 --minimizer custom_gmres
```


## Authors
Pembe Gizem Özdil, Zeynep Özge Orhan

