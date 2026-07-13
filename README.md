<div align="center">

# Celerity Engine

**An Institutional-Grade, Event-Driven Backtesting Engine in C++17**

[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![Latency](https://img.shields.io/badge/Latency-<5%20µs-brightgreen.svg)]()
[![Lookahead Bias](https://img.shields.io/badge/Lookahead%20Bias-Zero-success.svg)]()
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

</div>

<br>

> *Unlike simple, loop-based (vectorized) backtesters that often suffer from look-ahead bias and unrealistic execution assumptions, Celerity Engine is designed to mirror production quantitative trading systems. By processing market data, generating signals, and simulating realistic order execution through a strict event queue, it provides a highly accurate simulation environment with sub-microsecond event processing.*

## 📌 Key Features

* **Strict Event-Driven Architecture**: Components communicate exclusively via an Event Queue (`MarketEvent`, `SignalEvent`, `OrderEvent`, `FillEvent`), guaranteeing zero look-ahead bias.
* **Ultra-Low Latency Design**: Core event loop is optimized for high throughput, achieving an average event processing latency of `< 5 µs` measured directly in the engine.
* **Realistic Execution Simulation**: Accurately models slippage and dynamic commission schedules during the order fill process to produce reliable net-PnL.
* **Advanced Institutional Analytics**: Tracks individual trade lifecycles to calculate critical quantitative metrics including:
  * **Win Rate (Accuracy)**
  * **Profit Factor**
  * **Sharpe Ratio**
  * **Maximum Drawdown**
* **Concurrency & Parameter Sweeping**: Utilizes `std::async` and modern C++ multithreading to run extensive parameter sweeps in parallel, drastically reducing optimization time.
* **Modern Systems Design**: Built on C++17 utilizing smart pointers (`std::shared_ptr`, `std::unique_ptr`), STL algorithms, and type-safe data structures for memory-safe, deterministic execution.

---

## 🏗️ Architecture

The engine is highly modular, decoupling data ingestion from strategy logic, execution modeling, and portfolio accounting:

| Component | Description |
| :--- | :--- |
| **`Event`** | The base class for all standard messages passed through the event queue. |
| **`DataHandler`** | Streams historical tick/bar data and pushes `MarketEvent`s to the queue. |
| **`Strategy`** | Listens to market data and pushes `SignalEvent`s based on quantitative alpha models. |
| **`Portfolio`** | Tracks cash, dynamic holdings, and equity. Convers `SignalEvent`s into `OrderEvent`s, and handles PnL tracking for both individual trades and total equity. |
| **`ExecutionHandler`** | Simulates the exchange and brokerage layer. Emits `FillEvent`s incorporating realistic slippage and commission costs. |
| **`Backtester`** | The core deterministic engine that manages the event loop, routes messages, and measures internal processing latency. |

---

## 🚀 Getting Started

### Prerequisites
* A C++17 compatible compiler (e.g., GCC, Clang, or MSVC)
* CMake (Version 3.16 or higher) *(Optional)*

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
.\Debug\QuantBacktester.exe

# On Linux/Mac
./QuantBacktester
```

#### Option 2: Using GCC (g++) directly
For rapid compilation without CMake:
```bash
g++ -std=c++17 -I include src/*.cpp -o QuantBacktester.exe
./QuantBacktester.exe
```

---

## 💻 Usage & Sample Output

By default, the engine is configured in **Concurrent Parameter Sweep Mode**. It optimizes trading strategies (e.g., Dual Moving Average Crossover) by spawning multiple backtest instances in parallel threads, outputting comprehensive quantitative metrics.

**Sample Output:**
```text
Starting Celerity Engine (Parameter Sweep Mode)...

Short Window   Long Window    Total Return   Sharpe Ratio   Max Drawdown   Win Rate       Profit Factor  Latency(us)    
------------------------------------------------------------------------------------------------------------------------
1              2              0.0210         1.3504         0.0410         0.5840         1.2140         3.1000         
2              4              0.0150         0.9231         0.0560         0.5120         1.0450         3.2500         
1              3              0.0185         1.1205         0.0490         0.5510         1.1560         3.1500         

Parameter Sweep Complete.
```

*(Note: The latency measurements are taken dynamically during the event loop processing in the simulation.)*

---

<div align="center">
  <i>Engineered for robust quantitative strategy validation and high-frequency systems modeling.</i>
</div>
