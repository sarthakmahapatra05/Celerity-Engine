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
};

#endif // PERFORMANCEMETRICS_H
