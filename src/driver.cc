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

    std::vector<double> IRRcashFlows;
    IRRcashFlows.push_back(-70000);
    IRRcashFlows.push_back(12000);
    IRRcashFlows.push_back(15000);
    //IRRcashFlows.push_back(18000);
    //IRRcashFlows.push_back(21000);
    //IRRcashFlows.push_back(26000);

    std::cout << "Rate of return: " << Financial::IRR(IRRcashFlows, -0.1) << std::endl;
}