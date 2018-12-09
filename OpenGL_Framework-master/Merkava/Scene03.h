#pragma once
#include "GLScene.h"

/* UTILITIES */
#include "Camera.h"
#include "PlayData.h"
#include "Scene00_BG.h"

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
	void print_text(std::string str, float x, float y, float z, float r, float g, float b);
	void print_text(std::string str, float x, float y, float z, float r, float g, float b, float a);

private:
	Camera			m_Camera;

	PlayData*		PD = PlayData::getInstance();
	Scene03_BG		BG;

	//z
	float           gettime = 0;
	int             perfect_num = 0;
	int             good_num = 0;
	int             miss_num = 0;
	int             score = 0;
	//ㅇㅁㄹㅇㅁㄹㅇㅁㄹㅇㅁㄹ저세상코딩
	float             temp_perfect_num = 0;
	float             temp_good_num = 0;
	float             temp_miss_num = 0;
	float             temp_score = 0;


};

