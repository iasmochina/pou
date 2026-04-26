#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <string>
#include <vector>

using namespace std;

class Game;
class Pou;

class SaveManager {
public:
    SaveManager();
    SaveManager(const SaveManager& other);
    SaveManager& operator=(const SaveManager& other);
    ~SaveManager();

    void savePou(const Pou& pou, const vector<Game*>& games, const string& filePath) const;
    void loadPou(Pou& pou, vector<Game*>& games, const string& filePath) const;

    void saveGames(const std::vector<Game*>& games, const std::string& filePath) const;
    void loadGames(std::vector<Game*>& games, const std::string& filePath) const;
};

#endif