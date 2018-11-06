#pragma once
#include "GLScene.h"
#include "Camera.h"

class S07Main : public GLScene
{
public:
	S07Main();
	virtual ~S07Main();

	virtual void init();
	virtual void exit();
	virtual void reset();
	virtual void render();
	virtual void reshape(int w, int h);
	virtual void keyboard(int key, bool pressed, int x, int y, bool special);
	virtual void mouse(int button, bool pressed, int x, int y);
	virtual void motion(bool pressed, int x, int y);
	virtual void update(float fDeltaTime);

private:
	Camera			m_Camera;
	float			m_CameraRotation; // 회전각 알아내기
									  //
	bool s;

	float			pointz[19][3] = {0};
	int				numberOfPoint;
};


