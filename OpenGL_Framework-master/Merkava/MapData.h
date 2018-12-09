#pragma once
#include "LinearMath.h"
#include "Player.h"
#include <vector>


class MapData
{
public:

	Vector3 map[100] = {};
	Vector3 camera[100] = {};
	Vector3 pattern[600] = {};

	int flashIndex;
	Vector4 flashColor[100];
	float flashTime[100][2];

	int patternHit[600] = {0};
	float patternTime[600] = {0};
	float savedCameraOffset[3];
	int pointNum;
	int patternNum;
	float patternLineNum;


	void init(int stageNum);
	void render(bool coaster, float time, Vector3* Camera_worldspace, Vector3* axis);
	void drawBillboardCircle(float size, Vector3* Camera_worldspace);
	void drawArrowNote(float time, Vector3 CurrentLineVec,  Vector3 Vec_look, int dir);
	Vector3 getCameraPosition(float time);
	Vector3 getPlayerPosition(float time);
	Vector3 getCurrentLineVector(float time);


	typedef struct clap_check
	{
		bool is_hit;
		Vector3 pattern;
		int patternHit;
	};

	clap_check clap(Player& P);

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