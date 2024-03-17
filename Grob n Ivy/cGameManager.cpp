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
void cGameManager::StartGame()
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
			case sf::Event::KeyPressed:
	        {
		        if (event.key.code == sf::Keyboard::K)
		        {
                    for (shared_ptr<cPhysicsObject> physicsObjIter : m_physicsObjects)
                    {
                        if (physicsObjIter->GetObjectType() == ObjectType::tileTest)
                        {
                            if (physicsObjIter->GetHiddenState())
                            {
                                physicsObjIter->UnHideObject();
                            }
                            else
                            {
                                physicsObjIter->HideObject();
                            }
                        }
                        
                    }
		        }
	        }
        }

        sf::View levelView = CreateLevelViewPort(16.f, 9.f);

        // Apply the view to the window
        m_window->setView(levelView);

        m_window->clear();

        for (shared_ptr<cPhysicsObject> physicsObjIter : m_physicsObjects)
        {
            if (!physicsObjIter->GetHiddenState())
            {
                physicsObjIter->Draw(*m_window);
            }
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

sf::View cGameManager::CreateLevelViewPort(float _iTileCountX, float _iTileCountY)
{
    // set the view width and height based on how many tiles exists in the level on x and y axis
    float fViewWidth = _iTileCountX * g_sizeScale;
    float fViewHeight = _iTileCountY * g_sizeScale;

    sf::View newView(sf::FloatRect(0, 0, fViewWidth, fViewHeight));

    // get the view and window aspect ratios
    float fViewAspectRatio = newView.getSize().x / newView.getSize().y;
    float fWindowAspectRatio = m_window->getSize().x / m_window->getSize().y;

    float fScaleFactor = 1.0f;

    // If view's aspect ratio is wider than window's, scale by width
    // otherwise if the view's aspect ratio is taller than window's, scale by height
    if (fViewAspectRatio > fWindowAspectRatio)
    {
        fScaleFactor = static_cast<float>(m_window->getSize().x) / newView.getSize().x;
    }
    else 
    {
        fScaleFactor = static_cast<float>(m_window->getSize().y) / newView.getSize().y;
    }

    // Set the initial view size and center it
    newView.setSize(m_window->getSize().x / fScaleFactor, m_window->getSize().y / fScaleFactor);
    newView.setCenter(fViewWidth / 2.f, fViewHeight / 2.f);

    return newView;
}

//  returns all physics objects
vector<shared_ptr<cPhysicsObject>> cGameManager::GetPhysicsObjects()
{
    return m_physicsObjects;
}