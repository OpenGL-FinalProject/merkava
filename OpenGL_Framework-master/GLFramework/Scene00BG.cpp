#include "Scene00BG.h"
#include "stdafx.h"

Scene00BG::Scene00BG()
{
}

Scene00BG::~Scene00BG()
{
}

void Scene00BG::update(const float& fDeltaTime)
{
	cylinder_rotate_y +=  cylinder_rotate_y_speed_per_sec * fDeltaTime;
	if (cylinder_rotate_y > 360)
		cylinder_rotate_y -= 360;

	cylinder_translate_y += cylinder_translate_y_speed_per_sec * fDeltaTime;
	if (cylinder_translate_y > (cylinder_height / 16))
		cylinder_translate_y -= (cylinder_height / 16);
}
void Scene00BG::render()
{
	//�ϵ��ڵ� ü��ǿ��ǿ������ǿ�
	glPushMatrix();
	{
		glTranslatef(0, cylinder_height / 2 + cylinder_translate_y, -200);
		glRotatef(90, 1, 0, 0);  //�� �Ǹ����� �⺻������ ������ �׷����°� 
		glRotatef(cylinder_rotate_y, 0, 0, 1);
		glColor3f(1, 1, 0);
		glutWireCylinder(cylinder_width, cylinder_height, 12, 16);
	}
	glPopMatrix();
}

