"""
    Script to generate a CSV file for the heat distribution.
    Example usage:
    >>> python heat_distribution.py --xlim -1 1 --ylim -1 1 --pn_x 8 --pn_y 8 --radius 0.5 --filename heat_file_input.csv --plot

    File contains: [positions (N,3) velocities (N,3) force (N,3) masses (N,1) temperature (N,1) heat rate (n,3)]
"""
import argparse
import numpy as np

import matplotlib.pyplot as plt


def arg_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument('--xlim', action='store', type=float, default=[-1.,1.], nargs='+', help='Upper and lower limits for the x axis')
    parser.add_argument('--ylim', action='store', type=float, default=[-1.,1.], nargs='+', help='Upper and lower limits for the y axis')
    parser.add_argument('--pn_x', action='store', type=int, default=8, help="Number of particles in x direction")
    parser.add_argument('--pn_y', action='store', type=int, default=8, help="Number of particles in y direction")
    parser.add_argument('--plot', action='store_true', help="Plots the heat distribution")
    parser.add_argument(
        '--radius', action='store', type=float, default=0.5,
        help="Radius of the heat distribution")
    parser.add_argument(
        '--filename', action='store', default="heat_distribution.csv",
        help="Output path where the heat data will be saved")
    return parser.parse_args()

def heat_func(x, y, R):
    """ Heat function described in EX 4-5.

    Parameters
    ----------
    x : float
        x coordinates
    y : float
        y coordinates
    R : float
        radius
    """
    if  x**2 + y**2 < R:
        return 1

    return 0

def boundary_constraint(x, y, xlim, ylim):
    """ Enforces 0 temperature at the boundary and gives a random value otherwise.

    Parameters
    ----------
    x : float
        x coordinates
    y : float
        y coordinates
    xlim : NDArray
        x boundaries
    ylim : NDArray
        y boundaries
    """
    if  (x == min(xlim) or x == max(xlim) or y == min(ylim) or y == max(ylim)):
        return 0

    return np.random.randint(-10,10)


def plot_heat_distribution(nx, ny, temperature):
    """Plots the heat distribution with temperature color code.

    Parameters
    ----------
    nx : int
        Number of particlesi in x direction
    ny : int
        Number of particlesi in y direction
    temperature : NDarray
        Array containing the temperature values
    """

    fig, ax = plt.subplots()
    plt.pcolormesh(temperature.reshape((nx,ny)))
    cbar = plt.colorbar()
    cbar.set_label('temperature', rotation=90)
    plt.xlabel('Number of particles  in x')
    plt.ylabel('Number of particles in y')
    plt.title('Temperature in a grid')
    plt.show()


def main():
    args = arg_parser()

    xlim = args.xlim
    ylim = args.ylim
    pn_x = args.pn_x
    pn_y = args.pn_y
    radius = args.radius
    fname = args.filename
    plot = args.plot

    grid_size = pn_x * pn_y

    x_vals = np.linspace(xlim[0], xlim[1], pn_x)
    y_vals = np.linspace(ylim[0], ylim[1], pn_y)

    positions = np.random.random((grid_size, 3))
    velocity = np.zeros((grid_size, 3))
    force = velocity.copy()
    masses = 1e9*(np.random.random((grid_size, 1)) + 1)
    heat_rate = np.zeros((grid_size, 1))
    temperature = np.zeros((grid_size, 1))

    ind = 0
    for x in x_vals:
        for y in y_vals:
            positions[ind,:] = np.array([x,y,0])
            temperature[ind] = boundary_constraint(x,y,xlim,ylim)
            heat_rate[ind] = heat_func(x,y,radius)
            ind += 1

    file_data = np.hstack((positions, velocity, force, masses, temperature, heat_rate))
    np.savetxt(fname, file_data, delimiter=" ")
    print("Heat distribution file is saved at {}".format(fname))

    if plot:
        plot_heat_distribution(pn_x, pn_y, temperature)


if __name__ == "__main__":
    main()