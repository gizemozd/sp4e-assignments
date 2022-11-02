#include <cmath>

#ifndef HOMEWORK2_SERIES_H
#define HOMEWORK2_SERIES_H

/*!
 * @brief series Base class of series where ComputeArithmetic, ComputePi, and RiemannIntegral inherits from
 */
class Series {
public:
    long int currentTerm;
    double currentValue;

    virtual double compute(unsigned long N);

    virtual double getAnalyticPrediction() { return std::nan(""); };

    void addTerm();

    virtual double computeTerm(unsigned long k) = 0;
};

#endif //HOMEWORK2_SERIES_H
