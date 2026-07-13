#ifndef BACKTESTER_H
#define BACKTESTER_H

#include "Event.h"
#include "CSVReader.h"
#include "MovingAverageStrategy.h"
#include "Portfolio.h"
#include "ExecutionHandler.h"
#include "PerformanceMetrics.h"
#include <queue>
#include <memory>
#include <string>

class Backtester {
private:
    std::string symbol;
    std::string dataFile;
    int shortWindow;
    int longWindow;
    
    std::queue<std::shared_ptr<Event>> eventsQueue;
    
    std::unique_ptr<CSVReader> dataHandler;
    std::unique_ptr<MovingAverageStrategy> strategy;
    std::unique_ptr<Portfolio> portfolio;
    std::unique_ptr<ExecutionHandler> executionHandler;
    
    double totalLatencyMicroseconds;
    long long eventCount;
    
public:
    Backtester(const std::string& symbol, const std::string& dataFile, int shortWindow, int longWindow);
    
    void run();
    
    std::vector<std::pair<std::string, double>> getEquityCurve() const;
    double getAverageLatency() const;
    const std::vector<double>& getTradePnLs() const;
};

#endif // BACKTESTER_H
