#include "GuessTheNum.h"
#include "Pou.h"
#include "Utils.h"
#include <iostream>

using namespace std;

GuessTheNum::GuessTheNum() : Game("Guess the Number", 10), totalGuesses(0), correctGuesses(0) {}

GuessTheNum::GuessTheNum(const string& name, int rewardCoins, int totalGuesses, int correctGuesses)
    : Game(name, rewardCoins), totalGuesses(totalGuesses), correctGuesses(correctGuesses) {}

GuessTheNum::GuessTheNum(const GuessTheNum& other)
    : Game(other), totalGuesses(other.totalGuesses), correctGuesses(other.correctGuesses) {}

GuessTheNum& GuessTheNum::operator=(const GuessTheNum& other) {
    if (this != &other) {
        Game::operator=(other);
        totalGuesses = other.totalGuesses;
        correctGuesses = other.correctGuesses;
    }
    return *this;
}

GuessTheNum::~GuessTheNum() = default;

void GuessTheNum::play(Pou& pou) {
    cout << "--- Guess the Number ---" << endl;
    cout << "Your record: " << correctGuesses << "/" << totalGuesses;
    if (totalGuesses > 0) cout << " (" << (int)successRate() << "%)";
    cout << endl << endl;
    int guess, number = rand() % 10 + 1;
    cout << "Guess a number between 1 and 10: ";
    cin >> guess;
    totalGuesses++;

    if (guess == number) {
        cout << "You guessed it! 🎉" << endl;
        cout << "+10 happiness 😁" << endl;
        cout << "+" << getRewardCoins() << " coins 🤑" << endl;
        cout << "+10 experience 🟢" << endl;
        pou.addHappiness(10);
        pou.addCoins(getRewardCoins());
        pou.addExperience(10 + pou.accessoryXpBonus());
        correctGuesses++;
    } else {
        cout << "Bummer! The answer was " << number << ". " << pou.getName() << " is sadder now.." << endl;
        cout << "-10 happiness ☹️" << endl;
        pou.addHappiness(-10);
    }

    pou.addEnergy(-10);
    pou.addHunger(-10);
    proceed();
}

string GuessTheNum::getType() const {
    return "GuessTheNum";
}

double GuessTheNum::successRate() const {
    if (totalGuesses == 0) return 0.0;
    return static_cast<double>(correctGuesses) / static_cast<double>(totalGuesses) * 100.0;
}

void GuessTheNum::save(ostream& os) const {
    Game::save(os);
    os << totalGuesses << '\n' << correctGuesses << '\n';
}

void GuessTheNum::load(istream& is) {
    Game::load(is);
    is >> totalGuesses >> correctGuesses;
}
void GuessTheNum::display(ostream& out) const {
    out << "🎲 Guess the Number" << endl;
    out << "   Total guesses: " << totalGuesses << " | Correct: " << correctGuesses;
    if (totalGuesses > 0) out << " | Success rate: " << (int)successRate() << "%";
}

istream& operator>>(istream& is, GuessTheNum& game) {
    is >> static_cast<Game&>(game);
    is >> game.totalGuesses >> game.correctGuesses;
    return is;
}

ostream& operator<<(ostream& os, const GuessTheNum& game) {
    game.display(os);
    return os;
}