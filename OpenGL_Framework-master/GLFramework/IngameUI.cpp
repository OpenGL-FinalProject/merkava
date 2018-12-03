#include "stdafx.h"
#include "IngameUI.h"

IngameUI::IngameUI()
{
}


IngameUI::~IngameUI()
{
}

void IngameUI::init()
{

}

void IngameUI::render(float time, Vector3 * Camera_worldspace)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 31; i++)
	{
		Vector3 Vectorworld = V3::times(Camera_worldspace[0], 0.5f * DEF_WIN_HEIGHT);
		Vector3 Vectorup = V3::times(Camera_worldspace[1], 0.5 * DEF_WIN_WIDTH);

		glVertex3f(Vectorworld.x + Vectorup.x, Vectorworld.y + Vectorup.y, Vectorworld.z + Vectorup.z);
	}
	glEnd();
}

void IngameUI::update()
{
}
