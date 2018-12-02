#pragma once
#include "Transformations.h"
#include "Player.h"
#include <vector>

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
	Vector3 closest_pattern(Player& P);

	MapData();
	~MapData();

	float speed;			//한 박에 10씩 이동합니다
	float distance;
	Vector3 PointToPointVector;

	//결과
	int perfect_num;
	int good_num;
	//놓친걸 어떻게 세는 것이 가장 좋은 방법일까
	int miss_num;

	

	std::ifstream map_file;
};