# Sp4e Assignments

## HW1

## Description
Repository containing the first assignment for MATH-611: Scientific Programming for Engineers. The goal of this exercise is to get familiar with scipy and numpy module by implementing an iterative solver
and visualizing the results.

In the first exercise, scipy.optimize.minimize and scipy.sparse.linalg.lgmres routines are used to solve the minimization problem. In the second exercise, generalized minimal residual method (GMRES) technique is implemented.

## Visuals
Results for the solution with three techniques of the same problem are presented below.

As seen from Figure XX, (GMRES) method converges to the solution with less steps than the other two approaches.

## Installation
External packages are used in this project as listed below:
. numpy v.1.23.4
. scipy v.1.9.2.
. matplotlib v.3.6.1


## Usage
### The HW1 directory contains the following files:
- exercise1.py contains the main function for the exercise1
- exercise2.py contains the main function for the exercise2
- optimizer.py contains the minimzers used in exercise 1 
- plotting.py contains plotting routines
- GMRES.py contains the GMRES method implementation 


exercise1.py and exercise2.py are the main files for the exercises. All the arguments have to be manually set from inside of these two files.

## Authors
Gizem Özdil, Özge Orhan