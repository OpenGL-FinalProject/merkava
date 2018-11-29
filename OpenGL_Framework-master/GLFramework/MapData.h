#pragma once
#include "Transformations.h"

class MapData
{
public:
	Vector3 map[500] = {};
	int pointNum;

	void init(int stageNum);
	void render();
	Vector3 getCameraPosition(float time);
	Vector3 getPlayerPosition(float time);

	MapData();
	~MapData();

	float speed;			//�� �ڿ� 10�� �̵��մϴ�
	float distance;
	Vector3 PointToPointVector;

	std::ifstream map_file;
};