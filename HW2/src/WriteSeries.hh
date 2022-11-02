#include "DumperSeries.hh"
#include "Series.hh"

#ifndef HOMEWORK2_WRITESERIES_H
#define HOMEWORK2_WRITESERIES_H

/*!
 * @brief class definition for writing series to output files
 */
class WriteSeries : public DumperSeries {
public:
    WriteSeries(Series &series, unsigned long maxIter);

    virtual ~WriteSeries() {};

    unsigned int maxIter;
    unsigned int freq;

    void dump(std::ostream &os = std::cout) override;

    void setSeparator(char c);

protected:
    char separator = ' ';
};


#endif //HOMEWORK2_WRITESERIES_H
