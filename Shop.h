#ifndef SHOP_H
#define SHOP_H

#include <iostream>
#include <string>
#include <vector>

#include "Item.h"
#include "Food.h"
#include "Accessory.h"

using namespace std;

class Shop { 
    static int noShops;
    int id;
    string name;
    vector<Item*> foodStock;
    vector<Item*> accessoryStock;

    public:
        Shop();
        Shop(string, vector<Item*>, vector<Item*>);
        Shop(const Shop& obj);
        Shop& operator=(const Shop& obj);
        ~Shop();

        friend ostream& operator<<(ostream&, const Shop& obj);
        friend istream& operator>>(istream&, Shop& obj);

        string getName() { return name; }
        vector<Item*>& getFoodStock() { return foodStock; }
        vector<Item*>& getAccessoryStock() { return accessoryStock; }

        Item* buyFood(const int nr) { return foodStock[nr]; }
        Item* buyAccessory(const int nr) { return accessoryStock[nr]; }
        void loadFood(const string& filename);
        void loadAccessories(const string& filename);
};

#endif