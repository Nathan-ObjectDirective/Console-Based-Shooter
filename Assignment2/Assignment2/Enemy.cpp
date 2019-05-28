#include "Enemy.h"

Enemy::Enemy()
{
	m_healthDrain = 3;
	direction = static_cast<Direction>(rand() % NUMCARDINALDIRECTIONS); // Casting an int representing a Cardinal Direction to a Direction enum.
	m_updates = 0;
}

Enemy::~Enemy()
{
	cout << "\nZombie down!\n" << endl;
}

void Enemy::update()
{
	// Increase the enemy update rate as the game progresses, making them faster.
	int updateSpeed = 12 - TheGame::Instance()->getLevel();
	m_updates++;

	// If a certain amount of updates has passed, they can move again.
	if (m_updates > updateSpeed)
	{
		determineMovement();

		m_updates = 0;
	}

}

// Basic state manipulation
void Enemy::determineMovement()
{
	if (m_isPassive)
	{
		m_speed = 2; // The zombies are much quicker running around when they aren't aware of the player.
		performPassiveMovement();
	}
	else
	{
		m_speed = 1;  // They slow down and start to converge on you.
		performAgressiveMovement();
	}
}

// Makes the Enemy do their normal passive patrol routine.
void Enemy::performPassiveMovement()
{
	if (direction == Up)
	{
		if ((m_y + m_speed) > MAXCOORDVALUE)
		{
			m_y = MAXCOORDVALUE; // Hit a wall.
			direction = Down; // Reverse Direction.
		}
		else
		{
			m_y += m_speed; 
		}
	}
	else if (direction == Left)
	{

		if ((m_x - m_speed) < MINCOORDVALUE)
		{
			m_x = MINCOORDVALUE; // Hit a wall.
			direction = Right; // Reverse Direction.
		}
		else
		{
			m_x -= m_speed;
		}
	}
	else if (direction == Down)
	{
		if ((m_y - m_speed) < MINCOORDVALUE)
		{
			m_y = MINCOORDVALUE; // Hit a wall.
			direction = Up; // Reverse Direction.
		}
		else
		{
			m_y -= m_speed;;
		}

	}
	else if (direction == Right)
	{
		if ((m_x + m_speed) > MAXCOORDVALUE)
		{
			m_x = MAXCOORDVALUE; // Hit a wall.
			direction = Left; // Reverse Direction.
		}
		else
		{
			m_x += m_speed;
		}
	}
}

void Enemy::performAgressiveMovement()
{
	m_x += m_autoMovementAdjust.first;
	m_y += m_autoMovementAdjust.second;	
}


void Enemy::controlAutoMovement(pair<int, int> coordsToMove)
{
	m_autoMovementAdjust.first = coordsToMove.first;
	m_autoMovementAdjust.second = coordsToMove.second;

	const int slowDownRange = 6;
}

vector<pair<int, int>> Enemy::shoot()
{
	return vector<pair<int, int>>();
	// Empty for now.
}

vector<pair<int, int>> Enemy::getShotDetails()
{
	return vector<pair<int, int>>();
	// Empty for now.
}

void Enemy::controlManualAction()
{
	// Empty for now.
}