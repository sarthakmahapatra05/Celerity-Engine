#include "C:\Users\sarth\Desktop\quantbacktester\include\Backtester.h"
#include <iostream>
#include <future>
#include <vector>
#include <iomanip>

struct BacktestResult {
    int shortWindow;
    int longWindow;
    double totalReturn;
    double sharpeRatio;
    double maxDrawdown;
    double winRate;
    double profitFactor;
    double averageLatency;
};

BacktestResult runBacktest(const std::string& symbol, const std::string& dataFile, int shortWindow, int longWindow) {
    Backtester engine(symbol, dataFile, shortWindow, longWindow);
    engine.run();
    
    auto equityCurve = engine.getEquityCurve();
    
    BacktestResult result;
    result.shortWindow = shortWindow;
    result.longWindow = longWindow;
    result.totalReturn = PerformanceMetrics::calculateTotalReturn(equityCurve);
    result.sharpeRatio = PerformanceMetrics::calculateSharpeRatio(equityCurve);
    result.maxDrawdown = PerformanceMetrics::calculateMaxDrawdown(equityCurve);
    
    auto tradePnLs = engine.getTradePnLs();
    result.winRate = PerformanceMetrics::calculateWinRate(tradePnLs);
    result.profitFactor = PerformanceMetrics::calculateProfitFactor(tradePnLs);
    result.averageLatency = engine.getAverageLatency();
    
    return result;
}

int main() {
    std::cout << "Starting Celerity Engine (Parameter Sweep Mode)...\n" << std::endl;
    
    std::string symbol = "AAPL";
    std::string dataFile = "C:\\Users\\sarth\\Desktop\\quantbacktester\\data\\sample.csv";

    // Define parameter grid
    std::vector<std::pair<int, int>> params = {
        {1, 2},   // fast
        {2, 4},   // medium
        {1, 3}    // another configuration
    };

    std::vector<std::future<BacktestResult>> futures;

    // Launch threads for parameter sweep
    for (const auto& p : params) {
        futures.push_back(std::async(std::launch::async, runBacktest, symbol, dataFile, p.first, p.second));
    }

    std::cout << std::left << std::setw(15) << "Short Window" 
              << std::setw(15) << "Long Window" 
              << std::setw(15) << "Total Return" 
              << std::setw(15) << "Sharpe Ratio" 
              << std::setw(15) << "Max Drawdown" 
              << std::setw(15) << "Win Rate"
              << std::setw(15) << "Profit Factor"
              << std::setw(15) << "Latency(us)" << std::endl;
    std::cout << std::string(120, '-') << std::endl;

    // Collect results
    for (auto& f : futures) {
        BacktestResult res = f.get();
        std::cout << std::left << std::setw(15) << res.shortWindow 
                  << std::setw(15) << res.longWindow 
                  << std::fixed << std::setprecision(4)
                  << std::setw(15) << res.totalReturn 
                  << std::setw(15) << res.sharpeRatio 
                  << std::setw(15) << res.maxDrawdown
                  << std::setw(15) << res.winRate
                  << std::setw(15) << res.profitFactor
                  << std::setw(15) << res.averageLatency << std::endl;
    }

    std::cout << "\nParameter Sweep Complete." << std::endl;

    return 0;
}
