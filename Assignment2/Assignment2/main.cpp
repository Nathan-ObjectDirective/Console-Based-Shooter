#define _CRT_SECURE_NO_WARNINGS

#include "Game.h"
#include "SDL.h"
#include "SoundManager.h"
#include <Windows.h>

using namespace std;

const int FPS = 10;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char **argv)
{
	srand(time(NULL)); // Seed random.
	SDL_Init(SDL_INIT_EVERYTHING); // Initialise all of the SDL components

	std::cout << "Attempting to init simulation...\n";

	Uint32 frameStart, frameTime; 

	if (TheGame::Instance()->init())
	{
			while (TheGame::Instance()->isRunning()) // While the game state is in active play.
			{
				frameStart = SDL_GetTicks();

				TheGame::Instance()->update(); // Update the entities of the world
				TheGame::Instance()->battle(); // Resolve battle between enemy and player
				TheGame::Instance()->clean(); // Clean up anything that has died

				frameTime = SDL_GetTicks() - frameStart;

				// If we haven't travelled far through the sands of time
				if (frameTime < DELAY_TIME)
				{
					SDL_Delay((int)(DELAY_TIME - frameTime));
				}
			}	

			string repeatPlayInput = "";
	}
	else
	{
		std::cout << "game init failure - " << "\n";
		return -1;
	}

	std::cout << "\n Game closing...\n";
	TheGame::Instance()->clean(); // Clean up any remaining objects.


	cout << "\n\n\tPlease press Start to exit..." << endl;
	cout << "\t";

	// Wait until the player has pressed start.
	while (!TheInputHandler::Instance()->isButtonDown(SDL_CONTROLLER_BUTTON_START))
	{
		TheInputHandler::Instance()->update();
	}

	cout << "\n\t\tThanks for playing!\n\n" << endl;

	cout << "\nExiting Z++ Industries Simulation Program..." << endl;
	
	Sleep(3400);
	return 0;
}