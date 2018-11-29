#include "stdafx.h"
#include "Scene02_MIR.h"
#include "GLFramework.h"

Scene02_MIR::Scene02_MIR()
{
}

Scene02_MIR::~Scene02_MIR()
{
}

void Scene02_MIR::init()
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

void Scene02_MIR::exit()
{
	
}

void Scene02_MIR::reset()
{

}

void Scene02_MIR::render()
{
	m_Camera.ready();

	Map.render();
	P.render();
}

void Scene02_MIR::reshape(int w, int h)
{

}

void Scene02_MIR::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
	{
		switch (key)
		{
		case '0': s = (s + 1) % 2; break;
		}
	}
}

void Scene02_MIR::mouse(int button, bool pressed, int x, int y)
{
}

void Scene02_MIR::motion(bool pressed, int x, int y)
{
	if (s)
		m_Camera.rotate(x, 0.f, pressed);
	else
		m_Camera.rotate(0.f, y, pressed);
}

void Scene02_MIR::update(float fDeltaTime)
{
	get_time += fDeltaTime;
	P.update(fDeltaTime, Map.getPlayerPosition(get_time));
	//m_Camera.setEye(Map.getCameraPosition(get_time));
	m_Camera.setEye(Vector3(P.Position.x + 50.f, P.Position.y + 50.f, P.Position.z + 50.f));
	m_Camera.setTarget(P.Position);
}