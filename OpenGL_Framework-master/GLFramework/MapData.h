#pragma once
#include "Transformations.h"

class MapData
{
public:
	Vector3 map[200] = {};
	int pointNum;

	void init(int stageNum);
	void render();
	Vector3 getCameraPosition(float time);
	Vector3 getPlayerPosition(float time);

	MapData();
	~MapData();
};