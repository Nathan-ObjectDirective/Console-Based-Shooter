#include "InputHandler.h"
#include "Game.h"
#include <iostream>

InputHandler* InputHandler::s_pInstance = 0;

InputHandler::InputHandler() :  m_bJoysticksInitialised(false)
{
}

InputHandler::~InputHandler()
{
}

void InputHandler::clean()
{
    // we need to clean up after ourselves and close the joysticks we opened
    if(m_bJoysticksInitialised)
    {
        for(int i = 0; i < SDL_NumJoysticks(); i++)
        {
			SDL_GameControllerClose(m_controller);
        }
    }
}

void InputHandler::initialiseJoysticks()
{
    // if we haven't already initialised the joystick subystem, we will do it here
    if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
    {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }
    
    // if there is a controller present
    if(SDL_NumJoysticks() > 0)
    {   
        // if the controller opened correctly we need to set it as our controller
        if(SDL_GameControllerOpen(0))
        {
            // Load the open controller 
			m_controller = SDL_GameControllerOpen(0);
        }
        else
        {
            // if there was an error initialising a controller we want to know about it
            std::cout << SDL_GetError();
        }

		// get controller haptic device
		gControllerHaptic = SDL_HapticOpen(0);

		if (gControllerHaptic == NULL)
		{
			printf("Warning: Controller does not support haptics! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			// get initialize rumble
			if (SDL_HapticRumbleInit(gControllerHaptic) < 0)
			{
				printf("Warning: Unable to initialize rumble! SDL Error: %s\n", SDL_GetError());
			}
		}
        
        // enable controller events
        SDL_GameControllerEventState(SDL_ENABLE);
        m_bJoysticksInitialised = true;
        
       // std::cout << "Initialised " << SDL_GameControllerName(m_controller) << "\n";
    }
    else
    {
        m_bJoysticksInitialised = false;
    }
}

// Rumble the controller
void InputHandler::callHaptic()
{
	SDL_HapticRumblePlay(gControllerHaptic, 0.75, 350);
}

// Get the state of a passed in button
bool InputHandler::isButtonDown(SDL_GameControllerButton  button) const
{
	bool isButtonDown = SDL_GameControllerGetButton(m_controller, button);
	
	return isButtonDown;
}

// Update the inputhandler by refresing the SDL_Event cache
void InputHandler::update()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
     
    }
}

