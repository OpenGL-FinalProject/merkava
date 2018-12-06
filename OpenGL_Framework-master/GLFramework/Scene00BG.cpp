#include "Scene00_BG.h"
#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <math.h>


Scene00_BG::Scene00_BG()
{
	player.update(NULL, player_pos);
	time_to_change_scene = 2.f;
	cylinder_alpha = 1.f;
	line_alpha = 1.f;
	elapsed_time_since_scene_change_started = 0.f;
}

Scene00_BG::Scene00_BG(const float & _time_to_change_scene)
{
}



Scene00_BG::~Scene00_BG()
{
}

void Scene00_BG::update(const float& fDeltaTime)
{

	cylinder_rotate_y +=  cylinder_rotate_y_speed_per_sec * fDeltaTime;
	if (cylinder_rotate_y > 360)
		cylinder_rotate_y -= 360;

	cylinder_translate_y += cylinder_translate_y_speed_per_sec * fDeltaTime;
	if (cylinder_translate_y > (cylinder_height / 16))
		cylinder_translate_y -= (cylinder_height / 16);

	if (is_started_to_change_scene == true)
	{
		elapsed_time_since_scene_change_started += fDeltaTime;
		cylinder_alpha = sin((1-elapsed_time_since_scene_change_started)*M_PI / (time_to_change_scene));
		line_alpha = cos((elapsed_time_since_scene_change_started)*M_PI / (time_to_change_scene*2));
		player_pos.y = (1-cos(elapsed_time_since_scene_change_started*M_PI / (time_to_change_scene*2)))*30;
		player.update(NULL, player_pos);
	}
}
void Scene00_BG::render()
{
	//하드코딩 체고ㅗ오ㅗ오오오ㅗ오


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//실린더
	glPushMatrix();
	{
		glTranslatef(0, cylinder_height / 2 - cylinder_translate_y, -200);
		glRotatef(90, 1, 0, 0);  //왜 실린더는 기본적으로 눕혀서 그려지는가 
		glRotatef(cylinder_rotate_y, 0, 0, 1);

		glColor4f(1, 1, 0, cylinder_alpha);
		glutWireCylinder(cylinder_width, cylinder_height, 12, 16);
	
	}
	glPopMatrix();

	
	//라인	
	glColor4f(1, 1, 1, line_alpha);
	glBegin(GL_LINES);
	glVertex3f(0, -500, player_pos[2]);
	glVertex3f(0, 500, player_pos[2]);
	glEnd();

	glDisable(GL_BLEND);

	//플레이어
	glColor3f(1, 1, 1);
	player.render();
}

void Scene00_BG::start_to_change_scene()
{
	is_started_to_change_scene = true;
	cylinder_alpha = 1.f;
	line_alpha = 1.f;
}


Scene03_BG::Scene03_BG()
{
	time_to_change_scene = 2.f;
	cylinder_alpha = 1.f;
	line_alpha = 1.f;
	elapsed_time_since_scene_change_started = 0.f;
}

Scene03_BG::Scene03_BG(const float & _time_to_change_scene)
{
}



Scene03_BG::~Scene03_BG()
{
}

void Scene03_BG::update(const float& fDeltaTime)
{

	cylinder_rotate_y -= cylinder_rotate_y_speed_per_sec * fDeltaTime;
	if (cylinder_rotate_y > 360)
		cylinder_rotate_y -= 360;

	cylinder_translate_y -= cylinder_translate_y_speed_per_sec * fDeltaTime;
	if (cylinder_translate_y > (cylinder_height / 16))
		cylinder_translate_y -= (cylinder_height / 16);

	if (is_started_to_change_scene == true)
	{
		elapsed_time_since_scene_change_started += fDeltaTime;
		cylinder_alpha = sin((1 - elapsed_time_since_scene_change_started)*M_PI / (time_to_change_scene));
		line_alpha = cos((elapsed_time_since_scene_change_started)*M_PI / (time_to_change_scene * 2));
	}
}
void Scene03_BG::render()
{
	//하드코딩 체고ㅗ오ㅗ오오오ㅗ오


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//실린더
	glPushMatrix();
	{
		glTranslatef(0, cylinder_height / 2 - cylinder_translate_y, -200);
		glRotatef(90, 1, 0, 0);  //왜 실린더는 기본적으로 눕혀서 그려지는가 
		glRotatef(cylinder_rotate_y, 0, 0, 1);

		glColor4f(0.1f, 0.1f, 0.6f, cylinder_alpha);
		glutWireCylinder(cylinder_width, cylinder_height, 12, 16);

	}
	glPopMatrix();


	//라인	
	glColor4f(1, 1, 1, line_alpha);

	glDisable(GL_BLEND);

}

void Scene03_BG::start_to_change_scene()
{
	is_started_to_change_scene = true;
	cylinder_alpha = 1.f;
	line_alpha = 1.f;
}
