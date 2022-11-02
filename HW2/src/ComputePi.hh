#ifndef TEST_HW2_V2_COMPUTEPI_H
#define TEST_HW2_V2_COMPUTEPI_H

#include "Series.hh"

class ComputePi: public Series{
public:
    double compute(unsigned long N) override;
    double computeTerm(unsigned long k) override;
    double getAnalyticPrediction() override;
};

#endif //TEST_HW2_V2_COMPUTEPI_H
