#include "financial.hpp"
#include "utilities.hpp"
#include <vector>
#include <iostream>

int main() {
    std::vector<int> dates;
    dates.push_back(20080101);
    dates.push_back(20080301);
    dates.push_back(20081030);
    dates.push_back(20090401);
    dates.push_back(20090215);

    std::vector<double> cashFlows;
    cashFlows.push_back(-10000);
    cashFlows.push_back(2750);
    cashFlows.push_back(4250);
    cashFlows.push_back(2750);
    cashFlows.push_back(3250);

    std::vector<int> dates2;
    dates2.push_back(20160401);
    dates2.push_back(20210401);

    std::vector<double> cashFlows2;
    cashFlows2.push_back(-1113.4);
    cashFlows2.push_back(2515.2);

    std::cout << "Rate of return: " << Financial::XIRR(cashFlows, dates) << std::endl;
}