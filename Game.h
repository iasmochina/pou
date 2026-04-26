#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
using namespace std;

class Pou;

class Game {
    std::string name;
    int rewardCoins;

public:
    Game();
    Game(const string& name, int rewardCoins);
    Game(const Game& other);
    Game& operator=(const Game& other);
    virtual ~Game();

    virtual void play(Pou& pou) = 0;
    virtual string getType() const = 0;

    virtual void save(ostream& out) const;
    virtual void load(istream& in);
    virtual void display(ostream& out) const;

    string getName() const;
    int getRewardCoins() const;
    void setName(const string& newName);
    void setRewardCoins(int newRewardCoins);

    friend istream& operator>>(istream& in, Game& game);
    friend ostream& operator<<(ostream& out, const Game& game);
};

#endif
