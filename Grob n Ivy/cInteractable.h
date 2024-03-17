#pragma once
#include "cPhysicsObject.h"

class cInteractable : public cPhysicsObject
{
private:


public:
	using cPhysicsObject::cPhysicsObject;
	~cInteractable();

	void Tick() override;
	void CheckDistanceFromPlayers();
};

