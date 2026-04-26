#include "Menu.h"
#include "Pou.h"
#include "Game.h"
#include "GuessTheNum.h"
#include "RockPaperScissors.h"
#include "SolveEq.h"
#include "SaveManager.h"
#include "Shop.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

Menu::Menu() {
    pou = nullptr;
    saveManager = new SaveManager();
    games.push_back(new RockPaperScissors());
    shop = new Shop();
    shop->loadFood("data/foods.txt");
    shop->loadAccessories("data/accessories.txt");
    games.push_back(new GuessTheNum());
    games.push_back(new SolveEq());
}

Menu::Menu(const Menu& other) {
    pou = new Pou(*other.pou);
    saveManager = new SaveManager(*other.saveManager);
    shop = new Shop(*other.shop);
    games.push_back(new RockPaperScissors(*dynamic_cast<RockPaperScissors*>(other.games[0])));
    games.push_back(new GuessTheNum(*dynamic_cast<GuessTheNum*>(other.games[1])));
    games.push_back(new SolveEq(*dynamic_cast<SolveEq*>(other.games[2])));
}

Menu& Menu::operator=(const Menu& other) {
    if (this != &other) {
        delete pou;
        delete saveManager;
        delete shop;
        for (int i = 0; i < games.size(); i++) delete games[i];
        games.clear();

        pou = new Pou(*other.pou);
        saveManager = new SaveManager(*other.saveManager);
        games.push_back(new RockPaperScissors(*dynamic_cast<RockPaperScissors*>(other.games[0])));
        games.push_back(new GuessTheNum(*dynamic_cast<GuessTheNum*>(other.games[1])));
        games.push_back(new SolveEq(*dynamic_cast<SolveEq*>(other.games[2])));
    }
    return *this;
}

Menu::~Menu() {
    delete pou;
    delete saveManager;
    delete shop;
    for (int i = 0; i < games.size(); i++) delete games[i];
}

void Menu::newGame() {
    string name;
    cout << "Enter your Pou's name: ";
    cin >> name;
    pou = new Pou(name);
    cout << "Pou " << name << " successfully created!" << endl;
}

bool Menu::loadGame() {
    ifstream in("data/save.txt");
    if (!in.is_open() || in.peek() == ifstream::traits_type::eof()) {
        cout << "\n=== Load Game ===" << endl;
        cout << "No saved Pou found! Start a new game first. 🐣" << endl;
        proceed();
        return false;
    }

    pou = new Pou();
    pou->deserialize(in);
    for (int i = 0; i < games.size(); i++) {
        games[i]->load(in);
    }

    cout << "\n=== Load Game ===" << endl;
    cout << "1. " << pou->getName() << " | Level " << pou->getLevel() << " | Coins: " << pou->getCoins() << endl;
    cout << "2. Back" << endl;

    int choice = getIntInRange(1, 2);
    if (choice == 2) {
        delete pou;
        pou = nullptr;
        return false;
    }

    cout << "Welcome back, " << pou->getName() << "! 👋" << endl;
    return true;
}

void Menu::handlePlay() {
    if (pou->getEnergy() <= 0) {
        cout << "⚠️ " << pou->getName() << " is too tired to play!" << endl;
        proceed();
        return;
    }
    bool back = false;
    while (!back) {
        cout << *pou << endl;
        cout << "\n=== Choose a game ===" << endl;
        cout << "1. Guess the Number 🎲" << endl;
        cout << "2. Solve the Equation 🧮" << endl;
        cout << "3. Rock, Paper, Scissors ✂️" << endl;
        cout << "4. Back" << endl;

        int option = getIntInRange(1,4);
        switch (option) {
            case 1: games[1]->play(*pou); break;
            case 2: games[2]->play(*pou); break;
            case 3: games[0]->play(*pou); break;
            case 4: back = true; break;
            default: cout << "Invalid option!" << endl;
        }
        if (pou->statIsZero()) return;
    }
}

void Menu::handleFeed() {
    pou->feedMenu();
}

void Menu::handleSleep() {
    pou->sleep();
}

void Menu::handleShop() {
    bool back = false;
    while (!back) {
        cout << "\n=== " << shop->getName() << " 🛒 ===" << endl;
        cout << "1. Food 🍗" << endl;
        cout << "2. Accessories 🧢" << endl;
        cout << "3. Back" << endl;

        int option = getSafeIntOption();
        if (option == 1) {
            const vector<Item*>& stock = shop->getFoodStock();
            if (stock.empty()) { cout << "No food available!" << endl; continue; }
            for (int i = 0; i < stock.size(); i++) cout << i+1 << ". " << *stock[i] << endl;
            cout << stock.size()+1 << ". Back" << endl;

            int choice = getSafeIntOption();
            if (choice == stock.size()+1) continue;
            if (choice >= 1 && choice <= stock.size()) {
                Item* selected = shop->buyFood(choice-1);
                if (pou->getCoins() < selected->getPrice()) {
                    cout << "Not enough coins! ❌" << endl;
                    proceed();
                } else {
                    pou->addFood(dynamic_cast<Food*>(selected));
                    pou->pay(selected->getPrice());
                    cout << "Bought " << selected->getName() << "! 💸" << endl;
                    proceed();
                }
            }
        } else if (option == 2) {
            const vector<Item*>& stock = shop->getAccessoryStock();
            if (stock.empty()) { cout << "No accessories available!" << endl; proceed(); continue; }
            for (int i = 0; i < stock.size(); i++) cout << i+1 << ". " << *stock[i] << endl;
            cout << stock.size()+1 << ". Back" << endl;

            int choice = getSafeIntOption();
            if (choice == stock.size()+1) continue;
            if (choice >= 1 && choice <= stock.size()) {
                Item* selected = shop->buyAccessory(choice-1);
                if (pou->getCoins() < selected->getPrice()) {
                    cout << "Not enough coins! ❌" << endl;
                    proceed();
                } else {
                    pou->addAccessory(dynamic_cast<Accessory*>(selected));
                    pou->pay(selected->getPrice());
                    cout << "Bought " << selected->getName() << "! 💸" << endl;
                    proceed();
                }
            }
        } else back = true;
    }
}

void Menu::handleInventory() {
    bool back = false;
    while (!back) {
        cout << "\n=== Inventory 🎒 ===" << endl;
        cout << "1. Food 🥤" << endl;
        cout << "2. Accessories 🧢" << endl;
        cout << "3. Back" << endl;

        int option = getSafeIntOption();
        if (option == 1) {
            if (pou->getFoodItems().empty()) { cout << "No food available!" << endl; proceed(); continue; }
            for (int i = 0; i < pou->getFoodItems().size(); i++) {
                cout << i+1 << ". " << *pou->getFoodItems()[i] << " | x" << pou->getFoodItems()[i]->getQuantity() << endl;
            }
            proceed();
        } else if (option == 2) {
            if (pou->getAccessoryItems().empty()) { cout << "No accessories available!" << endl; proceed(); continue; }
            for (int i = 0; i < pou->getAccessoryItems().size(); i++) {
                cout << i+1 << ". " << *pou->getAccessoryItems()[i];
                cout << (pou->getAccessoryItems()[i]->getIsEquipped() ? " [EQUIPPED]" : "") << endl;
            }
            cout << "Select accessory to equip/unequip: ";
            int choice = getSafeIntOption();
            if (choice >= 1 && choice <= pou->getAccessoryItems().size()) {
                Accessory* a = pou->getAccessoryItems()[choice-1];
                a->setIsEquipped(!a->getIsEquipped());
                cout << a->getName() << (a->getIsEquipped() ? " equipped! ✅" : " unequipped!") << endl;
                proceed();
            }
        } else back = true;
    }
}

void Menu::handleStatistics() {
    cout << "\n=== Statistics 📊 ===" << endl;
    for (int i = 0; i < games.size(); i++) {
        cout << *games[i] << endl;
    }
    proceed();
}

void Menu::run() {
    bool running = true;
    while (running) {
        cout << "\n=== POO Squared ===" << endl;
        cout << "1. New Game 🐣" << endl;
        cout << "2. Load Game 💾" << endl;
        cout << "3. Exit" << endl;

        int choice = getIntInRange(1,3);
        if (choice == 1) newGame();
        else if (choice == 2) loadGame();
        else { running = false; continue; }

        if (pou == nullptr) continue;

        bool inGame = true;
        while (inGame && pou) {
            if (pou->statIsZero()) {
                cout << pou->getName() << " died! 😱☠️" << endl;
                cout << "╔═══╗─────────╔═══╗" << endl;
                cout << "║╔═╗║─────────║╔═╗║" << endl;
                cout << "║║─╚╬══╦╗╔╦══╗║║─║╠╗╔╦══╦═╗" << endl;
                cout << "║║╔═╣╔╗║╚╝║║═╣║║─║║╚╝║║═╣╔╝" << endl;
                cout << "║╚╩═║╔╗║║║║║═╣║╚═╝╠╗╔╣║═╣║" << endl;
                cout << "╚═══╩╝╚╩╩╩╩══╝╚═══╝╚╝╚══╩╝" << endl;
                delete pou;
                pou = nullptr;
                inGame = false;
                running = false;
                return;
            }

            cout << *pou << endl;
            cout << "================== MENU ==================" << endl;
            cout << "1. Play with " << pou->getName() << " 🎮" << endl;
            cout << "2. Feed " << pou->getName() << " 🍕" << endl;
            cout << "3. Put " << pou->getName() << " to sleep 😴" << endl;
            cout << "4. Shop 🛍️" << endl;
            cout << "5. Inventory 🎒" << endl;
            cout << "6. Statistics 📊" << endl;
            cout << "7. Save & Exit" << endl;

            int option = getIntInRange(1,6);
            switch (option) {
                case 1: handlePlay(); break;
                case 2: handleFeed(); break;
                case 3: handleSleep(); break;
                case 4: handleShop(); break;
                case 5: handleInventory(); break;
                case 6: handleStatistics(); break;
                case 7:
                    saveManager->savePou(*pou, games, "data/save.txt");
                    inGame = false;
                    running = false;
                    break;
                default: {
                    cout << "Invalid option!" << endl;
                    proceed();
                }
            }
        }
    }
}
