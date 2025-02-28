#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <ctime>

namespace utilities {
    double dateDifferenceInYears(int date1, int date2);

    std::tm yyyymmddToTm(int date);

    bool isValidDate(int date);
}
#endif