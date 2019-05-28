#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <iostream>
#include <vector>

#include "SDL.h"

class InputHandler
{
public:
    
    static InputHandler* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new InputHandler();
        }
        
        return s_pInstance;
    }
    
    // init joysticks
    void initialiseJoysticks();
    bool joysticksInitialised() const { return m_bJoysticksInitialised; }
    
    
    // update and clean the input handler
    void update();
    void clean();
   
    // controller events
	
	bool isButtonDown(SDL_GameControllerButton  button) const;
	void callHaptic();
      
private:
    
    InputHandler();
    ~InputHandler();
    
    InputHandler(const InputHandler&);
    // private functions to handle different event types
    
    // joystick specific
    SDL_GameController* m_controller;
	SDL_Haptic* gControllerHaptic = NULL;

    bool m_bJoysticksInitialised;

    // The instance of the singleton
    static InputHandler* s_pInstance;
};
typedef InputHandler TheInputHandler;


#endif /* defined(__SDL_Game_Programming_Book__InputHandler__) */
