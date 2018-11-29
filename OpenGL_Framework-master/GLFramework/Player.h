#pragma once
#include "Transformations.h"

class Player
{
public:
	Player();
	~Player();
	void update(float fDeltaTime, Vector3 playerPosition);
	void render();

	Vector3 Position;
};

