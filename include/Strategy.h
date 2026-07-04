#ifndef STRATEGY_H
#define STRATEGY_H

#include "Event.h"
#include <memory>

class Strategy {
public:
    virtual ~Strategy() = default;
    
    // Calculate signals based on a MarketEvent
    virtual void calculateSignals(std::shared_ptr<Event> event) = 0;
};

#endif // STRATEGY_H
