#include "cPlayerCharacter.h"

#include <iostream>

cPlayerCharacter::~cPlayerCharacter()
{

}

void cPlayerCharacter::Tick()
{
	cPhysicsObject::Tick();
	
}

void cPlayerCharacter::Initialize(bool _bPlayer1, bool _bIsKeyboard)
{
	// Set controls and player # 
	m_bIsKeyboard = _bIsKeyboard;
	m_bPlayer1 = _bPlayer1;

	if (m_bPlayer1)
	{
		m_currentColor = m_allColors[0];
	}
	else
	{
		m_currentColor = m_allColors[1];
	}
}

void cPlayerCharacter::ProcessMovement()
{
	if (m_bIsKeyboard)
	{
		if (m_bPlayer1)		// PLAYER 1 MOVEMENT CONTROLS
		{
			// Move right
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				m_b2Body->ApplyLinearImpulseToCenter(b2Vec2(1.0f, 0.0f), true);
			}

			// Move left
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				m_b2Body->ApplyLinearImpulseToCenter(b2Vec2(-1.0f, 0.0f), true);
			}

			// Jump
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				m_b2Body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, 10.0f), true);
			}
		}
		else				// PLAYER 2 MOVEMENT CONTROLS
		{
			// Move right
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				m_b2Body->ApplyLinearImpulseToCenter(b2Vec2(1.0f, 0.0f), true);
			}

			// Move left
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				m_b2Body->ApplyLinearImpulseToCenter(b2Vec2(-1.0f, 0.0f), true);
			}

			// Jump
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				m_b2Body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, 10.0f), true);
			}
		}
	
	}
}

void cPlayerCharacter::Interact()
{

}

void cPlayerCharacter::CycleColor()
{
	int index = 0;
	for (int i = 0; i < m_allColors.size(); i++)
	{
		if (m_allColors[i] == m_currentColor)
		{
			index = i;
			break;
		}
	}

	// Change to the following color if not at the end of vector
	if (index < m_allColors.size())
	{
		m_currentColor = m_allColors[index + 1];
	}
	else // Wrap around to the first color
	{
		m_currentColor = m_allColors[0];
	}
}
