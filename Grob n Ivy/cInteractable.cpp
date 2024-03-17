#include "cInteractable.h"

#include <iostream>

#include "cGameManager.h"
#include "cPlayerCharacter.h"

cInteractable::~cInteractable()
{
}

void cInteractable::Tick()
{
	CheckDistanceFromPlayers();
}

void cInteractable::CheckDistanceFromPlayers()
{
	float fInteractRange = 1.5f;

	if (m_game)
	{
		if (m_game->GetPlayerCharacters().size() > 0)
		{
			for (int i = 0; i < m_game->GetPlayerCharacters().size(); i++)
			{
				if ((GetBody()->GetTransform().p - m_game->GetPlayerCharacters()[i]->GetBody()->GetTransform().p).Length() < fInteractRange)
				{
					std::cout << "close enough" << std::endl;
				}
			}
		}
	}	
}
