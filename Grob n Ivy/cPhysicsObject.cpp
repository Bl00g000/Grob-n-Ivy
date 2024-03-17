#include "cPhysicsObject.h"

cPhysicsObject::cPhysicsObject()
{

}

cPhysicsObject::cPhysicsObject(cGameManager* _game, b2Shape::Type _shapeType, std::shared_ptr<b2World> _box2DWorld, sf::Vector2f _size,
	sf::Vector2f _position, float _rotation, b2BodyType _bodyType, ObjectType _objectType, sf::Sprite* _sprite,
	int16 _filterGroup)
{
	m_box2DWorld = _box2DWorld;
	m_v2fSize = _size * g_sizeScale;
	m_Sprite = _sprite;
	m_game = _game;
	m_int16FilterGroup = _filterGroup;
	m_objectType = _objectType;

	// Defining body and creating it with world
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2((_position.x * g_sizeScale) / g_moveScale, (_position.y * g_sizeScale) / g_moveScale);
	bodyDef.angle = DegToRad(_rotation);
	bodyDef.type = _bodyType;
	m_b2Body = m_box2DWorld->CreateBody(&bodyDef);

	b2CircleShape circleShape;
	b2PolygonShape polyShape;

	switch (_shapeType)
	{
	case b2Shape::e_circle:
		
		circleShape.m_radius = m_v2fSize.x / 2 / g_moveScale;
		m_fixtureDef.shape = &circleShape;
		break;
	case b2Shape::e_polygon:

		// Create box using poly shape
		polyShape.SetAsBox(m_v2fSize.x / 2 / g_moveScale, m_v2fSize.y / 2 / g_moveScale);
		m_fixtureDef.shape = &polyShape;
		break;
	default: ;
	}

	// Fixture for body using poly shape
	m_fixtureDef.friction = 0.5f;
	m_fixtureDef.density = 1.0f; // kg/m^3
	m_fixtureDef.restitution = 0.3f; // bounciness
	m_fixtureDef.filter.groupIndex = m_int16FilterGroup; // Allows objects of the same negative index to not collide with each other
	m_b2Body->CreateFixture(&m_fixtureDef);

	// Set the scale of the sprite
	m_v2fSpriteScale = { m_v2fSize.x / m_Sprite->getTexture()->getSize().x, m_v2fSize.y / m_Sprite->getTexture()->getSize().y };
	
}

void cPhysicsObject::HideObject()
{
	m_fixtureDef.filter.groupIndex = -1;
	m_bHidden = true;
}

void cPhysicsObject::UnHideObject()
{
	m_fixtureDef.filter.groupIndex = m_int16FilterGroup;
	m_bHidden = false;
}

cPhysicsObject::~cPhysicsObject()
{
	m_box2DWorld->DestroyBody(m_b2Body);
}

void cPhysicsObject::Tick()
{

}

// draw the object to the game window
void cPhysicsObject::Draw(sf::RenderWindow& _window)
{
	// Set the scale of the sprite
	m_Sprite->setScale(m_v2fSpriteScale);

	// Set origin of sprite to center (location of the object)
	m_Sprite->setOrigin(float(m_Sprite->getTexture()->getSize().x / 2), float(m_Sprite->getTexture()->getSize().y / 2));

	// Set sprite position using the position of box2D body
	m_Sprite->setPosition(m_b2Body->GetPosition().x * g_moveScale, m_b2Body->GetPosition().y * g_moveScale);

	// Set sprite rotation
	// Need to convert radians (box2D body angle) to degrees (SFML sprite rotation)
	m_Sprite->setRotation(RadToDeg(m_b2Body->GetAngle()));

	_window.draw(*m_Sprite);
}

// returns the object body
b2Body* cPhysicsObject::GetBody()
{
	return m_b2Body;
}

// sets the health of the object
void cPhysicsObject::SetHealth(float _newHealth, bool _indestructible)
{
	m_fHealth = _newHealth;
	m_bIndestructible = _indestructible;
}

// lowers health when the object receives impact based on the impact strength
void cPhysicsObject::ReceiveImpact(float _impactStrength)
{
	if (m_bIndestructible) return;

	if (GetBody()->GetType() == b2_staticBody) return;

	if (_impactStrength > 1.0f)
	{
		m_fHealth -= _impactStrength;

		if (m_fHealth <= 0)
		{
			m_bMarkedForDestroy = true;
		}
	}
}

// returns the value of markedForDestroy
bool cPhysicsObject::IsMarkedForDestruction()
{
	return m_bMarkedForDestroy;
}

// set the value of hasCollided
void cPhysicsObject::SetHasCollided(bool _hasCollided)
{
	m_bHasCollided = _hasCollided;
}

// returns the value of hasCollided
bool cPhysicsObject::GetHasCollided()
{
	return m_bHasCollided;
}

bool cPhysicsObject::GetHiddenState()
{
	return m_bHidden;
}

ObjectType cPhysicsObject::GetObjectType()
{
	return m_objectType;
}
