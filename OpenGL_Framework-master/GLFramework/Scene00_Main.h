#pragma once
#include "GLScene.h"

/* UTILITIES */
#include "Model.h"
#include "Object.h"
#include "Camera.h"
#include "Scene00_BG.h"
#include "Texture.h"

/* ------------ */

class S00_Logo :
	public GLScene
{
public:
	S00_Logo();
	virtual ~S00_Logo();

	virtual void init();
	virtual void exit();
	virtual void reset();
	virtual void render();
	virtual void reshape(int w, int h);
	virtual void keyboard(int key, bool pressed, int x, int y, bool special);
	virtual void mouse(int button, bool pressed, int x, int y);
	virtual void motion(bool pressed, int x, int y);
	virtual void update(float fDeltaTime);
	void start_to_change_scene();
	GLubyte* LoadDIBitmap(const char *filename, BITMAPINFO **info);


private:

	Camera	      m_Camera;
	Model         m_Model;
	Object	      m_Title;
	Scene00_BG    BG;
	Scene00_TITLE TITLE;

	float         get_time;
	float         start_button_alpha;
	bool          is_started_to_change_scene;
	float         elapsed_time_since_scene_change_started;
	float         time_to_change_scene;
};

	