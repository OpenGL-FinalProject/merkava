#include "stdafx.h"
#include "IngameUI.h"
#include "MapData.h"

IngameUI::IngameUI()
{
}


IngameUI::~IngameUI()
{
}

void IngameUI::init()
{

}

void IngameUI::render(Vector3 UIPosition, Vector3 * Camera_worldspace, float dist)
{
	glPushMatrix();
	glTranslatef(UIPosition.x, UIPosition.y, UIPosition.z);
	
	glScalef(dist /50.f, dist / 50.f, dist / 50.f);
	//printf("%f , %f\n", dist, dist / 50.f);
	glColor3f(1.0f, 1.0f, 1.0f);
	
	glBegin(GL_LINE_LOOP);
	Vectorworld = V3::times(Camera_worldspace[0], 2.4f * 5.f);
	Vectorup = V3::times(Camera_worldspace[1], -3.9f* 5.f);
	glVertex3f(Vectorworld.x + Vectorup.x, Vectorworld.y + Vectorup.y, Vectorworld.z + Vectorup.z);

	Vectorworld = V3::times(Camera_worldspace[0], -2.4f* 5.f);
	glVertex3f(Vectorworld.x + Vectorup.x, Vectorworld.y + Vectorup.y, Vectorworld.z + Vectorup.z);

	Vectorup = V3::times(Camera_worldspace[1], -4.0f* 5.f);
	glVertex3f(Vectorworld.x + Vectorup.x, Vectorworld.y + Vectorup.y, Vectorworld.z + Vectorup.z);

	Vectorworld = V3::times(Camera_worldspace[0], 2.4f* 5.f);
	glVertex3f(Vectorworld.x + Vectorup.x, Vectorworld.y + Vectorup.y, Vectorworld.z + Vectorup.z);
	glEnd();

	/*glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 31; i++)
	{
		Vectorworld = V3::times(Camera_worldspace[0], cos(i*3.14f*6.f / 90.f)  * 10.f);
		Vectorup = V3::times(Camera_worldspace[1], sin(i*3.14f*6.f / 90.f) * 10.f);

		glVertex3f(Vectorworld.x + Vectorup.x, Vectorworld.y + Vectorup.y, Vectorworld.z + Vectorup.z);
	}
	glEnd();*/
	glPopMatrix();
}

void IngameUI::update()
{
}
