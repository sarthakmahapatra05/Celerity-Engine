#include "C:\Users\sarth\Desktop\quantbacktester\include\Portfolio.h"
#include <iostream>

Portfolio::Portfolio(CSVReader* dataHandler, std::queue<std::shared_ptr<Event>>* eventsQueue, double initialCapital)
    : dataHandler(dataHandler), eventsQueue(eventsQueue), 
      initialCapital(initialCapital), currentCash(initialCapital), currentPositions(0), averageEntryPrice(0.0) {}

void Portfolio::updateSignal(std::shared_ptr<Event> event) {
    if (event->type == EventType::SIGNAL) {
        auto signal = std::static_pointer_cast<SignalEvent>(event);
        
        // Simple position sizing logic: 
        // If LONG and we have no position, buy 100 shares.
        // If EXIT and we have position, sell all.
        if (signal->signal_type == "LONG" && currentPositions == 0) {
            eventsQueue->push(std::make_shared<OrderEvent>(signal->symbol, "MKT", 100, "BUY"));
        } else if (signal->signal_type == "EXIT" && currentPositions > 0) {
            eventsQueue->push(std::make_shared<OrderEvent>(signal->symbol, "MKT", currentPositions, "SELL"));
        }
    }
}

void Portfolio::updateFill(std::shared_ptr<Event> event) {
    if (event->type == EventType::FILL) {
        auto fill = std::static_pointer_cast<FillEvent>(event);
        
        double fill_val = fill->quantity * fill->fill_cost;
        if (fill->direction == "BUY") {
            if (currentPositions == 0) {
                averageEntryPrice = (fill_val + fill->commission) / fill->quantity;
            } else {
                double totalCost = (currentPositions * averageEntryPrice) + fill_val + fill->commission;
                averageEntryPrice = totalCost / (currentPositions + fill->quantity);
            }
            currentPositions += fill->quantity;
            currentCash -= (fill_val + fill->commission);
        } else if (fill->direction == "SELL") {
            double pnl = (fill->fill_cost * fill->quantity - fill->commission) - (averageEntryPrice * fill->quantity);
            closedTradePnLs.push_back(pnl);
            
            currentPositions -= fill->quantity;
            if (currentPositions == 0) {
                averageEntryPrice = 0.0;
            }
            currentCash += (fill_val - fill->commission);
        }
    }
}

void Portfolio::updateTimeindex(std::shared_ptr<Event> event) {
    if (event->type == EventType::MARKET) {
        try {
            MarketData bar = dataHandler->getLatestBar();
            double holdingsValue = currentPositions * bar.close;
            double totalEquity = currentCash + holdingsValue;
            equityCurve.push_back({bar.date, totalEquity});
        } catch (const std::exception& e) {
            // No data yet
        }
    }
}
