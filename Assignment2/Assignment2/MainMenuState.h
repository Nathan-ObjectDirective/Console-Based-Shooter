#ifndef INITIALMENUSTATE_H
#define INITIALMENUSTATE_H

#include <vector>
#include "MenuState.h"
#include "GameObject.h"

class MainMenuState : public MenuState
{
public:
    
    virtual ~MainMenuState() {}

    virtual void update();
    
    virtual bool onEnter(); 
    virtual bool onExit(); 
    
    virtual std::string getStateID() const { return s_menuID; }
    
private:
    
    static void s_menuToPlay();
    static void s_exitFromMenu();
    
    static const std::string s_menuID;
};

#endif
