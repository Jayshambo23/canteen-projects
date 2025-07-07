# Canteen Management System

## Overview
The Canteen Management System is a console-based application designed to facilitate the management of a canteen's inventory and order processing. It allows customers to view available food items and place orders, while administrators can manage the inventory by adding, updating, or deleting items.

## Table of Contents
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Functions](#functions)
- [Contributors](#contributors)

## Features
- **Customer Section**: Customers can view the menu and place orders for food items.
- **Admin Section**: Administrators can manage the canteen's inventory by adding, updating, or deleting food items.
- **Password Protection**: Admin access is secured with a strong password validation mechanism to ensure security.

## Installation
To run this application, you need a C compiler. Follow these steps to set up the project:

1. Clone the repository or download the source code.
2. Open the terminal or command prompt.
3. Navigate to the directory containing the source code.
4. Compile the code using a C compiler, e.g., `gcc canteen_management.c -o canteen_management`.
5. Run the executable, e.g., `./canteen_management` on Unix or `canteen_management.exe` on Windows.

## Usage
1. Upon starting the application, a welcome message will be displayed.
2. The user will be prompted to log in as either a customer or an admin.
3. Customers can view the canteen's menu and place orders.
4. Admins can manage the inventory by adding, updating, or deleting food items.

### Customer Actions
- View available food items with their prices and stock.
- Place orders by selecting item IDs and specifying quantities.
- Receive a final receipt summarizing the order.

### Admin Actions
- View the current inventory of food items.
- Add new food items to the inventory.
- Update details of existing food items.
- Delete food items from the inventory.

## Functions
- `isStrongPassword(struct admin a1)`: Validates the strength of the admin password.
- `welcome()`: Displays the welcome message and project details.
- `content()`: Displays the table of contents.
- `showInventory()`: Displays the current inventory of food items.
- `placeOrder()`: Allows customers to place orders for food items.
- `addItem()`: Adds a new food item to the inventory.
- `updateItem()`: Updates the details of an existing food item.
- `deleteItem()`: Deletes a food item from the inventory.
- `adminMenu()`: Displays the admin menu for inventory management.

## Contributors
- Sabin Dangol
- Sachin Belbase
- Roshan Koirala
- Sandesh Shrestha
