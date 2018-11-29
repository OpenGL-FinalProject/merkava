#pragma once
#include "GLScene.h"

/* UTILITIES */
#include "Model.h"
#include "NormalObject.h"
#include "Camera.h"
#include "SoundPlayer.h"
#include "MapData.h"
#include "Player.h"
/* ------------ */

class Scene02_MIR :
	public GLScene
{
public:
	Scene02_MIR();
	virtual ~Scene02_MIR();

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
	float			rX, rY, rZ;
	int				tX, tY;
	Camera			m_Camera;

	SoundPlayer		MIL;
	bool			s;

	//

	MapData			Map;
	Player			P;
	float			get_time;
};