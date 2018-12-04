#pragma once
#include "LinearMath.h"
#include "MapData.h"
class IngameUI
{
public:
	IngameUI();
	~IngameUI();

	void init(MapData*);
	void samplerRectangle(Vector3 * Camera_worldspace);
	void render(Vector3 CameraPosition, Vector3 * Camera_worldspace, float dist);
	void update();

	Vector3 Vectorworld;
	Vector3 Vectorup;

	MapData* Mapdata;
	float gap;
};