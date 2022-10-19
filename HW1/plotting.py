""" Scripts containing the plotting function and related utilities. """
from typing import Tuple, List
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm

from optimizer import surface_func


def calc_iterations(
    x_iterations: List[np.ndarray],
    A: np.ndarray, b: np.ndarray
) -> Tuple[List[np.ndarray], List[np.ndarray], List[np.ndarray]]:
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
    List[np.ndarray], List[np.ndarray], List[np.ndarray]
        returns iterations of x=[x1, x2] and calculated surface funtion values
    """
    func_value_iterations = []
    for x_iter in x_iterations:
        func_value_calc = surface_func(x_iter, [A, b])
        func_value_iterations.append(func_value_calc)
    x_iterations = np.array(x_iterations)
    x1_iterations = x_iterations[:, 0]
    x2_iterations = x_iterations[:, 1]
    return x1_iterations, x2_iterations, func_value_iterations


def calc_surface(
    plot_xlim: List[np.ndarray],
    plot_ylim: List[np.ndarray],
    A: np.ndarray,
    b: np.ndarray, plot_axis_offset: float
) -> None:
    """Calculate surface function values

    Parameters
    ----------
    plot_xlim : List[np.ndarray]
        x-axis limits of the plot
    plot_ylim : List[np.ndarray]
        y-axis limits of the plot
    A : np.ndarray
        matrix A
    b : np.ndarray
        vector b
    plot_axis_offset : float
        offset for the changes in the x and y axes of the plot

    Returns
    -------
    List[np.ndarray], List[np.ndarray], List[np.ndarray],
        x1,x2 values with their calculated surface function values for plotting
    """
    x1 = np.linspace(min(plot_xlim) - plot_axis_offset, max(plot_xlim) + plot_axis_offset, 100)
    x2 = np.linspace(min(plot_ylim) - plot_axis_offset, max(plot_ylim) + plot_axis_offset, 100)
    x1, x2 = np.meshgrid(x1, x2)
    x = x1, x2

    func_value = surface_func(x, [A, b])
    return x1, x2, func_value


def surface_plot(
        x1: List[np.ndarray],
        x2: List[np.ndarray],
        func_value: List[np.ndarray],
        x1_iterations: List[np.ndarray],
        x2_iterations: List[np.ndarray],
        func_value_iterations: List[np.ndarray],
        **kwargs) -> None:
    """Plot the surface function.

    Parameters
    ----------
    x1 : List[np.ndarray],
        x = [x1, x2]
    x2 : List[np.ndarray],
        x = [x1, x2]
    func_value: : List[np.ndarray] : List[np.ndarray],
        calculated function value
    x1_iterations : List[np.ndarray],
        iterations on first element of x vector during the minimization
    x2_iterations : List[np.ndarray],
        iterations on first element of x vector during the minimization
    func_value_iterations : List[np.ndarray],
        iterations on surface function value during the minimization
    """
    azim = kwargs.get('azim', 130)
    elev = kwargs.get('elev', 50)
    format_img = kwargs.get('format_img', 'png')
    export_path = kwargs.get('export_path', None)
    title = kwargs.get('title', '')

    fig = plt.figure()
    ax = fig.gca(projection='3d')   # Create the axes
    ax.view_init(azim=azim, elev=elev)

    # Plot the 3d surface
    ax.plot_surface(x1, x2, func_value,
                              alpha=0.5,
                              cmap=cm.coolwarm,
                              rstride=2,
                              cstride=2)

    ax.contour3D(x1, x2, func_value, colors='black')

    ax.plot(x1_iterations, x2_iterations, func_value_iterations, 'or--')

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
