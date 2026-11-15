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
        int itemID;
        string itemType;
        string itemName;
        int itemQuantity;
        double itemPrice;
    public:
        squishyData(int id, string type, string name, int quantity, double price) :
            itemID(id), itemType(type), itemName(name), itemQuantity(quantity), itemPrice(price) {}

        int getID() const {
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
            items.push_back(squishyData(stoi(itemIDStr), itemType, itemName, stoi(itemQuantityStr), stod(itemPriceStr)));
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

// Search Engine
// =============================
// Function Prototypes (Pick One)
void searchByID();
void searchByName();

// Main Function
int main() {
    /*
    FLOW:
    Display Menu -> User Input -> Call chosen menu UI function -> User Input / Execute
    (Loop until user exits)
    */
    return 0;
}