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

freq = np.fft.fftfreq(n, d=timestep)

print(freq)

"""
{
          0.      ,  0.015625,  0.03125 ,  0.046875,  0.0625  ,  0.078125,  0.09375,
          0.109375,  0.125   ,  0.140625,  0.15625 ,  0.171875,  0.1875  ,  0.203125,
          0.21875 ,  0.234375,  0.25    ,  0.265625,  0.28125 ,  0.296875,  0.3125,
          0.328125,  0.34375 ,  0.359375,  0.375   ,  0.390625,  0.40625 ,  0.421875,
          0.4375  ,  0.453125,  0.46875 ,  0.484375, -0.5     , -0.484375, -0.46875,
          -0.453125, -0.4375  , -0.421875, -0.40625 , -0.390625, -0.375   , -0.359375,
          -0.34375 , -0.328125, -0.3125  , -0.296875, -0.28125 , -0.265625, -0.25,
          -0.234375, -0.21875 , -0.203125, -0.1875  , -0.171875, -0.15625 , -0.140625,
          -0.125   , -0.109375, -0.09375 , -0.078125, -0.0625  , -0.046875, -0.03125,
          -0.015625,
}
"""