#ifndef HW2_COMPUTEARITHMETIC_H
#define HW2_COMPUTEARITHMETIC_H

#include "Series.hh"

/*!
 * @brief class definition for arithmetic series computation
 */
class ComputeArithmetic : public Series {
public:
    double getAnalyticPrediction() override;

    double computeTerm(unsigned long k) override;
};

#endif //HW2_COMPUTEARITHMETIC_H
