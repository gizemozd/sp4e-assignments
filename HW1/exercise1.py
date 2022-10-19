""" Exercise 1. """
import numpy as np

from optimizer import solve_system, store_iterations
from plotting import calc_iterations, set_limits, calc_surface, surface_plot

if __name__ == '__main__':

    print('################### EXERCISE 1 ###################')
    
    A = np.array([[8, 1], [1, 3]])
    b = np.array([1, 2])
    x0 = np.array([0, 0])
    # x_iterations = [x0]
    plotAxisOffset = 2
    method = 'lgmres'

    x = solve_system(A, b, x0, method)
    x_iterations = store_iterations(x)
    x1_iterations, x2_iterations, funcValue_iterations = calc_iterations(x_iterations, A, b)
    plotxlim, plotylim = set_limits(x1_iterations, x2_iterations)
    x1, x2, funcValue = calc_surface(plotxlim, plotylim, A, b, plotAxisOffset)
    surface_plot(x1, x2, funcValue, x1_iterations, x2_iterations, funcValue_iterations)
