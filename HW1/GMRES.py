"""
    Contains functions to implement the GMRES method.
    This code is adapted to Python from its original MATLAB implementation:
    https://en.wikipedia.org/wiki/Generalized_minimal_residual_method

"""
from typing import Tuple, List
import numpy as np


def multiply_matrices(matrix_first, matrix_second):
    """ Matrix multiplication using einsum.
        Equivalent to matrix_first @ matrix_second
    """
    return np.einsum("ij, jk -> ik", matrix_first, matrix_second)


def find_norm(vector):
    """ Finds the norm of a vector. """
    return np.sqrt(np.einsum('k,k->', vector, vector))


def dot_product_vectors(vector_first, vector_second):
    """ Dot product of two vectors. """
    return np.einsum('i,i->', vector_first, vector_second)


def multiply_matrix_w_vector(matrix_first, matrix_second):
    """ Multiplies a matrix with a vector. """
    # If the second entry is a vector, then use a proper einsum
    if matrix_second.ndim == 1:
        return np.einsum("ij, j -> i", matrix_first, matrix_second)
    elif matrix_first.ndim == 1:
        return np.einsum("i, ij -> j", matrix_first, matrix_second)
    else:
        raise ValueError("Either first or second entry should be 1D vector")


def transpose_matrix(matrix):
    """ Takes the transpose of a matrix. """
    return np.einsum('ij->ji', matrix)


def arnoldi_function(A, Q, k):
    """ Implementation of the Arnoldi function. """
    # Take the column k of the matrix Q
    Q_k = Q[:, k - 1]  # Krylov Vector
    q = multiply_matrix_w_vector(A, Q_k)  # Modified Gram-Schmidt, keeping the Hessenberg matrix

    h = np.zeros(k + 1)

    for i in range(0, k):
        h[i] = dot_product_vectors(q.T, Q[:, i])
        q = q - h[i] * Q[:, i]

    h[k] = find_norm(q)
    q = q / h[k]

    return h, q


def apply_givens_rotation(h, cs, sn, k):
    """ Apply Givens rotation to H column. """
    # Apply for the ith column
    for i in range(0, k - 1):
        temp = cs[i] * h[i] + sn[i] * h[i + 1]
        h[i + 1] = -sn[i] * h[i] + cs[i] * h[i + 1]
        h[i] = temp
        # h[i+1], h[i] = -sn[i] * h[i] + cs[i] * h[i+1], cs[i] * h[i] + sn[i] * h[i+1]

    # update the next sin cos values for rotation
    cs_k, sn_k = givens_rotation(h[k - 1], h[k])

    # eliminate H(i + 1, i)
    h[k - 1] = cs_k * h[k - 1] + sn_k * h[k]
    h[k] = 0.0
    return h, cs_k, sn_k


def givens_rotation(v1, v2):
    """ Calculate the Givens rotation matrix. """
    if v1 == 0 and v2 == 0:
        cs, sn = 0, 0
    else:
        t = np.sqrt(v1**2 + v2**2)
        cs, sn = v1 / t, v2 / t

    return cs, sn


def gmres(
    A: np.ndarray, b: np.ndarray,
    x: np.ndarray,
    max_iter: int = 1e3,
    threshold: float = 1e-9
) -> Tuple[np.ndarray, List[float], List[np.ndarray]]:
    """ Solves the linear system of equations by using generalized minimal residual method.

    Parameters
    ----------
    A : np.ndarray
        matrix A
    b : np.ndarray
        vector b
    x : np.ndarray
        initial values
    max_iter : int, optional
        maximum number of iterations to solve the system, by default 1e3
    threshold : float, optional
        threshold of error to stop the iterations, by default 1e-9

    Returns
    -------
    Tuple[np.ndarray, List[float], List[np.ndarray]]
        returns the solution x, a list containing the error over iterations,
        and list containing the solution x at each iteration
    """
    x_iterations = [x]

    # use x as the initial vector
    r = b - multiply_matrix_w_vector(A, x)

    b_norm = find_norm(b)
    error = find_norm(r) / b_norm

    # initialize the 1D vectors
    sn = np.zeros((max_iter, 1))
    cs = np.zeros((max_iter, 1))

    # e1 = zeros(n, 1);
    e1 = np.zeros((max_iter + 1, 1))
    e1[0] = 1
    e = [error]
    r_norm = find_norm(r)

    Q = np.zeros((r.shape[0], max_iter + 1))
    H = np.zeros((max_iter + 2, max_iter))

    Q[:, 0] = r / r_norm
    beta = r_norm * e1

    # Note: this is not the beta scalar in section "The method" above but the beta scalar multiplied by e1
    for k in range(0, max_iter):
        # Arnoldi
        H[:k + 2, k], Q[:, k + 1] = arnoldi_function(A, Q, k + 1)

        #  eliminate the last element in H ith row and update the rotation matrix
        H[:k + 2, k], cs[k], sn[k] = apply_givens_rotation(H[:k + 2, k], cs, sn, k + 1)

        #  update the residual vector
        beta[k + 1] = -sn[k] * beta[k]
        beta[k] = cs[k] * beta[k]
        error = abs(beta[k + 1]) / b_norm

        e.append(error)

        if error <= threshold:
            break

        H_inv = np.linalg.inv(H[:k + 1, :k + 1])
        y = multiply_matrices(H_inv, beta[:k + 1])
        x_current = x + multiply_matrices(Q[:, :k + 1], y).reshape(x.shape)
        x_iterations.append(x_current)

    H_inv = np.linalg.inv(H[:k + 1, :k + 1])
    y = multiply_matrices(H_inv, beta[:k + 1])
    x = x + multiply_matrices(Q[:, :k + 1], y).reshape(x.shape)
    x_iterations.append(x)

    return x, e, x_iterations
