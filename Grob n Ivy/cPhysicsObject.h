#pragma once
#include "PhysicsLibrary.h"
#include "SFML/Graphics.hpp"

enum ObjectType
{
	none,
	tileGround,
	tileTest,
};

class cPhysicsObject
{
protected:
	std::shared_ptr<b2World> m_box2DWorld;
	b2Body* m_b2Body;
	class cGameManager* m_game = nullptr;

	// Size of object scaled to pixels per meter
	sf::Vector2f m_v2fSize;

	ObjectType m_objectType;

	sf::Sprite* m_Sprite;
	sf::Vector2f m_v2fSpriteScale;

	b2FixtureDef m_fixtureDef;
	int16 m_int16FilterGroup;

	float m_fHealth = 10.f;
	bool m_bIndestructible = false;
	bool m_bMarkedForDestroy = false;
	bool m_bHidden = false;
	bool m_bHasCollided = false;

public:
	cPhysicsObject(cGameManager* _game, b2Shape::Type _shapeType, std::shared_ptr<b2World> _box2DWorld,
		sf::Vector2f _size, sf::Vector2f _position, float _rotation, 
		b2BodyType _bodyType, ObjectType _tileType, sf::Sprite* _sprite,
		int16 _filterGroup = 0);

	virtual ~cPhysicsObject();

	virtual void Tick();

	void Draw(sf::RenderWindow& _window);

	void ReceiveImpact(float _impactStrength);

	bool IsMarkedForDestruction();

	void HideObject();
	void UnHideObject();

	// setters
	void SetHasCollided(bool _hasCollided);
	void SetHealth(float _newHealth, bool _indestructible = false);

	// getters
	bool GetHasCollided();
	bool GetHiddenState();
	ObjectType GetObjectType();
	b2Body* GetBody();
};

