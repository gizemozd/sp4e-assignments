# Sp4e Assignments

## HW1

## Description
Repository containing the first assignment for MATH-611: Scientific Programming for Engineers. The goal of this exercise is to get familiar with scipy and numpy modules by implementing an iterative solver
and visualizing the results.

In the first exercise, scipy.optimize.minimize and scipy.sparse.linalg.lgmres routines are used to solve the minimization problem. In the second exercise, the generalized minimal residual method (GMRES) technique is implemented.

## Visuals
Results for the solution with three techniques of the same problem are presented below.

The solution to the quadratic surface function with different minimization methods is presented the below figures. These figures are obtained where A = ([8, 1] [1, 3]), b = ([2, 4]) with initial condition x0 = ([10, 10]). 
As seen from the presented figures LMGRES and GMRES methods converge to the solution with fewer steps than the other approaches. The comparison between LGMRES and GMRES could yield a different result once the system parameters or initial conditions are changed.
<p align="center">
<img src="HW1/figures/BFGS.png" width="200" />
<img src="HW1/figures/custom.png" width="200" />
<img src="HW1/figures/lgmres.png" width="200" />
<img src="HW1/figures/neldermead.png" width="200" />
</p>

## Installation
External packages are used in this project as listed below:
- numpy v.1.23.4
- scipy v.1.9.2.
- matplotlib v.3.6.1


## Usage
### The HW1 directory contains the following files:
- exercise1.py contains the main function for the exercise1
- exercise2.py contains the main function for the exercise2
- optimizer.py contains the minimizers used in exercise 1 
- plotting.py contains plotting routines
- GMRES.py contains the GMRES method implementation 


exercise1.py and exercise2.py are the main files for the exercises. All the arguments have to be manually set from inside these two files.

## Authors
Gizem Özdil, Özge Orhan