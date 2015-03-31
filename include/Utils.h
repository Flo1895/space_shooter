#ifndef UTILS_H_
#define UTILS_H_

#include <time.h>
#include <stdlib.h>

class Utils {
public:
  static void initPRNG();
  static int getRandomNumber(int min = 1, int max = 10);
};

#endif // UTILS_H_
