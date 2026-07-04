#ifndef EVENT_H
#define EVENT_H

#include <string>

enum class EventType {
    MARKET,
    SIGNAL,
    ORDER,
    FILL
};

class Event {
public:
    EventType type;
    virtual ~Event() = default;
};

class MarketEvent : public Event {
public:
    MarketEvent() {
        type = EventType::MARKET;
    }
};

class SignalEvent : public Event {
public:
    std::string symbol;
    std::string datetime;
    std::string signal_type; // "LONG" or "SHORT" or "EXIT"
    double strength;         // e.g. 1.0 for full allocation

    SignalEvent(const std::string& sym, const std::string& dt, const std::string& sig_type, double strength = 1.0)
        : symbol(sym), datetime(dt), signal_type(sig_type), strength(strength) {
        type = EventType::SIGNAL;
    }
};

class OrderEvent : public Event {
public:
    std::string symbol;
    std::string order_type;  // "MKT" or "LMT"
    int quantity;
    std::string direction;   // "BUY" or "SELL"

    OrderEvent(const std::string& sym, const std::string& ord_type, int qty, const std::string& dir)
        : symbol(sym), order_type(ord_type), quantity(qty), direction(dir) {
        type = EventType::ORDER;
    }
    
    void printOrder() const {
        // Example: "Order: BUY 100 AAPL MKT"
    }
};

class FillEvent : public Event {
public:
    std::string timeindex;
    std::string symbol;
    std::string exchange;
    int quantity;
    std::string direction;
    double fill_cost;
    double commission;

    FillEvent(const std::string& timeindex, const std::string& sym, const std::string& exch, 
              int qty, const std::string& dir, double cost, double comm = 0.0)
        : timeindex(timeindex), symbol(sym), exchange(exch), 
          quantity(qty), direction(dir), fill_cost(cost), commission(comm) {
        type = EventType::FILL;
    }
};

#endif // EVENT_H
