//
//  PlayState.cpp
//  SDL Game Programming Book

#include <iostream>
#include "PlayState.h"
#include "GameOverState.h"
#include "PauseState.h"
#include "Game.h"


const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	TheInputHandler::Instance()->update();

    if(m_loadingComplete && !m_exiting)
    {

		if (TheInputHandler::Instance()->isButtonDown(SDL_CONTROLLER_BUTTON_BACK))
		{
			TheGame::Instance()->getStateMachine()->pushState(new PauseState());
			TheGame::Instance()->update();
		}
        
       TheGame::Instance()->advanceFrame();
    }
}

bool PlayState::onEnter()
{
    
	TheGame::Instance()->beginLevel();
 
	m_loadingComplete = true;

 
    std::cout << "Game is now playing. (Entered PlayState)\n";

    return true;
}

bool PlayState::onExit()
{
	TheGame::Instance()->endLevel();
    m_exiting = true;
    
    std::cout << "exiting PlayState\n";
    return true;
}
