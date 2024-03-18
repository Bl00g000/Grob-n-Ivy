#pragma once
#include "cPhysicsObject.h"

class cInteractable : public cPhysicsObject
{
private:
	std::vector<std::shared_ptr<cPhysicsObject>> m_interactTargets;

public:
	using cPhysicsObject::cPhysicsObject;
	~cInteractable();

	void Tick() override;
	void SetTarget(std::vector<std::shared_ptr<cPhysicsObject>> _targetObjects);
	void CheckDistanceFromPlayers();

	virtual void Activate();
};

