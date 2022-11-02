# Sp4e Assignments

# Homework 2

## Description
Repository containing the second assignment for MATH-611: Scientific Programming for Engineers. The goal of this exercise is to get familiar with the concepts related to object oriented programming in C++.

## Requirements
Minimum requirements and compile options are listed below:
For C++:
- cmake_minimum_required (VERSION 2.8.11)
- add_compile_options(-std=c++14)

For Python:
- numpy v.1.23.4
- matplotlib v.3.6.1
- csv v.1.0

## Usage
### The HW2 directory contains the following structure:
HW2/
- src/ # Contains .hh and .cc files
    - ```CMakeLists.txt:``` contains the executable file names to run CMake
    - ```main.cc:``` main code where all the exercises can be run
    - ```ComputeArithmetic.{cc,hh}:``` computes the terms and summation of the arithmetic series (Exercise 2)
    - ```ComputePi.{cc,hh}:``` computes the terms and summation of the pi series (Exercise 2)
    - ```DumperSeries.hh:``` base class for the dumper series (Exercise 3)
    - ```PrintSeries.{cc,hh}:``` prints out the iteration number, result of the series and its convergence (Exercise 3) 
    - ```RiemannIntegral.{cc,hh}:``` calculates the discretized integral of a given function for a specific interval (Exercise 6)
    - ```Series.{cc,hh}:``` base class for the series (Exercise 2)
    - ```WriteSeries.{cc,hh}:``` writes iteration number, series summation, and convergence into a file of given format (Exercise 3) 
- build/ # folder for compilation (not to be commited)
- ```plot_series.py:``` Loads the results saved in Ex. 5 in any foramt (.psv, .csv, or .txt) and plots them.  
- CMakeLists.txt
- .gitignore
- README.md

### Running the program
Build the program as the following: 
```
cd sp4e-assignments/HW2
mkdir build
cd build 
cmake ..
make
```
### Series
To run the series operations the arguments needed are the following:
- ```exerciseType```: "series"
- ```maxIter```: maximum number of iterations that the series will be run.
- ```freq```: frequency at which the series summation will be printed/written.
- ```seriesType```: type of series, choose "arithmetic" or "pi"
    - "arithmetic" for arithmetic series
    - "pi" for series converging towards pi
- ```separatorType```: separator used in the write IO, choose "comma" "pipe" "space" "tab"
    - "comma" generates a .csv file
    - "pipe" generates a .psv file
    - "space" and "tab" generates a .txt file
- ```outputOption```: defines how the results will be given, "print", "write"
    - "print" results in printing on terminal
    - "write" results in generating an output file called "output"

An example set of program arguments for maximum 100 iteration with frequency of 10 for pi series to printing on the screen.
```cpp
./src/HW2 "series" "100" "10" "pi" "print" ""
```
An example set of program arguments for maximum 100 iteration with frequency of 10 for arithmetic series to printing on the screen.
```cpp
./src/HW2 "series" "100" "10" "arithmetic" "print" ""
```
An example set of program arguments for maximum 150 iteration with frequency of 20 for pi series to writing to a CSV output file.
```cpp
./src/HW2 "series" "150" "20" "pi" "write" "comma"
```
An example set of program arguments for maximum 150 iteration with frequency of 20 for arithmetic series to writing to a TXT file.
```cpp
./src/HW2 "series" "150" "20" "arithmetic" "write" "space"
```

To plot the numerical results saved by ```WriteSeries``` class, go to ```HW2``` directory and run:
```python
python plot_series.py --file_path output.csv
python plot_series.py --file_path output.psv
python plot_series.py --file_path output.txt
```

Sample output results after having run the Pi series are already given in the folder. If the command above is run on one of the sample data files, the resulting plot will be the following:
<p align="center">
<img src="HW2/figures/SeriesPi.png" width="650" />
</p>

### Riemann Integral

To run the integral operations the arguments needed are the following:
- ```exerciseType```: "integral"
- ```lowerLimit```: lower limit of the definite integral.
- ```upperLimit```: upper limit of the definite integral.
- ```functionType```: type of the function inside the integral.
    - "cos" for cosine
    - "sin" for sine
    - "cube" for cubic function.

An example set of program arguments for taking the integral of a cubic function from 0 to 1.
```cpp
./src/HW2 integral 0 1 cube
```
An example set of program arguments for taking the integral of a cosine function from 0 to pi.
```cpp
./src/HW2 integral 0 3.14159 cos
```
An example set of program arguments for taking the integral of a sine function from 0 to pi/2.
```cpp
./src/HW2 integral 0 1.5707  sin
```

------
## Answers to the questions

**Exercise 2.1:** 
_What is the best way/strategy to divide the work among yourselves?_

After writing the base ```Series``` Class together, we divided the workload among us based on the series type. One of us wrote the code for computing the Pi series whereas the other implemented the arithmetic series. Since the implementation of the arithmetic series was relatively easier, that person also was responsible for testing and documenting the code. For the rest of the project, we followed a similar strategy: we allocated the Exercise 3 into Write and Print, so each could implement a class indepently. Then, the person who finished earlier continued with the documentation and testing.

**Exercise 5.1:** 
_Evaluate the global complexity of your program._

In the previous case of the implementation, we calculated the sum of series as the following: for index i between 1 and N, we stored a common "sum" variable in the class, and increased it by ith term. Therefore, global complexity of calculating the sum was O(n). In addition, we calculated the sum at each given frequency by calculating the entire series from stracth, which makes the overall complexity O(n^2). Note that the complexity converges to O(n) when the frequency is so low that the series is calculated only a few times. 

**Exercise 5.4:** 
_Evaluate the global complexity of your program._

As we have computed the entire series only once and accesing the result at a given frequency, the complexity is now $O(n\n)$.

**Exercise 5.5:** 
_In the case you want to reduce the rounding errors over floating point operation by summing terms
reversely, what is the best complexity you can achieve ?_

In this case, that will again increase the complexity to O(n) because at each frequency the sum operation will be executed. 

**Exercise 6.4:** 
_Do you get the values expected ? For each function, at which value of N do you get the value expected
(~2 digits after the decimal point)?_
Case 1 - cube - min N needed: 1e2 for 2 digits: 0.255025
Case 2 - cosine - min N needed: 1e3 for 2 digits: -0.00314159
Case 3 - sine - min N needed: 1e2 for 2 digits: 1.00266

----

## Authors
Pembe Gizem Özdil, Zeynep Özge Orhan
