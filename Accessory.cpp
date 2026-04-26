#include "Accessory.h"

#include <iostream>
#include <string>

using namespace std;

int Accessory::noAccessoryItems = 0;

Accessory::Accessory() : Item("N/A", 0), id(++noAccessoryItems) {
    color = "N/A";
    isEquipped = false;
}
Accessory::Accessory(string name, string color, int price, bool isEquipped) : Item(name, price), id(++noAccessoryItems) {
    this->color = color;
    this->isEquipped = isEquipped;
}
Accessory::Accessory(const Accessory &obj) : Item(obj), id(++noAccessoryItems) {
    this->color = obj.color;
    this->isEquipped = obj.isEquipped;
}
Accessory& Accessory::operator=(const Accessory& obj) {
    if (this == &obj) return *this;
    Item::operator=(obj);
    this->color = obj.color;
    this->isEquipped = obj.isEquipped;

    return *this;
}
Accessory::~Accessory() = default;

ostream& operator<<(ostream& os, const Accessory& obj) {
    os << "Name: " << obj.getName() << " | ";
    os << "Color: " << obj.color << " | ";
    os << "Equipped: " << (obj.isEquipped ? "Yes" : "No") << " | ";
    os << "Price: " << obj.getPrice();
    return os;
}
istream& operator>>(istream& is, Accessory& obj) {
    string name;
    cout << "Name: "; is >> name;
    obj.setName(name);

    string color;
    cout << "Color: "; is >> color;
    obj.color = color;

    int price;
    obj.isEquipped = false;
    cout << "Price: "; is >> price;
    cout << "==========================================" << endl;
    cout << obj.getName() << " successfully added!" << endl;
    cout << "==========================================" << endl;
    obj.setPrice(price);

    return is;
}

void Accessory::display() const {
    cout << "Name: " << getName() << " | ";
    cout << "Color: " << color << " | ";
    cout << "Equipped: " << (isEquipped ? "Yes" : "No") << " | ";
    cout << "Price: " << getPrice();
}