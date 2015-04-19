#ifndef HIGHSCORE_H_
#define HIGHSCORE_H_

#include <string>
#include <fstream>
#include <sstream>

class Highscore {
private:
  int highscore;
  std::string path;
  void loadFromFile();
  void saveToFile();

public:
  Highscore(std::string path);
  ~Highscore();
  void set(int kills);
  int get();
};

#endif // HIGHSCORE_H_
