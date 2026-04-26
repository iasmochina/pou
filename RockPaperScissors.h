#ifndef ROCKPAPERSCISSORS_H
#define ROCKPAPERSCISSORS_H

#include "Game.h"
#include <string>

using namespace std;
class RockPaperScissors : public Game {
    int roundsPlayed;
    int roundsWon;

public:
    RockPaperScissors();
    RockPaperScissors(const string& name, int rewardCoins, int roundsPlayed, int roundsWon);
    RockPaperScissors(const RockPaperScissors& other);
    RockPaperScissors& operator=(const RockPaperScissors& other);
    ~RockPaperScissors() override;

    void play(Pou& pou) override;
    string getType() const override;

    int determineWinner(int userChoice, int aiChoice) const;
    double winRate() const;

    void save(ostream& out) const override;
    void load(istream& in) override;
    void display(ostream& out) const override;

    friend istream& operator>>(istream& in, RockPaperScissors& game);
    friend ostream& operator<<(ostream& out, const RockPaperScissors& game);
};

#endif
