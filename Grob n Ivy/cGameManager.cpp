#include "cGameManager.h"

cGameManager::cGameManager()
{
    //Creates an SFML window at a desired resolution.
    m_window = new sf::RenderWindow(sf::VideoMode(1280, 720), "SFML and Box2D");
    m_window->setFramerateLimit(60);

    sf::Texture groundTex;
    groundTex.loadFromFile("Sprites/plank.png");
    
    m_groundSprite.setTexture(groundTex);

    m_gameFont.loadFromFile("Fonts/arial.ttf");
    m_gameText.setFont(m_gameFont);
    m_gameText.setCharacterSize(30);
    m_gameText.setFillColor(sf::Color::White);
    m_gameText.setOrigin(0.f, 20.f);

    StartGame();
}

cGameManager::~cGameManager()
{
}

//  create box2Dworld and start the game
void cGameManager::StartGame()
{
    shared_ptr<b2World> newBox2DWorld(new b2World(g_gravity));
    m_box2DWorld = newBox2DWorld;

    shared_ptr<cMyContactListener> newContactListener(new cMyContactListener(m_box2DWorld.get(), this));
    m_contactListener = newContactListener;

    m_box2DWorld->SetContactListener(m_contactListener.get());

    // Create our first level here
    CreateBorder();
    CreatePlayers();

    //This is the drawing section for SFML.
    while (m_window->isOpen())
    {
    	Tick();
    }
}

// function to step box2D World forward
void cGameManager::Tick()
{
    // step box2D world forward
    m_box2DWorld->Step(1.0f / 60, 8, 3);

    //Window events:
    sf::Event event;

    while (m_window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
        {
            m_window->close();
            break;
        }
        case sf::Event::Resized:
        {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            m_window->setView(sf::View(visibleArea));
        }
        case sf::Event::KeyPressed:
        {
            for (shared_ptr<cPlayerCharacter> characterIter : m_characters)
            {
                characterIter->ProcessMovement();
            }
        }
        }
    }

    m_window->clear();

    for (shared_ptr<cPhysicsObject> physicsObjIter : m_physicsObjects)
    {
        physicsObjIter->Draw(*m_window);
    }

    for (shared_ptr<cPlayerCharacter> characterIter : m_characters)
    {
        characterIter->Draw(*m_window);
    }

    //m_player1->Draw(*m_window);

    //Finally, display the window.
    m_window->display();

    if (m_flagForClose)
    {
        m_levelState = eLevelState::ClosingGame;
        m_window->close();
    }
}

// creates the level border which consists of 2 walls a ceiling and 1 ground object
void cGameManager::CreateBorder()
{
    shared_ptr<cPhysicsObject> newGroundObject(new cPhysicsObject(this,
        b2Shape::Type::e_polygon,
        m_box2DWorld,
        sf::Vector2f(43.f, 1.f),            // Size
        sf::Vector2f(21.3f, 22.0f),           // Position
        180,
        b2BodyType::b2_staticBody,               // Body Type
        &m_groundSprite));                         // Sprite
    m_groundObject = newGroundObject;
    m_physicsObjects.push_back(newGroundObject);

    shared_ptr<cPhysicsObject> RoofObject(new cPhysicsObject(this,
        b2Shape::Type::e_polygon,
        m_box2DWorld,
        sf::Vector2f(43.f, 1.f),            // Size
        sf::Vector2f(21.3f, 0.f),           // Position
        180,
        b2BodyType::b2_staticBody,               // Body Type
        &m_groundSprite));                         // Sprite
    m_physicsObjects.push_back(RoofObject);

    shared_ptr<cPhysicsObject> rightWallObject(new cPhysicsObject(this,
        b2Shape::Type::e_polygon,
        m_box2DWorld,
        sf::Vector2f(1.f, 43.f),            // Size
        sf::Vector2f(40.f, 12.f),           // Position
        180,
        b2BodyType::b2_staticBody,               // Body Type
        &m_groundSprite));                         // Sprite
    m_physicsObjects.push_back(rightWallObject);

    shared_ptr<cPhysicsObject> leftWallObject(new cPhysicsObject(this,
        b2Shape::Type::e_polygon,
        m_box2DWorld,
        sf::Vector2f(1.f, 43.f),            // Size
        sf::Vector2f(0.f, 12.f),           // Position
        180,
        b2BodyType::b2_staticBody,               // Body Type
        &m_groundSprite));                         // Sprite
    m_physicsObjects.push_back(leftWallObject);
}

void cGameManager::CreatePlayers()
{
    // THIS IS MEANT TO WORK BUT ITS GIVING NO DEFAULT CONSTRUCTOR ERROR FOR CPHYSICSOBJECT
    // AND IDK WHY BECAUSE THIS IS HOW WE CREATED EVERYTHING IN ANGY BOIDS PROJECT

    shared_ptr<cPlayerCharacter> newPlayer1(new cPlayerCharacter(this,
        b2Shape::Type::e_polygon,
        m_box2DWorld,
        sf::Vector2f(1.f, 1.f),
        sf::Vector2f(5.f, 5.f),
        0.0f,
        b2BodyType::b2_dynamicBody,
        &m_groundSprite));
    
    newPlayer1->Initialize(true, true);
    m_characters.push_back(newPlayer1);
    
    shared_ptr<cPlayerCharacter> newPlayer2(new cPlayerCharacter(this,
        b2Shape::Type::e_polygon,
        m_box2DWorld,
        sf::Vector2f(1.f, 1.f),
        sf::Vector2f(10.f, 5.f),
        0.0f,
        b2BodyType::b2_dynamicBody,
        &m_groundSprite));
    
    newPlayer2->Initialize(false, true);
    m_characters.push_back(newPlayer2);
}

//  returns all physics objects
vector<shared_ptr<cPhysicsObject>> cGameManager::GetPhysicsObjects()
{
    return m_physicsObjects;
}