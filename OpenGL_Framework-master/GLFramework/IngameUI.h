#pragma once
#include "LinearMath.h"
class IngameUI
{
public:
	IngameUI();
	~IngameUI();

	void init();
	void render(float time, Vector3* Camera_worldspace);
	void update();

};

