#ifndef STATE_MANAGER_H_
#define STATE_MANAGER_H_

#include "GameState.h"

class StateManager {
public:
  StateManager();
  ~StateManager();
  GameState getState();
  void setState(GameState state);

private:
  GameState curGameState;
};

#endif // STATE_MANAGER_H_
