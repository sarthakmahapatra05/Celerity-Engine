#include "C:\Users\sarth\Desktop\quantbacktester\include\ExecutionHandler.h"

ExecutionHandler::ExecutionHandler(std::queue<std::shared_ptr<Event>>* eventsQueue, CSVReader* dataHandler)
    : eventsQueue(eventsQueue), dataHandler(dataHandler) {}

void ExecutionHandler::executeOrder(std::shared_ptr<Event> event) {
    if (event->type == EventType::ORDER) {
        auto order = std::static_pointer_cast<OrderEvent>(event);
        
        // Simulating execution by querying the latest market price from dataHandler
        MarketData bar = dataHandler->getLatestBar();
        
        // Assume slippage pushes cost against us slightly
        double slippage = 0.01; // 1 cent slippage per share
        double execution_price = bar.close;
        if (order->direction == "BUY") {
            execution_price += slippage;
        } else {
            execution_price -= slippage;
        }

        // Commission model: $1.00 minimum or $0.005 per share
        double commission = std::max(1.0, 0.005 * order->quantity);

        eventsQueue->push(std::make_shared<FillEvent>(
            bar.date, order->symbol, "SIM_EXCHANGE", order->quantity, order->direction, execution_price, commission
        ));
    }
}
