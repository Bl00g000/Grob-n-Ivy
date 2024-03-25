#include "cMyContactListener.h"
#include "cGameManager.h"
#include "cLevelLoader.h"

cMyContactListener::cMyContactListener(b2World* _world, cGameManager* _game)
{
	m_box2DWorld = _world;
	m_game = _game;
}

cMyContactListener::~cMyContactListener()
{
}

void cMyContactListener::PreSolve(b2Contact* _contact, const b2Manifold* _oldManifold)
{
    b2WorldManifold worldManifold;
    _contact->GetWorldManifold(&worldManifold);

    b2PointState state1[2], state2[2];
    b2GetPointStates(state1, state2, _oldManifold, _contact->GetManifold());

    if (state2[0] == b2_addState)
    {
        const b2Body* bodyA = _contact->GetFixtureA()->GetBody();
        const b2Body* bodyB = _contact->GetFixtureB()->GetBody();
        b2Vec2 point = worldManifold.points[0];
        b2Vec2 vA = bodyA->GetLinearVelocityFromWorldPoint(point);
        b2Vec2 vB = bodyB->GetLinearVelocityFromWorldPoint(point);

        float approachSpeed = b2Dot(vB - vA, -worldManifold.normal);

        shared_ptr<cPhysicsObject> objA;
        shared_ptr<cPhysicsObject> objB;

        for (shared_ptr<cPhysicsObject> iter : m_game->GetLevelLoader()->GetPhysicsObjects())
        {
            if (iter->GetBody() == bodyA)
            {
                objA = iter;
            }
            else if (iter->GetBody() == bodyB)
            {
                objB = iter;
            }

            for (shared_ptr<cPhysicsObject> iter : m_game->GetPlayerCharacters())
            {
                if (iter->GetBody() == bodyA)
                {
                    objA = iter;
                }
                else if (iter->GetBody() == bodyB)
                {
                    objB = iter;
                }
            }

            if (objA && objB)
            {
                if (objA->GetObjectType() == ObjectType::player)
                {
                    if (objB->GetObjectType() == ObjectType::tileGround)
                    {
                        objA->SetGrounded(true);
                    }
                }

                if (objB->GetObjectType() == ObjectType::player)
                {
                    if (objA->GetObjectType() == ObjectType::tileGround)
                    {
                        objB->SetGrounded(true);
                    }
                }
            }
        }
    }
}
