#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cctype>
#include <unistd.h>

using namespace std;

// OOP
class squishyData
{
private:
    string itemID;
    string itemType;
    string itemName;
    int itemQuantity;
    double itemPrice;

public:
    squishyData(string id, string type, string name, int quantity, double price) : itemID(id), itemType(type), itemName(name), itemQuantity(quantity), itemPrice(price) {}

    string getID() const
    {
        return itemID;
    }
    string getType() const
    {
        return itemType;
    }
    string getName() const
    {
        return itemName;
    }
    int getQuantity() const
    {
        return itemQuantity;
    }
    double getPrice() const
    {
        return itemPrice;
    }

    void setID(string id)
    {
        itemID = id;
    }

    void setQuantity(int quantity)
    {
        itemQuantity = quantity;
    }

    void setPrice(double price)
    {
        itemPrice = price;
    }

    void setType(string type)
    {
        itemType = type;
    }
};

struct squishyInventory
{
    vector<squishyData> defaultItems = {
        squishyData("NJ101", "Maltose", "Cat Squishy", 15, 55.75),
        squishyData("NJ102", "Coconut Oil", "Bunny Squishy", 8, 45.00),
        squishyData("NJ103", "Crunchy", "Dumpling Squishy", 25, 120.50),
        squishyData("NJ104", "Maltose", "Unicorn Squishy", 12, 95.75),
        squishyData("NJ105", "Vaseline", "Cactus Squishy", 20, 75.00)};
};

// Function Prototypes
bool createFile(string filename);
bool appendFile(string filename, const squishyData &item);
bool readFile(string filename, vector<squishyData> &items);
bool updateFile(string filename, const vector<squishyData> &items);
void searchByID(const vector<squishyData> &items);

// File Handling
bool createFile(string filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Could not create file '" << filename << "'." << '\n';
        return false;
    }
    file.close();
    return true;
}

bool appendFile(string filename, const squishyData &item)
{
    ofstream file(filename, ios::app);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file '" << filename << "' for appending." << '\n';
        return false;
    }
    file << item.getID() << "," << item.getType() << "," << item.getName() << ","
         << item.getQuantity() << "," << item.getPrice() << '\n';
    file.close();
    return true;
}

bool readFile(string filename, vector<squishyData> &items)
{
    fstream file(filename, ios::in);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file '" << filename << "'." << '\n';
        cout << "Creating a new file..." << '\n';
        createFile(filename);
        return false;
    }

    items.clear();
    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string itemIDStr, itemType, itemName, itemQuantityStr, itemPriceStr;
        getline(ss, itemIDStr, ',');
        getline(ss, itemType, ',');
        getline(ss, itemName, ',');
        getline(ss, itemQuantityStr, ',');
        getline(ss, itemPriceStr, ',');

        try
        {
            items.push_back(squishyData(itemIDStr, itemType, itemName, stoi(itemQuantityStr), stod(itemPriceStr)));
        }
        catch (...)
        {
            cerr << "Error found in file: Line " << line << ". Skipping this line...\n";
        }
    }
    return true;
}

bool updateFile(string filename, const vector<squishyData> &items)
{
    fstream file(filename, ios::out);
    if (!file.is_open())
    {
        cerr << "Error: Could not open file '" << filename << "'." << '\n';
        return false;
    }

    for (const squishyData &item : items)
    {
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
void addItem(string filename, vector<squishyData> &inventory);
void updateItem(string filename, vector<squishyData> &inventory);
void deleteItem(string filename, vector<squishyData> &inventory);
void viewInventory(const vector<squishyData> &inventory);

void displayMenu()
{
    cout << "\n=============================" << '\n';
    cout << "Squishy Inventory Management" << '\n';
    cout << "=============================" << '\n';
    cout << "1. Add Squishy" << '\n';
    cout << "2. Update Squishy Details" << '\n';
    cout << "3. Delete Squishy" << '\n';
    cout << "4. View Inventory" << '\n';
    cout << "5. Search Squishy by Item ID" << '\n';
    cout << "6. Exit" << '\n';
    cout << "=============================" << '\n';
}

void addItem(string filename, vector<squishyData> &inventory)
{
    string id, type, name;
    int quantity;
    double price;

    cout << "\n--- Add Squishy ---" << '\n';

    // Get unique ID
    while (true)
    {
        cout << "Enter Item ID: ";
        getline(cin, id);

        bool exists = false;
        for (const squishyData &item : inventory)
        {
            if (item.getID() == id)
            {
                exists = true;
                break;
            }
        }

        if (id.empty())
        {
            cout << "ID cannot be empty." << '\n';
        }
        else if (exists)
        {
            cout << "ID already exists. Enter a different ID." << '\n';
        }
        else
        {
            break;
        }
    }

    cout << "Enter Squishy Type: ";
    getline(cin, type);

    cout << "Enter Squishy Name: ";
    getline(cin, name);

    cout << "Enter Squishy Item Quantity: ";
    while (!(cin >> quantity) || quantity < 0)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Enter a valid quantity: ";
    }

    cout << "Enter Squishy Price: ";
    while (!(cin >> price) || price < 0)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Enter a valid price: ";
    }
    cin.ignore(10000, '\n');

    squishyData newItem(id, type, name, quantity, price);

    if (appendFile(filename, newItem))
    {
        inventory.push_back(newItem);
        cout << "Squishy added successfully!" << '\n';
    }
}

void updateItem(string filename, vector<squishyData> &inventory)
{
    if (inventory.empty())
    {
        cout << "\n--- Update Squishy Details ---" << '\n';
        cout << "Inventory is empty. Nothing to update." << '\n';
        return;
    }

    string id;
    cout << "\n--- Update Squishy Details ---" << '\n';
    cout << "Enter Item ID to update: ";
    getline(cin, id);

    int index = -1;
    for (size_t i = 0; i < inventory.size(); ++i)
    {
        if (inventory[i].getID() == id)
        {
            index = static_cast<int>(i);
            break;
        }
    }

    if (index == -1)
    {
        cout << "Item with ID '" << id << "' not found." << '\n';
        return;
    }

    int choice = 0;
    do
    {
        cout << "\nCurrent details (Item ID: " << id << "):" << '\n';
        cout << "Type: " << inventory[index].getType() << '\n';
        cout << "Name: " << inventory[index].getName() << '\n';
        cout << "Quantity: " << inventory[index].getQuantity() << '\n';
        cout << "Price: " << inventory[index].getPrice() << '\n';

        cout << "\nWhat would you like to update?\n";
        cout << "1. Squishy Type\n";
        cout << "2. Stocks Available\n";
        cout << "3. Price\n";
        cout << "4. Go Back\n";
        cout << "Enter choice (1-4): ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number from 1 to 4.\n";
            choice = 0;
            continue;
        }
        cin.ignore(10000, '\n');

        switch (choice)
        {
        case 1:
        {
            string type;
            cout << "Enter new Squishy Type: ";
            getline(cin, type);
            inventory[index].setType(type);
            break;
        }
        case 2:
        {
            int quantity;
            cout << "Enter new stocks available: ";
            while (!(cin >> quantity) || quantity < 0)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Enter a valid number.\n";
                cout << "Enter new stocks available: ";
            }
            cin.ignore(10000, '\n');
            inventory[index].setQuantity(quantity);
            break;
        }
        case 3:
        {
            double price;
            cout << "Enter new Squishy price: ";
            while (!(cin >> price) || price < 0)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Enter a valid price.\n";
                cout << "Enter new Squishy price: ";
            }
            cin.ignore(10000, '\n');
            inventory[index].setPrice(price);
            break;
        }
        case 4:
            break;
        default:
            cout << "Invalid choice! Please enter a number from 1 to 4.\n";
            continue; // this is for skipping the save para there's no unintentional updates
        }

        // Save lang pag may na-update talaga
        if (choice >= 1 && choice <= 3)
        {
            if (updateFile(filename, inventory))
            {
                cout << "Item updated successfully!" << '\n';
            }
            else
            {
                cout << "Error: Could not save changes to file." << '\n';
            }
        }

    } while (choice != 4);
}

void deleteItem(string filename, vector<squishyData> &inventory)
{
    if (inventory.empty())
    {
        cout << "\n--- Delete Item ---" << '\n';
        cout << "Inventory is empty. Nothing to delete." << '\n';
        return;
    }

    string id;
    cout << "\n--- Delete Item ---" << '\n';
    cout << "Enter Item ID to delete: ";
    getline(cin, id);

    int index = -1;
    for (size_t i = 0; i < inventory.size(); ++i)
    {
        if (inventory[i].getID() == id)
        {
            index = static_cast<int>(i);
            break;
        }
    }

    if (index == -1)
    {
        cout << "Item with ID '" << id << "' not found." << '\n';
        cout << "Press Enter to return to the main menu...";
        cin.get();
        return;
    }

    // Remove from vector
    inventory.erase(inventory.begin() + index);

    // Save changes to the text file
    if (updateFile(filename, inventory))
    {
        cout << "Item deleted successfully!" << '\n';
    }
    else
    {
        cout << "Error: Could not save changes to file." << '\n';
    }
}

void viewInventory(const vector<squishyData> &inventory)
{
    cout << "\n--- Squishy Inventory ---" << '\n';

    if (inventory.empty())
    {
        cout << "Inventory is empty." << '\n';
        return;
    }
    else
    {
        cout << "------------------------------------------------------------------------------------------------" << '\n';
        cout << left << setw(12) << "ID"
             << left << setw(20) << "Type"
             << left << setw(40) << "Name"
             << right << setw(10) << "Quantity"
             << right << setw(12) << "Price" << '\n';
        cout << "------------------------------------------------------------------------------------------------" << '\n';

        cout << fixed << setprecision(2);
        for (const squishyData &item : inventory)
        {
            cout << left << setw(12) << item.getID()
                 << left << setw(20) << item.getType()
                 << left << setw(40) << item.getName()
                 << right << setw(10) << item.getQuantity()
                 << right << setw(12) << item.getPrice() << '\n';
        }
        cout << "------------------------------------------------------------------------------------------------" << '\n';
    }
    cout << "Press Enter to return to the main menu...";
    cin.get();
}

// Search Engine
// =============================
void searchByID(const vector<squishyData> &items)
{
    bool searchID = true;
    cout << "\n--- Search Inventory ---" << '\n';
    while (searchID)
    {
        string searchIDInput;
        char searchChoice;
        bool foundID = false;

        cout << '\n'
             << "Enter Item ID to search inventory: ";
        cin >> searchIDInput;
        cin.ignore();

        for (const auto &item : items)
        {
            if (item.getID() == searchIDInput)
            {
                cout << '\n'
                     << "[Item Found! See the details below.]" << endl;
                cout << '\n'
                     << "ID: " << item.getID() << endl;
                cout << "Type: " << item.getType() << endl;
                cout << "Name: " << item.getName() << endl;
                cout << "Quantity: " << item.getQuantity() << endl;
                cout << "Price: " << item.getPrice() << endl;
                foundID = true;
                break;
            }
        }
        if (foundID)
        {
            while (true)
            {
                cout << '\n'
                     << "Would you like to search for another item? [Y/N]: ";
                cin >> searchChoice;
                cin.ignore();
                searchChoice = toupper(searchChoice);

                if (searchChoice == 'Y')
                {
                    cout << "\n\t-----------------------------------\n";
                    break;
                }
                else if (searchChoice == 'N')
                {
                    searchID = false;
                    break;
                }
                else
                {
                    cout << '\n'
                         << "Error: Invalid Input. Please enter 'Y' or 'N'." << endl;
                }
            }
        }
        else
        {
            cout << '\n'
                 << "Error: Item with ID " << searchIDInput << " not found in inventory." << endl;

            while (true)
            {
                cout << '\n'
                     << "Try again? [Y/N]: ";
                cin >> searchChoice;
                cin.ignore();
                searchChoice = toupper(searchChoice);

                if (searchChoice == 'Y')
                {
                    cout << "\n\t-----------------------------------\n";
                    break;
                }
                else if (searchChoice == 'N')
                {
                    searchID = false;
                    break;
                }
                else
                {
                    cout << '\n'
                         << "Error: Invalid Input. Please enter 'Y' or 'N'." << endl;
                }
            }
        }
    }
}

// Main Function
int main()
{
    const string FILENAME = "inventory.txt";
    vector<squishyData> inventory;

    if (!readFile(FILENAME, inventory) || inventory.empty())
    {
        squishyInventory defaultInventory;
        inventory = defaultInventory.defaultItems;
        updateFile(FILENAME, inventory);
    }

    int choice = 0;
    do
    {
        displayMenu();
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            // Non-number typed: clear the error and throw away the bad input
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0;
            cout << "Invalid input. Please enter a number from 1 to 6." << '\n';
            continue;
        }

        cin.ignore(10000, '\n');

        switch (choice)
        {
        case 1:
            addItem(FILENAME, inventory);
            break;
        case 2:
            updateItem(FILENAME, inventory);
            break;
        case 3:
            deleteItem(FILENAME, inventory);
            break;
        case 4:
            viewInventory(inventory);
            break;
        case 5:
            searchByID(inventory);
            break;
        case 6:
            cout << "Thank you for using the Squishy Inventory Manager!" << '\n';
            cout << "Exiting the program..." << '\n';
            sleep(2);
            break;
        default:
            cout << "Invalid choice. Please enter a number from 1 to 6." << '\n';
        }
    } while (choice != 6);

    return 0;
}