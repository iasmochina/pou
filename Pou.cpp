#include "Pou.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>

using namespace std;

int Pou::noPous = 0;

void Pou::checkLevelUp() {
    if (experience >= level * 50) {
        level++;
        experience = 0;
        coins += 50;
        cout << name << " is now level " << level << "! 🥳 Keep going!" << endl;
    }
}

Pou::Pou() : id(++noPous), name("N/A"), hunger(100), health(100), energy(100), happiness(100), coins(0), experience(0), level(1) {}

Pou::Pou(string name) : id(++noPous), name(name), hunger(100), health(100), energy(100), happiness(100), coins(0), experience(0), level(1) {}

Pou::Pou(const Pou& obj) : id(++noPous) {
    this->name = obj.name;
    this->hunger = obj.hunger;
    this->health = obj.health;
    this->energy = obj.energy;
    this->happiness = obj.happiness;
    this->coins = obj.coins;
    this->experience = obj.experience;
    this->level = obj.level;
    this->foodItems = obj.foodItems;
    this->accessoryItems = obj.accessoryItems;
}

Pou& Pou::operator=(const Pou& obj) {
    if (this == &obj) return *this;
    this->name = obj.name;
    this->hunger = obj.hunger;
    this->health = obj.health;
    this->energy = obj.energy;
    this->happiness = obj.happiness;
    this->coins = obj.coins;
    this->experience = obj.experience;
    this->level = obj.level;
    this->foodItems = obj.foodItems;
    this->accessoryItems = obj.accessoryItems;
    return *this;
}

Pou::~Pou() {
    for (auto f : foodItems) delete f;
    for (auto a : accessoryItems) delete a;
}

void Pou::addFood(Food* f) {
    for (int i = 0; i < foodItems.size(); i++) {
        if (foodItems[i]->getName() == f->getName()) {
            foodItems[i]->setQuantity(foodItems[i]->getQuantity() + 1);
            return;
        }
    }
    Food* newItem = new Food(*f);
    newItem->setQuantity(1);
    foodItems.push_back(newItem);
}

void Pou::addAccessory(Accessory* a) {
    accessoryItems.push_back(new Accessory(*a));
}

void Pou::feed(Food& foodItem) {
    hunger = min(100, hunger + foodItem.getHungerPoints());
    if (foodItem.getIsHealthy()) {
        health = min(100.0f, health + foodItem.getHealthPoints());
    } else {
        health = max(0.0f, health + foodItem.getHealthPoints());
    }
    foodItem.setQuantity(foodItem.getQuantity() - 1);
}

void Pou::feedMenu() {
    if (statIsZero()) return;
    if (foodItems.empty()) {
        cout << "No food available!" << endl;
        proceed();
        return;
    }
    cout << "============== FOOD 🥤 ==============" << endl;
    for (int i = 0; i < foodItems.size(); i++) {
        cout << i+1 << ". " << *foodItems[i] << " | Quantity: x" << foodItems[i]->getQuantity() << endl;
    }
    cout << foodItems.size() + 1 << ". Back" << endl;

    int option;
    cout << "Choose what to feed " << name << ": ";
    option = getSafeIntOption();

    if (option < 1 || option > (int)foodItems.size()) {
        cout << "Invalid option!" << endl;
        proceed();
        return;
    }
    feed(*foodItems[option-1]);
    cout << name << " ate " << foodItems[option-1]->getName() << " 😋" << endl;
    if (foodItems[option-1]->getQuantity() == 0) {
        delete foodItems[option-1];
        foodItems.erase(foodItems.begin() + option - 1);
    }
    proceed();
}

void Pou::sleep() {
    if (energy >= 70) {
        cout << name << " is not tired. Try again later." << endl;
        proceed();
        return;
    }
    cout << name << " got some sleep and now is feeling energetic 🔋" << endl;
    energy = 100;
    proceed();
}

int Pou::accessoryXpBonus() const {
    int bonus = 0;
    for (int i = 0; i < accessoryItems.size(); i++) {
        if (accessoryItems[i]->getIsEquipped()) {
            bonus += accessoryItems[i]->getPrice() / 10;
        }
    }
    return bonus;
}

ostream& operator<<(ostream& os, const Pou& obj) {
    os << "=============== CURRENT POU ===============" << endl;
    os << "ID: " << obj.id << " | Name: " << obj.name << " | Coins: " << obj.coins << endl;
    os << "⚡️ Energy: " << obj.energy << endl;
    os << "😄 Happiness: " << obj.happiness << endl;
    os << "🍗 Hunger: " << obj.hunger << endl;
    os << "❤️ Health: " << obj.health << endl;
    os << "Level: " << obj.level << " | Experience: " << obj.experience << endl;
    return os;
}

istream& operator>>(istream& is, Pou& obj) {
    string name;
    cout << "Enter Pou's name: ";
    is >> name;
    obj.name = name;
    return is;
}

void Pou::serialize(ostream& os) const {
    os << name << '\n';
    os << hunger << '\n';
    os << health << '\n';
    os << energy << '\n';
    os << happiness << '\n';
    os << coins << '\n';
    os << experience << '\n';
    os << level << '\n';
    os << foodItems.size() << '\n';
    for (int i = 0; i < foodItems.size(); i++) {
        os << foodItems[i]->getName() << '\n';
        os << foodItems[i]->getQuantity() << '\n';
    }
    os << accessoryItems.size() << '\n';
    for (int i = 0; i < accessoryItems.size(); i++) {
        os << accessoryItems[i]->getName() << '\n';
    }
}

void Pou::deserialize(istream& is) {
    getline(is >> ws, name);
    is >> hunger >> health >> energy >> happiness >> coins >> experience >> level;

    int foodSize;
    is >> foodSize;
    for (int i = 0; i < foodSize; i++) {
        string foodName;
        int quantity;
        getline(is >> ws, foodName);
        is >> quantity;
        Food* f = new Food(foodName, 0, false, 0, quantity, 0);
        foodItems.push_back(f);
    }

    int accSize;
    is >> accSize;
    for (int i = 0; i < accSize; i++) {
        string accName;
        getline(is >> ws, accName);
        Accessory* a = new Accessory(accName, "N/A", 0, false);
        accessoryItems.push_back(a);
    }
}