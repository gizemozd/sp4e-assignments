"""
    Loads a file that contains the iteration (1st column), function values (2nd column), and
    analytic prediction of the series (3rd column) and plots the results.
    Example usage:
    >>> python plot_series.py --file_path output.csv
    >>> python plot_series.py --file_path output.psv
    >>> python plot_series.py --file_path output.txt
"""
import argparse
from typing import Tuple, List
from pathlib import Path
import csv
import numpy as np
import matplotlib.pyplot as plt

EXT_SEPARATOR = {
    ".csv": ",",
    ".psv": "|",
    ".txt": " ",
}


def arg_parser():
    """Arg parser."""
    parser = argparse.ArgumentParser(description="pipeline to input matrices")
    parser.add_argument("--file_path", type=str, help="Directory of the data file")

    return parser.parse_args()


def load_file(file_path: str) -> Tuple[List[str], np.ndarray]:
    """Loads a file (csv, txt, or psv).

    Parameters
    ----------
    file_path : str
        Path where the file to be read is.

    Returns
    -------
    np.ndarray
        Returns the file content as a (N,3) array.
        N is the number of iterations.
    """
    # Extension of the file
    path_extension = Path(file_path).suffix
    # Based on the extension, we select a delimiter
    delimiter = EXT_SEPARATOR[path_extension]

    with open(file_path) as csv_file:

        # Delimiter is used to load the file independent of its extension
        csv_reader = csv.reader(csv_file, delimiter=delimiter)
        file_data = list(csv_reader)
        # from IPython import embed; embed()
        header = file_data[0]  # read once to skip the header once
        values = file_data[1:]

    return header, np.array(values, dtype=float)


if __name__ == "__main__":

    args = arg_parser()
    header_name, file_values = load_file(args.file_path)

    # First column is the x data points
    x_axis = file_values[:, 0]
    # Second column is the series
    y_values = file_values[:, 1]
    # Third column is the analytical pred
    analytical_pred = file_values[:, 2]

    fig, ax = plt.subplots(figsize=(8, 4))

    ax.plot(
        x_axis, y_values, label=header_name[1], marker=".", lw=2.0, color="firebrick"
    )
    ax.plot(
        x_axis,
        analytical_pred,
        label=header_name[2],
        ls="--",
        lw=2.0,
        color="steelblue",
    )

    ax.legend()
    ax.grid(True)

    ax.set_xlabel("Iterations")
    ax.set_ylabel("Function value")

    plt.title("Series computation and analytic value over iterations")
    plt.show()
