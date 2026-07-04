#include "C:\Users\sarth\Desktop\quantbacktester\include\Backtester.h"
#include <iostream>

Backtester::Backtester(const std::string& symbol, const std::string& dataFile, int shortWindow, int longWindow)
    : symbol(symbol), dataFile(dataFile), shortWindow(shortWindow), longWindow(longWindow) {
    
    dataHandler = std::make_unique<CSVReader>(symbol, dataFile, &eventsQueue);
    strategy = std::make_unique<MovingAverageStrategy>(symbol, dataHandler.get(), &eventsQueue, shortWindow, longWindow);
    portfolio = std::make_unique<Portfolio>(dataHandler.get(), &eventsQueue);
    executionHandler = std::make_unique<ExecutionHandler>(&eventsQueue, dataHandler.get());
}

void Backtester::run() {
    while (true) {
        // First, check if we need to pull more data
        if (dataHandler->continueBacktestFlag()) {
            dataHandler->updateBars();
        } else {
            break;
        }

        // Process all events in the queue
        while (!eventsQueue.empty()) {
            auto event = eventsQueue.front();
            eventsQueue.pop();

            if (event->type == EventType::MARKET) {
                strategy->calculateSignals(event);
                portfolio->updateTimeindex(event); // Update equity curve
            } else if (event->type == EventType::SIGNAL) {
                portfolio->updateSignal(event);
            } else if (event->type == EventType::ORDER) {
                executionHandler->executeOrder(event);
            } else if (event->type == EventType::FILL) {
                portfolio->updateFill(event);
            }
        }
    }
}

std::vector<std::pair<std::string, double>> Backtester::getEquityCurve() const {
    return portfolio->getEquityCurve();
}
