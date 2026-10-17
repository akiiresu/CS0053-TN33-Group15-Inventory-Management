// This is only the skeleton of the code, changes will be made along the way :)
// Note: Parang pareho lang yung vector and arrays, pero mas flexible lang yung vector
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool createFile(string filename);
bool appendFile(string filename, squishyData& squishyData);
bool readFile(string filename, vector<squishyData>& squishyData);
bool updateFile(string filename, vector<squishyData>& squishyData);
bool retrieveFileData(string filename, string line);

// OOP - Achi
class squishyData {
    private:
        int itemID;
        string itemType;
        string itemName;
        int itemQuantity;
        double itemPrice;
    public:
        squishyData(int id, string type, string name, int quantity, double price);

        int getID() {
            return itemID;
        }
        string getType() {
            return itemType;
        }
        string getName() {
            return itemName;
        }
        int getQuantity() {
            return itemQuantity;
        }
        double getPrice() {
            return itemPrice;
        }

        void setQuantity(int quantity) {
            itemQuantity = quantity;
        }

        void setPrice(double price) {
            itemPrice = price;
        }
};

// File Handling - Achi
bool createFile(string filename) {
    fstream file(filename, ios::out);
    if (!file.is_open()) {
        cerr << "Error: Could not create file '" << filename << "'." << '\n';
        return false;
    }
    file.close();
    return true;
}

bool appendFile(string filename, squishyData& squishyData) {
    fstream file(filename, ios::app);
    if (!file.is_open()) {
        cerr << "Error: Could not open file '" << filename << "' for appending." << '\n';
        return false;
    }
    file << squishyData.getID() << "," << squishyData.getType() << "," << squishyData.getName() << "," 
         << squishyData.getQuantity() << "," << squishyData.getPrice() << '\n';
    file.close();
    return true;
}
// Incomplete
bool readFile(string filename, vector<squishyData>& squishyData) {
    fstream file(filename, ios::in);
    if (!file.is_open()) {
        cerr << "Error: Could not open file '" << filename << "'." << '\n';
        cout << "Creating a new file..." << '\n';
        createFile(filename);
        return false;
    }

}

// Not sure how to do this pa but I will experiment
bool updateFile(string filename, vector<squishyData>& squishyData) {
    fstream file(filename, ios::out);
    if (!file.is_open()) {
        cerr << "Error: Could not open file '" << filename << "'." << '\n';
        return false;
    }

}

// If there's an existing file, this will take the data in the file and store it into the vector
bool retrieveFileData(vector<squishyData>& squishyData, string filename) {
    fstream file(filename, ios::in);
    if (!file.is_open()) {
        cerr << "Error: Could not open file '" << filename << "'." << '\n';
        return false;
    }

    vector<string> lines; // For storing yung lines na na-read sa file
    string line; // For storing yung current line na na-read sa file

    /*
    Explanation for tomorrow programmer me:
    Basically, let's say this .txt file contains these lines:
    FEU
    UST
    NU

    We will read each line, first line is FEU.
    string line -> the current line -> FEU
    vector<string> lines -> where the current line (string line) being read is stored -> FEU
    Then, we will read the next line, which is UST. Repeat.
    */

    // Read each line from the file, this basically means na as long as may line sa file,
    // it will get each line and store it sa vector
    while (getline(file, line)) {
        stringstream ss(line);
        
        while(getline(ss, line, ',')) {
            // Split the line by commas and store each part in the vector
            lines.push_back(line);
        }

        // Will end it here muna, I'll continue this another time
    }
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