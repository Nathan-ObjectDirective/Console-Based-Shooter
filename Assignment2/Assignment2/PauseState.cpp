#include "PauseState.h"
#include "PlayState.h"
#include "Game.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_resumePlay()
{
    TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::update()
{
	if (m_loadingComplete && !m_exiting)
	{
		cout << "Game is paused, press start to unpause." << endl;

		TheGame::Instance()->info();

		while(!TheInputHandler::Instance()->isButtonDown(SDL_CONTROLLER_BUTTON_START))
		{
			TheInputHandler::Instance()->update();
		}

		s_resumePlay(); // Pop this pause state and go back to playing the game
	}
}

bool PauseState::onEnter()
{
	
	
    m_loadingComplete = true;
    
    std::cout << "(Entering PauseState)\n";
    return true;
}

bool PauseState::onExit()
{
   
    std::cout << "exiting PauseState\n";
    return true;
}
