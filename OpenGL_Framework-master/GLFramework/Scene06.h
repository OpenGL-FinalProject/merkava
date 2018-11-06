#pragma once
#include "GLScene.h"

/* UTILITIES */
#include "Model.h"
#include "NormalObject.h"
#include "Camera.h"
#include "AirPlane.h"
#include "Robot.h"

class S06Main : public GLScene
{
public:
	S06Main();
	virtual ~S06Main();

	virtual void init();
	virtual void exit();
	virtual void reset();
	void Triangles();
	void Treez();
	void Pressz();
	void Runningz();
	void Ironz();
	void Circlez();
	virtual void render();
	virtual void reshape(int w, int h);
	virtual void keyboard(int key, bool pressed, int x, int y, bool special);
	virtual void mouse(int button, bool pressed, int x, int y);
	virtual void motion(bool pressed, int x, int y);
	virtual void update(float fDeltaTime);

	void Square();
	void Point(int num);
private:
	Camera			m_Camera;
	NormalObject	m_Plane;

	NormalObject	Tree[2];

	float			tX = 0, tY = 0;

	//
	
	bool ad;
	bool s;
	float anim;
	int spin;

	AirPlane Air;
	Robot robot;
	float si, co;
	bool onair = false;
	bool reverse = false;

	bool			onoff[3];

	int BoxSpin;
	bool open;
};

