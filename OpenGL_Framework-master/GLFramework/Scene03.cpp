#include "stdafx.h"
#include "Scene03.h"
#include "GLFramework.h"

S03Main::S03Main()
{
}

S03Main::~S03Main()
{
}

void S03Main::init()
{
	m_Camera.setDistance(200.f);
	m_Camera.setPerspective(60.f, 0.125f, 3500.f);
	m_Camera.setSensitivity(1.f);

	score = PD->score;
	for (int i = 0; i < PD->patternNum; i++)
	{
		if (PD->patternHit[i] == 2)
			perfect_num++;
		else if (PD->patternHit[i] == 1)
			good_num++;
		else
			miss_num++;
	}
	//score = 316351;
	//perfect_num = 257;
	//good_num = 1325;
	//miss_num = 13235;
}

void S03Main::exit()
{
	
}

void S03Main::render()
{
	m_Camera.ready();

	BG.render();

	//하드코딩 정말 최고다 최고 
	print_text("result", -10, 60, 0, 1, 1, 1);

	if (gettime > 0.5f)
	{
		print_text("perfect", -30, 40, 0, 1, 1, 1);

		if (gettime < 2.5f)
			print_text(std::to_string((int)temp_perfect_num),10, 40, 0, 1, 1, 1);
		else
			print_text(std::to_string(perfect_num), 10, 40, 0, 1, 1, 1);
	}

	if (gettime > 2.7f)
	{
		print_text("good", -30, 20, 0, 1, 1, 1);

		if (gettime < 4.7f)
			print_text(std::to_string((int)temp_good_num), 10, 20, 0, 1, 1, 1);
		else
			print_text(std::to_string(good_num), 10, 20, 0, 1, 1, 1);
	}

	if (gettime > 4.9)
	{
		print_text("miss", -30, 0, 0, 1, 1, 1);

		if (gettime < 6.9f)
			print_text(std::to_string((int)temp_miss_num), 10, 0, 0, 1, 1, 1);
		else
			print_text(std::to_string(miss_num), 10, 0, 0, 1, 1, 1);
	}

	if (gettime> 7.1 )
	{
		print_text("score", -30, -20, 0, 1, 1, 1);

		if (gettime < 9.1)
			print_text(std::to_string((int)temp_score), 10, -20, 0, 1, 1, 1);
		else
			print_text(std::to_string(score), 10, -20, 0, 1, 1, 1);
	}
}

void S03Main::reshape(int w, int h)
{
}

void S03Main::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
	{
		switch (key)
		{
		}
	}
}

void S03Main::mouse(int button, bool pressed, int x, int y)
{

}

void S03Main::motion(bool pressed, int x, int y)
{

}

void S03Main::clap()
{
	
}

void S03Main::update(float fDeltaTime)
{
	BG.update(fDeltaTime);
	gettime += fDeltaTime;

	if ((0.5f < gettime) && (gettime < 2.5f))
	{
		temp_perfect_num += perfect_num / 2.f * fDeltaTime;
	}
	else if ((2.7f < gettime) && (gettime < 4.7f))
	{
		temp_good_num += good_num / 2.f * fDeltaTime;
	}
	else if ((4.9f < gettime) && (gettime < 6.9f))
	{
		temp_miss_num += miss_num / 2.f * fDeltaTime;
	}
	else if ((7.1f < gettime) && (gettime < 9.1f))
	{
		temp_score += score / 2.f * fDeltaTime;
	}
}

//ㅇㅁㄹㅇㅁㄹㅇㅁㄹ졸려어 
void S03Main::print_text(std::string str, float x, float y, float z, float r, float g, float b)
{

	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(0.05, 0.05, 0.05);
	for (size_t s = 0; s < str.size(); s++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[s]);

	glPopMatrix();

}

void S03Main::print_text(std::string str, float x, float y, float z, float r, float g, float b, float a)
{

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(r, g, b, a);


	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(0.05, 0.05, 0.05);
	for (size_t s = 0; s < str.size(); s++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[s]);

	glPopMatrix();

	glDisable(GL_BLEND);
}

