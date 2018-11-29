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

	float speed;			//한 박에 10씩 이동합니다
	float distance;
};