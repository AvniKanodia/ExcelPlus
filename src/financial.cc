#include "financial.hpp"
#include "utilities.hpp"
#include <stdexcept>
#include <iostream>

namespace Financial {
    double XIRR(const std::vector<double>& cashFlows, const std::vector<int>& dates, const double& rateOfReturn = 0.1) {
        // Check that cashFlows and dates are not empty and equal
        if (cashFlows.size() != dates.size() || cashFlows.empty()) throw std::invalid_argument("XIRR: incorrect date/cash flow values");
        

        // Check if cashFlows has atleast one positive and one negative value
        bool hasPositive = false;
        bool hasNegative = false;
        for (double cashFlow : cashFlows) {
            if (cashFlow > 0) hasPositive = true;
            if (cashFlow < 0) hasNegative = true;
            if (hasPositive && hasNegative) break;
        }

        if (!hasNegative || !hasPositive) throw std::invalid_argument("XIRR: incorrect cash flow values: must have at least one positive and one negative value");

        // Sort cashFlows and dates in chronological order
        std::vector<size_t> indices(dates.size());
        for (size_t i = 0; i < indices.size(); ++i) {
            indices[i] = i;
        }

        // Sort indices based on dates
        std::sort(indices.begin(), indices.end(), [&dates](size_t i1, size_t i2) {
            if (!utilities::isValidDate(dates[i1]) || !utilities::isValidDate(dates[i2])) throw std::invalid_argument("XIRR: incorrect date values");
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
        double rate = rateOfReturn;

        // Calculating the closest rate
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

    double IRR(const std::vector<double>& cashFlows, const double& rateOfReturn = 0.1) {
        // Check that cashFlows and dates are not empty and equal
        if (cashFlows.empty()) throw std::invalid_argument("IRR: incorrect cash flow values");
        
        // Check if cashFlows has atleast one positive and one negative value
        bool hasPositive = false;
        bool hasNegative = false;
        for (double cashFlow : cashFlows) {
            if (cashFlow > 0) hasPositive = true;
            if (cashFlow < 0) hasNegative = true;
            if (hasPositive && hasNegative) break;
        }

        if (!hasNegative || !hasPositive) throw std::invalid_argument("IRR: incorrect cash flow values");

        int maxIterations = 20;
        double precision = 0.000001;
        double rate = rateOfReturn;

        // Calculating the closest rate
        for (int i = 0; i < maxIterations; ++i) {
            double pv = 0.0;
            double pvDeriv = 0.0;

            // Calculate present value and its derivative
            for (size_t j = 0; j < cashFlows.size(); ++j) {
                pv += cashFlows[j] / std::pow(1.0 + rate, j);
                pvDeriv -= (j * cashFlows[j]) / std::pow(1.0 + rate, j + 1);
            }

            double newRate = rate - pv / pvDeriv;
            if (std::abs(newRate - rate) < precision) return newRate; //Converged 

            rate = newRate;
        }

        throw std::runtime_error("IRR did not converge.");
    }

    double XNPV(const double &discountRate, const std::vector<double> &cashFlows, const std::vector<int> &dates) {
        // Check that cashFlows and dates are not empty and equal
        if (cashFlows.size() != dates.size() || cashFlows.empty()) throw std::invalid_argument("XNPV: incorrect date/cash flow values");

        // Check if cashFlows has at least one positive and one negative value
        bool hasPositive = false;
        bool hasNegative = false;
        for (double cashFlow : cashFlows) {
            if (cashFlow > 0) hasPositive = true;
            if (cashFlow < 0) hasNegative = true;
            if (hasPositive && hasNegative) break;
        }

        if (!hasNegative || !hasPositive) throw std::invalid_argument("XNPV: incorrect cash flow values: must have at least one positive and one negative value");

        // Sort cashFlows and dates in chronological order
        std::vector<size_t> indices(dates.size());
        for (size_t i = 0; i < indices.size(); ++i) {
            indices[i] = i;
        }

        // Sort indices based on dates
        std::sort(indices.begin(), indices.end(), [&dates](size_t i1, size_t i2) {
            if (!utilities::isValidDate(dates[i1]) || !utilities::isValidDate(dates[i2])) throw std::invalid_argument("XNPV: incorrect date values");
            return dates[i1] < dates[i2];
        });

        // Reorder cashFlows and dates using the sorted indices
        std::vector<double> sortedCashFlows;
        std::vector<int> sortedDates;
        for (size_t i : indices) {
            sortedCashFlows.push_back(cashFlows[i]);
            sortedDates.push_back(dates[i]);
        }

        // Verify no dates precede the first date
        int firstDate = sortedDates[0];
        for (size_t i = 1; i < sortedDates.size(); ++i) {
            if (sortedDates[i] < firstDate) {
                throw std::invalid_argument("XNPV: dates must not precede the starting date");
            }
        }

        // Calculate XNPV
        double result = 0.0;
        for (size_t i = 0; i < sortedCashFlows.size(); ++i) {
            double days = utilities::dateDifferenceInYears(firstDate, sortedDates[i]);
            result += sortedCashFlows[i] / std::pow(1.0 + discountRate, days / 365.0);
        }

        return result;
    }

    double NPV(const double &discountRate, const std::vector<double> &cashFlows) {
       // Check that cashFlows and dates are not empty and equal
       if (cashFlows.empty()) throw std::invalid_argument("NPV: incorrect date/cash flow values");

       // Check if cashFlows has at least one positive and one negative value
       bool hasPositive = false;
       bool hasNegative = false;
       for (double cashFlow : cashFlows) {
           if (cashFlow > 0) hasPositive = true;
           if (cashFlow < 0) hasNegative = true;
           if (hasPositive && hasNegative) break;
       }

       if (!hasNegative || !hasPositive) throw std::invalid_argument("NPV: incorrect cash flow values: must have at least one positive and one negative value");

       // Calculate NPV
       double result = 0.0;
       for (size_t i = 0; i < cashFlows.size(); ++i) {
           result += cashFlows[i] / std::pow(1.0 + discountRate, static_cast<double>(i + 1));
       }

       return result;
    }
}