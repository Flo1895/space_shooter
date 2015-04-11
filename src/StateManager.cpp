#include "StateManager.h"

StateManager::StateManager()
: curGameState(MENU) {}

StateManager::~StateManager() {}

GameState StateManager::getState() {
  return this->curGameState;
}

void StateManager::setState(GameState gameState) {
  this->curGameState = gameState;
}
