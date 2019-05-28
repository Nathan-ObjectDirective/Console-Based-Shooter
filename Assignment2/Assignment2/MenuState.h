#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"

// This class only acts as a go between for the game state inheritance as GameState is an abstract class
class MenuState : public GameState
{
public:
    
    virtual ~MenuState() {}
    
protected:
    
};


#endif
