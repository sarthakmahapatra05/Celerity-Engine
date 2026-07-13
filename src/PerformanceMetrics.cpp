#include "C:\Users\sarth\Desktop\quantbacktester\include\PerformanceMetrics.h"
#include <cmath>
#include <numeric>
#include <algorithm>

double PerformanceMetrics::calculateTotalReturn(const std::vector<std::pair<std::string, double>>& equityCurve) {
    if (equityCurve.empty()) return 0.0;
    double initial = equityCurve.front().second;
    double final_val = equityCurve.back().second;
    return (final_val - initial) / initial;
}

double PerformanceMetrics::calculateSharpeRatio(const std::vector<std::pair<std::string, double>>& equityCurve, double riskFreeRate) {
    if (equityCurve.size() < 2) return 0.0;

    std::vector<double> returns;
    for (size_t i = 1; i < equityCurve.size(); ++i) {
        double r = (equityCurve[i].second - equityCurve[i-1].second) / equityCurve[i-1].second;
        returns.push_back(r);
    }

    double meanReturn = std::accumulate(returns.begin(), returns.end(), 0.0) / returns.size();
    
    double variance = 0.0;
    for (double r : returns) {
        variance += (r - meanReturn) * (r - meanReturn);
    }
    variance /= returns.size();
    
    double stdDev = std::sqrt(variance);
    if (stdDev == 0.0) return 0.0;

    // Assuming daily returns, annualized multiplier is sqrt(252)
    return std::sqrt(252.0) * (meanReturn - riskFreeRate) / stdDev;
}

double PerformanceMetrics::calculateMaxDrawdown(const std::vector<std::pair<std::string, double>>& equityCurve) {
    if (equityCurve.empty()) return 0.0;

    double maxDrawdown = 0.0;
    double peak = equityCurve.front().second;

    for (const auto& point : equityCurve) {
        if (point.second > peak) {
            peak = point.second;
        }
        double drawdown = (peak - point.second) / peak;
        if (drawdown > maxDrawdown) {
            maxDrawdown = drawdown;
        }
    }

    return maxDrawdown;
}

double PerformanceMetrics::calculateWinRate(const std::vector<double>& tradePnLs) {
    if (tradePnLs.empty()) return 0.0;
    
    int winningTrades = 0;
    for (double pnl : tradePnLs) {
        if (pnl > 0) {
            winningTrades++;
        }
    }
    return static_cast<double>(winningTrades) / tradePnLs.size();
}

double PerformanceMetrics::calculateProfitFactor(const std::vector<double>& tradePnLs) {
    if (tradePnLs.empty()) return 0.0;

    double grossProfit = 0.0;
    double grossLoss = 0.0;

    for (double pnl : tradePnLs) {
        if (pnl > 0) {
            grossProfit += pnl;
        } else if (pnl < 0) {
            grossLoss -= pnl; // Make it positive
        }
    }

    if (grossLoss == 0.0) return grossProfit > 0 ? 9999.0 : 0.0; // Use a high number for infinite profit factor
    return grossProfit / grossLoss;
}
