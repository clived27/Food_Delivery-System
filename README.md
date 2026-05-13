# 🍔 VNIT Online Food Management System

> A robust, modular command-line food delivery application built in C. 

This project is a comprehensive restaurant management and food ordering system. It features a complete dual-interface architecture for both **Customers** (to browse, search, and place orders) and **Administrators** (to manage restaurant inventories and monitor live operations). 

## ✨ Features

### 👤 Customer Interface
* **Smart Search:** Find the fastest restaurant for a specific food item or check general availability across the network.
* **Dynamic Sorting:** Browse restaurant menus sorted alphabetically or by price (High-to-Low/Low-to-High).
* **Location-Based Filtering:** View all restaurants, menus, and "Items of the Day" mapped to specific areas.
* **Advanced Queries:** Discover unique items exclusive to single restaurants, or find common items sold across all platforms.
* **Automated Order Tracking:** Calculates expected delivery times dynamically based on food preparation time + restaurant delivery overhead.

### 👑 Admin / Owner Interface
* **Inventory Management:** Add new restaurants, input generic/special food items, and set the "Special Item of the Day."
* **Live Order Tracking:** View a sorted queue of all active/live orders for any restaurant, including expected completion times and total costs.
* **Data Persistence:** Automatically saves all new inventory and restaurant data to local text files for future sessions.

## 📁 Project Structure

The project follows a standard C modular architecture to separate business logic, file handling, and UI components:

```text
Food-Delivery-System/
├── data/
│   └── restaurents.txt     # Persistent database for restaurants and menus
├── include/
│   └── food_system.h       # Header file containing structs, macros, and prototypes
├── src/
│   ├── main.c              # Application entry point
│   ├── core.c              # Core business logic (ordering, searching, filtering)
│   ├── file_handling.c     # I/O operations for saving/loading data
│   ├── helpers.c           # Utility functions and sorting algorithms (Merge Sort/Binary Search)
│   └── menus.c             # UI prompts and display formatting
└── README.md
```

🚀 Getting Started
Prerequisites
A C compiler (like GCC or MinGW for Windows)

A terminal or command prompt


Compilation & Execution
To run this project locally, clone the repository and compile the source files together:

Clone the repository:

Bash
git clone [https://github.com/clived27/Food-Delivery-System.git](https://github.com/clived27/Food-Delivery-System.git)
cd Food-Delivery-System
Compile the code:


Bash
gcc src/main.c src/helpers.c src/file_handling.c src/core.c src/menus.c -I include -o food_app
Run the application:


On Windows:

Bash
.\food_app.exe


On Linux/Mac:

Bash
./food_app



🛠️ Technical Highlights
Implements Binary Search for highly efficient O(log n) food item and restaurant lookups.

Utilizes Merge Sort to maintain strictly ordered arrays of structs based on complex primary and secondary keys (e.g., sorting live orders by order time, then by expected delivery time).

Built entirely with custom data structures and pure C standard libraries.

Developed by Clive Dsilva | B.Tech Computer Science and Engineering, VNIT Nagpur
