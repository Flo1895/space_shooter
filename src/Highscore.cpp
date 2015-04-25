#include "Highscore.h"

#include <iostream>
#include <cstdlib>

Highscore::Highscore(std::string path)
: highscore(0),
  path(path) {
  this->loadFromFile();
}

Highscore::~Highscore() {}

void Highscore::set(int kills) {
  this->highscore = kills;

  this->saveToFile();
}

int Highscore::get() {
  return this->highscore;
}

void Highscore::loadFromFile() {
  std::string line;
  std::ifstream highscoreFile(this->path);
  if (highscoreFile.is_open()) {
    getline(highscoreFile, line);
    if (line != "") {
      this->highscore = std::atoi(line.c_str());
    }
    highscoreFile.close();
  }
}

void Highscore::saveToFile() {
  remove(this->path.c_str());
  std::ofstream highscoreFile(this->path);
  if (highscoreFile.is_open()) {
    highscoreFile << this->highscore;
    highscoreFile.close();
  }
}
