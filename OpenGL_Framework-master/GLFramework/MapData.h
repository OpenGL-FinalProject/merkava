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

	float speed;			//�� �ڿ� 10�� �̵��մϴ�
	float distance;
	Vector3 PointToPointVector;

	//���
	int perfect_num;
	int good_num;
	//��ģ�� ��� ���� ���� ���� ���� ����ϱ�
	int miss_num;

	

	std::ifstream map_file;
};