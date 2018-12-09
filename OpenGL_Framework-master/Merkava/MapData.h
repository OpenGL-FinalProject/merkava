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