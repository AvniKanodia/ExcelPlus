#include "utilities.hpp"
#include <chrono>
#include <ctime>

namespace utilities {
    double dateDifferenceInYears(int date1, int date2) {
        tm tm1 = yyyymmddToTm(date1);
        tm tm2 = yyyymmddToTm(date2);

        // Convert std::tm to std::chrono::system_clock::time_point
        std::time_t time1 = std::mktime(&tm1);
        std::time_t time2 = std::mktime(&tm2);
        
        // Convert the difference to days
        double days_diff = std::difftime(time2, time1) / 86400.0;
        return days_diff;
    }

    std::tm yyyymmddToTm(int date) {
        tm t{};
        t.tm_year = (date / 10000) - 1900; // Years since 1900
        t.tm_mon = (date / 100) % 100 - 1; // Months are 0-based
        t.tm_mday = date % 100;            // Day of the month
        return t;
    }

    bool isValidDate(int date) {
        int year = date / 10000;
        int month = (date / 100) % 100;
        int day = date % 100;

        // Check if month is valid
        if (month < 1 || month > 12) return false;

        // Check if day is valid
        if (day < 1 || day > 31) return false;

        // Check for months with 30 days
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;

        // Check for February
        if (month == 2) {
            // Check for leap year
            bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (day > 29 || (day == 29 && !isLeapYear)) return false;
        }

        return true;
    }
}