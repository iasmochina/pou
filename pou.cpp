#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

class Food {
    char* name;
    int hungerPoints;
    bool isHealthy;
    float pleasurePoints;
    double price;

public:
    Food();
    Food(char*, int, bool, float, double);
    Food(const Food &obj);
    Food& operator=(const Food& obj);
    ~Food();

    friend ostream& operator<<(ostream&, const Food&);
    friend istream& operator>>(istream&, Food&);

    int getHungerPoints() const { return hungerPoints; }
    float getPleasurePoints() const { return pleasurePoints; }
    double getPrice() const { return price; }
    bool getIsHealthy() const { return isHealthy; }
};

Food::Food() {
    name = strcpy(new char[4], "N/A");
    hungerPoints = 0;
    isHealthy = false;
    pleasurePoints = 0.0;
    price = 0.0;
}

Food::Food(char* name, int hungerPoints, bool isHealthy, float pleasurePoints, double price) {
    this->name = strcpy(new char[strlen(name) + 1], name);
    this->hungerPoints = hungerPoints;
    this->isHealthy = isHealthy;
    this->pleasurePoints = pleasurePoints;
    this->price = price;
}

Food::Food(const Food &obj) {
    this->name = strcpy(new char[strlen(obj.name) + 1], obj.name);
    this->hungerPoints = obj.hungerPoints;
    this->isHealthy = obj.isHealthy;
    this->pleasurePoints = obj.pleasurePoints;
    this->price = obj.price;
}

Food& Food::operator=(const Food& obj) {
    if (this == &obj) {
        return *this;
    }
    delete[] this->name;
    this->name = strcpy(new char[strlen(obj.name) + 1], obj.name);
    this->hungerPoints = obj.hungerPoints;
    this->isHealthy = obj.isHealthy;
    this->pleasurePoints = obj.pleasurePoints;
    this->price = obj.price;
    return *this;
}

Food::~Food() {
    if (name != NULL) {
        delete[] name;
        name = NULL;
    }
}

ostream& operator<<(ostream& os, const Food& obj) {
    os << "Item: " << obj.name << endl;
    os << " -> Hunger points: " << obj.hungerPoints << endl;
    os << " -> Pleasure points: " << obj.pleasurePoints << endl;
    os << " -> Price " << obj.price << endl;
    os << " -> Is this healthy?" << (obj.isHealthy ? "Yes" : "No") << endl;
    return os;
}

istream& operator>>(istream& is, Food& obj) {
    char itemName[100];
    cout << "Enter item name: ";
    is >> itemName;

    if(obj.name) delete[] obj.name;

    cout << "Enter hunger points: ";
    is >> obj.hungerPoints;
    cout << "Enter pleasure points: ";
    is >> obj.pleasurePoints;
    cout << "Is this healthy? (0/1)";
    is >> obj.isHealthy;
    cout << "Enter price: ";
    is >> obj.price;

    return is;
}

class Pou {
    static int noPous;
    int id;
    char* name;
    float hunger;
    float health;
    float energy;
    float happiness;
    double coins;
    double experience;
    int level;

public:

    Pou();
    Pou(char*);
    Pou(const Pou&);
    Pou& operator=(const Pou&);
    ~Pou();

    friend ostream& operator<<(ostream&, const Pou&);
    friend istream& operator>>(istream&, Pou&);

    char* getName() const {
        return name;
    }

};

int Pou::noPous = 0;

Pou::Pou(char* name) : id(++noPous) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    this->hunger = 100;
    this->health = 100;
    this->energy = 100;
    this->happiness = 100;
    this->coins = 0;
    this->experience = 0;
    this->level = 1;
}
Pou::Pou(const Pou& obj) {
    this->id = obj.id;
    this->name = new char[strlen(obj.name) + 1];
    strcpy(this->name, obj.name);
    this->hunger = obj.hunger;
    this->health = obj.health;
    this->energy = obj.energy;
    this->happiness = obj.happiness;
    this->coins = obj.coins;
    this->experience = obj.experience;
    this->level = obj.level;
}
Pou& Pou::operator=(const Pou& obj) {
    if (this == &obj) {
        return* this;
    }
    delete[] this->name;
    this->name = strcpy(new char[strlen(obj.name) + 1], obj.name);
    this->hunger = obj.hunger;
    this->health = obj.health;
    this->energy = obj.energy;
    this->happiness = obj.happiness;
    this->coins = obj.coins;
    this->experience = obj.experience;
    this->level = obj.level;
    return *this;
}

ostream& operator<<(ostream& os, const Pou& obj) {
    os << "=============== CURRENT POU ===============" << endl;
    os << "ID: " << obj.id << " | Name: " << obj.name << " | Coins: " << obj.coins << endl;
    os << "Energy: " << obj.energy << " | Happiness: " << obj.happiness << " | Hunger: " << obj.hunger << endl;
    os << "Health: " << obj.health << " | Level: " << obj.level << " | Experience: " << obj.experience << endl;
    return os;
}

istream& operator>>(istream& is, Pou& obj) {
    char name[100];
    cout << "Enter" << obj.name <<"'s new name: ";
    is >> name;
    delete[] obj.name;
    obj.name = new char[strlen(name) + 1];
    strcpy(obj.name, name);
    return is;
}

Pou::~Pou() {
    if (name != NULL) {
        delete[] name;
        this->name = NULL;
    }
}

void printInteractMenu(const Pou& pou) {
    int option;
    cout << "____________________________________" << endl
        << "Choose what you want to do with " << pou.getName() << ":" << endl
        << "____________________________________" << endl;
    cout << "1. Feed " << pou.getName() << endl;
    cout << "2. Wash " << pou.getName() << endl;
    cout << "3. Play with " << pou.getName() << endl;
    cout << "4. Shop " << endl;
    cout << "5. Inventory " << endl;
    cout << "6. Go to Menu" << endl;
    cin >> option;
    switch (option) {
        case 6:
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
}

int createPou(vector<Pou>& pouList) {
    char name[50];
    cout << "Enter your Pou's name: ";
    cin >> name;

    pouList.push_back(Pou(name));
    cout << "Pou " << name << " successfully created!" << endl;
    cout << endl;

    return pouList.size() - 1;
}

void printMenu(vector<Pou>& pouList, int& currentPou) {
    int option;

    cout << "================== MENU ==================" << endl;
    cout << "1. Interact with " << pouList[currentPou].getName() << endl;
    cout << "2. Switch Pou" << endl;
    cout << "3. Create a new Pou" << endl;
    cout << "4. Inventory" << endl;
    cout << "5. Shop" << endl;
    cout << "6. Exit" << endl;

    cin >> option;
    switch (option) {
        case 1:
            printInteractMenu(pouList[currentPou]);
            break;
        case 2:
            int selectedPou;
            cout << "Select Pou (1-" << pouList.size() << "): " << endl;
            for (int i = 0; i < pouList.size(); i++) {
                cout << i+1 << "." << pouList[i].getName() << endl;
            }
            cin >> selectedPou;
            if (selectedPou >= 1 && selectedPou <= pouList.size()) {
                currentPou = selectedPou - 1;
            } else cout << "Invalid choice! Sticking to your current Pou." << endl;
            break;
        case 3:
            currentPou = createPou(pouList);
            break;
        case 6:
            cout << "Bye bye!";
            exit(0);
        default:
            cout << "Invalid choice!" << endl;
            break;
    }
}

void printShopMenu(){}
void printGamesMenu(){}

int main() {
    vector<Pou> pouList;
    int currentPou = 0;

    while (true) {
        cout << "========== POU ==========" << endl;
        if (pouList.empty()) {
            cout << "Create a Pou!" << endl;
            currentPou = createPou(pouList);
        } else {
            cout << pouList[currentPou] << endl;
            printMenu(pouList, currentPou);
        }
    }
}
