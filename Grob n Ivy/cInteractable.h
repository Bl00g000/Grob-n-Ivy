#pragma once
#include "cPhysicsObject.h"
#include "cPlayerCharacter.h"

class cInteractable : public cPhysicsObject
{
private:


public:
	using cPhysicsObject::cPhysicsObject;
	~cInteractable();

	void Tick() override;
	void CheckDistanceFromPlayers(std::vector<cPlayerCharacter> _players);
};

