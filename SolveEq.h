#ifndef SOLVEEQ_H
#define SOLVEEQ_H

#include "Game.h"

using namespace std;

class SolveEq : public Game {
    int equationsSolved;
    int correctAnswers;

public:
    SolveEq();
    SolveEq(const string& name, int rewardCoins, int equationsSolved, int correctAnswers);
    SolveEq(const SolveEq& other);
    SolveEq& operator=(const SolveEq& other);
    ~SolveEq() override;

    void play(Pou& pou) override;
    string getType() const override;

    double successRate() const;

    void save(ostream& out) const override;
    void load(istream& in) override;
    void display(ostream& out) const override;

    friend istream& operator>>(istream& is, SolveEq& game);
    friend ostream& operator<<(ostream& os, const SolveEq& game);
};

#endif
