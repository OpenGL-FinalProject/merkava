#include "stdafx.h"
#include "Scene01_Tutorial.h"
#include "GLFramework.h"

S01_Tutorial::S01_Tutorial()
{
}

S01_Tutorial::~S01_Tutorial()
{
}

void S01_Tutorial::init()
{
	m_Camera.setDistance(3000.f);
	m_Camera.setPerspective(45.f, 0.125f, 7'000.f);
	m_Camera.setSensitivity(10.f);
	m_Camera.setEye(Vector3{ 100.f,100.f,200.f });

	m_Plane.setModel("Cube", 2000, false);
	m_Plane.setColor(Vector3(0.f, 1.f, 1.f));
	m_Plane.move(0.f, -700.f, 0.f);
	m_Plane.scale(1.f, 0.01f, 1.f);

	m_Sphere.setModel("Sphere", 200, true);
	m_Sphere.move(0.f, -500.f, 0.f);

	rX = 0, rY = 0, rZ = 0;
	tX = 0, tY = 0;

	s = 0;
}

void S01_Tutorial::exit()
{
	m_Plane.move(0.f, 700.f, 0.f);
	m_Sphere.move(0.f, 500.f, 0.f);
}

void S01_Tutorial::reset()
{

}

void S01_Tutorial::render()
{
	m_Camera.ready();
	
	glTranslatef(0.f, 20.f * tY, 0.f);
	glTranslatef(20.f * tX, 0.f, 0.f);
	
	m_Plane.render();
	m_Sphere.render();
}

void S01_Tutorial::reshape(int w, int h)
{

}

void S01_Tutorial::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
	{
		switch (key)
		{
		case 'w': if (rX < 155) { rX += 2.707; m_Sphere.move(0.f, 0.f, -2.707 * 200 / 36); }
				  m_Sphere.m_qrRotation.rotate(0.1, m_Sphere.m_qrRotation.rotatePoint({ 1, 0, 0 })); break;
		case '2':  break;
		case 'e':
			m_Sphere.m_qrRotation.rotate(-0.1, m_Sphere.m_qrRotation.rotatePoint({ 0, 1, 0 })); break;
		case 'q':
			m_Sphere.m_qrRotation.rotate(0.1, m_Sphere.m_qrRotation.rotatePoint({ 0, 1, 0 })); break;
		case 'a': if (rZ < 155) { m_Sphere.move(-2.707 * 200 / 36, 0.f, 0.f); rZ += 2.707; }
				  m_Sphere.m_qrRotation.rotate(-0.1, m_Sphere.m_qrRotation.rotatePoint({ 0, 0, 1 })); break;
		case 's': if (rX > -155) { rX -= 2.707; m_Sphere.move(0.f, 0.f, 2.707 * 200 / 36); }
				  m_Sphere.m_qrRotation.rotate(-0.1, m_Sphere.m_qrRotation.rotatePoint({ 1, 0, 0 })); break;
		case 'x':  break;
		case 'd': if (rZ > -155) {m_Sphere.move(2.707 * 200 / 36, 0.f, 0.f); rZ -= 2.707;}
			m_Sphere.m_qrRotation.rotate(0.1, m_Sphere.m_qrRotation.rotatePoint({ 0, 0, 1 })); break;	
		case ' ': m_Framework->toScene("Main"); break;
		case 'o': rX = 0; rY = 0; rZ = 0; m_Sphere.m_qrRotation.resetQuaternion(); m_Sphere.setPosition(0, -500.f, 0); m_Camera.resetRotation(); break;
		case '+': m_Camera.setDistance(m_Camera.getDistance() - 5); break;
		case '-': m_Camera.setDistance(m_Camera.getDistance() + 5); break;
		case 'i': tY++; break;
		case 'j': tX--; break;
		case 'k': tY--; break;
		case 'l': tX++; break;
		case '0': s = (s + 1) % 2; break;	
		}
	}
}

void S01_Tutorial::mouse(int button, bool pressed, int x, int y)
{
}

void S01_Tutorial::motion(bool pressed, int x, int y)
{
	if (s)
		m_Camera.rotate(x, 0.f, pressed);
	else
		m_Camera.rotate(0.f, y, pressed);
}

void S01_Tutorial::update(float fDeltaTime)
{

}