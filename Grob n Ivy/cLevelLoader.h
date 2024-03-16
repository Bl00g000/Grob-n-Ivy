#pragma once
#include <string>
#include <vector>
#include <fstream>

#include "cGameManager.h"

enum TileType
{
	tileGround,
	tileTest,
};

class cLevelLoader
{
private:
	static int m_iLevelWidth;
	static int m_iLevelHeight;

	std::shared_ptr<b2World> b2WorldRef;
	cGameManager* gameManagerRef;

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
	void BuildLevel(std::vector<std::shared_ptr<class cPhysicsObject>>* _physicsObjects);

	// Creating the tiles
	void CreateTile(sf::Vector2f _pos, TileType _tileType, std::vector<std::shared_ptr<cPhysicsObject>>* _physicsObject);
	void CreateTilePhysicsObject(sf::Vector2f _pos, TileType _tileType,
	                             std::vector<std::shared_ptr<cPhysicsObject>>* _physicsObject, sf::Sprite* _sprite);

	// Loading all required sprites and textures
	void LoadSprites();

	// Getters
	sf::Vector2f GetPlayerSpawn();
	std::string GetName();
	int GetLevelWidth();
	int GetLevelHeight();
};

