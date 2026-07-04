#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <vector>
#include <queue>
#include <memory>
#include "MarketData.h"
#include "Event.h"

class CSVReader {
private:
    std::string symbol;
    std::vector<MarketData> data;
    size_t currentIndex;
    bool continueBacktest;
    std::queue<std::shared_ptr<Event>>* eventsQueue;

public:
    CSVReader(const std::string& symbol, const std::string& filename, std::queue<std::shared_ptr<Event>>* events);
    
    // Reads the entire CSV into memory
    void loadData(const std::string& filename);
    
    // Pushes the next MarketEvent to the queue
    void updateBars();
    
    // Returns the latest available bar
    MarketData getLatestBar() const;
    
    // Check if more data is available
    bool continueBacktestFlag() const { return continueBacktest; }
};

#endif // CSVREADER_H