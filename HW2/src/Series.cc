/* -------------------------------------------------------------------------- */
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "Series.hh"
/* -------------------------------------------------------------------------- */

/*!
 * @brief compute method
 * @param N upper limit for the summation
 * @return current value of the term
 */
double Series::compute(unsigned long N){
    if (this->currentTerm <= N){
        N -= this->currentTerm;
    }
    else{
        this->currentValue = 0;
        this->currentTerm = 0;
    }

    for (int i = 1; i <= N; i++){
        this->addTerm();
    };
    return this->currentValue;
};

/*!
 * @brief increase index by 1 and ith term by its value
 */
void Series::addTerm(){
    this->currentTerm += 1;
    this->currentValue += this->computeTerm(this->currentTerm);

    return;
};
