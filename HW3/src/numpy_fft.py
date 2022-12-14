"""
    Run this script to obtain the fourier frequencies using numpy.
    Set the size of the array to print frequencies for different matrices.
"""

import numpy as np
import matplotlib.pyplot as plt

N = 64
k = 2 * np.pi / N

complex_array = np.zeros((N,N))

for i in range(0, N):
    for j in range(0, N):
        complex_array[i,j] = np.cos(k * i)

# Visualize the signal

fig, ax = plt.subplots()
# Row-wise
for i in range(0, N):
    ax.plot(complex_array[:,i], alpha=0.5)

plt.title('Row wise signals')
plt.show()

fig, ax = plt.subplots()
# Column-wise
for i in range(0, N):
    ax.plot(complex_array[i,:], alpha=0.5)

plt.title('Column wise signals')
plt.show()

signal = complex_array[:,0]

fourier = np.fft.fft(signal)
n = signal.size
timestep = 1

freq = np.fft.fftfreq(n, d=timestep) * n

print(freq)
