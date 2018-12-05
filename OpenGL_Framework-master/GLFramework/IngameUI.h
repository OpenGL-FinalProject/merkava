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
	void setGridColor(float x, float y, float z);
	void grid();
	void render(Vector3 CameraPosition, Vector3 * Camera_worldspace, float dist);
	void scoreUp(bool critical);
	void update();

	Vector3 Vectorworld;
	Vector3 Vectorup;

	MapData* Mapdata;
	float gap;

	int printScore;
	int score;

	float gridColor[3];
};