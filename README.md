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
  
## Roles & System Outline
Programming Language: C++

**1. Data Management (OOP)**\
&emsp;- Item ID\
&emsp;- Item Type\
&emsp;- Item Name\
&emsp;- Stock available in Inventory\
&emsp;- Price per Unit

**2. File Handling**\
&emsp;> All data will be saved into a file using file handling\
&emsp;> Data will be retrieved from existing files (if applicable) and insert it into a vector for data retention and allow for search engine to function 

**3. User Interface & Functions**\
&emsp;- Add Item Option\
&emsp;- Update Item Option\
&emsp;- Delete Item Option\
&emsp;- View Inventory Option

**4. Search Engine**\
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
* Retrieve Data - `retrieveData()`

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