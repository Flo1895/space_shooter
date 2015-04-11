#include "Highscore.h"

Highscore::Highscore(std::string path)
: path(path) {
  this->loadFromFile();
}

Highscore::~Highscore() {}

void Highscore::add(int kills, std::string playerName) {
  this->loadFromFile();

  // convert kills from int to string
  std::ostringstream killsStringstream;
  killsStringstream << kills;
  this->highscore[killsStringstream.str()] = playerName;
  
  // remove entry with lowest kills if number of entries > 10
  if (this->highscore.size() > 10) {
    this->highscore.erase(this->highscore.begin());
  }

  this->saveToFile();
}

std::map<std::string, std::string> Highscore::get() {
  return this->highscore;
}

void Highscore::loadFromFile() {
  std::string line;
  std::ifstream highscoreFile(this->path);
  if (highscoreFile.is_open()) {
    while (getline(highscoreFile, line)) {
      std::size_t pos = line.find("||");
      std::string kills = line.substr(0, pos-1);
      std::string name = line.substr(pos+1, std::string::npos);
      this->highscore[kills] = name;
    }
    highscoreFile.close();
  }
}

void Highscore::saveToFile() {
  std::ofstream highscoreFile(this->path);
  if (highscoreFile.is_open()) {
    for (highscoreIt = highscore.begin();
         highscoreIt != highscore.end();
         ++highscoreIt) {
      highscoreFile << highscoreIt->second << "||" << highscoreIt->first << "\n";
    }
    highscoreFile.close();
  }
}
