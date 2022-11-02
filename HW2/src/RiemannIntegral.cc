//
// Created by ozdil@INTRANET.EPFL.CH on 30.10.22.
//
#include <iostream>
#include <fstream>
#include "RiemannIntegral.hh"

/*!
 * @brief constructor
 * @param a lower bound
 * @param b upper bound
 * @param f function
 */
RiemannIntegral::RiemannIntegral(double a, double b, std::function<double(double)> f) {
    this->lowerBound = a;
    this->upperBound = b;
    this->function = f;
    this->deltaX = (1.0*(b - a)) / (1.0*this->maxIter);
};

/*!
 * @brief
 * @param k
 * @return
 */
double RiemannIntegral::getXi(unsigned long k){
    return (1.0*this->lowerBound) + (1.0*this->deltaX*k);
};

/*!
 * @brief computes the kth term
 * @param k kth term
 * @return computed term
 */
double RiemannIntegral::computeTerm(unsigned long k){
    double currentX = this->getXi(k);
    return 1.0*this->function(currentX)*this->deltaX;
};

/*!
 * @brief
 * @return
 */
double RiemannIntegral::compute(){
    return Series::compute(this->maxIter);
};

