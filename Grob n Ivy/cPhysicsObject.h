#pragma once
#include "PhysicsLibrary.h"
#include "SFML/Graphics.hpp"

class cPhysicsObject
{
protected:
	std::shared_ptr<b2World> m_box2DWorld;
	b2Body* m_b2Body;
	class cGameManager* m_game = nullptr;

	// Size of object scaled to pixels per meter
	sf::Vector2f m_v2fSize;

	sf::Sprite* m_Sprite;
	sf::Vector2f m_v2fSpriteScale;

	float m_fHealth = 10.f;
	bool m_bIndestructible = false;
	bool m_bMarkedForDestroy = false;
	bool m_bHasCollided = false;

public:
	cPhysicsObject(cGameManager* _game, b2Shape::Type _shapeType, std::shared_ptr<b2World> _box2DWorld,
		sf::Vector2f _size, sf::Vector2f _position, float _rotation, 
		b2BodyType _bodyType, sf::Sprite* _sprite, int16 _filterGroup = 0);

	virtual ~cPhysicsObject();

	virtual void Tick();

	void Draw(sf::RenderWindow& _window);

	b2Body* GetBody();

	void SetHealth(float _newHealth, bool _indestructible = false);

	void ReceiveImpact(float _impactStrength);

	bool IsMarkedForDestruction();

	void SetHasCollided(bool _hasCollided);
	bool GetHasCollided();

	void SetLifetime(float _lifetime);
	float GetLifetime();
};

