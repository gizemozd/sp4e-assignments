""" Scipts that implement the minimizer problem using SciPy. """

from typing import Tuple, List
import numpy as np
from scipy.sparse.linalg import lgmres
from scipy.optimize import minimize

x_iterations = []


def surface_func(x: np.ndarray, matrices: Tuple[np.ndarray, np.ndarray]) -> float:
    """Creates a surface function in the form:
    S(x) = (1/2) * x^T * A - x^T * b

    Parameters
    ----------
    x : np.ndarray
        x is a solution of system equation
    matrices : Tuple[np.ndarray,np.ndarray]
        Includes matrix A and vector b

    Returns
    -------
    float
        calculated function value
    """
    x1, x2 = x
    A, b = matrices
    return x1 * ((A[0, 0] * x1) / 2 + (A[1, 0]
                                       * x2) / 2) - b[1] * x2 - b[0] * x1 + x2 * ((A[0, 1] * x1) / 2 + (A[1, 1] * x2) / 2)


def store_iterations(x: np.ndarray) -> List[np.ndarray]:
    """ Stores the value of x vector at each iteration.

    Parameters
    ----------
    x : np.ndarray
        x is a solution of system equation

    Returns
    -------
    List[np.ndarray]
        contains x values at each iteration
    """
    global x_iterations
    x_iterations.append(x)
    return x_iterations


def solve_system(A: np.ndarray, b: np.ndarray, x0: np.ndarray, method: str = None) -> np.ndarray:
    """ Solves the system with a chosen method.

    Parameters
    ----------
    A : np.ndarray
        matrix A
    b : np.ndarray
        vector b
    x0 : np.ndarray
        initial values
    method : str, optional
        methods to solve the problem with an option of 'lmgres, by default minimizer

    Returns
    -------
    np.ndarray
        returns the solution of the system, x
    """
    if method == 'lgmres':
        global x_iterations
        x_iterations.append(x0)
        res, _ = lgmres(A, b, x0=x0, tol=1e-9, callback=store_iterations)
        return res
    else:
        x_iterations.append(x0)
        result = minimize(surface_func, x0, args=[A, b], tol=1e-9, method=method, callback=store_iterations)
        return result.x
