#pragma once
#include "Transformations.h"
#include "Player.h"

class MapData
{
public:
	Vector3 map[100] = {};
	Vector3 camera[100] = {};
	Vector3 pattern[600] = {};
	int patternHit[600] = {0};
	float savedCameraOffset[3];
	int pointNum;
	int patternNum;
	float patternLineNum;

	void init(int stageNum);
	void render(bool coaster);
	Vector3 getCameraPosition(float time);
	Vector3 getPlayerPosition(float time);

	Vector3 getcoasterPlayerPosition(float time);

	bool clap(Player& P);

	MapData();
	~MapData();

	float speed;			//한 박에 10씩 이동합니다
	float distance;
	Vector3 PointToPointVector;

	std::ifstream map_file;
};