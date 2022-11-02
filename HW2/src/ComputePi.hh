#ifndef HW2_COMPUTEPI_H
#define HW2_COMPUTEPI_H

#include "Series.hh"

/*!
 * @brief class definition for pi series computation
 */
class ComputePi : public Series {
public:
    double compute(unsigned long N) override;

    double computeTerm(unsigned long k) override;

    double getAnalyticPrediction() override;
};

#endif //HW2_COMPUTEPI_H
