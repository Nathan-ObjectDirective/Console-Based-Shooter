
#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include <iostream>
#include <vector>
#include "GameState.h"
#include "MenuState.h"

class GameObject;

class PauseState : public MenuState
{
public:
    
    virtual ~PauseState() {}
    
    virtual void update();
    
    virtual bool onEnter();
    virtual bool onExit();
    
    virtual std::string getStateID() const { return s_pauseID; }

private:
    
    static void s_resumePlay();
    
    static const std::string s_pauseID;
};

#endif
