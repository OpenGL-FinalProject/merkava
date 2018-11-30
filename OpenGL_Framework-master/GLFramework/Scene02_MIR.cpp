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

	pause = false;
	
	MIL.init();
	clap.init();
	MIL.selectFolder("Resources");
	clap.addSound("FX\\clap.mp3", true);

	MIL.play();
	Map.init(1);
	get_time = 0;
	patternNum = 0;
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
		case 's':
			if (pause == false)
			{
				pause = true;
				MIL.pause();
			}
			else
			{
				pause = false;
				MIL.unpause();
			}
			break;
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
	if (!pause)
	{
		get_time += fDeltaTime;
		P.update(fDeltaTime, Map.getPlayerPosition(get_time));
		//printf("%f %f %f =?= %f %f %f\n",P.Position.x, P.Position.y, P.Position.z, Map.pattern[patternNum].x, Map.pattern[patternNum].y, Map.pattern[patternNum].z);
		if (P.Position == Map.pattern[patternNum])
		{
			printf("clap\n");
			clap.play(0, false);
			patternNum++;
		}
		//m_Camera.setEye(Map.getCameraPosition(get_time));
		m_Camera.setEye(Vector3(P.Position.x + 50.f, P.Position.y + 50.f, P.Position.z + 50.f));
		m_Camera.setTarget(P.Position);
	}
}