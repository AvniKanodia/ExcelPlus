#include "financial.hpp"
#include "statistics.hpp"
#include "utilities.hpp"
#include <vector>
#include <iostream>

int main() {
    std::vector<double> x;
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);
    x.push_back(6);
    x.push_back(4);
    x.push_back(7);

    std::vector<double> y;
    y.push_back(6);
    y.push_back(5);
    y.push_back(11);
    y.push_back(7);
    y.push_back(5);

    std::cout << Statistics::SKEW_P(x) << std::endl;
}