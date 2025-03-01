#include "statistics.hpp"
#include "statistics.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cmath>

namespace Statistics {
    double AVERAGE(const std::vector<double>& values) {
        if (values.empty()) throw std::invalid_argument("Invalid values");
        
        double sum = 0;
        for (double value : values) sum += value;

        return sum / values.size();
    }

    double VAR_P(const std::vector<double> &values) {
        if (values.empty()) throw std::invalid_argument("Invalid values");

       double avg = AVERAGE(values);
       double sum = 0;
       for (double value : values) sum += pow((avg - value), 2);

       return sum / values.size();
    }

    double VAR_S(const std::vector<double> &values) {
        if (values.empty()) throw std::invalid_argument("Invalid values");

       double avg = AVERAGE(values);
       double sum = 0;
       for (double value : values) sum += pow((avg - value), 2);

       return sum / (values.size() - 1);
    }

    double COVARIANCE_P(const std::vector<double>& x, const std::vector<double>& y) {
        if (x.empty() || y.size() != x.size()) throw std::invalid_argument("Invalid values");
        double avg_x = AVERAGE(x);
        double avg_y = AVERAGE(y);
        double sum = 0;

        for (size_t i = 0; i < x.size(); ++i) sum += (x[i] - avg_x) * (y[i] - avg_y);

        return sum / x.size();
    }

    double COVARIANCE_S(const std::vector<double> &x, const std::vector<double> &y) {
        if (x.empty() || y.size() != x.size()) throw std::invalid_argument("Invalid values");
        double avg_x = AVERAGE(x);
        double avg_y = AVERAGE(y);
        double sum = 0;

        for (size_t i = 0; i < x.size(); ++i) sum += (x[i] - avg_x) * (y[i] - avg_y);

        return sum / (x.size() - 1);
    }

    double STDEV_P(const std::vector<double>& values) {
       if (values.empty()) throw std::invalid_argument("Invalid values");
       return pow(VAR_P(values), 0.5);
    }
    
    double STDEV_S(const std::vector<double> &values) {
        if (values.empty()) throw std::invalid_argument("Invalid values");
       return pow(VAR_S(values), 0.5);
    }

    double CORREL(const std::vector<double> &x, const std::vector<double> &y) {
        if (x.empty() || y.size() != x.size()) throw std::invalid_argument("Invalid values");
        return COVARIANCE_P(x, y) / (STDEV_P(x) * STDEV_P(y));
    }

    double SLOPE(const std::vector<double> &x, const std::vector<double> &y) {
        if (x.empty() || y.size() != x.size()) throw std::invalid_argument("Invalid values");
        if (VAR_P(x) == 0) throw std::runtime_error("Division by 0");
        return COVARIANCE_P(x, y) / VAR_P(x);
    }

    double INTERCEPT(const std::vector<double> &x, const std::vector<double> &y) {
        if (x.empty() || y.size() != x.size()) throw std::invalid_argument("Invalid values");
        if (VAR_P(x) == 0) throw std::runtime_error("VAR is 0");
        return AVERAGE(y) - AVERAGE(x) * SLOPE(x, y);
    }
}
