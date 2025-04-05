#ifndef FINANCIAL_HPP
#define FINANCIAL_HPP
#include <vector>
#include <string>

namespace Financial {
    double XIRR(const std::vector<double>& cashFlows, const std::vector<int>& dates, const double& rateOfReturn);

    double IRR(const std::vector<double>& cashFlows, const double& rateOfReturn);

    double XNPV(const double& discountRate, const std::vector<double>& cashFlows, const std::vector<int>& dates);

    double NPV(const double& discountRate, const std::vector<double>& cashFlows);
}

#endif 