#include <iostream>
#include "MainMenuState.h"
#include "Game.h"
#include "PlayState.h"

const std::string MainMenuState::s_menuID = "MENU";

// Callbacks
void MainMenuState::s_menuToPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
    TheGame::Instance()->quit();
}

void MainMenuState::update()
{
	cout << "\n Press start to begin the game." << endl;

	// Wait for the player to press start to continue
	while (TheInputHandler::Instance()->isButtonDown(SDL_CONTROLLER_BUTTON_START) == false)
	{
		TheInputHandler::Instance()->update();
	}

	s_menuToPlay();
}

bool MainMenuState::onEnter()
{
	std::cout << "Simulation initialised! \n";
   
    std::cout << "(Entering the Menu State)\n";

	// Story and Instructions.
	cout << "\n\t Welcome Recruit! \n" << endl;
	cout << " You've entered the training grounds of Z++ Industries.\n" << endl;
	cout << " I understand you're here to get some practice in against the dangling pointer Zombies, eh? \n" << endl;

	cout << " Well, here's your Combat Shotgun. You can shoot 3 tiles wide and across and you can freely move about the map. \n" << endl;
	cout << " While the Zombies can't find you they will dash around 2 tiles at a time.\n" << endl;
	cout << " If they catch wind of you they will slow down and begin the hunt, to 1 tile at a time.\n" << endl;

	cout << " Mind your blind spots. At close ranges they will dash around, dodging your shots.\n" << endl;

	cout << " Make sure to line up em at a good distance and then... SPLATT!\n\n" << endl;

	cout << " Be careful though, son. If they manage to reach you, you're done for." << endl;

	cout << " As you progress through the floors the zombies will get faster and faster." << endl;

	cout << "\n You can move around using the DPAD on your control device and shoot with A, B, X and Y.\n" << endl;
	cout << "\n How many can you take down before you perish, soldier?." << endl;

	m_loadingComplete = true;

    return true;
}

bool MainMenuState::onExit()
{
    m_exiting = true;
    
    std::cout << "exiting MenuState\n";
    return true;
}

