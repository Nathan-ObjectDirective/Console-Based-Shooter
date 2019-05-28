/*
	Gamestate abstract class.
*/

#ifndef GAMESTATE_h
#define GAMESTATE_h

#include <string>
#include <vector>

class GameState
{
public:
    
    virtual ~GameState() {}
    
    virtual void update() = 0; // Update the FSM
    virtual bool onEnter() = 0; // What happens when the state is entered
    virtual bool onExit() = 0; // What happens when the state is exited
    
    virtual void resume() {}
    
    virtual std::string getStateID() const = 0;
    
protected:
    
    GameState() : m_loadingComplete(false), m_exiting(false)
    {
        
    }
    
    bool m_loadingComplete;
    bool m_exiting;

};

#endif
