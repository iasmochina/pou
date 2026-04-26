#ifndef POU_H
#define POU_H

#include <string>
#include <vector>
#include <iostream>
#include "Food.h"
#include "Accessory.h"

using namespace std;

class Pou {
    static int noPous;
    int id;
    string name;
    int hunger;
    float health;
    int energy;
    int happiness;
    double coins;
    double experience;
    int level;
    vector<Food*> foodItems;
    vector<Accessory*> accessoryItems;

    void checkLevelUp();

public:
    Pou();
    Pou(string);
    Pou(const Pou&);
    Pou& operator=(const Pou&);
    ~Pou();

    friend ostream& operator<<(ostream&, const Pou&);
    friend istream& operator>>(istream&, Pou&);

    string getName() const { return name; }
    double getCoins() const { return coins; }
    int getHunger() const { return hunger; }
    float getHealth() const { return health; }
    int getEnergy() const { return energy; }
    int getHappiness() const { return happiness; }
    double getExperience() const { return experience; }
    int getLevel() const { return level; }
    vector<Food*>& getFoodItems() { return foodItems; }
    vector<Accessory*>& getAccessoryItems() { return accessoryItems; }

    void addCoins(double amount) { coins += amount; coins = max(0.0, coins); }
    void addHappiness(int amount) { happiness = min(100, max(0, happiness + amount)); }
    void addExperience(double amount) { experience += amount; checkLevelUp(); }
    void addEnergy(int amount) { energy = min(100, max(0, energy + amount)); }
    void addHunger(int amount) { hunger = min(100, max(0, hunger + amount)); }
    void pay(double amount) { coins -= amount; }
    int accessoryXpBonus() const;

    bool statIsZero() const { return hunger <= 0 || health <= 0; }

    void addFood(Food* f);
    void addAccessory(Accessory* a);
    void feed(Food& foodItem);
    void feedMenu();
    void sleep();

    void serialize(ostream& out) const;
    void deserialize(istream& in);
};

#endif