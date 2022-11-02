#include "Series.hh"
#include <memory>
#ifndef HW2_DUMPERSERIES_H
#define HW2_DUMPERSERIES_H

/*!
 * @brief bass class definition for dumper series
 */
class DumperSeries {
public:
    DumperSeries(std::shared_ptr<Series> series) : series(series) {}

    virtual void dump(std::ostream &os) = 0;

    void setPrecision(unsigned int precision);

protected:
    std::shared_ptr<Series> series;
};

inline std::ostream &operator<<(std::ostream &stream, DumperSeries &_this) {
    _this.dump(stream);
    return stream;
}

#endif //HW2_DUMPERSERIES_H
