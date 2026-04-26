#ifndef GUESSTHENUM_H
#define GUESSTHENUM_H

#include "Game.h"
using namespace std;

class GuessTheNum : public Game {
    int totalGuesses;
    int correctGuesses;

public:
    GuessTheNum();
    GuessTheNum(const string& name, int rewardCoins, int totalGuesses, int correctGuesses);
    GuessTheNum(const GuessTheNum& other);
    GuessTheNum& operator=(const GuessTheNum& other);
    ~GuessTheNum() override;

    void play(Pou& pou) override;
    string getType() const override;

    double successRate() const;

    void save(ostream& os) const override;
    void load(istream& is) override;
    void display(ostream& os) const override;

    friend istream& operator>>(istream& is, GuessTheNum& game);
    friend ostream& operator<<(ostream& os, const GuessTheNum& game);
};

#endif