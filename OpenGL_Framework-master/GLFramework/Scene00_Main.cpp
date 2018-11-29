
#include "stdafx.h"
#include "Scene00_Main.h"
#include "GLFramework.h"
#define _USE_MATH_DEFINES
#include <math.h>


S00Logo::S00Logo()
{
}

S00Logo::~S00Logo()
{
}

void S00Logo::init()
{

	m_Camera.setDistance(200.f);
	m_Camera.setPerspective(60.f, 0.125f, 3500.f);
	m_Camera.setSensitivity(1.f);

}

void S00Logo::exit()
{
}

void S00Logo::reset()
{
}

void S00Logo::render()
{
	m_Camera.ready();

	BG.render();
	
	print("Press any key to start",8 , -30, 100,1.f,1.f,1.f, start_button_alpha); //현재 x,y값 상수 
	           																			
}

void S00Logo::reshape(int w, int h)
{

}

void S00Logo::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
		switch (key)
		{
		case '1': m_Framework->toScene("1"); break;
		//case '2': m_Framework->toScene("2"); break;
		//case '3': m_Framework->toScene("3"); break;
		case 's': m_Framework->toScene("Made In Love"); break;
		}
		
}

void S00Logo::mouse(int button, bool pressed, int x, int y)
{
}

void S00Logo::motion(bool pressed, int x, int y)
{
}

void S00Logo::update(float fDeltaTime)
{
	BG.update(fDeltaTime);
	get_time += fDeltaTime;
	start_button_alpha = sin((get_time - (int)get_time) * M_PI);
	
}


