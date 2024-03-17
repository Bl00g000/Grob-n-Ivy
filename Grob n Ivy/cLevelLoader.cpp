#include "cLevelLoader.h"

#include <iostream>


int cLevelLoader::m_iLevelWidth;
int cLevelLoader::m_iLevelHeight;

cLevelLoader::cLevelLoader(std::string _sLevel, cGameManager* _gameManager, std::shared_ptr<b2World> _b2World)
{
	m_playerSpawn = sf::Vector2f(0, 0);
	b2WorldRef = _b2World;
	gameManagerRef = _gameManager;

	m_sLevelName = _sLevel;

	GetDynamicLevelSize(_sLevel);

	// Creates Dynamic 2D array
	m_cLevelArray = new char* [m_iLevelHeight];
	for (int i = 0; i < m_iLevelHeight; i++)
	{
		m_cLevelArray[i] = new char[m_iLevelWidth];
	}

	LoadSprites();
	LoadLevel("Levels/" + _sLevel + ".txt");
}

cLevelLoader::~cLevelLoader()
{
	// Delete Dynamic 2D Array
	for (int i = 0; i < m_iLevelHeight; i++) {
		delete[] m_cLevelArray[i];
	}
	delete[] m_cLevelArray;
}

// Name: GetDynamicLevelSize
// Author: Juan
// Parameters: string
// Returns: Void
// Purpose: sets level width and height size dynamically allowing for simple
//			editing of the text file to change the size of the levels
void cLevelLoader::GetDynamicLevelSize(std::string _sLevel)
{
	std::ifstream file("Levels/" + _sLevel + ".txt");

	if (file.is_open())
	{
		std::string sLine;
		m_iLevelHeight = 0;
		m_iLevelWidth = 0;

		while (std::getline(file, sLine))
		{
			int iLineSize = sLine.length();
			if (iLineSize > m_iLevelWidth)
			{
				m_iLevelWidth = iLineSize;
			}
			m_iLevelHeight++;
		}

		file.close();
	}
}

// Name: LoadLevel
// Author: Juan
// Parameters: string
// Returns: Void
// Purpose: Loads a level from a text file and saves it in a level data array
void cLevelLoader::LoadLevel(std::string _sFilePath)
{
	std::fstream loadFileStream;
	loadFileStream.open(_sFilePath, std::ios::in);

	std::string loadFileString;
	int lineCount = 0;

	if (loadFileStream.is_open())
	{
		while (std::getline(loadFileStream, loadFileString))
		{
			for (int i = 0; i < loadFileString.size(); i++)
			{
				m_cLevelArray[lineCount][i] = loadFileString[i];
			}

			lineCount++;
		}

		loadFileStream.close();
	}
}

// Name: BuildLevel
// Author: Juan
// Parameters: string
// Returns: Void
// Purpose: Runs through the level data and builds the level
void cLevelLoader::BuildLevel(std::vector<std::shared_ptr<class cPhysicsObject>>* _physicsObjects)
{
	for (int y = 0; y < m_iLevelHeight; y++)
	{
		for (int x = 0; x < m_iLevelWidth; x++)
		{
			// Fake tiles
			if (m_cLevelArray[y][x] == 'x')
			{
				CreateTile(sf::Vector2f(x, y), ObjectType::tileGround, _physicsObjects);
			}
			if (m_cLevelArray[y][x] == 'X')
			{
				CreateTile(sf::Vector2f(x, y), ObjectType::tileTest, _physicsObjects);
			}

			// Player spawn
			else if (m_cLevelArray[y][x] == 'P')
			{
				m_playerSpawn = sf::Vector2f(x, y);
			}
		}
	}
}

// Name: CreateTile
// Author: Juan
// Parameters: sf::vector2f, TileType, vector<shared_ptr<cPhysicsObject>>*
// Returns: Void
// Purpose: Creates level tiles based on tiletypes specified in the level data file
void cLevelLoader::CreateTile(sf::Vector2f _pos, ObjectType _tileType, std::vector<std::shared_ptr<class cPhysicsObject>>* _physicsObject)
{
	// different tiles to be created
	switch (_tileType)
	{
	case ObjectType::tileGround:
		CreateTilePhysicsObject(_pos, _tileType, _physicsObject, &m_sprTile);
		break;
	case ObjectType::tileTest:
		CreateInteractablePhysicsObject(_pos, _tileType, _physicsObject, &m_sprTile);
		break;
	}
}

// Name: LoadSprites
// Author: Juan
// Parameters: N/A
// Returns: Void
// Purpose: Creates a 1x1 (times the game scale size) physics object
void cLevelLoader::CreateTilePhysicsObject(sf::Vector2f _pos, ObjectType _tileType, std::vector<std::shared_ptr<class cPhysicsObject>>* _physicsObject, sf::Sprite* _sprite)
{
	shared_ptr<cPhysicsObject> testTile(new cPhysicsObject(gameManagerRef,
		b2Shape::Type::e_polygon,
		b2WorldRef,
		sf::Vector2f(1.f, 1.f),				  	// Size
		_pos + sf::Vector2f(.5f, .5f),         	// Position
		0,
		b2BodyType::b2_staticBody,				   	// Body type
		_sprite,									// Sprite
		1,
		_tileType,
		1.f, 0.f));								   	


	_physicsObject->push_back(testTile);
}

// Name: LoadSprites
// Author: Juan
// Parameters: N/A
// Returns: Void
// Purpose: Creates a 1x1 (times the game scale size) physics object
void cLevelLoader::CreateInteractablePhysicsObject(sf::Vector2f _pos, ObjectType _tileType, std::vector<std::shared_ptr<class cPhysicsObject>>* _physicsObject, sf::Sprite* _sprite)
{
	shared_ptr<cInteractable> testInteractable(new cInteractable(gameManagerRef,
		b2Shape::Type::e_polygon,
		b2WorldRef,
		sf::Vector2f(1.f, 1.f),				  	// Size
		_pos + sf::Vector2f(.5f, .5f),         	// Position
		0,
		b2BodyType::b2_staticBody,				   	// Body type
		_sprite,									// Sprite
		1,
		_tileType,
		1.f, 0.f));									   	

	_physicsObject->push_back(testInteractable);
}

// Name: LoadSprites
// Author: Juan
// Parameters: N/A
// Returns: Void
// Purpose: Loads all the required sprites and textures for the level loader to function
void cLevelLoader::LoadSprites()
{
	if (!m_groundTexture.loadFromFile("Sprites/Plank.png"))
	{
		std::cout << "plank not loaded" << std::endl;
	}

	// Setting textures to sprite variables
	m_sprTile.setTexture(m_groundTexture);
}

// Name: getPlayerSpawn
// Author: Juan
// Parameters: N/A
// Returns: Vector of sf::FloatRect
// Purpose: Returns m_playerSpawn
sf::Vector2f cLevelLoader::GetPlayerSpawn()
{
	return m_playerSpawn;
}

// Name: getName
// Author: Justhine
// Parameters: N/A
// Returns: Vector of std::string
// Purpose: Returns m_sLevelName
std::string cLevelLoader::GetName()
{
	return m_sLevelName;
}

// Name: getLevelWidth
// Author: Juan
// Parameters: N/A
// Returns: int
// Purpose: Returns m_iLevelWidth
int cLevelLoader::GetLevelWidth()
{
	int levelWidth = m_iLevelWidth;
	return levelWidth;
}

// Name: getLevelHeight
// Author: Juan
// Parameters: N/A
// Returns: int
// Purpose: Returns m_iLevelHeight
int cLevelLoader::GetLevelHeight()
{
	int levelHeight = m_iLevelHeight;
	return levelHeight;
}


