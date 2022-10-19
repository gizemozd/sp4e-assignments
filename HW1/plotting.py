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
        contains the x values during the minimization steps
    A : np.ndarray
        matrix A
    b : np.ndarray
        vector b

    Returns
    -------
    _type_
        returns iterations of x=[x1, x2] and calculated surface funtion values
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
        x-axis limits
    plotylim : List[np.ndarray]
        y-axis limits
    A : np.ndarray
        matrix A
    b : np.ndarray
        vector b
    plotAxisOffset : float
        offset for the changes in the x and y axes of the plot

    Returns
    -------
    _type_
        x1,x2 values with their calculated surface function values for plotting
    """
    x1 = np.linspace(min(plotxlim) - plotAxisOffset, max(plotxlim) + plotAxisOffset, 100)
    x2 = np.linspace(min(plotylim) - plotAxisOffset, max(plotylim) + plotAxisOffset, 100)
    x1, x2 = np.meshgrid(x1, x2)
    x = x1, x2

    funcValue = surface_func(x, [A, b])
    return x1, x2, funcValue


def surface_plot(x1, x2, funcValue, x1_iterations, x2_iterations, funcValue_iterations, **kwargs):
    """Plot the surface function.

    Parameters
    ----------
    x1 : _type_
        x = [x1, x2]
    x2 : _type_
        x = [x1, x2]
    funcValue : _type_
        calculated function value
    x1_iterations : _type_
        iterations on first element of x vector during the minimization
    x2_iterations : _type_
        iterations on first element of x vector during the minimization
    funcValue_iterations : _type_
        iterations on surface function value during the minimization
    """
    azim = kwargs.get('azim',130)
    elev = kwargs.get('elev',50)
    format_img = kwargs.get('format_img', 'png')
    export_path = kwargs.get('export_path', None)
    title = kwargs.get('title', '')

    fig = plt.figure()
    ax = fig.gca(projection='3d')   # Create the axes
    ax.view_init(azim=azim, elev=elev)

    # Plot the 3d surface
    surface = ax.plot_surface(x1, x2, funcValue,
                              alpha=0.5,
                              cmap=cm.coolwarm,
                              rstride=2,
                              cstride=2)

    surface = ax.contour3D(x1, x2, funcValue, colors='black')

    ax.plot(x1_iterations, x2_iterations, funcValue_iterations, 'or--')

    # Set some labels
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('function value')

    ax.grid(False)

    ax.set_title(title.replace('_', ' '))

    # Save the figures if export path is given
    if export_path is not None:
        fig.savefig(export_path, bbox_inches='tight', format=format_img)
        print(f'Figure is saved at {export_path}')

    plt.show()
