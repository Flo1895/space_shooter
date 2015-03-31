#include "Utils.h"

void Utils::initPRNG() {
  srand(time(NULL));
}

int Utils::getRandomNumber(int min, int max) {
  return rand() % max + min;
}
