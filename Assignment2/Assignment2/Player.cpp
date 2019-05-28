#include "Player.h"


Player::Player() 
{
	m_healthDrain = 2;
	bulletCounter = 10;
}

Player::~Player()
{
}

void Player::update()
{
	controlManualAction();
}

// User tells the player what to do.
void Player::controlManualAction()
{
	movePlayer();
	m_vShotDetails = shoot();
}

// Handle the input and logic of the player shooting. This function leaves a lot to be desired in terms of implementation.
vector<pair<int, int>> Player::shoot() // User has told the Player to shoot.
{
	string userShootInput = "";
	bool isShootInputValid = true;

	vector<pair<int, int>> bulletSpread;
	const int shotXRange = 2;
	const int shotYRange = 2;

	bulletCounter++;
	m_isShooting = true;

	if (TheInputHandler::Instance()->isButtonDown(SDL_CONTROLLER_BUTTON_Y) && bulletCounter > 10) // 
	{
		for (int i = m_x - 1; i < (m_x + shotXRange); i++) // Shoot Across 3 x, centered on Player.
		{
			for (int j = m_y + 1; j <= (m_y + shotYRange + 1); j++) // Shoot Up 3 y, centered on Player.
			{
				if ((i <= MAXCOORDVALUE) && (j <= MAXCOORDVALUE))
				{
					if ((i >= MINCOORDVALUE) && (j >= MINCOORDVALUE))
					{
						TheSoundManager::Instance()->playSound("shotgun", 0);
						bulletSpread.push_back(make_pair(i, j)); // Save where the bullets went
						TheInputHandler::Instance()->callHaptic(); // Rumble the controller
						bulletCounter = 0;
					}
				}
			}
		}
	}
	else if (TheInputHandler::Instance()->isButtonDown(SDL_CONTROLLER_BUTTON_A) && bulletCounter > 10)
	{
		for (int i = m_x - 1; i < (m_x + shotXRange); i++) // Shoot Across 3 x, centered on Player.
		{
			for (int j = m_y - shotXRange - 1; j < (m_y); j++)  // Shoot Down 3 y, centered on Player.
			{
				if ((i <= MAXCOORDVALUE) && (j <= MAXCOORDVALUE))
				{
					if ((i >= MINCOORDVALUE) && (j >= MINCOORDVALUE))
					{
						TheSoundManager::Instance()->playSound("shotgun", 0);
						bulletSpread.push_back(make_pair(i, j)); // Save where the bullets went
						TheInputHandler::Instance()->callHaptic(); // Rumble the controller
						bulletCounter = 0;
					}
				}
			}
		}
	}
	else if (TheInputHandler::Instance()->isButtonDown(SDL_CONTROLLER_BUTTON_X) && bulletCounter > 10)
	{
		for (int i = m_x - shotXRange-1; i <= (m_x-1); i++) // Shoot Across and down 3 x, centered on Player.
		{
			for (int j = m_y - 1; j < (m_y + shotYRange); j++) // Shoot Right 3 y, centered on Player.
			{
				if ((i <= MAXCOORDVALUE) && (j <= MAXCOORDVALUE))
				{
					if ((i >= MINCOORDVALUE) && (j >= MINCOORDVALUE))
					{
						TheSoundManager::Instance()->playSound("shotgun", 0);
						bulletSpread.push_back(make_pair(i, j)); // Save where the bullets went
						TheInputHandler::Instance()->callHaptic(); // Rumble the controller
						bulletCounter = 0;
					}
				}
			}
		}
	}
	else if (TheInputHandler::Instance()->isButtonDown(SDL_CONTROLLER_BUTTON_B) && bulletCounter > 10)
	{
		for (int i = m_x + 1; i <= (m_x + shotXRange+1); i++) // Shoot Across and down 3 x, centered on Player.
		{
			for (int j = m_y - 1; j < (m_y + shotYRange); j++) // Shoot Left 3 y, centered on Player.
			{
				if ((i <= MAXCOORDVALUE) && (j <= MAXCOORDVALUE))
				{
					if ((i >= MINCOORDVALUE) && (j >= MINCOORDVALUE)) 
					{
						TheSoundManager::Instance()->playSound("shotgun", 0);

						bulletSpread.push_back(make_pair(i, j)); // Save where the bullets went
						TheInputHandler::Instance()->callHaptic(); // Rumble the controller
						bulletCounter = 0;
					}
				}
			}
		}
	}
	else
	{
		m_isShooting = false;
	}

	return bulletSpread;
}
// Player returns where he shot.
vector<pair<int, int>> Player::getShotDetails()
{
	return m_vShotDetails;
}

// User has told the Player to move.
void Player::movePlayer()
{
	// handle controller input
	if (TheInputHandler::Instance()->isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_UP))
	{
		if ((m_y + m_speed) > MAXCOORDVALUE)
		{
			m_y = MAXCOORDVALUE; // Hit a wall.
		}
		else
		{
			m_y += m_speed; // Go Up.
		}
	}
	else if (TheInputHandler::Instance()->isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_DOWN))
	{
		if ((m_y - m_speed) < MINCOORDVALUE)
		{
			m_y = MINCOORDVALUE; // Hit a wall.
		}
		else
		{
			m_y -= m_speed;  // Go Down
		}
	}

	if (TheInputHandler::Instance()->isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT))
	{
		if ((m_x - m_speed) < MINCOORDVALUE)
		{
			m_x = MINCOORDVALUE;  // Hit a wall.
		}
		else
		{
			m_x -= m_speed;  // Go Left.
		}
	}
	else if (TheInputHandler::Instance()->isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
	{
		if ((m_x + m_speed) > MAXCOORDVALUE)
		{
			m_x = MAXCOORDVALUE; // Hit a wall.
		}
		else
		{
			m_x += m_speed; // GoRight.
		}
	}
}

// Not yet implemented for this Player Class.
void Player::controlAutoMovement(pair<int, int>)
{
	// Empty for now. If the player ever moves from something other than input I will use this.
}