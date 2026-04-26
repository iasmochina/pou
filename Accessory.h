#ifndef POO_SQUARED_ACCESSORY_H
#define POO_SQUARED_ACCESSORY_H

#include "Item.h"

#include <iostream>
#include <string>

using namespace std;

class Accessory : public Item {
    static int noAccessoryItems;
    int id;
    string color;
    bool isEquipped;

public:
    Accessory();
    Accessory(string, string, int, bool);
    Accessory(const Accessory& obj);
    Accessory& operator=(const Accessory& obj);
    ~Accessory();

    friend ostream& operator<<(ostream&, const Accessory& obj);
    friend istream& operator>>(istream&, Accessory& obj);

    void display() const override;

    string getColor() const { return color; }
    bool getIsEquipped() const { return isEquipped; }
    int getId() const { return id; }

    void setIsEquipped(bool e) { isEquipped = e; }
};

#endif