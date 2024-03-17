#include "cInteractable.h"

cInteractable::~cInteractable()
{
}

void cInteractable::Tick()
{
	
}

void cInteractable::CheckDistanceFromPlayers(std::vector<cPlayerCharacter> _players)
{
	for (cPlayerCharacter player : _players)
	{
		// CHECK DISTANCE TO PLAYER
		// ONLY DO THE BELOW CODE IF DISTANCE IS WITHIN INTERACT RANGE
		if (player.CanInteract())
		{
			player.SetInteractableObject(this);
		}
	}
}
