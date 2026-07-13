#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "Event.h"
#include "CSVReader.h"
#include <queue>
#include <memory>
#include <map>

class Portfolio {
private:
    CSVReader* dataHandler;
    std::queue<std::shared_ptr<Event>>* eventsQueue;

    double initialCapital;
    double currentCash;
    int currentPositions; // For simplicity, only handling one symbol right now
    
    double averageEntryPrice;
    std::vector<double> closedTradePnLs;

    std::vector<std::pair<std::string, double>> equityCurve;

public:
    Portfolio(CSVReader* dataHandler, std::queue<std::shared_ptr<Event>>* eventsQueue, double initialCapital = 100000.0);

    void updateSignal(std::shared_ptr<Event> event);
    void updateFill(std::shared_ptr<Event> event);
    void updateTimeindex(std::shared_ptr<Event> event); // For tracking equity curve

    const std::vector<std::pair<std::string, double>>& getEquityCurve() const { return equityCurve; }
    const std::vector<double>& getClosedTradePnLs() const { return closedTradePnLs; }
};

#endif // PORTFOLIO_H
