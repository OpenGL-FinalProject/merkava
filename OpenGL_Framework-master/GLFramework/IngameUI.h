#pragma once
#include "LinearMath.h"
class IngameUI
{
public:
	IngameUI();
	~IngameUI();

	void init();
	void render(Vector3 CameraPosition, Vector3 * Camera_worldspace, float dist);
	void update();

	Vector3 Vectorworld;
	Vector3 Vectorup;
};

