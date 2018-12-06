#include "stdafx.h"
#include "Scene03.h"
#include "GLFramework.h"

S03Main::S03Main()
{
}

S03Main::~S03Main()
{
}

void S03Main::init()
{
	m_Camera.setDistance(200.f);
	m_Camera.setPerspective(60.f, 0.125f, 3500.f);
	m_Camera.setSensitivity(1.f);
}

void S03Main::exit()
{
	
}

void S03Main::render()
{
	m_Camera.ready();

	BG.render();
}

void S03Main::reshape(int w, int h)
{
}

void S03Main::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
	{
		switch (key)
		{
		}
	}
}

void S03Main::mouse(int button, bool pressed, int x, int y)
{

}

void S03Main::motion(bool pressed, int x, int y)
{

}

void S03Main::clap()
{
	
}

void S03Main::update(float fDeltaTime)
{
	BG.update(fDeltaTime);
}
