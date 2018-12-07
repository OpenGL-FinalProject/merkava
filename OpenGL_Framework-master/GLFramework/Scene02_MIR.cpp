#include "stdafx.h"
#include "Scene02_MIR.h"
#include "GLFramework.h"

Scene02_MIR::Scene02_MIR()
{
	music_ended = false;

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

	coaster = false;
	spaceKeydown = false;
	
	MIL.init();
	clap.init();

	s = false;
	k = false;

	MIL.selectFolder("Resources");
	clap.addSound("FX\\clap.mp3", true);

	MIL.play();
	Map.init(1);
	get_time = 0;
	patternNum = 0;

	flashedNums = 0;

	mayidrawUI = true;
	UI.init(&Map);
	gridOn = true;
	UI.setGridColor(0.f, 0.f, 0.f);
	UI.setFlashColor(1.f, 1.f, 1.f);

	pause = false;
	//MIL.pause();
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

	Map.render(coaster,get_time, Camera_worldspace, axis);
	if (!coaster)
		P.render();
	hit_effect.render();
	
	if (mayidrawUI)
	{
		UIPosition = V3::add(Map.getCameraPosition(get_time), V3::subtract(P.Position, Map.getCameraPosition(get_time)));
		//printf("%f %f = %f\n", P.Position.x, Map.getCameraPosition(get_time).x, V3::dist(P.Position, Map.getCameraPosition(get_time)));
		UI.render(UIPosition, Camera_worldspace, V3::dist(P.Position, Map.getCameraPosition(get_time)));
	}
	if (gridOn && get_time < 79.0f)
		UI.grid();
	UI.skybox(get_time);
	UI.flash(m_Camera.getEye());
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
		case 'g':
			gridOn = (gridOn + 1) % 2; break;
		case ' ':
			if (!spaceKeydown)
			{
				auto temp_clap = Map.clap(P);
				if (temp_clap.is_hit)
				{
					// note hit
					printf("clap\n");
					hit_effect.create_cube_set(temp_clap.pattern, temp_clap.patternHit);
					UI.scoreUp(temp_clap.patternHit);
					//UI.setFlashColor(1, 0, 0, 0.5);
					//UI.flash(m_Camera.getEye());
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
	if (button == GLUT_LEFT_BUTTON && pressed)
		k = false;
	else if (button == GLUT_RIGHT_BUTTON && pressed)
		k = true;

}

void Scene02_MIR::motion(bool pressed, int x, int y)
{
	if (k)
	{
		if (s)
		{
			m_Camera.rotate(x, 0.f, pressed);
			if (pressed)
				mayidrawUI = false;
		}
		else
		{
			m_Camera.rotate(0.f, y, pressed);
			if (pressed)
				mayidrawUI = false;
		}
	}
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

		if(music_ended)
		{
			PD->patternNum = Map.patternNum;
			PD->score = UI.score;
			memcpy(PD->patternHit, Map.patternHit, sizeof(float) * 600);
			if (UI.fadeout(fDeltaTime))
				m_Framework->toScene("Result");
		}
		else
		{
			if (flashedNums < Map.flashIndex)
			{
				if (get_time > Map.flashTime[flashedNums][1])
				{
					if (Map.flashTime[flashedNums][0] == 0)
					{
						UI.setGridColor(Map.flashColor[flashedNums].x, Map.flashColor[flashedNums].y, Map.flashColor[flashedNums].z);
					}
					else
						UI.setFlashColor(Map.flashColor[flashedNums].x, Map.flashColor[flashedNums].y, Map.flashColor[flashedNums].z, Map.flashColor[flashedNums].w);
					flashedNums++;
				}
			}

			if (get_time >= 138.f)
			{
				music_ended = true;
				UI.setFlashColor(0, 0, 0, 0);
			}
		}
		
		UI.update(fDeltaTime);
	}
	axis[2] = V3::normalize(m_Camera.getLook());
	axis[0] = V3::normalize(m_Camera.getRight());
	axis[1] = V3::cross(axis[2], axis[0]);

	Camera_worldspace[0] = V3::normalize(axis[0]);
	Camera_worldspace[1] = V3::normalize(axis[1]);
}

