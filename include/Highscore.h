#ifndef HIGHSCORE_H_
#define HIGHSCORE_H_

#include <map>
#include <string>
#include <fstream>
#include <sstream>

class Highscore {
private:
  // map contains kills as keys and player names as values
  std::map<int, std::string, std::greater<int>> highscore;
  std::string path;
  void loadFromFile();
  void saveToFile();

public:
  Highscore(std::string path);
  ~Highscore();
  void add(int kills, std::string playerName);
  std::map<int, std::string, std::greater<int>> get();
  int size();
};

#endif // HIGHSCORE_H_
