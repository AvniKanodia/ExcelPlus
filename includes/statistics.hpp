#ifndef STATISTICS_HPP
#define STATISTICS_HPP
#include <vector>
#include <string>

namespace Statistics {
    double AVERAGE(const std::vector<double>& values);

    double STDEV_P(const std::vector<double>& values);

    double STDEV_S(const std::vector<double>& values);
}

#endif 