#include "stdafx.h"
#include "Scene04.h"
#include "GLFramework.h"

S04Main::S04Main()
{

}

S04Main::~S04Main()
{

}

void S04Main::init()
{
	m_Camera.setDistance(1000.f);
	m_Camera.setPerspective(45.f, 0.125f, 7'000.f);
	m_Camera.setSensitivity(10.f);

	glShadeModel(GL_SMOOTH);
	s = false;

	rX = 0; rY = 0; rZ = 0;
	tX = 0; tY = 0;

	for (int i = 0; i < 5; i++)
		onoff[i] = false;
	for (int i = 0; i < 2; i++)
		open[i] = 0;
}

void S04Main::exit()
{

}

void S04Main::reset()
{

}

void S04Main::render()
{
	m_Camera.ready();

	Square();
		UpSphere();
		UpSpring();
		DownSphere();
}

void S04Main::reshape(int w, int h)
{

}

void S04Main::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
	{
		switch (key)
		{
		case 'w': break;
		case 'e': break;
		case ' ': m_Framework->toScene("Main"); break;
		case 'o': rX = 0; rY = 0; rZ = 0; break;
		case '+': m_Camera.setDistance(m_Camera.getDistance() - 5); break;
		case '-': m_Camera.setDistance(m_Camera.getDistance() + 5); break;
		case 'i': tY++; break;
		case 'j': tX--; break;
		case 'k': tY--; break;
		case 'l': tX++; break;
		case '0': if (s) s = false; else s = true; break;
		case '1': if (onoff[0]) onoff[0] = false; else onoff[0] = true; break;
		case '2': if (onoff[1]) onoff[1] = false; else onoff[1] = true; break;
		case '3': if (onoff[2]) onoff[2] = false; else onoff[2] = true; break;
		case '4': if (onoff[3]) onoff[3] = false; else onoff[3] = true; break;
		case '5': if (onoff[4]) onoff[4] = false; else onoff[4] = true; break;
		}
	}
}

void S04Main::mouse(int button, bool pressed, int x, int y)
{
}

void S04Main::motion(bool pressed, int x, int y)
{
	if (s)
		m_Camera.rotate(x, 0.f, pressed);
	else
		m_Camera.rotate(0.f, y, pressed);
}

void S04Main::update(float fDeltaTime)
{
	if (onoff[0])
		glDisable(GL_DEPTH_TEST);
	else
		glEnable(GL_DEPTH_TEST);

	if (onoff[1])
		glDisable(GL_CULL_FACE);
	else
		glEnable(GL_CULL_FACE);

	if (onoff[2])
		glShadeModel(GL_FLAT);
	else
		glShadeModel(GL_SMOOTH);

	if (onoff[3])
	{
		if (open[0] < 90)
			open[0]++;
	}
	else
	{
		if (open[0] > 0)
			open[0]--;
	}
	if (onoff[4])
	{
		if (open[1] < 90)
			open[1]++;
	}
	else
	{
		if (open[1] > 0)
			open[1]--;
	}
}

void S04Main::Square()
{
	glBegin(GL_QUADS);
	{
		Point(3);
		Point(0);
		Point(1);
		Point(2);
		
		Point(5);
		Point(6);
		Point(2);
		Point(1);

		Point(1);
		Point(0);
		Point(4);
		Point(5);

		Point(3);
		Point(2);
		Point(6);
		Point(7);
	}
	glEnd();

	//앞면
	glPushMatrix();
	{
		glTranslatef(0.f, -100.f, 100.f);
		glRotatef(open[0], 1.f, 0.f, 0.f);
		glTranslatef(0.f, 100.f, -100.f);
		glBegin(GL_QUADS);
		{
			Point(7);
			Point(6);
			Point(5);
			Point(4);
		}glEnd();
	}glPopMatrix();

	//윗면
	glPushMatrix();
	{
		glTranslatef(0.f, 100.f, -100.f);
		glRotatef(-open[1], 1.f, 0.f, 0.f);
		glTranslatef(0.f, -100.f, 100.f);
		glBegin(GL_QUADS);
		{
			Point(4);
			Point(0);
			Point(3);
			Point(7);
		}glEnd();
	}glPopMatrix();
}

void S04Main::Point(int num)
{
	switch (num)
	{
	case 0:
		glColor3f(1.0f, 1.0f, 0.0f); // Red+Green
		glVertex3f(100.0, 100.0, -100.0);
		break;
	case 1:
		glColor3f(1.0f, 0.0f, 0.0f); // Red
		glVertex3f(100.0, -100.0, -100.0);
		break;
	case 2:
		glColor3f(0.0f, 0.0f, 0.0f); // Black
		glVertex3f(-100.0, -100.0, -100.0);
		break;
	case 3:
		glColor3f(0.0f, 1.0, 0.0f); // Green
		glVertex3f(-100.0, 100.0, -100.0);
		break;
	case 4:
		glColor3f(1.0f, 1.0f, 1.0f); // White
		glVertex3f(100.0, 100.0, 100.0);
		break;
	case 5:
		glColor3f(1.0f, 0.0f, 1.0f); // Magenta
		glVertex3f(100.0, -100.0, 100.0);
		break;
	case 6:
		glColor3f(0.0f, 0.0f, 1.0f); // Blue
		glVertex3f(-100.0, -100.0, 100.0);
		break;
	case 7:
		glColor3f(0.0f, 1.0, 1.0f); // Cyan
		glVertex3f(-100.0, 100.0, 100.0);
		break;
	}
	
}

void S04Main::UpSphere()
{
	glPushMatrix();
	{
		glColor3f(1.f, 1.f, 1.f);
		glTranslatef(0.f,open[1]*3.f,0.f);
		glutSolidSphere(50.f, 12, 12);
		glColor3f(0.f, 0.f, 0.f);
	}glPopMatrix();
}
void S04Main::DownSphere()
{
	//스프링 (바보임)
	glPushMatrix();
	{
		glColor3f(1.f, 1.f, 1.f);
		glBegin(GL_LINE_LOOP);
		{
			for (int i = 0; i < 720; i++)
			{
				glVertex3d(50 * cos(i) , (open[1]/133.f) * i/2,50 * sin(i));
			}
		}glEnd();
		glColor3f(0.f, 0.f, 0.f);
	}glPopMatrix();
}

void S04Main::UpSpring()
{
	glPushMatrix();
	{
		glColor3f(1.f, 1.f, 1.f);
		glTranslatef(0.f,0.f, open[0] * 2.5f);
		glRotatef(open[0]*2.f, 1.f, 0.f, 0.f);
		glutWireSphere(50.f, 12, 12);
		glColor3f(0.f, 0.f, 0.f);
	}glPopMatrix();
}

