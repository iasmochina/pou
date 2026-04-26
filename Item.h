#ifndef ITEM_H
#define ITEM_H


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Item {
    string name;
    int price;
public:
    Item();
    Item(string, int);
    Item(const Item& obj);
    Item& operator=(const Item& obj);
    virtual ~Item();

    string getName() const { return name; }
    int getPrice() const { return price; }
    void setName(const string& n) { name = n; }
    void setPrice(const int p) { price = p; }

    virtual void display() const = 0;

    friend ostream& operator<<(ostream& os, const Item& obj);
    friend istream& operator>>(istream& is, Item& obj);
};

#endif