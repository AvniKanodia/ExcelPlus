#include "financial.hpp"
#include "statistics.hpp"
#include "utilities.hpp"
#include <vector>
#include <iostream>

int main() {
    std::vector<double> x;
    x.push_back(2);
    x.push_back(3);
    x.push_back(9);
    x.push_back(1);
    x.push_back(8);

    std::vector<double> y;
    y.push_back(6);
    y.push_back(5);
    y.push_back(11);
    y.push_back(7);
    y.push_back(5);

    std::cout << Statistics::INTERCEPT(y,x) << std::endl;
}