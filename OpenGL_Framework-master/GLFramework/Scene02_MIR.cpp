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
	coaster = false;
	spaceKeydown = false;
	
	MIL.init();
	clap.init();
	UI.init();
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

	Map.render(coaster,get_time, Camera_worldspace);
	if (!coaster)
		P.render();
	hit_effect.render();

	UI.render();
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
		case '!':
			coaster = (coaster + 1) % 2; break;
			break;
		case ' ':
			if (!spaceKeydown)
			{
				auto temp_clap = Map.clap(P);
				if (temp_clap.is_hit)
				{
					// note hit
					printf("clap\n");
					hit_effect.create_cube_set(temp_clap.pattern, temp_clap.patternHit);
					clap.play(0, false);
				}
				P.hit();
				spaceKeydown = true;
			}
			break;
		}
	}
	else
	{
		switch (key)
		{
		case ' ':
			spaceKeydown = false;
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
		hit_effect.update(fDeltaTime);
		if (P.Position == Map.pattern[patternNum])
		{
			printf("note\n");
			patternNum++;
		}
		if (coaster)
		{
			m_Camera.setEye(Map.getPlayerPosition(get_time));
			m_Camera.setTarget(V3::add(Map.getPlayerPosition(get_time+0.7f),Vector3(0.5f,1.f,1.f)));
		}
		else
		{
			m_Camera.setEye(Map.getCameraPosition(get_time));
			m_Camera.setTarget(P.Position);
		}
		
	}
	axis[2] = V3::normalize(m_Camera.getLook());
	axis[0] = V3::normalize(m_Camera.getRight());
	axis[1] = V3::cross(axis[2], axis[0]);

	Camera_worldspace[0] = V3::normalize(axis[0]);
	Camera_worldspace[1] = V3::normalize(axis[1]);

	UI.update();
}