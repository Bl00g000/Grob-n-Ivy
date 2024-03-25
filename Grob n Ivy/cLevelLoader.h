#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "cPhysicsObject.h"
#include "cInteractable.h"

#include "cGameManager.h"

class cLevelLoader
{
private:
	static int m_iLevelWidth;
	static int m_iLevelHeight;

	vector<shared_ptr<cPhysicsObject>> m_physicsObjects;

	shared_ptr<cInteractable> m_interactable1;
	vector<shared_ptr<cPhysicsObject>> m_toggledTiles1;

	shared_ptr<cInteractable> m_interactable2;
	vector<shared_ptr<cPhysicsObject>> m_toggledTiles2;

	shared_ptr<cInteractable> m_interactable3;
	vector<shared_ptr<cPhysicsObject>> m_toggledTiles3;

	shared_ptr<cInteractable> m_interactable4;
	vector<shared_ptr<cPhysicsObject>> m_toggledTiles4;

	shared_ptr<cInteractable> m_interactable5;
	vector<shared_ptr<cPhysicsObject>> m_toggledTiles5;


	shared_ptr<b2World> m_b2WorldRef;
	cGameManager* m_gameManagerRef;

	std::string m_sLevelName;

	char** m_cLevelArray;

	sf::Vector2f m_player1Spawn;
	sf::Vector2f m_player2Spawn;

	// Textures
	sf::Texture m_groundTexture;
	sf::Texture m_leverTexture;
	sf::Texture m_toggleFloorTexture;

	// Sprites
	sf::Sprite m_sprTile;
	sf::Sprite m_sprLever;
	sf::Sprite m_sprToggleFloor;

public:
	cLevelLoader(std::string _sLevel, cGameManager* _gameManager, std::shared_ptr<b2World> _b2World);
	~cLevelLoader();

	// Loading and building the level
	void GetDynamicLevelSize(std::string _sLevel);
	void LoadLevel(std::string _sFilePath);
	void BuildLevel();

	void Tick();
	void DrawLevel(sf::RenderWindow* _window);

	// Loading all required sprites and textures
	void LoadSprites();

	// Getters
	sf::Vector2f GetPlayer1Spawn();
	sf::Vector2f GetPlayer2Spawn();
	std::string GetName();
	int GetLevelWidth();
	int GetLevelHeight();
	vector<shared_ptr<cPhysicsObject>> GetPhysicsObjects();
};

