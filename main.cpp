// This is only the skeleton of the code, changes will be made along the way :)

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

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

};