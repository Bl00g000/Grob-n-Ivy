#include "cPlayerCharacter.h"

#include <iostream>

cPlayerCharacter::~cPlayerCharacter()
{
	delete m_interactableObject;
}

void cPlayerCharacter::Tick()
{
	cPhysicsObject::Tick();
	
}

void cPlayerCharacter::Initialize(bool _bPlayer1, bool _bIsKeyboard)
{
	// Load sprite textures
	sf::Texture tempTex;
	for (int i = 0; i < m_allColors.size(); i++)
	{
		m_allTextures.push_back(tempTex);
	}
	m_allTextures[0].loadFromFile("Sprites/Red.png");
	m_allTextures[1].loadFromFile("Sprites/Blue.png");
	m_allTextures[2].loadFromFile("Sprites/Yellow.png");

	// Set controls and player # 
	m_bIsKeyboard = _bIsKeyboard;
	m_bPlayer1 = _bPlayer1;

	if (m_bPlayer1)
	{
		ChangeColor(0);
	}
	else
	{
		ChangeColor(1);
	}

	m_bCanInteract = true;
	m_interactableObject = nullptr;
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
				//m_b2Body->ApplyLinearImpulseToCenter(b2Vec2(1.0f, 0.0f), true);
				m_b2Body->SetLinearVelocity(b2Vec2(10.0f, m_b2Body->GetLinearVelocity().y));
			}

			// Move left
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				m_b2Body->SetLinearVelocity(b2Vec2(-10.0f, m_b2Body->GetLinearVelocity().y));
			}

			// Jump
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				m_b2Body->ApplyLinearImpulseToCenter(b2Vec2(m_b2Body->GetLinearVelocity().x, -1.0f), true);
			}
		}
		else				// PLAYER 2 MOVEMENT CONTROLS
		{
			// Move right
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				//m_b2Body->ApplyLinearImpulseToCenter(b2Vec2(1.0f, 0.0f), true);
				m_b2Body->SetLinearVelocity(b2Vec2(10.0f, m_b2Body->GetLinearVelocity().y));
			}

			// Move left
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				//m_b2Body->ApplyLinearImpulseToCenter(b2Vec2(-1.0f, 0.0f), true);
				m_b2Body->SetLinearVelocity(b2Vec2(-10.0f, m_b2Body->GetLinearVelocity().y));
			}

			// Jump
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				m_b2Body->ApplyLinearImpulseToCenter(b2Vec2(m_b2Body->GetLinearVelocity().x, -1.0f), true);
			}
		}
	}
}

void cPlayerCharacter::StopMovement(sf::Event _event)
{
	if (m_bIsKeyboard)
	{
		if (m_bPlayer1)
		{
			if (_event.key.code == sf::Keyboard::A || _event.key.code == sf::Keyboard::D)
			{
				m_b2Body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			}
		}
		else
		{
			if (_event.key.code == sf::Keyboard::Left || _event.key.code == sf::Keyboard::Right)
			{
				m_b2Body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			}
		}
	}
}

void cPlayerCharacter::Interact(sf::Event _event)
{
	if (m_bIsKeyboard)
	{
		if (m_bPlayer1)
		{
			if (_event.key.code == sf::Keyboard::Q)
			{
				// would need to do a check here first
				// to see if the player is already interacting with something
			}
		}
		else
		{
			if (_event.key.code == sf::Keyboard::RControl)
			{
				// would need to do a check here first
				// to see if the player is already interacting with something
			}
		}
	}
}

void cPlayerCharacter::CycleColor(sf::Event _event)
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

	if (m_bIsKeyboard)
	{
		if (m_bPlayer1)
		{
			if (_event.key.code == sf::Keyboard::S)
			{
				// Change to the following color if not at the end of vector
				if (index < m_allColors.size() - 1)
				{
					ChangeColor(index + 1);
				}
				else // Wrap around to the first color
				{
					ChangeColor(0);
				}
			}
		}
		else
		{
			if (_event.key.code == sf::Keyboard::Down)
			{
				// Change to the following color if not at the end of vector
				if (index < m_allColors.size() - 1)
				{
					ChangeColor(index + 1);
				}
				else // Wrap around to the first color
				{
					ChangeColor(0);
				}
			}
		}
	}
}

bool cPlayerCharacter::IsPlayer1()
{
	return m_bPlayer1;
}

bool cPlayerCharacter::CanInteract()
{
	return m_bCanInteract;
}

void cPlayerCharacter::ChangeColor(int _iColorIndex)
{
	m_currentColor = m_allColors[_iColorIndex];
	m_Sprite->setTexture(m_allTextures[_iColorIndex]);
}

void cPlayerCharacter::SetInteractableObject(cInteractable* _itrObj)
{
	m_interactableObject = _itrObj;
}
