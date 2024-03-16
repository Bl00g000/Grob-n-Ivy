#include "cGameManager.h"
#include "cLevelLoader.h"

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

    startGame();
}

cGameManager::~cGameManager()
{
}

//  create box2Dworld and start the game
void cGameManager::startGame()
{
    shared_ptr<b2World> newBox2DWorld(new b2World(g_gravity));
    m_box2DWorld = newBox2DWorld;

    shared_ptr<cMyContactListener> newContactListener(new cMyContactListener(m_box2DWorld.get(), this));
    m_contactListener = newContactListener;

    m_box2DWorld->SetContactListener(m_contactListener.get());

    m_levelLoader = new cLevelLoader("Level0", this, m_box2DWorld);
    m_levelLoader->BuildLevel(&m_physicsObjects);

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
	            break;
	        }
	        case sf::Event::Resized:
	        {
	            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
	            m_window->setView(sf::View(visibleArea));
	        }
        }

        m_window->clear();


        for (shared_ptr<cPhysicsObject> physicsObjIter : m_physicsObjects)
        {
            physicsObjIter->Draw(*m_window);
        }

        //Finally, display the window.
        m_window->display();

        if (m_flagForClose)
        {
            m_levelState = eLevelState::ClosingGame;
            m_window->close();
        }
    }
}

//  returns all physics objects
vector<shared_ptr<cPhysicsObject>> cGameManager::GetPhysicsObjects()
{
    return m_physicsObjects;
}