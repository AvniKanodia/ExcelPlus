#include "financial.hpp"
#include "statistics.hpp"
#include "utilities.hpp"
#include <vector>
#include <iostream>

int main() {
    std::vector<double> values;
    values.push_back(1345);
    values.push_back(1301);
    values.push_back(1368);
    values.push_back(1322);
    values.push_back(1310);
    values.push_back(1370);
    values.push_back(1318);
    values.push_back(1350);
    values.push_back(1303);
    values.push_back(1299);

    std::cout << Statistics::STDEV_S(values) << std::endl;
}