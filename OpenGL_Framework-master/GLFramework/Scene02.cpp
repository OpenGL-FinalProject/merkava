#include "stdafx.h"
#include "Scene02.h"
#include "GLFramework.h"

S02Main::S02Main()
{
}


S02Main::~S02Main()
{
}

void S02Main::init()
{
	m_Camera.setDistance(3000.f);
	m_Camera.setPerspective(45.f, 0.125f, 7'000.f);
	m_Camera.setSensitivity(10.f);

	m_Plane.setModel("Cube", 3000, false);
	m_Plane.setColor(Vector3(0.7f, 0.4f, 0.8f));
	m_Plane.move(0.f, -700.f, 0.f);
	m_Plane.scale(1.f, 0.01f, 1.f);

	for (int i = 0; i < 3; i++)
	{
		m_Box[i].setModel("Cube", 500, false);
		m_Box[i].setColor(Vector3(0.1f * (i+1), 0.2f * (i + 1), 0.3f * (i + 1)));
	}
	m_Box[0].move(0.f, -500.f, 0.f);
	m_Box[0].scale(1.5f, 0.9f, 1.f);
	m_Box[1].move(0.f, -130.f, 0.f);
	m_Box[1].scale(0.2f, 0.7f, 0.2f);
	m_Box[2].move(0.f, +150.f, 0.f);
	m_Box[2].scale(0.1f, 0.6f, 0.1f);

	for (int i = 0; i < 3; i++)
	{
		m_wBox[i].setModel("Cube", 530, true);
		m_wBox[i].setColor(Vector3(1.f,1.f,1.f));
	}
	m_wBox[0].move(0.f, -500.f, 0.f);
	m_wBox[0].scale(1.5f, 0.9f, 1.f);
	m_wBox[1].move(0.f, -130.f, 0.f);
	m_wBox[1].scale(0.2f, 0.7f, 0.2f);
	m_wBox[2].move(0.f, +150.f, 0.f);
	m_wBox[2].scale(0.1f, 0.6f, 0.1f);
}

void S02Main::exit()
{
	m_Plane.move(0.f, 700.f, 0.f);
	m_Box[0].move(0.f, 500.f, 0.f);

	m_Box[1].move(0.f, 130.f, 0.f);

	m_Box[2].move(0.f, -150.f, 0.f);


	m_wBox[0].move(0.f, 500.f, 0.f);

	m_wBox[1].move(0.f, 130.f, 0.f);

	m_wBox[2].move(0.f, -150.f, 0.f);

}

void S02Main::reset()
{

}

void S02Main::render()
{
	m_Camera.ready();

	glTranslatef(0.f, 20.f * tY, 0.f);
	glTranslatef(20.f * tX, 0.f, 0.f);

	m_Plane.render();

	glTranslatef(oX, 0.f, 0.f);
	glPushMatrix();
	{
		glRotatef(rY, 0.f, 1.f, 0.f);
		m_Box[0].render(); m_wBox[0].render();
		glTranslatef(0.f, -300.f, 0.f);
		glRotatef(secX, 1.f, 0.f, 0.f);
		glTranslatef(0.f, 300.f, 0.f);
		glRotatef(secY, 0.f, 1.f, 0.f);
		m_Box[1].render(); m_wBox[1].render();
		glRotatef(thdX, 1.f, 0.f, 0.f);
		glRotatef(thdZ, 0.f, 0.f, 1.f);
		m_Box[2].render(); m_wBox[2].render();
	}glPopMatrix();
}

void S02Main::reshape(int w, int h)
{

}

void S02Main::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
	{
		switch (key)
		{
		case '1':rY += 1; break;
		case '2': if (thdX > -90) thdX -= 2; break;
		case 's': if (secX > -90) secX -= 2; break;
		case 'w': if (thdX < 90) thdX += 2; break;
			//m_Sphere.m_qrRotation.rotate(0.1, m_Sphere.m_qrRotation.rotatePoint({ 0, 1, 0 })); break;
		case 'a': if (thdZ < 90) thdZ += 2; break;
		case '3': rY -= 2; break;
		case 'x': if (secX < 90) secX += 2; break;
		case 'q': if (secY < 90) secY += 2; break;
		case 'e': if (secY > -90) secY -= 2; break;
		case 'd': if (thdZ > -90) thdZ -= 2; break;
		case ' ': m_Framework->toScene("Main"); break;
		case 'o': rY = 0; secX = 0; thdX = 0; secY = 0; thdZ = 0; tX = 0; tY = 0; break;
		case '+': m_Camera.setDistance(m_Camera.getDistance() - 5); break;
		case '-': m_Camera.setDistance(m_Camera.getDistance() + 5); break;
		case 'i': tY++; break;
		case 'j': tX--; break;
		case 'k': tY--; break;
		case 'l': tX++; break;
		}
	}
}

void S02Main::mouse(int button, bool pressed, int x, int y)
{
}

void S02Main::motion(bool pressed, int x, int y)
{
	m_Camera.rotate(x, y, pressed);
}

void S02Main::update(float fDeltaTime)
{
	if (direction)
		oX += 500*fDeltaTime;
	else
		oX -= 500 * fDeltaTime;

	if (oX > 1100)
		direction = false;
	if (oX < -1100)
		direction = true;

}