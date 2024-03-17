#pragma once
#include "cPhysicsObject.h"
#include "cPlayerCharacter.h"
#include "cMyContactListener.h"
#include <vector>

using std::shared_ptr;
using std::weak_ptr;
using std::vector;

enum eLevelState
{
	MainMenu,
	LobbyScreen,
	level1,
	level2,
	EndScreen,
	ClosingGame
};

class cGameManager
{
private:
	// SFML window
	sf::RenderWindow* m_window;
	bool m_flagForClose = false;

	// Sprites
	sf::Sprite m_sprGround;
	sf::Sprite m_sprPlayer1;
	sf::Sprite m_sprPlayer2;

	// Box2D
	shared_ptr<b2World> m_box2DWorld;
	shared_ptr<cMyContactListener> m_contactListener;
	weak_ptr<cPhysicsObject> m_groundObject;

	// Key Objects
	vector<shared_ptr<cPhysicsObject>> m_physicsObjects;
	vector<shared_ptr<cPlayerCharacter>> m_characters;

	//States
	eLevelState m_levelState = eLevelState::level1;

	// Text Variables
	sf::Font m_gameFont;
	sf::Text m_gameText;

	void Tick();

	// Create level border with indestructible walls
	void CreateBorder();
	void CreatePlayers();

public:
	cGameManager();
	~cGameManager();

	void StartGame();

	vector<shared_ptr<cPhysicsObject>> GetPhysicsObjects();
};

