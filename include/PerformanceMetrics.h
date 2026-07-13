#ifndef PERFORMANCEMETRICS_H
#define PERFORMANCEMETRICS_H

#include <vector>
#include <string>
#include <utility>

class PerformanceMetrics {
public:
    static double calculateSharpeRatio(const std::vector<std::pair<std::string, double>>& equityCurve, double riskFreeRate = 0.0);
    static double calculateMaxDrawdown(const std::vector<std::pair<std::string, double>>& equityCurve);
    static double calculateTotalReturn(const std::vector<std::pair<std::string, double>>& equityCurve);
    static double calculateWinRate(const std::vector<double>& tradePnLs);
    static double calculateProfitFactor(const std::vector<double>& tradePnLs);
};

#endif // PERFORMANCEMETRICS_H
