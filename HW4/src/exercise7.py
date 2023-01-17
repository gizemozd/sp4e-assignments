"""
Script to optimize initial velocity input and plot the evolution of the error vs the scaling factor.

Example usage:
>>>  python3 exercise7.py --planet_name mercury --filename init.csv --nb_steps 365 --freq 1 --max_iter 10 --init_guess 1

"""

import argparse

import numpy as np
import matplotlib.pyplot as plt
import scipy.optimize

from exercise6 import generateInput, launchParticles, runAndComputeError
from scipy import optimize


def optimization(planet_name: str, filename: str, nb_steps: int, freq: int, max_iter: int, init_guess:int, plot: int):
    opt_init_vel, fopt, iter, funcalls, warnflag, allvecs = optimize.fmin(runAndComputeError,
                                                                          [init_guess],
                                                                          args=(planet_name, filename, nb_steps, freq),
                                                                          maxiter=max_iter,
                                                                          full_output=True,
                                                                          retall=True,
                                                                          disp=True,
                                                                          xtol=1e-4, ftol=1e-4
                                                                          )

    scalings = allvecs
    errors = np.zeros(len(scalings))

    # Calculate errors wrt to scaling factor at each optimization step
    for i, scaling in enumerate(scalings):
        errors[i] = runAndComputeError(scaling, planet_name, filename, nb_steps, freq)
    print('errors:', errors)
    print('scalings:', scalings)

    # Err vs scaling plot
    plt.figure()
    plt.semilogy(scalings, errors, marker=".")
    plt.xlabel("scaling")
    plt.ylabel("error")
    plt.grid()
    plt.show()
