#include "stdafx.h"
#include "Scene07.h"
#include "GLFramework.h"

S07Main::S07Main()
{

}

S07Main::~S07Main()
{

}

void S07Main::init()
{
	numberOfPoint = 0;
	s = false;
}

void S07Main::exit()
{

}

void S07Main::reset()
{

}

void S07Main::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < numberOfPoint; i++)
	{
		glBegin(GL_POINTS);
		glVertex3f(pointz[i][0], pointz[i][1], pointz[i][2]);
		glEnd();
	}
}

void S07Main::reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 600);
	glOrtho(0, 800, 0, 600, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

void S07Main::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
	{
		switch (key)
		{
		case 'w': break;
		case 'e': break;
		case ' ': m_Framework->toScene("Main"); break;
		case 'o':  break;
		case '+': m_Camera.setDistance(m_Camera.getDistance() - 5); break;
		case '-': m_Camera.setDistance(m_Camera.getDistance() + 5); break;
		case '0': if (s) s = false; else s = true; break;
		}
	}
	if (special && pressed)
	{
		switch (key)
		{
		case GLUT_KEY_LEFT:
			
			break;
		}
	}
}

void S07Main::mouse(int button, bool pressed, int x, int y)
{
	if (pressed && button == GLUT_LEFT_BUTTON)
	{
		pointz[numberOfPoint][0] = x;
		pointz[numberOfPoint][1] = 600-y;
		pointz[numberOfPoint][2] = 0.f;
		numberOfPoint++;

		if ((numberOfPoint - 3) % 4 == 0)
		{
			pointz[numberOfPoint][0] = x;
			pointz[numberOfPoint][1] = 600 - y;
			pointz[numberOfPoint][2] = 0.f;
			numberOfPoint++;
		}
	}
	if (pressed && button == GLUT_RIGHT_BUTTON)
	{

	}
}

void S07Main::motion(bool pressed, int x, int y)
{
	
}

void S07Main::update(float fDeltaTime)
{
	
}