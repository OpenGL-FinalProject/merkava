#pragma once
#include "Player.h"

class Scene00_BG
{
public:
	Scene00_BG();
	~Scene00_BG();
	void update(const float& fDeltaTime);
	void render();

private:
	float   cylinder_width = 1000.f;
	float   cylinder_height = 3000.f;
	float   cylinder_rotate_y = 45.f;
	float   cylinder_translate_y = 0.f;
	float   cylinder_rotate_y_speed_per_sec = 15.f;
	float   cylinder_translate_y_speed_per_sec = 50.f;
	Player  player;
	Vector3 player_pos = { 0,0,150 };
};
