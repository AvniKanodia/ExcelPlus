#ifndef FINANCIAL_HPP
#define FINANCIAL_HPP
#include <vector>
#include <string>

namespace Financial {
    double XIRR(const std::vector<double>& cashFlows, const std::vector<std::string>& dates, const double& rateOfReturn);

    double IRR(const std::vector<double>& cashFlows, const double& rateOfReturn);
}

#endif 