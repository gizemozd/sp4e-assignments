#include <iostream>
#include <cmath>
#include "ComputePi.hh"

/*!
 * @brief compute function
 * @param N upper bound
 * @return computes the series converging towards pi
 */
double ComputePi::compute(unsigned long N) {
    Series::compute(N);
    return sqrt(6.0 * this->currentValue);
};

/*!
 * @brief computes the kth term
 * @param k kth term
 * @return computed term
 */
double ComputePi::computeTerm(unsigned long k) {
    return 1.0 / (1. * k * k);
};

/*!
 * @brief analytic prediction value of pi
 * @return pi value is returned
 */
double ComputePi::getAnalyticPrediction() {
    return M_PI;
};

