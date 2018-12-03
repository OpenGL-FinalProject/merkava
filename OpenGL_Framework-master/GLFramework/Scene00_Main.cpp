
#include "stdafx.h"
#include "Scene00_Main.h"
#include "GLFramework.h"
#define _USE_MATH_DEFINES
#include <math.h>


S00_Logo::S00_Logo()
{
	elapsed_time_since_scene_change_started = 0.f;
	time_to_change_scene = 2.f;
}

S00_Logo::~S00_Logo()
{
}

void S00_Logo::init()
{

	m_Camera.setDistance(200.f);
	m_Camera.setPerspective(60.f, 0.125f, 3500.f);
	m_Camera.setSensitivity(1.f);

}

void S00_Logo::exit()
{
}

void S00_Logo::reset()
{
}

void S00_Logo::render()
{
	m_Camera.ready();

	BG.render();
	
	//ÅØ½ºÆ®µµ °´Ã¼·Î »©¾ßÇÏ´Âµ¥.. ±ÍÂú¾Æ
	print("Press s to start",6 , -30, 100,1.f,1.f,1.f, start_button_alpha); //ÇöÀç x,y°ª »ó¼ö 
	           																			
}

void S00_Logo::reshape(int w, int h)
{

}

void S00_Logo::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
		switch (key)
		{
		case's':
			start_to_change_scene();
			BG.start_to_change_scene();
			break;
		}
		
}

void S00_Logo::mouse(int button, bool pressed, int x, int y)
{
}

void S00_Logo::motion(bool pressed, int x, int y)
{
}

void S00_Logo::update(float fDeltaTime)
{
	BG.update(fDeltaTime);
	get_time += fDeltaTime;

	if (is_started_to_change_scene == false)
	{
		start_button_alpha = sin((get_time - (int)get_time) * M_PI);
	}
	else if(is_started_to_change_scene==true)
	{
		elapsed_time_since_scene_change_started += fDeltaTime;
		start_button_alpha = sin((1-elapsed_time_since_scene_change_started)*M_PI / (time_to_change_scene));
	}

	if(elapsed_time_since_scene_change_started>= time_to_change_scene)
		m_Framework->toScene("Made In Love"); 
	
}

void S00_Logo::start_to_change_scene()
{
	is_started_to_change_scene = true;
	start_button_alpha = 1.f;
}