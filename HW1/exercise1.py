""" 
    Exercise 1
    Runs the given optimization problem with three different methods: lgmres, BFGS, and Nelder-Mead
    Please change the metrices A, b, and initial condition x0 to run the optimization for other matrices.
"""
import numpy as np

from optimizer import solve_system, store_iterations
from plotting import calc_iterations, calc_surface, surface_plot

if __name__ == '__main__':

    print('EXERCISE 1')
    print('_______________________________________________________')
    
    A = np.array([[8, 1], [1, 3]])
    b = np.array([1, 2])
    x0 = np.array([5, 5])

    plot_axis_offset = 5
    print(f'Matrix A: {A}\nVector b: {b}\nInitial values of x: {x0}')
    print('_______________________________________________________')
    
    method = 'lgmres' # 'BFGS', 'Nelder-Mead

    x = solve_system(A, b, x0, method)
    x_iterations = store_iterations(x)
    x1_iterations, x2_iterations, funcValue_iterations = calc_iterations(x_iterations, A, b)
    x1, x2, funcValue = calc_surface(x1_iterations, x2_iterations, A, b, plot_axis_offset)
    print(f'Method is {method}, number of iterations is {len(x_iterations)}...')
    surface_plot(x1, x2, funcValue, x1_iterations, x2_iterations, funcValue_iterations, title=method)
    x_iterations = []

