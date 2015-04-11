#include "Highscore.h"

#include <iostream>

Highscore::Highscore(std::string path)
: path(path) {
  this->loadFromFile();
}

Highscore::~Highscore() {}

void Highscore::add(int kills, std::string playerName) {
  this->loadFromFile();

  this->highscore[kills] = playerName;
  
  // remove entry with lowest kills if number of entries > 10
  if (this->highscore.size() > 10) {
    this->highscore.erase(this->highscore.begin());
  }

  this->saveToFile();
}

std::map<int, std::string, std::greater<int>> Highscore::get() {
  return this->highscore;
}

int Highscore::size() {
  return this->highscore.size();
}

void Highscore::loadFromFile() {
  std::string line;
  std::ifstream highscoreFile(this->path);
  if (highscoreFile.is_open()) {
    while (getline(highscoreFile, line)) {
      std::size_t pos = line.find("||");
      std::string name = line.substr(0, pos);
      std::string kills = line.substr(pos+2, std::string::npos);
      this->highscore[atoi(kills.c_str())] = name;
    }
    highscoreFile.close();
  }
}

void Highscore::saveToFile() {
  remove(this->path.c_str());
  std::ofstream highscoreFile(this->path);
  if (highscoreFile.is_open()) {
    for (auto& highscoreEntryPair : this->highscore) {
      highscoreFile << highscoreEntryPair.second << "||" << highscoreEntryPair.first << "\n";
    }
    highscoreFile.close();
  }
}
