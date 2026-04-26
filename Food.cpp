#define RED "\033[31m"
#define RESET "\033[0m"
#include "Food.h"

using namespace std;

int Food::noFoodItems = 0;

Food::Food() : Item("N/A", 0), id(++noFoodItems) {
    hungerPoints = 0;
    isHealthy = false;
    healthPoints = 0.0;
    quantity = 0;
}
Food::Food(string name, int hungerPoints, bool isHealthy, float healthPoints, int quantity, int price) : Item(name, price), id(++noFoodItems) {
    this->hungerPoints = hungerPoints;
    this->isHealthy = isHealthy;
    this->healthPoints = healthPoints;
    this->quantity = quantity;
}

Food::Food(const Food &obj) : Item(obj), id(++noFoodItems) {
    this->hungerPoints = obj.hungerPoints;
    this->isHealthy = obj.isHealthy;
    this->healthPoints = obj.healthPoints;
    this->quantity = obj.quantity;
}
Food& Food::operator=(const Food& obj) {
    if (this == &obj) {
        return *this;
    }
    Item::operator=(obj);
    this->id = obj.id;
    this->hungerPoints = obj.hungerPoints;
    this->isHealthy = obj.isHealthy;
    this->healthPoints = obj.healthPoints;
    this->quantity = obj.quantity;
    return *this;
}
Food::~Food() = default; 

ostream& operator<<(ostream& os, const Food& obj) {
    os << "Item: " << obj.getName() << " | ";
    os << "Hunger points: " << obj.hungerPoints << " | ";
    os << "Health points: " << obj.healthPoints << " | ";
    os << "Price: " << obj.getPrice() << " | ";
    os << "Is this healthy? " << (obj.isHealthy ? "Yes" : "No") ;
    return os;
}
istream& operator>>(istream& is, Food& obj) {
    string itemName;
    cout << "Enter item name: ";
    is >> itemName;
    obj.setName(itemName);

    cout << "Enter hunger points: ";
    while (!(is >> obj.hungerPoints)) {
        cout << RED << "Use only numbers! (0-100)" << RESET << endl << "Your value: ";
        is.clear();
        is.ignore(1000, '\n');
    }

    cout << "Enter health points: ";
    while (!(is >> obj.healthPoints)) {
        cout << RED << "Use only numbers! (0-100)" << RESET << endl << "Your value: ";
        is.clear();
        is.ignore(1000, '\n');
    }

    cout << "Is this healthy? (0-No/1-Yes): ";
    while (!(is >> obj.isHealthy)) {
        cout << RED << "Use only 0(False) or 1(True)! " << RESET << endl << "Your value: ";
        is.clear();
        is.ignore(1000, '\n');
    }

    int price;
    cout << "Enter price: ";
    while (!(is >> price)) {
        cout << RED << "Use only numbers! (1-100)" << RESET << endl << "Your value: ";
        is.clear();
        is.ignore(1000, '\n');
    }
    obj.setPrice(price);

    cout << "==========================================" << endl;
    cout << obj.getName() << " successfully added!" << endl;
    cout << "==========================================" << endl;

    return is;
}

void Food::display() const {
    cout << "Item: " << getName() << " | ";
    cout << "Hunger points: " << hungerPoints << " | ";
    cout << "Health points: " << healthPoints << " | ";
    cout << "Price: " << getPrice() << " | ";
    cout << "Is this healthy? " << (isHealthy ? "Yes" : "No") ;
}
