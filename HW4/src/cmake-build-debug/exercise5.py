"""
Script to compare planet positions.

Example usage:
>>> python exercise5.py --planet_name jupiter --directory dumps --directory_ref trajectories
>>>  python exercise5.py --planet_name sun --directory dumps --directory_ref trajectories --plot
>>>  python exercise5.py --planet_name mercury --directory dumps --directory_ref trajectories --plot

To plot the trajectories, simple append `--plot` to the command which will save the figure as well.

"""
import argparse

import csv
from pathlib import Path
import numpy as np
import matplotlib.pyplot as plt


def readPosition(planet_name: str, csv_file_path: str) -> np.ndarray:
    """Reads the position of the planet from a given CSV file.

    Parameters
    ----------
    planet_name : str
        Name of the planet.
    directory : str
        The path of the step-0000x.csv file.

    Returns
    -------
    np.ndarray
        Position of the planet at one time step.
    """
    with open(csv_file_path, 'r') as file:
        csvreader = csv.reader(file, delimiter=' ')

        for row in csvreader:
            if planet_name.lower() in row:
                # drop empty elements
                new_row = [x for x in row if x != '']
                return np.array(new_row[:3], dtype=float)


def readPositions(planet_name: str, directory: str) -> np.ndarray:
    """Reads the position of the planet from all the files in a given directory.

    Parameters
    ----------
    planet_name : str
        Name of the planet.
    directory : str
        The path of the step-0000x.csv file.

    Returns
    -------
    np.ndarray
        Position of the planet for the entire course of the simulation.
    """
    csv_file_names = sorted(Path(directory).rglob('step-*.csv'))
    ndays = len(csv_file_names)
    planet_trajectory = np.empty((ndays, 3))

    for i, csv_file_name in enumerate(csv_file_names):
        planet_trajectory[i] = readPosition(planet_name, csv_file_name)

    return planet_trajectory


def computeError(positions: np.ndarray, positions_ref: np.ndarray) -> float:
    """Computes the error between the computed trajectory and the reference one.

    Parameters
    ----------
    positions : np.ndarray
        Computed trajectory.
    positions_ref : np.ndarray
        Reference trajectory.

    Returns
    -------
    float
        Error between the computed trajectory and the reference one.
    """
    return np.sqrt(np.sum((np.linalg.norm(positions - positions_ref, axis=1)**2)))


def compute(planet_name: str, directory: str, directory_ref: str, plot: int):
    # Read the positions from given directories
    positions = readPositions(planet_name, directory)
    print(positions)
    positions_ref = readPositions(planet_name, directory_ref)
    # Compute the error between the reference and the computed trajectories
    error = computeError(positions, positions_ref)
    print(f'Error is in {planet_name} trajectory is: {error}')

    if plot:
        fig, axs = plt.subplots(1, 3, figsize=(12, 3))
        for i, ax_name in enumerate(['x', 'y', 'z']):
            axs[i].plot(positions[:, i], label='computed', lw=1.7, color='firebrick')
            axs[i].plot(positions_ref[:, i], ':', label='reference', lw=1.7, color='steelblue')
            axs[i].set_ylabel(ax_name)
            axs[i].set_xlabel('Days [#]')

        axs[2].legend()
        plt.suptitle(f'{planet_name} position (error: {round(error,3)})')
        fig.savefig(f'{planet_name}_positions.png')
        plt.tight_layout()
        plt.show()