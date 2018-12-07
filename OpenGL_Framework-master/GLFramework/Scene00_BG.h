#pragma once
#include "Player.h"

class Scene00_BG
{
public:
	Scene00_BG();
	Scene00_BG(const float& _time_to_change_scene);
	~Scene00_BG();
	void update(const float& fDeltaTime);
	void render();
	void start_to_change_scene();

private:
	float   cylinder_alpha = 1.f;
	float   cylinder_width = 1000.f;
	float   cylinder_height = 3000.f;
	float   cylinder_rotate_y = 45.f;
	float   cylinder_translate_y = 0.f;
	float   cylinder_rotate_y_speed_per_sec = 15.f;
	float   cylinder_translate_y_speed_per_sec = 50.f;

	bool   is_started_to_change_scene;
	float   time_to_change_scene;
	float   elapsed_time_since_scene_change_started;
	float   line_alpha;

	Player  player;
	Vector3 player_pos = { 0,0,150 };
};

class Scene00_TITLE
{
public:
	Scene00_TITLE();
	~Scene00_TITLE();
	void render();
private:

};

class Scene03_BG
{
public:
	Scene03_BG();
	Scene03_BG(const float& _time_to_change_scene);
	~Scene03_BG();
	void update(const float& fDeltaTime);
	void render();
	void start_to_change_scene();

private:
	float   cylinder_alpha = 1.f;
	float   cylinder_width = 1000.f;
	float   cylinder_height = 3000.f;
	float   cylinder_rotate_y = 45.f;
	float   cylinder_translate_y = 0.f;
	float   cylinder_rotate_y_speed_per_sec = 15.f;
	float   cylinder_translate_y_speed_per_sec = 50.f;

	bool   is_started_to_change_scene;
	float   time_to_change_scene;
	float   elapsed_time_since_scene_change_started;
	float   line_alpha;
};
