#include "stdafx.h"
#include "Scene05.h"
#include "GLFramework.h"

S5Main::S5Main()
{

}

S5Main::~S5Main()
{

}

void S5Main::init()
{
	m_Camera.setDistance(500.f);
	m_Camera.setPerspective(45.f, 0.125f, 7'000.f);
	m_Camera.setSensitivity(10.f);

	m_CameraRotation = 0;
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	rX = 0; rY = 0; rZ = 0;
	tX = 0; tY = 0;

	for (int i = 0; i < 5; i++)
	{
		ball[i].x = rand() % 150 - 75;
		ball[i].y = rand() % 150 - 75;
		ball[i].dir = rand() % 4;
	}

	for (int i = 0; i < 3; i++)
	{
		box[i].x = 0;
		box[i].y = -50 + 50 * i;
		box[i].dir = 0;
	}
}

void S5Main::exit()
{

}

void S5Main::reset()
{

}

void S5Main::render()
{
	m_Camera.ready();

	for (int i = 0; i < 5; i++)
	{
		glColor3f(0.f, 0.f, 1.f);
		glPushMatrix();
		{
			glTranslatef(-ball[i].x, -ball[i].y, (i-2) * 30.f);
			glutSolidSphere(12.f, 12, 12);
		}glPopMatrix();
	}

	Square();
	Box();
}

void S5Main::reshape(int w, int h)
{

}

void S5Main::keyboard(int key, bool pressed, int x, int y, bool special)
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
		case ',': rX += 1; m_Camera.rotate(rX, rY, pressed); break;
		case 'm': rX -= 1; m_Camera.rotate(rX, rY, pressed); break;
		case '.': rY += 1; m_Camera.rotate(rX, rY, pressed); break;
		case '/': rY -= 1; m_Camera.rotate(rX, rY, pressed); break;
		case 'i': tY++; break;
		case 'j': tX--; break;
		case 'k': tY--; break;
		case 'l': tX++; break;
		case '0': if (s) s = false; else s = true; break;
		case 'b': 
			for (int i = 0; i < 5; i++)
			{
				ball[i].x = rand() % 150 - 75;
				ball[i].y = rand() % 150 - 75;
				ball[i].dir = rand() % 4;
			}
			break;
		}
	}
}

void S5Main::mouse(int button, bool pressed, int x, int y)
{
}

void S5Main::motion(bool pressed, int x, int y)
{
	if (s)
	{
		m_CameraRotation += 1.f;
		m_Camera.rotate((2.f * 3.14f / 360.f), Vector3(0.f, 0.f, 1.f));
	}
	else
	{
		m_CameraRotation -= 1.f;
		m_Camera.rotate((-2.f * 3.14f / 360.f), Vector3(0.f, 0.f, 1.f));
	}
	if (m_CameraRotation > 360)
	{
		m_CameraRotation -= 360;
	}
	if (m_CameraRotation < 0)
	{
		m_CameraRotation += 360;
	}
}

void S5Main::update(float fDeltaTime)
{
	BoxUpdate();
	for (int i = 0; i < 5; i++)
	{
		switch (ball[i].dir)
		{
		case 0:
			ball[i].x++;
			if (ball[i].x > 88)
				ball[i].dir = 2;
			break;
		case 1:
			ball[i].y++;
			if (ball[i].y > 88)
				ball[i].dir = 3;
			break;
		case 2:
			ball[i].x--;
			if (ball[i].x < -88)
				ball[i].dir = 0;
			break;
		case 3:
			ball[i].y--;
			if (ball[i].y < -88)
				ball[i].dir = 1;
			break;
		}
	}
}

void S5Main::Square()
{
	glBegin(GL_QUADS);
	{
		glColor3f(0.2f, 0.2f, 0.2f); // Black
		Point(3);
		Point(2);
		Point(1);
		Point(0);
		glColor3f(0.3f, 0.3f, 0.3f); // Black
		Point(5);
		Point(1);
		Point(2);
		Point(6);
		glColor3f(0.4f, 0.4f, 0.4f); // Black
		Point(1);
		Point(5);
		Point(4);
		Point(0);
		glColor3f(0.5f, 0.5f, 0.5f); // Black
		Point(3);
		Point(7);
		Point(6);
		Point(2);

		//¾Õ¸é
		glColor3f(0.6f, 0.6f, 0.6f); // Black
		Point(7);
		Point(4);
		Point(5);
		Point(6);

		//À­¸é
		glColor3f(0.7f, 0.7f, 0.7f); // Black
		Point(4);
		Point(7);
		Point(3);
		Point(0);
	}
	glEnd();

}

void S5Main::Point(int num)
{
	switch (num)
	{
	case 0:
		glVertex3f(100.0, 100.0, -100.0);
		break;
	case 1:
		glVertex3f(100.0, -100.0, -100.0);
		break;
	case 2:
		glVertex3f(-100.0, -100.0, -100.0);
		break;
	case 3:
		glVertex3f(-100.0, 100.0, -100.0);
		break;
	case 4:
		glVertex3f(100.0, 100.0, 100.0);
		break;
	case 5:
		glVertex3f(100.0, -100.0, 100.0);
		break;
	case 6:
		glVertex3f(-100.0, -100.0, 100.0);
		break;
	case 7:
		glVertex3f(-100.0, 100.0, 100.0);
		break;
	}

}

void S5Main::Box()
{
	for (int i = 0; i < 3; i++)
	{
		glColor3f(1.f, 0.f, 0.f);
		glPushMatrix();
		{
			glTranslatef(-box[i].x, -box[i].y, (i - 2) * 30.f);
			glutSolidCube(7.f * (3-i));
			glColor3f(1.f, 0.f, 1.f);
			glutWireCube(7.1f * (3-i));
		}glPopMatrix();
	}
}

void S5Main::BoxUpdate()
{
	std::cout << m_CameraRotation << std::endl;
	for (int i = 0; i < 3; i++)
	{
		if (m_CameraRotation > 0.f && m_CameraRotation < 180.f &&  box[i].x > -100 +(7.f * (3.f - i)) / 2.f)
			box[i].x -= 1.f;
		if (m_CameraRotation > 180.f && m_CameraRotation < 360.f &&  box[i].x < 100 - (7.f * (3.f - i)) / 2.f)
			box[i].x += 1.f;
		if (m_CameraRotation > 90.f && m_CameraRotation < 270.f &&  box[i].y > -100 + (7.f * (3.f - i)) / 2.f)
			box[i].y -= 1.f;
		if ((m_CameraRotation > 270.f && m_CameraRotation < 360.f || m_CameraRotation >= 0.f && m_CameraRotation < 90.f) &&  box[i].y < 100 - (7.f * (3.f - i)) / 2.f)
			box[i].y += 1.f;
	}
	
}