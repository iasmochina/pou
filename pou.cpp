#include <iostream>
#include <string.h>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;


class Menu {
    Menu();
};
// ----------------------ACCESSORY----------------------
class Accessory {
    static int noAccessoryItems;
    int id;
    char* name;
    char* color;
    int price;
    bool isEquipped;

public:
    Accessory();
    Accessory(int, char*, char*, int, bool);
    Accessory(const Accessory& obj);
    Accessory& operator=(const Accessory& obj);
    ~Accessory();

    friend ostream& operator<<(ostream&, const Accessory& obj);
    friend istream& operator>>(istream&, Accessory& obj);

};

int Accessory::noAccessoryItems = 0;

Accessory::Accessory() : id(++noAccessoryItems) {
    name = strcpy(new char[4], "N/A");
    color = strcpy(new char[4], "N/A");
    price = 0;
    isEquipped = false;
}
Accessory::Accessory(int id, char* name, char* color, int price, bool isEquipped) {
    this->id = id;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    this->color = new char [strlen(color) + 1];
    strcpy(this->color, color);
    this->price = price;
    this->isEquipped = isEquipped;
}
Accessory::Accessory(const Accessory &obj) {
    this->id = obj.id;
    this->name = strcpy(new char[strlen(obj.name) + 1], obj.name);
    this->color = strcpy(new char[strlen(obj.color) + 1], obj.color);
    this->price = obj.price;
    this->isEquipped = obj.isEquipped;
}
Accessory& Accessory::operator=(const Accessory& obj) {
    if (this == &obj) {
        return *this;
    }
    delete[] name;
    delete[] color;

    this->id = obj.id;
    this->name = strcpy(new char[strlen(obj.name) + 1], obj.name);
    this->color = strcpy(new char[strlen(obj.color) + 1], obj.color);
    this->price = obj.price;
    this->isEquipped = obj.isEquipped;

    return *this;
}
Accessory::~Accessory() {
    if (name != NULL) {
        delete[] name;
        name = NULL;
    }
    if (color != NULL) {
        delete[] color;
        color = NULL;
    }
}

ostream& operator<<(ostream& os, const Accessory& obj) {
    os << "Name: " << obj.name << endl;
    os << "Color: " << obj.color << endl;
    os << "Equipped: " << (obj.isEquipped ? "Yes" : "No") << endl;
    os << "Price: " << obj.price << endl;
    return os;
}
istream& operator>>(istream& is, Accessory& obj) {
    char name[50];
    cout << "Name: "; is >> name;
    delete[] obj.name;
    obj.name = new char[strlen(name) + 1];
    strcpy(obj.name, name);

    char color[50];
    cout << "Color: "; is >> obj.color;
    delete[] obj.color;
    obj.color = new char[strlen(color) + 1];
    strcpy(obj.color, color);

    obj.isEquipped = false;
    cout << "Price: "; is >> obj.price;
    cout << "==========================================" << endl;
    cout << obj.name << " successfully added!" << endl;
    cout << "==========================================" << endl;

    return is;
}

// ----------------------FOOD----------------------

class Food {
    static int noFoodItems;
    int id;
    char* name;
    int hungerPoints;
    bool isHealthy;
    float pleasurePoints;
    int quantity;
    double price;

public:
    Food();
    Food(int, char*, int, bool, float, int, double);
    Food(const Food &obj);
    Food& operator=(const Food& obj);
    ~Food();

    friend ostream& operator<<(ostream&, const Food&);
    friend istream& operator>>(istream&, Food&);

    int getHungerPoints() const { return hungerPoints; }
    float getPleasurePoints() const { return pleasurePoints; }
    double getPrice() const { return price; }
    bool getIsHealthy() const { return isHealthy; }
    int getQuantity() const { return quantity; }

    void setQuantity(const int q) { quantity = q; }
};

int Food::noFoodItems = 0;

Food::Food() : id(++noFoodItems) {
    name = strcpy(new char[4], "N/A");
    hungerPoints = 0;
    isHealthy = false;
    pleasurePoints = 0.0;
    quantity =0;
    price = 0.0;
}
Food::Food(int id, char* name, int hungerPoints, bool isHealthy, float pleasurePoints, int quantity, double price) : id(++noFoodItems) {
    this->id = id;
    this->name = strcpy(new char[strlen(name) + 1], name);
    this->hungerPoints = hungerPoints;
    this->isHealthy = isHealthy;
    this->pleasurePoints = pleasurePoints;
    this->quantity = quantity;
    this->price = price;
}
Food::Food(const Food &obj) : id(++noFoodItems) {
    this->id = obj.id;
    this->name = strcpy(new char[strlen(obj.name) + 1], obj.name);
    this->hungerPoints = obj.hungerPoints;
    this->isHealthy = obj.isHealthy;
    this->pleasurePoints = obj.pleasurePoints;
    this->quantity = obj.quantity;
    this->price = obj.price;
}
Food& Food::operator=(const Food& obj) {
    if (this == &obj) {
        return *this;
    }
    delete[] this->name;
    this->id = obj.id;
    this->name = strcpy(new char[strlen(obj.name) + 1], obj.name);
    this->hungerPoints = obj.hungerPoints;
    this->isHealthy = obj.isHealthy;
    this->pleasurePoints = obj.pleasurePoints;
    this->quantity = obj.quantity;
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

    if(obj.name != NULL) delete[] obj.name;
    obj.name = new char[strlen(itemName) + 1];
    strcpy(obj.name, itemName);

    cout << "Enter hunger points: ";
    is >> obj.hungerPoints;
    cout << "Enter pleasure points: ";
    is >> obj.pleasurePoints;
    cout << "Is this healthy? (0-No/1-Yes): ";
    is >> obj.isHealthy;
    cout << "Enter price: ";
    is >> obj.price;
    cout << "==========================================" << endl;
    cout << obj.name << " successfully added!" << endl;
    cout << "==========================================" << endl;

    return is;
}

//---------------------- SHOP ----------------------

class Shop {
    char* name;
    vector<Food> foodStock;
    vector<Accessory> accessoryStock;
    int totalFoodItems;
    int totalAccessoryItems;

public:
    Shop();
    Shop(char*, vector<Food> Food, vector<Accessory> Accessory, int, int);
    Shop(const Shop& obj);
    Shop& operator=(const Shop& obj);
    ~Shop();

    friend ostream& operator<<(ostream&, const Shop& obj);
    friend istream& operator>>(istream&, Shop& obj);

};

Shop::Shop() {
    name = strcpy(new char[4], "N/A");
    totalFoodItems = 0;
    totalAccessoryItems = 0;
}
Shop::Shop(char* name, vector<Food> foodStock, vector<Accessory> accessoryStock, int totalFoodItems, int totalAccessoryItems) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    this->foodStock = foodStock;
    this->accessoryStock = accessoryStock;
    this->totalFoodItems = totalFoodItems;
    this->totalAccessoryItems = totalAccessoryItems;
}
Shop::Shop(const Shop& obj) {
    this->name = new char[strlen(obj.name) + 1];
    strcpy(this->name, obj.name);
    this->foodStock = obj.foodStock;
    this->accessoryStock = obj.accessoryStock;
    this->totalFoodItems = obj.totalFoodItems;
    this->totalAccessoryItems = obj.totalAccessoryItems;
}
Shop& Shop::operator=(const Shop& obj) {
    if (this == &obj) {
        return* this;
    }
    delete[] name;
    this->name = new char[strlen(obj.name) + 1];
    strcpy(this->name, obj.name);
    this->foodStock = obj.foodStock;
    this->totalFoodItems = obj.totalFoodItems;
    this->totalAccessoryItems = obj.totalAccessoryItems;
    return* this;
}
Shop::~Shop() {
    delete[] name;
}

ostream& operator<<(ostream& os, const Shop& obj) {
    os << "=============== " << obj.name << " ===============" << endl;
    os << "---> FOOD:" << endl;
    if (obj.foodStock.empty()) os << "No food items available!" << endl;
    else for (int i = 0; i < obj.foodStock.size(); i++) {
        os << i + 1 << ". " <<obj.foodStock[i] << endl;
    }
    os << "---> ACCESSORIES:" << endl;
    if (obj.accessoryStock.empty()) os << "No accessory items available!" << endl;
    else for (int i = 0; i < obj.accessoryStock.size(); i++) {
        os << i + 1 << ". " << obj.accessoryStock[i] << endl;
    }

    return os;
}

istream& operator>>(istream& is, Shop& obj) {
    char name[50];
    cout << "Enter shop name (don't use spaces): "; is >> name;

    delete[] obj.name;
    obj.name = new char[strlen(name) + 1];
    strcpy(obj.name, name);

    int nrfood, nracc;

    cout << "How many food items do you want to add?:"; is >> nrfood;
    for (int i = 0; i < nrfood; i++) {
        Food f;
        is >> f;
        obj.foodStock.push_back(f);
    }

    cout << "How many accessory items do you want to add?:"; is >> nracc;
    for (int i = 0; i < nracc; i++) {
        Accessory a;
        is >> a;
        obj.accessoryStock.push_back(a);
    }

    return is;
}

//----------------------POU----------------------

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
    vector<Food> foodItems;
    vector<Accessory> accessoryItems;

    void checkLevelUp() {
        if (experience >= level*50) {
            level++;
            experience = 0;
            coins += 50;
            cout << name << " is now level " << level << "! 🥳 Keep going!" << endl << endl;
        }
    }

public:

    Pou();
    Pou(char*);
    Pou(const Pou&);
    Pou& operator=(const Pou&);
    ~Pou();

    friend ostream& operator<<(ostream&, const Pou&);
    friend istream& operator>>(istream&, Pou&);

    char* getName() const { return name; }

    bool pay(double amount) {
        if (coins >= amount) {
            coins -= amount;
            return true;
        } else return false;
    }

    void feed() {

    }

    void play() {
        int option;
        int back = false;
        while (!back) {
            cout << *this << endl;

            if (energy <= 0) {
                cout << "⚠️ " << name << " is too tired to play. Feed him something and come back!" << endl;
                back = true;
                continue;
            }

            cout << "Choose a game: " << endl;
            cout << "1. Guess the number" << endl;
            cout << "2. Solve the equation" << endl;
            cout << "3. Rock, paper, scissors" << endl;
            cout << "4. Exit" << endl;

            cin >> option;

            switch (option) {
                case 1: {
                    int guess, number = rand() % 10 + 1;
                    cout << "Guess a number between 1 and 10: " << endl;
                    cin >> guess;
                    if (guess == number) {
                        cout << "You guessed it!" << endl;
                        cout << "+10 happiness 😁" << endl;
                        cout << "+15 coins 🤑" << endl;
                        cout << "+10 experience 🟢" << endl;
                        happiness = min(100.0f, happiness+10);
                        coins += 15;
                        experience += 10;
                    } else {
                        cout << "Bummer! The answer was " << number << ". " << name << " is sadder now.."<< endl;
                        cout << "-10 happiness ☹️";
                        happiness = max(0.0f, happiness-10);
                    }
                    energy = max(0.0f, energy-10);
                    checkLevelUp();
                    break;
                }
                case 2: {
                    int op1 = rand() % 20 + 1, op2 = rand() % 20 + 1, symb = rand() % 3 + 1, res, guess;
                    cout << "Solve the equation!:" << endl;
                    if (symb == 1) { //plus
                        cout << op1 << "+" << op2 << "=";
                        res = op1 + op2;
                    } else if (symb == 2) { //minus
                        cout << op1 << "-" << op2 << "=";
                        res = op1 - op2;
                    } else { //multiply
                        cout << op1 << "*" << op2 << "=";
                        res = op1 * op2;
                    }
                    cin >> guess;
                    if (guess == res) {
                        cout << endl << "Correct!" << endl;
                        cout << "+5 happiness 😁" << endl;
                        cout << "+10 coins 🤑" << endl;
                        cout << "+10 experience 🟢" << endl;
                        happiness = min(100.0f, happiness+5);
                        coins += 10;
                        experience += 10;
                    } else {
                        cout << "Bummer! The answer was " << res << ". " << name << " is sadder now.."<< endl;
                        cout << "-10 happiness ☹️";
                        happiness = max(0.0f, happiness-10);
                    }
                    energy = max(0.0f, energy-10);
                    checkLevelUp();
                    break;
                }
                case 3: {
                    const char* moves[] = {"", "Rock 🪨", "Paper 📄", "Scissors ✂️"};
                    int userMove, pouMove = rand() % 3 + 1;
                    cout << "Play against " << name << ". Choose your move:" << endl;
                    cout << "1. Rock 🪨" << endl;
                    cout << "2. Paper 📄" << endl;
                    cout << "3. Scissors ✂️" << endl;

                    cin >> userMove;

                    if (userMove < 1 || userMove > 3) {
                        cout << "Invalid move!" << endl;
                    } else {
                        cout << "You chose: " << moves[userMove]  << endl;
                        cout << name << " chose: " << moves[pouMove] << endl;

                        if (userMove == pouMove) cout << "It's a draw." << endl;
                        else if ((userMove == 1 && pouMove == 3) || (userMove == 2 && pouMove == 1) || (userMove == 3 && pouMove == 2)) {
                            cout << "You won! 🏆";
                            cout << "+10 happiness 😁" << endl;
                            cout << "+10 coins 🤑" << endl;
                            cout << "+10 experience 🟢" << endl;
                            happiness = min(100.0f, happiness+10);
                            coins += 10;
                            experience += 10;
                        } else {
                            cout << "You lost! Womp Womp :(" << endl;
                            cout << "-10 happiness ☹️";
                            happiness = max(0.0f, happiness-10);
                        }
                        energy = max(0.0f, energy-10);
                    }
                    checkLevelUp();
                    break;
                }
                case 4: {
                    back = true;
                    break;
                }
                default:
                    cout<< "Invalid option. Try again." << endl;
                    break;
            }

        }

    }
};

int Pou::noPous = 0;
Pou::Pou() : id(++noPous) {
    name = strcpy(new char[4], "N/A");
    hunger = 100;
    health = 100;
    energy = 100;
    happiness = 100;
    coins = 0;
    experience = 0;
    level = 1;
}
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
Pou::~Pou() {
    if (name != NULL) {
        delete[] name;
        this->name = NULL;
    }
}

ostream& operator<<(ostream& os, const Pou& obj) {
    os << "=============== CURRENT POU ===============" << endl;
    os << "ID: " << obj.id << " | Name: " << obj.name << " | Coins: " << obj.coins << endl;
    os << "Energy: " << obj.energy << " | Happiness: " << obj.happiness << " | Hunger: " << obj.hunger << " | Health: " << obj.health << endl;
    os << "Level: " << obj.level << " | Experience: " << obj.experience << endl;
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

void printInteractMenu(Pou& pou) {
    int option;
    cout << "____________________________________" << endl
        << "Choose what you want to do with " << pou.getName() << ":" << endl
        << "____________________________________" << endl;
    cout << "1. Feed " << pou.getName() << " 🍕" << endl;
    cout << "2. Play with " << pou.getName() << " 🎮 " << endl;
    cout << "3. Shop " << " 🛍️ " << endl;
    cout << "4. Inventory " << " 🎒 " << endl;
    cout << "5. Go to Menu" << endl;
    cin >> option;
    switch (option) {
        case 1:
            break;
        case 2:
            pou.play();
            break;
        case 5:

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

int main() {
    srand(time(0));
    vector<Pou> pouList;
    int currentPou = 0;
    Shop shop;

    cout << "First of all, let's configure your store!" << endl;
    cin >> shop;
    cout << "Success!" << endl;

    while (true) {
        // cout << "=============== POU ===============" << endl;
        if (pouList.empty()) {
            cout << "Create a Pou!" << endl;
            currentPou = createPou(pouList);
        } else {
            cout << pouList[currentPou] << endl;
            printMenu(pouList, currentPou);
        }
    }
}

// ADAUGA CLASA MENIU, cu constructor default!
