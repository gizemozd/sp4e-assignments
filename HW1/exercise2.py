""" 
    Runs the chosen optimizer with the given A matrix and vector.
    Example usage:
    >>> python exercise2.py --matrixdata_A  8 1 1 3 --nrows_A 2 --vectordata_b 2 4 --nrows_b 2 --minimizer custom_gmres

    To plot the results, simply append `--plot` to the command.

"""
import argparse
import numpy as np

from optimizer import solve_system, store_iterations
from GMRES import gmres
from plotting import calc_iterations, calc_surface, surface_plot


def arg_parser():
    """ Arg parser. """
    parser = argparse.ArgumentParser(description='pipeline to input matrices')
    parser.add_argument('--matrixdata_A', action='store', type=float, nargs='+', help='A matrix elements')
    parser.add_argument('--nrows_A', action='store', type=int, help='Number of rows of A matrix')
    parser.add_argument('--vectordata_b', action='store', type=float, nargs='+', help='b vector elements')
    parser.add_argument('--nrows_b', action='store', type=int, help='Number of rows of b vector')
    parser.add_argument('--minimizer', action='store', type=str,
                        help='Specify minimizer: custom_gmres, lgmres, BFGS etc.')
    parser.add_argument('--plot', action='store_true', default=False, help='Plot the results')

    return parser.parse_args()



def make_matrix_from_args(matrix_data, n_rows):
    """ Convert comman-line args into matrices """
    return np.array(matrix_data).reshape((n_rows, len(matrix_data) // n_rows))


if __name__ == '__main__':
    args = arg_parser()

    A = make_matrix_from_args(args.matrixdata_A, args.nrows_A)
    b = make_matrix_from_args(args.vectordata_b, args.nrows_b).flatten()
    x0 = np.zeros_like(b) + 10

    method = args.minimizer
    plot_axis_offset = 10

    if method == 'custom_gmres':
        print('Selected method is custom GMRES, running the algorithm...')
        x, _, x_iterations = gmres(A, b, x0, 800, 1e-9)
        print(f'Solution x is {x}')
    elif method in ['lgmres', 'Nelder-Mead', 'Powell', 'BFGS', 'L-BFGS-B', 'SLSQP']:
        print(f'Selected method is {method}, running the algorithm...')
        x = solve_system(A, b, x0, method)
        x_iterations = store_iterations(x)
        print(f'Solution x is {x}')
    else:
        raise NameError(f'{method} method is invalid, please choose a valid solver!')

    if args.plot:
        x1_iterations, x2_iterations, funcValue_iterations = calc_iterations(x_iterations, A, b)
        x1, x2, funcValue = calc_surface(x1_iterations, x2_iterations, A, b, plot_axis_offset)
        surface_plot(x1, x2, funcValue, x1_iterations, x2_iterations, funcValue_iterations)
