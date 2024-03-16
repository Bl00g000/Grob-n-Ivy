#pragma once
#include "box2d/b2_world_callbacks.h"


class cMyContactListener :
    public b2ContactListener
{
private:
    class b2World* m_box2DWorld = nullptr;
    class cGameManager* m_game = nullptr;

public:
    cMyContactListener(b2World* _world, cGameManager* _game);
    ~cMyContactListener() override;

    void PreSolve(b2Contact* _contact, const b2Manifold* _oldManifold);
};

