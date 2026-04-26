#include "SolveEq.h"
#include "Pou.h"
#include "Utils.h"
#include <iostream>
#include <cstdlib>

using namespace std;

SolveEq::SolveEq() : Game("Solve Equation", 15), equationsSolved(0), correctAnswers(0) {}

SolveEq::SolveEq(const string& name, int rewardCoins, int equationsSolved, int correctAnswers)
    : Game(name, rewardCoins), equationsSolved(equationsSolved), correctAnswers(correctAnswers) {}

SolveEq::SolveEq(const SolveEq& other)
    : Game(other), equationsSolved(other.equationsSolved), correctAnswers(other.correctAnswers) {}

SolveEq& SolveEq::operator=(const SolveEq& other) {
    if (this != &other) {
        Game::operator=(other);
        equationsSolved = other.equationsSolved;
        correctAnswers = other.correctAnswers;
    }
    return *this;
}

SolveEq::~SolveEq() = default;

void SolveEq::play(Pou& pou) {
    cout << "--- Solve the Equation ---" << endl;
    cout << "Your record: " << correctAnswers << "/" << equationsSolved;
    if (equationsSolved > 0) cout << " (" << (int)successRate() << "%)";
    cout << endl << endl;
    int op1 = rand() % 20 + 1;
    int op2 = rand() % 20 + 1;
    int symb = rand() % 3 + 1;
    int res, guess;

    cout << "Solve the equation!" << endl;

    if (symb == 1) {
        cout << op1 << " + " << op2 << " = ";
        res = op1 + op2;
    } else if (symb == 2) {
        cout << op1 << " - " << op2 << " = ";
        res = op1 - op2;
    } else {
        cout << op1 << " * " << op2 << " = ";
        res = op1 * op2;
    }

    cin >> guess;
    equationsSolved++;

    if (guess == res) {
        cout << "Correct! 🎉" << endl;
        cout << "+5 happiness 😁" << endl;
        cout << "+" << getRewardCoins() << " coins 🤑" << endl;
        cout << "+10 experience 🟢" << endl;
        pou.addHappiness(5);
        pou.addCoins(getRewardCoins());
        pou.addExperience(10 + pou.accessoryXpBonus());
        correctAnswers++;
        proceed();
    } else {
        cout << "Bummer! The answer was " << res << ". " << pou.getName() << " is sadder now.." << endl;
        cout << "-10 happiness ☹️" << endl;
        pou.addHappiness(-10);
        proceed();
    }

    pou.addEnergy(-10);
    pou.addHunger(-10);
}

string SolveEq::getType() const {
    return "SolveEq";
}

double SolveEq::successRate() const {
    if (equationsSolved == 0) return 0.0;
    return static_cast<double>(correctAnswers) / static_cast<double>(equationsSolved) * 100.0;
}

void SolveEq::save(ostream& os) const {
    Game::save(os);
    os << '\n' << equationsSolved << '\n' << correctAnswers << '\n';
}

void SolveEq::load(istream& is) {
    Game::load(is);
    is >> equationsSolved >> correctAnswers;
}
void SolveEq::display(ostream& os) const {
    os << "🧮 Solve the Equation" << endl;
    os << "   Solved: " << equationsSolved << " | Correct: " << correctAnswers;
    if (equationsSolved > 0) os << " | Success rate: " << (int)successRate() << "%";
}

istream& operator>>(istream& is, SolveEq& game) {
    is >> static_cast<Game&>(game);
    is >> game.equationsSolved >> game.correctAnswers;
    return is;
}

ostream& operator<<(ostream& os, const SolveEq& game) {
    game.display(os);
    return os;
}