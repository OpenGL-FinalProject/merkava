#pragma once
#include "Transformations.h"

class MapData
{
public:
	Vector3 map[100] = {};
	Vector3 camera[100] = {};
	Vector3 pattern[1000] = {};
	float savedCameraOffset[3];
	int pointNum;
	int patternNum;
	float patternLineNum;

	void init(int stageNum);
	void render(bool coaster);
	Vector3 getCameraPosition(float time);
	Vector3 getPlayerPosition(float time);

	Vector3 getcoasterPlayerPosition(float time);

	MapData();
	~MapData();

	float speed;			//�� �ڿ� 10�� �̵��մϴ�
	float distance;
	Vector3 PointToPointVector;

	std::ifstream map_file;
};