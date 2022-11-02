#include "Series.hh"

#ifndef TEST_HW2_V2_DUMPERSERIES_H
#define TEST_HW2_V2_DUMPERSERIES_H

/*!
 * @brief bass class definition for dumper series
 */
class DumperSeries {
public:
    DumperSeries(Series &series) : series(series) {}

    virtual void dump(std::ostream &os) = 0;

    void setPrecision(unsigned int precision);

protected:
    Series &series;
};

#endif //TEST_HW2_V2_DUMPERSERIES_H
