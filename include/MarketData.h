#ifndef MARKETDATA_H
#define MARKETDATA_H

#include <string>

struct MarketData {
    std::string date;
    double open;
    double high;
    double low;
    double close;

    long volume;
};

#endif // MARKETDATA_H

    