#ifndef TEST_HW2_V2_COMPUTEARITHMETIC_H
#define TEST_HW2_V2_COMPUTEARITHMETIC_H

#include "Series.hh"

/*!
 * @brief class definition for arithmetic series computation
 */
class ComputeArithmetic: public Series{
public:
    double getAnalyticPrediction() override;
    double computeTerm(unsigned long k) override;
};

#endif //TEST_HW2_V2_COMPUTEARITHMETIC_H
