# G15 Final Project: Squishy Inventory

A simple and lightweight C++ program that is designed to manage a collection of squishies.

### Features
* Add Squishy to Inventory
  
* Update Squishy Details
  
* Delete Squishy from Inventory
    
* View Inventory

### Group Members
* Butaslac, Nj

* Cueto, Janine Mae

* Munsayac, Jilliane Margaret

* Oblan, Neo Achilles

## Run Instructions
1. Run the Program
2. A user interface will appear, asking what the user wants to do with the inventory management system. Simply choose one action within the given selection.
3. Depending on the chosen action, you may be prompted to enter details of items. This is required to be able to access the specific item within the inventory.
4. You may exit the program freely or continue to use as much as you want.

### Sample Output

```
=============================
Squishy Inventory Management
=============================
1. Add Item
2. Update Item
3. Delete Item
4. View Inventory
5. Search Item by ID
6. Exit
=============================
Enter your choice: 1

--- Add Squishy ---
Enter Item ID: NA201
Enter Squishy Type: Coconut Oil
Enter Squishy Name: Cheese Squishy
Enter Squishy Item Quantity: 50
Enter Squishy Price: 175.25
Squishy added successfully!

=============================
Squishy Inventory Management
=============================
1. Add Squishy
2. Update Squishy Details
3. Delete Squishy
4. View Inventory
5. Search Squishy by Item ID
6. Exit
=============================
Enter your choice: 4

--- Squishy Inventory ---
------------------------------------------------------------------------------------------------
ID          Type                Name                                      Quantity       Price
------------------------------------------------------------------------------------------------
NJ101       Maltose             Cat Squishy                                     15       55.75
NJ102       Coconut Oil         Bunny Squishy                                    8       45.00
NJ103       Crunchy             Dumpling Squishy                                25      120.50
NJ104       Maltose             Unicorn Squishy                                 12       95.75
NJ105       Vaseline            Cactus Squishy                                  20       75.00
NA201       Coconut Oil         Cheese Squishy                                  50      175.25
------------------------------------------------------------------------------------------------
Press Enter to return to the main menu...
```

## Roles & System Outline
Programming Language: C++
Compiler: GCC/G++
IDE: Any (Preferably Visual Studio Code)

**1. Data Management (OOP) - Oblan**\
&emsp;- Item ID\
&emsp;- Item Type\
&emsp;- Item Name\
&emsp;- Stock available in Inventory\
&emsp;- Price per Unit

**2. File Handling - Oblan & NJ**\
&emsp;> All data will be saved into a file using file handling\
&emsp;> Data will be retrieved from existing files (if applicable) and insert it into a vector for data retention and allow for search engine to function 

**3. User Interface & Functions - Cueto & Munsayac**\
&emsp;- Add Item Option\
&emsp;- Update Item Option\
&emsp;- Delete Item Option\
&emsp;- View Inventory Option

**4. Search Engine - NJ**\
&emsp;> Allows searching for items through ID or Name

## Coding Standards
**Functions**
* Menu - `displayMenu()`
* Add Item - `addItem()`
* Update Item - `updateItem()`
* Delete Item - `deleteItem()`
* View Inventory - `viewInventory()`
* Search Engine - `searchByName()` or `searchByID()`
* Create File - `createFile()`
* Append File - `appendFile()`
* Read File - `readFile()`
* Update File - `updateFile()`

**Variables**
* Item ID - `itemID`
* Item Type - `itemType`
* Item Name - `itemName`
* Stock Available - `itemQuantity`
* Price per Unit - `itemPrice`
* Search ID - `searchID` or `searchName`
* File Name - `filename`

**Setters & Getters**
* Get ID - `getID()`
* Get Item Type - `getType()`
* Get Item Name - `getName()`
* Get Item Amount - `getQuantity()`
* Get Item Price - `getPrice()`
* Set Item Amount - `setQuantity()`
* Set Item Price - `setPrice()`