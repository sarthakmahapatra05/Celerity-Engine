#ifndef MOVINGAVERAGESTRATEGY_H
#define MOVINGAVERAGESTRATEGY_H

#include "Strategy.h"
#include "CSVReader.h"
#include <queue>
#include <vector>
#include <string>

class MovingAverageStrategy : public Strategy {
private:
    std::string symbol;
    CSVReader* dataHandler;
    std::queue<std::shared_ptr<Event>>* eventsQueue;
    
    int shortWindow;
    int longWindow;
    
    std::vector<double> prices;
    bool invested;

public:
    MovingAverageStrategy(const std::string& symbol, CSVReader* dataHandler, 
                          std::queue<std::shared_ptr<Event>>* eventsQueue,
                          int shortWindow = 10, int longWindow = 30);

    void calculateSignals(std::shared_ptr<Event> event) override;
};

#endif // MOVINGAVERAGESTRATEGY_H
