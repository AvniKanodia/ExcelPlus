#ifndef FINANCIAL_H
#define FINANCIAL_H
#include <vector>
#include <string>

namespace Financial {
    double XIRR(const std::vector<double>& cashFlows, const std::vector<std::string>& dates);

    double XIRR(const std::vector<double>& cashFlows, const std::vector<std::string>& dates, const double& rateOfReturn);
}

#endif 