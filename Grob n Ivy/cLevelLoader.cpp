#include "cLevelLoader.h"

#include <iostream>


int cLevelLoader::m_iLevelWidth;
int cLevelLoader::m_iLevelHeight;

cLevelLoader::cLevelLoader(std::string _sLevel, cGameManager* _gameManager, shared_ptr<b2World> _b2World)
{
	m_player1Spawn = sf::Vector2f(5, 5);
	m_player2Spawn = sf::Vector2f(6, 5);
	m_b2WorldRef = _b2World;
	m_gameManagerRef = _gameManager;

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
void cLevelLoader::BuildLevel()
{
	for (int y = 0; y < m_iLevelHeight; y++)
	{
		for (int x = 0; x < m_iLevelWidth; x++)
		{
			// Fake tiles
			if (m_cLevelArray[y][x] == 'x')
			{
				shared_ptr<cPhysicsObject> testTile(new cPhysicsObject(m_gameManagerRef,
					b2Shape::Type::e_polygon,
					m_b2WorldRef,
					sf::Vector2f(1.f, 1.f),				  	// Size
					sf::Vector2f(x,y) + sf::Vector2f(.5f, .5f),         	// Position
					0,
					b2BodyType::b2_staticBody,				   	// Body type
					&m_sprTile,									// Sprite
					1,
					ObjectType::tileGround,
					1.f, 0.f));

				m_physicsObjects.push_back(testTile);
			}
			if (m_cLevelArray[y][x] == '!')
			{
				shared_ptr<cInteractable> testInteractable(new cInteractable(m_gameManagerRef,
					b2Shape::Type::e_polygon,
					m_b2WorldRef,
					sf::Vector2f(1.f, 1.f),				  	// Size
					sf::Vector2f(x, y) + sf::Vector2f(.5f, .5f),         	// Position
					0,
					b2BodyType::b2_staticBody,				   	// Body type
					&m_sprLever,									// Sprite
					-1,
					ObjectType::tileGround,
					1.f, 0.f));

				m_interactable1 = testInteractable;
			}
			if (m_cLevelArray[y][x] == '1')
			{
				shared_ptr<cPhysicsObject> testTile(new cPhysicsObject(m_gameManagerRef,
					b2Shape::Type::e_polygon,
					m_b2WorldRef,
					sf::Vector2f(1.f, 1.f),				  	// Size
					sf::Vector2f(x, y) + sf::Vector2f(.5f, .5f),         	// Position
					0,
					b2BodyType::b2_staticBody,				   	// Body type
					&m_sprToggleFloor,									// Sprite
					1,
					ObjectType::tileGround,
					1.f, 0.f));

				m_toggledTiles1.push_back(testTile);
			}

			if (m_cLevelArray[y][x] == '@')
			{
				shared_ptr<cInteractable> testInteractable(new cInteractable(m_gameManagerRef,
					b2Shape::Type::e_polygon,
					m_b2WorldRef,
					sf::Vector2f(1.f, 1.f),				  	// Size
					sf::Vector2f(x, y) + sf::Vector2f(.5f, .5f),         	// Position
					0,
					b2BodyType::b2_staticBody,				   	// Body type
					&m_sprLever,									// Sprite
					-1,
					ObjectType::tileGround,
					1.f, 0.f));

				m_interactable2 = testInteractable;
			}
			if (m_cLevelArray[y][x] == '2')
			{
				shared_ptr<cPhysicsObject> testTile(new cPhysicsObject(m_gameManagerRef,
					b2Shape::Type::e_polygon,
					m_b2WorldRef,
					sf::Vector2f(1.f, 1.f),				  	// Size
					sf::Vector2f(x, y) + sf::Vector2f(.5f, .5f),         	// Position
					0,
					b2BodyType::b2_staticBody,				   	// Body type
					&m_sprToggleFloor,									// Sprite
					1,
					ObjectType::tileGround,
					1.f, 0.f));

				m_toggledTiles2.push_back(testTile);
			}

			if (m_cLevelArray[y][x] == '#')
			{
				shared_ptr<cInteractable> testInteractable(new cInteractable(m_gameManagerRef,
					b2Shape::Type::e_polygon,
					m_b2WorldRef,
					sf::Vector2f(1.f, 1.f),				  	// Size
					sf::Vector2f(x, y) + sf::Vector2f(.5f, .5f),         	// Position
					0,
					b2BodyType::b2_staticBody,				   	// Body type
					&m_sprLever,									// Sprite
					-1,
					ObjectType::tileGround,
					1.f, 0.f));

				m_interactable3 = testInteractable;
			}
			if (m_cLevelArray[y][x] == '3')
			{
				shared_ptr<cPhysicsObject> testTile(new cPhysicsObject(m_gameManagerRef,
					b2Shape::Type::e_polygon,
					m_b2WorldRef,
					sf::Vector2f(1.f, 1.f),				  	// Size
					sf::Vector2f(x, y) + sf::Vector2f(.5f, .5f),         	// Position
					0,
					b2BodyType::b2_staticBody,				   	// Body type
					&m_sprToggleFloor,									// Sprite
					1,
					ObjectType::tileGround,
					1.f, 0.f));

				m_toggledTiles3.push_back(testTile);
			}

			if (m_cLevelArray[y][x] == '$')
			{
				shared_ptr<cInteractable> testInteractable(new cInteractable(m_gameManagerRef,
					b2Shape::Type::e_polygon,
					m_b2WorldRef,
					sf::Vector2f(1.f, 1.f),				  	// Size
					sf::Vector2f(x, y) + sf::Vector2f(.5f, .5f),         	// Position
					0,
					b2BodyType::b2_staticBody,				   	// Body type
					&m_sprLever,									// Sprite
					-1,
					ObjectType::tileGround,
					1.f, 0.f));

				m_interactable4 = testInteractable;
			}
			if (m_cLevelArray[y][x] == '4')
			{
				shared_ptr<cPhysicsObject> testTile(new cPhysicsObject(m_gameManagerRef,
					b2Shape::Type::e_polygon,
					m_b2WorldRef,
					sf::Vector2f(1.f, 1.f),				  	// Size
					sf::Vector2f(x, y) + sf::Vector2f(.5f, .5f),         	// Position
					0,
					b2BodyType::b2_staticBody,				   	// Body type
					&m_sprToggleFloor,									// Sprite
					1,
					ObjectType::tileGround,
					1.f, 0.f));

				m_toggledTiles4.push_back(testTile);
			}

			if (m_cLevelArray[y][x] == '%')
			{
				shared_ptr<cInteractable> testInteractable(new cInteractable(m_gameManagerRef,
					b2Shape::Type::e_polygon,
					m_b2WorldRef,
					sf::Vector2f(1.f, 1.f),				  	// Size
					sf::Vector2f(x, y) + sf::Vector2f(.5f, .5f),         	// Position
					0,
					b2BodyType::b2_staticBody,				   	// Body type
					&m_sprLever,									// Sprite
					-1,
					ObjectType::tileGround,
					1.f, 0.f));

				m_interactable5 = testInteractable;
			}
			if (m_cLevelArray[y][x] == '5')
			{
				shared_ptr<cPhysicsObject> testTile(new cPhysicsObject(m_gameManagerRef,
					b2Shape::Type::e_polygon,
					m_b2WorldRef,
					sf::Vector2f(1.f, 1.f),				  	// Size
					sf::Vector2f(x, y) + sf::Vector2f(.5f, .5f),         	// Position
					0,
					b2BodyType::b2_staticBody,				   	// Body type
					&m_sprToggleFloor,									// Sprite
					1,
					ObjectType::tileGround,
					1.f, 0.f));

				m_toggledTiles5.push_back(testTile);
			}

			// Player spawn
			if (m_cLevelArray[y][x] == 'P')
			{
				m_player1Spawn = sf::Vector2f(x, y);
			}
			if (m_cLevelArray[y][x] == 'p')
			{
				m_player2Spawn = sf::Vector2f(x, y);
			}

		}
	}

	// attach toggleable tiles to their interactables
	m_interactable1->SetTarget(m_toggledTiles1);
	m_interactable2->SetTarget(m_toggledTiles2);
	m_interactable3->SetTarget(m_toggledTiles3);
	m_interactable4->SetTarget(m_toggledTiles4);
	m_interactable5->SetTarget(m_toggledTiles5);
}

void cLevelLoader::Tick()
{
	m_interactable1->Tick();
	m_interactable2->Tick();
	m_interactable3->Tick();
	m_interactable4->Tick();
	m_interactable5->Tick();
}


void cLevelLoader::DrawLevel(sf::RenderWindow* _window)
{
	m_interactable1->Draw(*_window);
	m_interactable2->Draw(*_window);
	m_interactable3->Draw(*_window);
	m_interactable4->Draw(*_window);
	m_interactable5->Draw(*_window);

	for (shared_ptr<cPhysicsObject> interactObjIter : m_toggledTiles1)
	{
		if (!interactObjIter->GetHiddenState())
		{
			interactObjIter->Draw(*_window);
		}
	}
	for (shared_ptr<cPhysicsObject> interactObjIter : m_toggledTiles2)
	{
		if (!interactObjIter->GetHiddenState())
		{
			interactObjIter->Draw(*_window);
		}
	}
	for (shared_ptr<cPhysicsObject> interactObjIter : m_toggledTiles3)
	{
		if (!interactObjIter->GetHiddenState())
		{
			interactObjIter->Draw(*_window);
		}
	}
	for (shared_ptr<cPhysicsObject> interactObjIter : m_toggledTiles4)
	{
		if (!interactObjIter->GetHiddenState())
		{
			interactObjIter->Draw(*_window);
		}
	}
	for (shared_ptr<cPhysicsObject> interactObjIter : m_toggledTiles5)
	{
		if (!interactObjIter->GetHiddenState())
		{
			interactObjIter->Draw(*_window);
		}
	}

	for (shared_ptr<cPhysicsObject> physicsObjIter : m_physicsObjects)
	{
		if (!physicsObjIter->GetHiddenState())
		{
			physicsObjIter->Draw(*_window);
		}
	}
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
	if (!m_leverTexture.loadFromFile("Sprites/Lever.png"))
	{
		std::cout << "plank not loaded" << std::endl;
	}
	if (!m_toggleFloorTexture.loadFromFile("Sprites/toggleFloor.png"))
	{
		std::cout << "plank not loaded" << std::endl;
	}
	
	

	// Setting textures to sprite variables
	m_sprTile.setTexture(m_groundTexture);
	m_sprLever.setTexture(m_leverTexture);
	m_sprToggleFloor.setTexture(m_toggleFloorTexture);
}

// Name: getPlayerSpawn
// Author: Juan
// Parameters: N/A
// Returns: Vector of sf::FloatRect
// Purpose: Returns m_playerSpawn
sf::Vector2f cLevelLoader::GetPlayer1Spawn()
{
	return m_player1Spawn;
}

// Name: getPlayerSpawn
// Author: Juan
// Parameters: N/A
// Returns: Vector of sf::FloatRect
// Purpose: Returns m_playerSpawn
sf::Vector2f cLevelLoader::GetPlayer2Spawn()
{
	return m_player2Spawn;
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

vector<shared_ptr<cPhysicsObject>> cLevelLoader::GetPhysicsObjects()
{
	return m_physicsObjects;
}


