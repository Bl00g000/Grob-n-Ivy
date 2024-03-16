#pragma once
#include "cPhysicsObject.h"

class cPlayerCharacter : public cPhysicsObject
{
private:
	bool m_bPlayer1 = 0;
	bool m_bIsKeyboard = true;

	sf::Color m_currentColor;
	std::vector<sf::Color> m_allColors = {
		sf::Color::Red,
		sf::Color::Blue,
		sf::Color::Yellow
	};

	cPhysicsObject* m_interactingObject;

public:
	using cPhysicsObject::cPhysicsObject;
	~cPlayerCharacter();

	void Tick() override;
	void Initialize(bool _bPlayer1, bool _bIsKeyboard);

	void ProcessMovement();
	void Interact();
	void CycleColor();
};