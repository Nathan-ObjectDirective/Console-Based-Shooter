#include "LevelChangeState.h"

const std::string LevelChangeState::s_transitionID = "LEVEL_CHANGE";

void LevelChangeState::update()
{
	if (m_loadingComplete && !m_exiting)
	{
		TheGame::Instance()->getStateMachine()->changeState(new PlayState());
	}
}

void LevelChangeState::render()
{
}

bool LevelChangeState::onEnter()
{
	m_loadingComplete = true;
	std::cout << "Entering Level Change State\n";
	return true;
}

bool LevelChangeState::onExit()
{
	m_exiting = true;

	std::cout << "Exiting Level Change State\n";

	return true;
}
