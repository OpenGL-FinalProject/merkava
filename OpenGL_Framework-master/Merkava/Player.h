#pragma once
#include "LinearMath.h"

class Player
{
public:
	Player();
	~Player();
	void update(float fDeltaTime, Vector3 playerPosition);
	void render();
	void hit();

	Vector3 Position;

private:
	int   hit_animation_dir;
	float hit_animation_cur_size;
	float hit_animation_speed;
	float hit_animation_max_size;
};

