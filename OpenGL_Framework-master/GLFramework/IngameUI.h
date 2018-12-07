#pragma once
#include "LinearMath.h"
#include "MapData.h"
class IngameUI
{
public:
	IngameUI();
	~IngameUI();

	void init(MapData*);
	GLubyte * LoadDIBitmap(const char * filename, BITMAPINFO ** info);
	GLuint LoadTexture(const char * filename, int width_1, int height_1);
	void samplerRectangle(Vector3 * Camera_worldspace);
	void setGridColor(float x, float y, float z);
	void setFlashColor(float x, float y, float z);
	void setFlashColor(float x, float y, float z, float a);
	void skybox(float time);
	void grid();
	void flash(Vector3 CameraPosition);
	void render(Vector3 CameraPosition, Vector3 * Camera_worldspace, float dist);
	void scoreUp(int critical);
	void update(float fDeltaTime);
	bool fadeout(float fDeltaTime);


	Vector3 Vectorworld;
	Vector3 Vectorup;

	MapData* Mapdata;
	float gap;

	int printScore;
	int score;

	float gridColor[3];
	float flashColor[4];

	bool isfadingout;

	GLubyte *pBytes;
	BITMAPINFO *info;
	GLuint texture_object[6];

};