""" Scripts containing the plotting function and related utilities. """
from typing import Tuple, List
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm

from optimizer import surface_func


def calc_iterations(x_iterations: List[np.ndarray], A: np.ndarray, b: np.ndarray):
    """Calculate function value for the iterations

    Parameters
    ----------
    x_iterations : List[np.ndarray]
        _description_
    A : np.ndarray
        _description_
    b : np.ndarray
        _description_

    Returns
    -------
    _type_
        _description_
    """
    funcValue_iterations = []
    for x_iter in x_iterations:
        funcValue_calc = surface_func(x_iter, [A, b])
        funcValue_iterations.append(funcValue_calc)
    x_iterations = np.array(x_iterations)
    x1_iterations = x_iterations[:, 0]
    x2_iterations = x_iterations[:, 1]
    return x1_iterations, x2_iterations, funcValue_iterations


def calc_surface(plotxlim: List[np.ndarray], plotylim: List[np.ndarray],
                 A: np.ndarray, b: np.ndarray, plotAxisOffset: float) -> None:
    """Calculate surface function values

    Parameters
    ----------
    plotxlim : List[np.ndarray]
        _description_
    plotylim : List[np.ndarray]
        _description_
    A : np.ndarray
        _description_
    b : np.ndarray
        _description_
    plotAxisOffset : float
        _description_

    Returns
    -------
    _type_
        _description_
    """
    x1 = np.linspace(min(plotxlim) - plotAxisOffset, max(plotxlim) + plotAxisOffset, 100)
    x2 = np.linspace(min(plotylim) - plotAxisOffset, max(plotylim) + plotAxisOffset, 100)
    x1, x2 = np.meshgrid(x1, x2)
    x = x1, x2

    funcValue = surface_func(x, [A, b])
    return x1, x2, funcValue


def surface_plot(x1, x2, funcValue, x1_iterations, x2_iterations, funcValue_iterations):
    """Plot the surface function.

    Parameters
    ----------
    x1 : _type_
        _description_
    x2 : _type_
        _description_
    funcValue : _type_
        _description_
    x1_iterations : _type_
        _description_
    x2_iterations : _type_
        _description_
    funcValue_iterations : _type_
        _description_
    """
    fig = plt.figure()
    ax = fig.gca(projection='3d')   # Create the axes

    # Plot the 3d surface
    surface = ax.plot_surface(x1, x2, funcValue,
                              alpha=0.5,
                              cmap=cm.coolwarm,
                              rstride=2,
                              cstride=2)

    surface = ax.contour3D(x1, x2, funcValue)

    # ax.scatter3D(x1_iterations, x2_iterations, funcValue_iterations, linewidths=5);
    ax.plot(x1_iterations, x2_iterations, funcValue_iterations, 'or--')

    ax.view_init(30, 180)

    # Set some labels
    ax.set_xlabel('x1')
    ax.set_ylabel('x2')
    ax.set_zlabel('Function Value')

    plt.show()