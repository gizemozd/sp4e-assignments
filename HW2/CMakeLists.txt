cmake_minimum_required(VERSION 3.20)
project(test_hw2v2)

set(CMAKE_CXX_STANDARD 14)

add_executable(test_hw2v2 main.cc Series.cc ComputeArithmetic.cc ComputePi.cc DumperSeries.hh PrintSeries.cc WriteSeries.cc RiemannIntegral.cc)
