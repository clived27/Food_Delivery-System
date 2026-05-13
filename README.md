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
