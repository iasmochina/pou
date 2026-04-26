#ifndef FOOD_H
#define FOOD_H

#include "Item.h"

#include <string>
#include <iostream>

using namespace std;

class Food : public Item {
    static int noFoodItems;
    int id;
    int hungerPoints;
    bool isHealthy;
    float healthPoints;
    int quantity;

    public:
        Food();
        Food(string, int, bool, float, int, int);
        Food(const Food& obj);
        Food& operator=(const Food& obj);
        ~Food();

        friend ostream& operator<<(ostream&, const Food&);
        friend istream& operator>>(istream&, Food&);

        void display() const override;

        int getId() const { return id; }
        int getHungerPoints() const { return hungerPoints; }
        float getHealthPoints() const { return healthPoints; }
        bool getIsHealthy() const { return isHealthy; }
        int getQuantity() const { return quantity; }

        void setQuantity(const int q) { quantity = q; }
};

#endif