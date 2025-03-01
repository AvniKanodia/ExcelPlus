#ifndef STATISTICS_HPP
#define STATISTICS_HPP
#include <vector>
#include <string>

namespace Statistics {
    double AVERAGE(const std::vector<double>& values);

    double VAR_P(const std::vector<double>& values);

    double VAR_S(const std::vector<double>& values);

    double COVARIANCE_P(const std::vector<double>& x, const std::vector<double>& y);

    double COVARIANCE_S(const std::vector<double>& x, const std::vector<double>& y);

    double STDEV_P(const std::vector<double>& values);

    double STDEV_S(const std::vector<double>& values);

    double CORREL(const std::vector<double>& x, const std::vector<double>& y);

    double SLOPE(const std::vector<double>& x, const std::vector<double>& y);

    double INTERCEPT(const std::vector<double>& x, const std::vector<double>& y);
}

#endif 