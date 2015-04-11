#ifndef HIGHSCORE_H_
#define HIGHSCORE_H_

#include <map>
#include <string>
#include <fstream>
#include <sstream>

class Highscore {
private:
  // map contains kills as keys and player names as values
  std::map<std::string, std::string> highscore;
  std::map<std::string, std::string>::iterator highscoreIt;
  std::string path;
  void loadFromFile();
  void saveToFile();

public:
  Highscore(std::string path);
  ~Highscore();
  void add(int kills, std::string playerName);
  std::map<std::string, std::string> get();
};

#endif // HIGHSCORE_H_
