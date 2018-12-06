#pragma once
#include "GLScene.h"

/* UTILITIES */
#include "Model.h"
#include "NormalObject.h"
#include "Camera.h"
#include "AirPlane.h"

class S03Main : public GLScene
{
public:
	S03Main();
	virtual ~S03Main();

	virtual void init();
	virtual void exit();
	virtual void render();
	virtual void reshape(int w, int h);
	virtual void keyboard(int key, bool pressed, int x, int y, bool special);
	virtual void mouse(int button, bool pressed, int x, int y);
	virtual void motion(bool pressed, int x, int y);
	void clap();
	virtual void update(float fDeltaTime);

private:
	Camera			m_Camera;

};

