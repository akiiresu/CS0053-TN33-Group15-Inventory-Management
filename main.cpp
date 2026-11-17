// This is only the skeleton of the code, changes will be made along the way :)
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

// OOP
class squishyData {
    private:
        string itemID;
        string itemType;
        string itemName;
        int itemQuantity;
        double itemPrice;
    public:
        squishyData(string id, string type, string name, int quantity, double price) :
            itemID(id), itemType(type), itemName(name), itemQuantity(quantity), itemPrice(price) {}

        string getID() const {
            return itemID;
        }
        string getType() const {
            return itemType;
        }
        string getName() const {
            return itemName;
        }
        int getQuantity() const {
            return itemQuantity;
        }
        double getPrice() const {
            return itemPrice;
        }

        void setID(string id) {
            itemID = id;
        }

        void setQuantity(int quantity) {
            itemQuantity = quantity;
        }

        void setPrice(double price) {
            itemPrice = price;
        }

        void setType(string type) {
            itemType = type;
        }
};

// Function Prototypes
bool createFile(string filename);
bool appendFile(string filename, const squishyData& item);
bool readFile(string filename, vector<squishyData>& items);
bool updateFile(string filename, const vector<squishyData>& items);

// File Handling
bool createFile(string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not create file '" << filename << "'." << '\n';
        return false;
    }
    file.close();
    return true;
}

bool appendFile(string filename, const squishyData& item) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cerr << "Error: Could not open file '" << filename << "' for appending." << '\n';
        return false;
    }
    file << item.getID() << "," << item.getType() << "," << item.getName() << ","
         << item.getQuantity() << "," << item.getPrice() << '\n';
    file.close();
    return true;
}

bool readFile(string filename, vector<squishyData>& items) {
    fstream file(filename, ios::in);
    if (!file.is_open()) {
        cerr << "Error: Could not open file '" << filename << "'." << '\n';
        cout << "Creating a new file..." << '\n';
        createFile(filename);
        return false;
    }

    items.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string itemIDStr, itemType, itemName, itemQuantityStr, itemPriceStr;
        getline(ss, itemIDStr, ',');
        getline(ss, itemType, ',');
        getline(ss, itemName, ',');
        getline(ss, itemQuantityStr, ',');
        getline(ss, itemPriceStr, ',');

        try {
            items.push_back(squishyData(itemIDStr, itemType, itemName, stoi(itemQuantityStr), stod(itemPriceStr)));
        } catch (...) {
            cerr << "Error found in file: Line " << line << ". Skipping this line...\n";
        }
    }
    return true;
}

bool updateFile(string filename, const vector<squishyData>& items) {
    fstream file(filename, ios::out);
    if (!file.is_open()) {
        cerr << "Error: Could not open file '" << filename << "'." << '\n';
        return false;
    }

    for (const squishyData& item : items) {
        file << item.getID() << "," << item.getType() << "," << item.getName() << ","
             << item.getQuantity() << "," << item.getPrice() << '\n';
    }
    file.close();
    return true;
}

// User Interface and Functions
// =============================
// Function Prototypes
void displayMenu();
void addItem(string filename, vector<squishyData>& inventory);
void updateItem(string filename, vector<squishyData>& inventory);
void deleteItem(string filename, vector<squishyData>& inventory);
void viewInventory(const vector<squishyData>& inventory);

void displayMenu() {
    cout << "\n=============================" << '\n';
    cout << "Squishy Inventory Management" << '\n';
    cout << "=============================" << '\n';
    cout << "1. Add Item" << '\n';
    cout << "2. Update Item" << '\n';
    cout << "3. Delete Item" << '\n';
    cout << "4. View Inventory" << '\n';
    cout << "5. Search Item by ID" << '\n';
    cout << "6. Exit" << '\n';
    cout << "=============================" << '\n';
}

void addItem(string filename, vector<squishyData>& inventory){ 
    string id, type, name;
    int quantity;
    double price;

    cout << "\n--- Add Item ---" << '\n';

    // Get unique ID
    while (true) {
        cout << "Enter Item ID: ";
        getline(cin, id);

        bool exists = false;
        for (const squishyData& item : inventory) {
            if (item.getID() == id) {
                exists = true;
                break;
            }
        }

        if (id.empty()) {
            cout << "ID cannot be empty." << '\n';
        } else if (exists) {
            cout << "ID already exists. Enter a different ID." << '\n';
        } else {
            break;
        }
    }

    cout << "Enter Item Type: ";
    getline(cin, type);

    cout << "Enter Item Name: ";
    getline(cin, name);

    cout << "Enter Item Quantity: ";
    while (!(cin >> quantity) || quantity < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Enter a valid quantity: ";
    }

    cout << "Enter Item Price: ";
    while (!(cin >> price) || price < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Enter a valid price: ";
    }
    cin.ignore(10000, '\n');

    squishyData newItem(id, type, name, quantity, price);

    if (appendFile(filename, newItem)) {
        inventory.push_back(newItem);
        cout << "Item added successfully!" << '\n';
    }
}
void updateItem(string filename, vector<squishyData>& inventory) {
    if (inventory.empty()) {
        cout << "\n--- Update Item ---" << '\n';
        cout << "Inventory is empty. Nothing to update." << '\n';
        return;
    }

    string id;
    cout << "\n--- Update Item ---" << '\n';
    cout << "Enter Item ID to update: ";
    getline(cin, id);

    int index = -1;
    for (size_t i = 0; i < inventory.size(); ++i) {
        if (inventory[i].getID() == id) {
            index = static_cast<int>(i);
            break;
        }
    }

    if (index == -1) {
        cout << "Item with ID '" << id << "' not found." << '\n';
        return;
    }

    cout << "\nItem found! Current details:" << '\n';
    cout << "Type: " << inventory[index].getType() << '\n';
    cout << "Name: " << inventory[index].getName() << '\n';
    cout << "Quantity: " << inventory[index].getQuantity() << '\n';
    cout << "Price: " << inventory[index].getPrice() << '\n';

    string type, name;
    int quantity;
    double price;

    cout << "Enter new Item Type: ";
    getline(cin, type);

    cout << "Enter new Item Name: ";
    getline(cin, name);

    cout << "Enter new Item Quantity: ";
    while (!(cin >> quantity) || quantity < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Enter a valid quantity: ";
    }

    cout << "Enter new Item Price: ";
    while (!(cin >> price) || price < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Enter a valid price: ";
    }
    cin.ignore(10000, '\n'); 

    inventory[index].setType(type);
    inventory[index].setName(name);
    inventory[index].setQuantity(quantity);
    inventory[index].setPrice(price);

    if (updateFile(filename, inventory)) {
        cout << "Item updated successfully!" << '\n';
    } else {
        cout << "Error: Could not save changes to file." << '\n';
    }
}

void deleteItem(string filename, vector<squishyData>& inventory) {
    if (inventory.empty()) {
        cout << "\n--- Delete Item ---" << '\n';
        cout << "Inventory is empty. Nothing to delete." << '\n';
        return;
    }

    string id;
    cout << "\n--- Delete Item ---" << '\n';
    cout << "Enter Item ID to delete: ";
    getline(cin, id);

    int index = -1;
    for (size_t i = 0; i < inventory.size(); ++i) {
        if (inventory[i].getID() == id) {
            index = static_cast<int>(i);
            break;
        }
    }

    if (index == -1) {
        cout << "Item with ID '" << id << "' not found." << '\n';
        return;
    }

    inventory.erase(inventory.begin() + index);

    if (updateFile(filename, inventory)) {
        cout << "Item deleted successfully!" << '\n';
    } else {
        cout << "Error: Could not save changes to file." << '\n';
    }
}
void viewInventory(const vector<squishyData>& inventory) { 
    cout << "\n--- Squishy Inventory ---" << '\n';

    if (inventory.empty()) {
        cout << "Inventory is empty." << '\n';
        return;
    }

    cout << "------------------------------------------------------------------------------------------------" << '\n';
    cout << left  << setw(12) << "ID"
         << left  << setw(20) << "Type"
         << left  << setw(40) << "Name"
         << right << setw(10) << "Quantity"
         << right << setw(12) << "Price" << '\n';
    cout << "------------------------------------------------------------------------------------------------" << '\n';

    cout << fixed << setprecision(2);
    for (const squishyData& item : inventory) {
        cout << left  << setw(12) << item.getID()
             << left  << setw(20) << item.getType()
             << left  << setw(40) << item.getName()
             << right << setw(10) << item.getQuantity()
             << right << setw(12) << item.getPrice() << '\n';
    }
    cout << "------------------------------------------------------------------------------------------------" << '\n';
}

// Search Engine
// =============================
// Function Prototypes (Pick One)
void searchByID();
void searchByName();

void searchByID()    { cout << "[Search by ID] Not implemented yet." << '\n'; }

// Main Function
int main() {
    /*
    FLOW:
    Display Menu -> User Input -> Call chosen menu UI function -> User Input / Execute
    (Loop until user exits)
    */
    const string FILENAME = "inventory.txt";
    vector<squishyData> inventory;

    readFile(FILENAME, inventory);

    int choice = 0;
    do {
        displayMenu();
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            // Non-number typed: clear the error and throw away the bad input
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0;
            cout << "Invalid input. Please enter a number from 1 to 6." << '\n';
            continue;
        }

        switch (choice) {
            case 1: addItem(FILENAME, inventory);       break;
            case 2: updateItem(FILENAME, inventory); break;
            case 3: deleteItem(FILENAME, inventory); break;
            case 4: viewInventory(inventory); break;
            case 5: searchByID();    break;
            case 6: cout << "Goodbye!" << '\n'; break;
            default: cout << "Invalid choice. Please enter a number from 1 to 6." << '\n';
        }
    } while (choice != 6);

    return 0;
}