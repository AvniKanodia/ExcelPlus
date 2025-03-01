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

    double STDEV_P(const std::vector<double>& values) {
       if (values.empty()) throw std::invalid_argument("Invalid values");
       double avg = AVERAGE(values);
       double sum = 0;
       for (double value : values) sum += pow((avg - value), 2);
       return pow(sum / values.size(), 0.5);
    }
    
    double STDEV_S(const std::vector<double> &values) {
        if (values.empty()) throw std::invalid_argument("Invalid values");
       double avg = AVERAGE(values);
       double sum = 0;
       for (double value : values) sum += pow((avg - value), 2);
       return pow(sum / (values.size() - 1), 0.5);
    }
}
