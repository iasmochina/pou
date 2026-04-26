#include "Item.h"

#include <string>

Item::Item() {
    name = "N/A";
    price = 0;
}

Item::Item(string name, int price) {
    this->name = name;
    this->price = price;
}

Item& Item::operator=(const Item& obj) {
    if (this == &obj) return *this;
    this->name = obj.name;
    this->price = obj.price;
    return *this;
}

Item::~Item() = default;

Item::Item(const Item& obj) {
    this->name = obj.name;
    this->price = obj.price;
}

ostream& operator<<(ostream& os, const Item& obj) {
    obj.display();
    return os;
}
