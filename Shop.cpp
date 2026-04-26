#include "Shop.h"
#include "Food.h"
#include "Accessory.h"
#include "Utils.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int Shop::noShops = 0;

Shop::Shop() : id(++noShops) , name("SHOP") {}
Shop::Shop(string name, vector<Item*> foodStock, vector<Item*> accessoryStock) : id(++noShops)  {
    this->name = name;
    this->foodStock = foodStock;
    this->accessoryStock = accessoryStock;
}
Shop::Shop(const Shop& obj) : id(++noShops) {
    this->name = obj.name;
    for (int i = 0; i < obj.foodStock.size(); i++)
        this->foodStock.push_back(new Food(*dynamic_cast<Food*>(obj.foodStock[i])));
    for (int i = 0; i < obj.accessoryStock.size(); i++)
        this->accessoryStock.push_back(new Accessory(*dynamic_cast<Accessory*>(obj.accessoryStock[i])));
}

Shop& Shop::operator=(const Shop& obj) {
    if (this == &obj) return *this;

    for (int i = 0; i < foodStock.size(); i++) delete foodStock[i];
    for (int i = 0; i < accessoryStock.size(); i++) delete accessoryStock[i];
    foodStock.clear();
    accessoryStock.clear();

    this->name = obj.name;
    for (int i = 0; i < obj.foodStock.size(); i++)
        this->foodStock.push_back(new Food(*dynamic_cast<Food*>(obj.foodStock[i])));
    for (int i = 0; i < obj.accessoryStock.size(); i++)
        this->accessoryStock.push_back(new Accessory(*dynamic_cast<Accessory*>(obj.accessoryStock[i])));

    return *this;
}
Shop::~Shop() {
    for (auto item : foodStock) delete item;
    for (auto item : accessoryStock) delete item;
}

ostream& operator<<(ostream& os, const Shop& obj) {
    os << "=============== " << obj.name << " ===============" << endl;
    os << "---> FOOD:" << endl;
    if (obj.foodStock.empty()) os << "No food items available!" << endl;
    else for (int i = 0; i < obj.foodStock.size(); i++) {
        os << i + 1 << ". " << *obj.foodStock[i] << endl;
    }
    os << "---> ACCESSORIES:" << endl;
    if (obj.accessoryStock.empty()) os << "No accessory items available!" << endl;
    else for (int i = 0; i < obj.accessoryStock.size(); i++) {
        os << i + 1 << ". " << *obj.accessoryStock[i] << endl;
    }

    return os;
}
istream& operator>>(istream& is, Shop& obj) {
    string name;
    cout << "Enter shop name (don't use spaces): "; is >> name;

    obj.name = name;

    int nrfood, nracc;

    cout << "How many food items do you want to add?:";
    nrfood = getSafeIntOption();
    for (int i = 0; i < nrfood; i++) {
        Food* f = new Food();
        is >> *f;
        obj.foodStock.push_back(f);
    }

    cout << "How many accessory items do you want to add?:";
    nracc = getSafeIntOption();
    for (int i = 0; i < nracc; i++) {
        Accessory* a = new Accessory();
        is >> *a;
        obj.accessoryStock.push_back(a);
    }

    return is;
}

void Shop::loadFood(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) throw runtime_error("Could not load the food items!");

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        int hungerPoints, price;
        float healthPoints;
        bool isHealthy;

        getline(ss, name, ',');
        ss >> hungerPoints; ss.ignore();
        ss >> healthPoints; ss.ignore();
        ss >> isHealthy; ss.ignore();
        ss >> price;

        foodStock.push_back(new Food(name, hungerPoints, isHealthy, healthPoints, 1, price));
    }
}

void Shop::loadAccessories(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) throw runtime_error("Could not load accessories!");

    string line;
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string name, color;
        int price;

        getline(ss, name, ',');
        getline(ss, color, ',');
        ss >> price;

        accessoryStock.push_back(new Accessory(name, color, price, false));
    }
}