// This is only the skeleton of the code, changes will be made along the way :)
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype> // for character conversion

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

struct squishyInventory {
    vector<squishyData> defaultItems = {
        squishyData("101", "Gel", "Cat Squishy", 15, 55.75),
        squishyData("102", "Bead", "Bunny Squishy", 8, 45.00),
        squishyData("103", "Food", "Dumpling Squishy", 25, 120.50),
        squishyData("104", "Plush", "Unicorn Squishy", 12, 95.75),
        squishyData("105", "Mesh", "Cactus Squishy", 30, 44.75)
    };
};

// Function Prototypes
bool createFile(string filename);
bool appendFile(string filename, const squishyData& item);
bool readFile(string filename, vector<squishyData>& items);
bool updateFile(string filename, const vector<squishyData>& items);
void searchByID (const vector<squishyData>& items);

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
/*void displayMenu();
void addItem();
void updateItem();
void deleteItem();
void viewInventory();*/

// Search Engine
// =============================
void searchByID(const vector<squishyData>& items) {
    bool searchID = true;
    cout << "\n\t\t || SEARCH INVENTORY || \n" << endl;
    while (searchID) {
        string searchIDInput;
        char searchChoice;
        bool foundID = false;

        cout << '\n' << "Enter Item ID to search inventory: ";
        cin >> searchIDInput;
        cin.ignore();

        for (const auto& item : items) {
            if (item.getID() == searchIDInput) {
                cout << '\n' << "[Item Found! See the details below.]" << endl;
                cout << '\n' << "ID: " << item.getID() << endl;
                cout << "Type: " << item.getType() << endl;
                cout << "Name: " << item.getName() << endl;
                cout << "Quantity: " << item.getQuantity() << endl;
                cout << "Price: " << item.getPrice() << endl;
                foundID = true;
                break;
            }
        }

        if (foundID) {
            while (true) {
                cout << '\n' << "Would you like to search for another item? [Y/N]: ";
                cin >> searchChoice;
                cin.ignore();
                searchChoice = toupper(searchChoice);

                if (searchChoice == 'Y') {
                    cout << "\n\t-----------------------------------\n";
                    break;
                } else if (searchChoice == 'N') {
                    searchID = false;
                    break;
                } else {
                    cout << '\n' << "Error: Invalid Input. Please enter 'Y' or 'N'." << endl;
                }
            }
        } else {
            cout << '\n' << "Error: Item with ID " << searchIDInput << " not found in inventory." << endl;

            while (true) {
                cout << '\n' << "Try again? [Y/N]: ";
                cin >> searchChoice;
                cin.ignore();
                searchChoice = toupper(searchChoice);

                if (searchChoice == 'Y') {
                    cout << "\n\t-----------------------------------\n";
                    break;
                } else if (searchChoice == 'N') {
                    searchID = false;
                    break;
                } else {
                    cout << '\n' << "Error: Invalid Input. Please enter 'Y' or 'N'." << endl;
                }
            }
        }
    }
}

// Main Function
int main() {
    string filename = "inventory.txt";
    vector <squishyData> items;

    if (!readFile(filename, items)) {
        squishyInventory initialStock;
        items = initialStock.defaultItems;
        updateFile(filename, items);
    }

    searchByID(items);

    return 0;
}