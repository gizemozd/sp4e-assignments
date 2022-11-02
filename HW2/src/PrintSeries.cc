#include <iostream>
#include "PrintSeries.hh"

/*!
 * @brief constructor
 * @param series  series taken into consideration
 * @param maxIter maximum iteration
 * @param freq frequency
 */
PrintSeries::PrintSeries(Series &series, unsigned long maxIter, unsigned long freq) : DumperSeries(series) {
    this->maxIter = maxIter;
    this->freq = freq;
};

/*!
 * @brief prints out the iteration number, series summation,
 * and convergence difference on the screen.
 * @param os output stream
 */
void PrintSeries::dump(std::ostream &os) {
    double result;
    double convergenceValue;
    double convergenceDiff;

    for (unsigned long i = 1; i <= this->maxIter / this->freq; i++) {
        result = series.compute(i * this->freq);
        convergenceValue = series.getAnalyticPrediction();
        // Set precision here
        PrintSeries::setPrecision(10)
        if (std::isnan(convergenceValue)) {
            std::cerr << "The convergence is nan!";
        } else {
            convergenceDiff = convergenceValue - result;
            os << "Iteration: " << i * this->freq << " Result: " << result << " Convergence diff: " << convergenceDiff << std::endl;
        }
    }
};

/*!
 * @brief set the decimal precision
 * @param precision floating-point values
 */
void PrintSeries::setPrecision(unsigned int precision) {
    std::cout.precision(precision);
};
