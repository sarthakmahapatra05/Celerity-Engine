#ifndef EXECUTIONHANDLER_H
#define EXECUTIONHANDLER_H

#include "Event.h"
#include "CSVReader.h"
#include <queue>
#include <memory>

class ExecutionHandler {
private:
    std::queue<std::shared_ptr<Event>>* eventsQueue;
    CSVReader* dataHandler;

public:
    ExecutionHandler(std::queue<std::shared_ptr<Event>>* eventsQueue, CSVReader* dataHandler);
    void executeOrder(std::shared_ptr<Event> event);
};

#endif // EXECUTIONHANDLER_H
