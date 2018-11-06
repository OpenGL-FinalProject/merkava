#pragma once
#include "GLScene.h"

#include "Camera.h"

class S04Main : public GLScene
{
public:
	S04Main();
	virtual ~S04Main();

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
			void UpSphere();
			void DownSphere();
			void UpSpring();
private:
	Camera			m_Camera;
	//
	bool			s;
	//
	int				rX, rY, rZ;
	int				tX, tY;
	//
	bool			onoff[5];

	int				open[2];
};

