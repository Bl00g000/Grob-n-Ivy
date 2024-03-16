#pragma once
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

// Size in pixels of a single box2D meter
const inline float g_sizeScale = 32.f;

// Movement scale in pixels of a box2D meter
const inline float g_moveScale = 30.0f;

// Gravity in box2D meters per second
const inline b2Vec2 g_gravity(0.0f, 9.81f);

// Radians to Degrees conversion
inline float RadToDeg (float _fRadians)
{
	return _fRadians * (180 / b2_pi);
}

// Degrees to Radians conversion
inline float DegToRad(float _fDegrees)
{
	return _fDegrees * (b2_pi / 180);
}