#include "ComputeArithmetic.hh"

/*!
 * @brief analytical prediction of series summation is returned
 * @return result of prediction
 */
double ComputeArithmetic::getAnalyticPrediction() {
    double result;
    result = 1. * this->currentTerm * (this->currentTerm + 1) / 2.;
    return result;
};

/*!
 * @brief computes the kth term
 * @param k term number
 * @return computed term at the index k
 */
double ComputeArithmetic::computeTerm(unsigned long k) {
    return 1. * k;
};