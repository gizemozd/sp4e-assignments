#include "DumperSeries.hh"
#include "Series.hh"
#include <memory>

#ifndef HOMEWORK2_PRINTSERIES_H
#define HOMEWORK2_PRINTSERIES_H

/*!
 * @brief Class definition for printing series to terminal
 */
class PrintSeries : public DumperSeries {
public:
    PrintSeries(std::shared_ptr<Series> series, unsigned long maxIter, unsigned long freq);

    virtual ~PrintSeries() {};

    unsigned long maxIter;
    unsigned long freq;

    void dump(std::ostream &os = std::cout) override;

    void setPrecision(unsigned int precision);
};

#endif //HOMEWORK2_PRINTSERIES_H
