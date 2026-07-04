<div align="center">

# Celerity Engine

**An Institutional-Grade, Event-Driven Backtesting Engine in C++17**

[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

</div>

<br>

> *Unlike simple, loop-based (vectorized) backtesters that often suffer from look-ahead bias and unrealistic execution assumptions, Celerity Engine is designed to mirror production trading systems. By processing market data, generating signals, and simulating realistic order execution through a strict event queue, it provides a highly accurate simulation environment.*

## 📌 Key Features

* **Event-Driven Architecture**: Components communicate exclusively via an Event Queue (`MarketEvent`, `SignalEvent`, `OrderEvent`, `FillEvent`), ensuring zero look-ahead bias.
* **Realistic Execution Simulation**: Accurately models slippage and commission costs dynamically during the order fill process.
* **Concurrency & Parameter Sweeping**: Utilizes `std::async` and modern C++ multithreading to run multiple backtest parameter combinations in parallel, drastically reducing optimization time.
* **Performance Metrics**: Automatically calculates Total Return, Sharpe Ratio, and Maximum Drawdown from the daily equity curve.
* **Modern Systems Design**: Heavy use of smart pointers (`std::shared_ptr`, `std::unique_ptr`), STL algorithms, and type-safe enums for memory-safe, high-performance execution.

---

## 🏗️ Architecture

The engine is modularly designed, separating data ingestion from strategy logic and execution modeling:

| Component | Description |
| :--- | :--- |
| **`Event`** | The base class for all messages passed through the system. |
| **`DataHandler`** | Streams historical price data and pushes `MarketEvent`s to the queue. |
| **`Strategy`** | Listens to market data and pushes `SignalEvent`s when trading criteria are met. |
| **`Portfolio`** | Tracks cash, holdings, and equity. Converts `SignalEvent`s into `OrderEvent`s based on position sizing logic. |
| **`ExecutionHandler`** | Simulates the brokerage. Fills `OrderEvent`s with realistic slippage and commission logic. |
| **`Backtester`** | The core engine that manages the event loop and routes events. |

---

## 🚀 Getting Started

### Prerequisites
* A C++17 compatible compiler (e.g., GCC, Clang, or MSVC)
* CMake (Version 3.16 or higher)

### Build Instructions

#### Option 1: Using CMake (Recommended)
```bash
mkdir build
cd build
cmake ..
cmake --build .
```
Run the executable:
```bash
# On Windows (MSVC)
.\Debug\CelerityEngine.exe

# On Linux/Mac
./CelerityEngine
```

#### Option 2: Using GCC (g++) directly
If you prefer not to use CMake, you can compile the project directly from the root directory:
```bash
g++ -std=c++17 -I include src/*.cpp -o CelerityEngine.exe
./CelerityEngine.exe
```

---

## 💻 Usage & Sample Output

By default, `main.cpp` is configured to run a **concurrent parameter sweep** (Grid Search). It optimizes moving average windows by spawning multiple backtest threads in parallel.

**Output:**
```text
Starting Celerity Engine (Parameter Sweep Mode)...

Short Window   Long Window    Total Return   Sharpe Ratio   Max Drawdown   
---------------------------------------------------------------------------
1              2              0.0080         25.8801        0.0000         
2              4              0.0030         9.1652         0.0000         
1              3              0.0060         15.8745        0.0000         

Parameter Sweep Complete.
```

---

<div align="center">
  <i>Developed for high-performance quantitative trading simulation.</i>
</div>
