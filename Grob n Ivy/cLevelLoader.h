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


	shared_ptr<b2World> m_b2WorldRef;
	cGameManager* m_gameManagerRef;

	std::string m_sLevelName;

	char** m_cLevelArray;

	sf::Vector2f m_playerSpawn;

	// Textures
	sf::Texture m_groundTexture;

	// Sprites
	sf::Sprite m_sprTile;

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
	sf::Vector2f GetPlayerSpawn();
	std::string GetName();
	int GetLevelWidth();
	int GetLevelHeight();
	vector<shared_ptr<cPhysicsObject>> GetPhysicsObjects();
};

