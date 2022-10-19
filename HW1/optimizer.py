""" Scipts that implement the minimizer problem using SciPy. """

from typing import Tuple, List
import numpy as np
from scipy.sparse.linalg import lgmres
from scipy.optimize import minimize

x_iterations = []


def surface_func(x: np.ndarray, matrices: Tuple[np.ndarray, np.ndarray]) -> float:
    """Creates a surface function in the form:
    ... formula here

    Parameters
    ----------
    x : np.ndarray
        _description_
    matrices : Tuple[np.ndarray,np.ndarray]
        _description_

    Returns
    -------
    float
        _description_
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
        _description_

    Returns
    -------
    List[np.ndarray]
        _description_
    """
    global x_iterations
    x_iterations.append(x)
    return x_iterations


def solve_system(A: np.ndarray, b: np.ndarray, x0: np.ndarray, method: str = None) -> np.ndarray:
    """ Solves the system with a chosen method.

    Parameters
    ----------
    A : np.ndarray
        _description_
    b : np.ndarray
        _description_
    x0 : np.ndarray
        _description_
    method : str, optional
        _description_, by default None

    Returns
    -------
    np.ndarray
        _description_
    """
    if method == 'lgmres':
        x, _ = lgmres(A, b, callback=store_iterations)
        return x
    else:
        result = minimize(surface_func, x0, args=[A, b], tol=1e-9, method=method, callback=store_iterations)
        return result.x
