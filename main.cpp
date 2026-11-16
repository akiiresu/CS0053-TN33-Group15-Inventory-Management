// This is only the skeleton of the code, changes will be made along the way :)
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

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
void addItem();
void updateItem();
void deleteItem();
void viewInventory();

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

void addItem()       { cout << "[Add Item] Not implemented yet." << '\n'; }
void updateItem()    { cout << "[Update Item] Not implemented yet." << '\n'; }
void deleteItem()    { cout << "[Delete Item] Not implemented yet." << '\n'; }
void viewInventory() { cout << "[View Inventory] Not implemented yet." << '\n'; }

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
            case 1: addItem();       break;
            case 2: updateItem();    break;
            case 3: deleteItem();    break;
            case 4: viewInventory(); break;
            case 5: searchByID();    break;
            case 6: cout << "Goodbye!" << '\n'; break;
            default: cout << "Invalid choice. Please enter a number from 1 to 6." << '\n';
        }
    } while (choice != 6);

    return 0;
}