#include "Game.h"

Game::Game() : name("Unknown"), rewardCoins(0) {}

Game::Game(const std::string& name, int rewardCoins) : name(name), rewardCoins(rewardCoins) {}

Game::Game(const Game& other) : name(other.name), rewardCoins(other.rewardCoins) {}

Game& Game::operator=(const Game& other) {
    if (this != &other) {
        name = other.name;
        rewardCoins = other.rewardCoins;
    }
    return *this;
}

Game::~Game() = default;

void Game::save(std::ostream& out) const {
    out << name << '\n' << rewardCoins << '\n';
}

void Game::load(std::istream& in) {
    std::getline(in >> std::ws, name);
    in >> rewardCoins;
}

void Game::display(ostream& out) const {
    out << "Game name: " << name << ", reward coins: " << rewardCoins;
}

std::string Game::getName() const {
    return name;
}

int Game::getRewardCoins() const {
    return rewardCoins;
}

void Game::setName(const std::string& newName) {
    name = newName;
}

void Game::setRewardCoins(int newRewardCoins) {
    rewardCoins = newRewardCoins;
}

std::istream& operator>>(std::istream& is, Game& game) {
    std::getline(is >> std::ws, game.name);
    is >> game.rewardCoins;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Game& game) {
    game.display(os);
    return os;
}
