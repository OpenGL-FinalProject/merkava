#pragma once
#include "GLScene.h"

#include "Camera.h"

typedef struct _Points
{
	float x;
	float y;
	int dir;
}Points;

class S5Main : public GLScene
{
public:
	S5Main();
	virtual ~S5Main();

	virtual void init();
	virtual void exit();
	virtual void reset();
	virtual void render();
	virtual void reshape(int w, int h);
	virtual void keyboard(int key, bool pressed, int x, int y, bool special);
	virtual void mouse(int button, bool pressed, int x, int y);
	virtual void motion(bool pressed, int x, int y);
	virtual void update(float fDeltaTime);

	void Square();

	void Point(int num);
	void Box();
	void BoxUpdate();
private:
	Camera			m_Camera;
	float			m_CameraRotation; // 회전각 알아내기
	//
	bool			s;
	//
	float			rX, rY, rZ;
	int				tX, tY;
	//
	Points			ball[5];
	Points			box[3];
};


