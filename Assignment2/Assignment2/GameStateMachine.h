#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H

#include <vector>
#include "GameState.h"

class GameStateMachine
{
public:
    
    GameStateMachine() {}
    ~GameStateMachine() {}
    
    void update(); // Update the current state.
    
    void pushState(GameState* pState); // Push a state onto the stack
    void changeState(GameState* pState); // Change from one state to another
    void popState(); // Pop a state off the stack
    
    void clean();

	std::vector<GameState*>& getGameStates() { return m_gameStates; }
    
private:
    std::vector<GameState*> m_gameStates;
};

#endif
