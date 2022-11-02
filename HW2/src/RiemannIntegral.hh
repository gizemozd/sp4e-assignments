//
// Created by ozdil@INTRANET.EPFL.CH on 30.10.22.
//
#include <functional>
#include "Series.hh"

#ifndef HOMEWORK2_RIEMANNINTEGRAL_H
#define HOMEWORK2_RIEMANNINTEGRAL_H

class RiemannIntegral: public Series{
public:
    RiemannIntegral(double a, double b, std::function<double(double)> f);
    virtual ~RiemannIntegral() {};

    double lowerBound;
    double upperBound;
    std::function<double(double)> function;
    unsigned long maxIter = 1e3;
    double deltaX;
    double compute();
    double getXi(unsigned long k);
    double computeTerm(unsigned long k) override;
};

#endif //HOMEWORK2_RIEMANNINTEGRAL_H
