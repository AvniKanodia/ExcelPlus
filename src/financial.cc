#include "financial.hpp"
#include "utilities.hpp"
#include <stdexcept>
#include <iostream>

namespace Financial {
    double XIRR(const std::vector<double>& cashFlows, const std::vector<int>& dates) {
        //Check that cashFlows and dates are not empty and equal
        if (cashFlows.size() != dates.size() || cashFlows.empty()) throw std::invalid_argument("Incorrect date/cash flow values");
        

        //Check if cashFlows has atleast one positive and one negative value
        bool hasPositive = false;
        bool hasNegative = false;
        for (double cashFlow : cashFlows) {
            if (cashFlow > 0) hasPositive = true;
            if (cashFlow < 0) hasNegative = true;
            if (hasPositive && hasNegative) break;
        }

        if (!hasNegative || !hasNegative) throw std::invalid_argument("Incorrect cash flow values");

        // Sort cashFlows and dates in chronological order
        std::vector<size_t> indices(dates.size());
        for (size_t i = 0; i < indices.size(); ++i) {
            indices[i] = i;
        }

        // Sort indices based on dates
        std::sort(indices.begin(), indices.end(), [&dates](size_t i1, size_t i2) {
            if (!utilities::isValidDate(dates[i1]) || !utilities::isValidDate(dates[i2])) throw std::invalid_argument("Incorrect date values");
            return dates[i1] < dates[i2];
        });

        // Reorder cashFlows and dates using the sorted indices
        std::vector<double> sortedCashFlows;
        std::vector<int> sortedDates;
        for (size_t i : indices) {
            sortedCashFlows.push_back(cashFlows[i]);
            sortedDates.push_back(dates[i]);
        }
        
         // Normalize dates to years from the first date
        std::vector<double> normalizedDates;
        int firstDate = sortedDates[0];
        for (int date : sortedDates) {
            normalizedDates.push_back(utilities::dateDifferenceInYears(firstDate, date));
        }

        int maxIterations = 100;
        double precision = 0.000001;
        double rate = 0.1;

        //Calculating the closest rate
        for (int i = 0; i < maxIterations; ++i) {
            double pv = 0.0;
            double pvDeriv = 0.0;

            // Calculate present value and its derivative
            for (size_t j = 0; j < sortedCashFlows.size(); ++j) {
                pv += sortedCashFlows[j] / std::pow(1.0 + rate, normalizedDates[j] / 365.0);
                pvDeriv -= normalizedDates[j] / 365.0 * sortedCashFlows[j] * std::pow(1.0 + rate, -1 - normalizedDates[j] / 365.0);
                }

            double newRate = rate - pv / pvDeriv;
            if (std::abs(newRate - rate) < precision) return newRate; //Converged 

            rate = newRate;
        }

        throw std::runtime_error("XIRR did not converge.");
    }
}