#include "C:\Users\sarth\Desktop\quantbacktester\include\CSVReader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

CSVReader::CSVReader(const std::string& symbol, const std::string& filename, std::queue<std::shared_ptr<Event>>* events)
    : symbol(symbol), currentIndex(0), continueBacktest(true), eventsQueue(events) {
    loadData(filename);
}

void CSVReader::loadData(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        continueBacktest = false;
        return;
    }

    std::string line;
    // Skip the header line
    getline(file, line);
    while (getline(file, line)) {
        std::istringstream ss(line);
        MarketData md;
        std::string token;

        getline(ss, md.date, ',');
        
        getline(ss, token, ',');
        md.open = std::stod(token);

        getline(ss, token, ',');
        md.high = std::stod(token);

        getline(ss, token, ',');
        md.low = std::stod(token);

        getline(ss, token, ',');
        md.close = std::stod(token);  

        getline(ss, token, ',');
        md.volume = std::stol(token);

        data.push_back(md);
    }
    file.close();
}

void CSVReader::updateBars() {
    if (currentIndex < data.size()) {
        eventsQueue->push(std::make_shared<MarketEvent>());
        currentIndex++;
    } else {
        continueBacktest = false;
    }
}

MarketData CSVReader::getLatestBar() const {
    if (currentIndex == 0 || data.empty()) {
        throw std::runtime_error("No data available.");
    }
    return data[currentIndex - 1]; // Return the bar we just pushed a MarketEvent for
}