#include "SaveManager.h"
#include "Game.h"
#include "Pou.h"
#include "RockPaperScissors.h"
#include "GuessTheNum.h"
#include "SolveEq.h"

#include <fstream>
#include <stdexcept>

using namespace std;

SaveManager::SaveManager() = default;
SaveManager::SaveManager(const SaveManager& other) = default;
SaveManager& SaveManager::operator=(const SaveManager& other) = default;
SaveManager::~SaveManager() = default;

void SaveManager::savePou(const Pou& pou, const vector<Game*>& games, const string& filePath) const {
    ofstream out(filePath);
    if (!out.is_open()) throw runtime_error("Could not open save file.");
    pou.serialize(out);
    for (int i = 0; i < games.size(); i++) {
        games[i]->save(out);
    }
}

void SaveManager::loadPou(Pou& pou, vector<Game*>& games, const string& filePath) const {
    ifstream in(filePath);
    if (!in.is_open()) throw runtime_error("Could not open save file.");
    pou.deserialize(in);
    for (int i = 0; i < games.size(); i++) {
        games[i]->load(in);
    }
}

void SaveManager::saveGames(const vector<Game*>& games, const string& filePath) const {
    ofstream out(filePath);
    if (!out.is_open()) throw runtime_error("Could not open games save file for writing.");
    out << games.size() << '\n';
    for (int i = 0; i < games.size(); i++) {
        out << games[i]->getType() << '\n';
        games[i]->save(out);
    }
}

void SaveManager::loadGames(vector<Game*>& games, const string& filePath) const {
    ifstream in(filePath);
    if (!in.is_open()) throw runtime_error("Could not open games save file for reading.");

    int size;
    in >> size;

    for (int i = 0; i < size; i++) {
        string type;
        getline(in >> ws, type);

        if (type == "RockPaperScissors") {
            RockPaperScissors* g = new RockPaperScissors();
            g->load(in);
            games.push_back(g);
        } else if (type == "GuessNumberGame") {
            GuessTheNum* g = new GuessTheNum();
            g->load(in);
            games.push_back(g);
        } else if (type == "SolveEq") {
            SolveEq* g = new SolveEq();
            g->load(in);
            games.push_back(g);
        }
    }
}