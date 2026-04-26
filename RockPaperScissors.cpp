#include "RockPaperScissors.h"
#include "Pou.h"
#include "Utils.h"

#include <vector>

using namespace std;

RockPaperScissors::RockPaperScissors() : Game("RPS", 10), roundsPlayed(0), roundsWon(0) {}

RockPaperScissors::RockPaperScissors(const string& name, int rewardCoins, int roundsPlayed, int roundsWon) : Game(name, rewardCoins), roundsPlayed(roundsPlayed), roundsWon(roundsWon) {}

RockPaperScissors::RockPaperScissors(const RockPaperScissors& other) : Game(other), roundsPlayed(other.roundsPlayed), roundsWon(other.roundsWon) {}

RockPaperScissors& RockPaperScissors::operator=(const RockPaperScissors& other) {
    if (this != &other) {
        Game::operator=(other);
        roundsPlayed = other.roundsPlayed;
        roundsWon = other.roundsWon;
    }
    return *this;
}

RockPaperScissors::~RockPaperScissors() = default;


void RockPaperScissors::play(Pou& pou) {
    cout << "--- Rock, Paper, Scissors ---" << endl;
    cout << "Your record: " << roundsWon << "/" << roundsPlayed << " wins";
    if (roundsPlayed > 0) cout << " (" << (int)(winRate()*100) << "%)";
    cout << endl << endl;
    const string moves[] = {"", "Rock 🪨", "Paper 📄", "Scissors ✂️"};
    int userMove, pouMove = rand() % 3 + 1;

    cout << "Play against " << pou.getName() << ". Choose your move:" << endl;
    cout << "1. Rock 🪨" << endl;
    cout << "2. Paper 📄" << endl;
    cout << "3. Scissors ✂️" << endl;
    cin >> userMove;

    if (userMove < 1 || userMove > 3) {
        cout << "Invalid move!" << endl;
        proceed();
        return;
    }

    cout << "You chose: " << moves[userMove] << endl;
    cout << pou.getName() << " chose: " << moves[pouMove] << endl;

    int result = determineWinner(userMove, pouMove);
    roundsPlayed++;

    if (result == 0) {
        cout << "It's a draw." << endl;
        proceed();
    } else if (result == 1) {
        cout << "You won! 🏆" << endl;
        cout << "+10 happiness 😁" << endl;
        cout << "+" << getRewardCoins() << " coins 🤑" << endl;
        cout << "+10 experience 🟢" << endl;
        pou.addHappiness(10);
        pou.addCoins(getRewardCoins());
        pou.addExperience(10 + pou.accessoryXpBonus());
        roundsWon++;
        proceed();
    } else {
        cout << "You lost! Womp Womp :(" << endl;
        cout << "-10 happiness ☹️" << endl;
        pou.addHappiness(-10);
        proceed();
    }

    pou.addEnergy(-10);
    pou.addHunger(-10);
}


string RockPaperScissors::getType() const {
    return "RockPaperScissors";
}

int RockPaperScissors::determineWinner(int userChoice, int aiChoice) const {
    if (userChoice == aiChoice) return 0;
    if ((userChoice == 1 && aiChoice == 3) || (userChoice == 2 && aiChoice == 1) || (userChoice == 3 && aiChoice == 2)) return 1;
    return -1;
}

double RockPaperScissors::winRate() const {
    if (roundsPlayed == 0) return 0.0;
    return static_cast<double>(roundsWon) / static_cast<double>(roundsPlayed);
}

void RockPaperScissors::save(ostream& os) const {
    Game::save(os);
    os << roundsPlayed << '\n' << roundsWon << '\n';
}

void RockPaperScissors::load(istream& is) {
    Game::load(is);
    is >> roundsPlayed >> roundsWon;
}

void RockPaperScissors::display(ostream& os) const  {
    os << "✂️ Rock, Paper, Scissors" << endl;
    os << "   Rounds played: " << roundsPlayed << " | Won: " << roundsWon;
    if (roundsPlayed > 0) os << " | Win rate: " << (int)(winRate() * 100) << "%";
}

istream& operator>>(istream& is, RockPaperScissors& game) {
    is >> static_cast<Game&>(game);
    is >> game.roundsPlayed >> game.roundsWon;
    return is;
}

ostream& operator<<(ostream& os, const RockPaperScissors& game) {
    game.display(os);
    return os;
}