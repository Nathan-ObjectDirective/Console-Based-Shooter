#include "GameStateMachine.h"
#include <iostream>

void GameStateMachine::clean()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->onExit();

        delete m_gameStates.back();
        
        m_gameStates.clear();
    }
}

// Update the gamestates
void GameStateMachine::update()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->update();
	}
}

// Push a state onto the stack
void GameStateMachine::pushState(GameState *pState)
{
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

// Pop a state off the stack
void GameStateMachine::popState()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->onExit();
        m_gameStates.pop_back();
    }
    
    m_gameStates.back()->resume();
}

// Change from one state to another
void GameStateMachine::changeState(GameState *pState)
{
    if(!m_gameStates.empty())
    {
        if(m_gameStates.back()->getStateID() == pState->getStateID())
        {
            return; // do nothing
        }

		m_gameStates.back()->onExit();
		m_gameStates.pop_back();
    }

	// initialise it
    pState->onEnter();
    
    // push back our new state
    m_gameStates.push_back(pState);
}