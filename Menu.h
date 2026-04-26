#ifndef MENU_H
#define MENU_H

#include <vector>

using namespace std;

class Game;
class Pou;
class SaveManager;
class Shop;

class Menu {
    Pou* pou;
    vector<Game*> games;
    SaveManager* saveManager;
    Shop* shop;

    void handlePlay();
    void handleFeed();
    void handleSleep();
    void handleShop();
    void handleInventory();
    void handleStatistics();
    void newGame();
    bool loadGame();
public:
    Menu();
    Menu(const Menu& other);
    Menu& operator=(const Menu& other);
    ~Menu();

    void run();
    void printOptions() const;
    void handleChoice(int choice);
};

#endif