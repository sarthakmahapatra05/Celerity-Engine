#include "C:\Users\sarth\Desktop\quantbacktester\include\MovingAverageStrategy.h"
#include <numeric>

MovingAverageStrategy::MovingAverageStrategy(const std::string& symbol, CSVReader* dataHandler, 
                                             std::queue<std::shared_ptr<Event>>* eventsQueue,
                                             int shortWindow, int longWindow)
    : symbol(symbol), dataHandler(dataHandler), eventsQueue(eventsQueue), 
      shortWindow(shortWindow), longWindow(longWindow), invested(false) {}

void MovingAverageStrategy::calculateSignals(std::shared_ptr<Event> event) {
    if (event->type == EventType::MARKET) {
        MarketData bar = dataHandler->getLatestBar();
        prices.push_back(bar.close);

        if (prices.size() >= longWindow) {
            double shortSum = 0.0;
            for (size_t i = prices.size() - shortWindow; i < prices.size(); ++i) {
                shortSum += prices[i];
            }
            double shortMa = shortSum / shortWindow;

            double longSum = 0.0;
            for (size_t i = prices.size() - longWindow; i < prices.size(); ++i) {
                longSum += prices[i];
            }
            double longMa = longSum / longWindow;

            if (shortMa > longMa && !invested) {
                // Generate a long signal
                eventsQueue->push(std::make_shared<SignalEvent>(symbol, bar.date, "LONG"));
                invested = true;
            } else if (shortMa < longMa && invested) {
                // Generate an exit signal
                eventsQueue->push(std::make_shared<SignalEvent>(symbol, bar.date, "EXIT"));
                invested = false;
            }
        }
    }
}
