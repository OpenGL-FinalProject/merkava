#include "stdafx.h"
#include "Scene01_MIR.h"
#include "GLFramework.h"

Scene01_MIR::Scene01_MIR()
{
}

Scene01_MIR::~Scene01_MIR()
{
}

void Scene01_MIR::init()
{
	m_Camera.setDistance(3000.f);
	m_Camera.setPerspective(45.f, 0.125f, 7'000.f);
	m_Camera.setSensitivity(10.f);
	m_Camera.setEye(Vector3{ 100.f,100.f,300.f });
	
	MIL.init();
	MIL.selectFolder("Resources");

	MIL.play();
	Map.init(1);
	get_time = 0;
}

void Scene01_MIR::exit()
{
	
}

void Scene01_MIR::reset()
{

}

void Scene01_MIR::render()
{
	m_Camera.ready();

	Map.render();
	P.render();
}

void Scene01_MIR::reshape(int w, int h)
{

}

void Scene01_MIR::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
	{
		switch (key)
		{
		case '0': s = (s + 1) % 2; break;
		}
	}
}

void Scene01_MIR::mouse(int button, bool pressed, int x, int y)
{
}

void Scene01_MIR::motion(bool pressed, int x, int y)
{
	if (s)
		m_Camera.rotate(x, 0.f, pressed);
	else
		m_Camera.rotate(0.f, y, pressed);
}

void Scene01_MIR::update(float fDeltaTime)
{
	get_time += fDeltaTime;
	P.update(fDeltaTime, Map.getPlayerPosition(get_time));
	//m_Camera.setEye(Map.getCameraPosition(get_time));
	m_Camera.setEye(Vector3(P.Position.x + 50.f, P.Position.y + 50.f, P.Position.z + 50.f));
	m_Camera.setTarget(P.Position);
}