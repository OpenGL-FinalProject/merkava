#include "stdafx.h"
#include "IngameUI.h"
#include "MapData.h"

IngameUI::IngameUI()
{
}


IngameUI::~IngameUI()
{
}

void IngameUI::init(MapData* md)
{
	Mapdata = md;
	gap = (4.8f * 5.f) / Mapdata->patternNum;
}

void IngameUI::samplerRectangle(Vector3 * Camera_worldspace)
{
	glColor3f(0.24f, 0.24f, 0.24f);
	glBegin(GL_QUADS);
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
}
void IngameUI::render(Vector3 UIPosition, Vector3 * Camera_worldspace, float dist)
{
	glPushMatrix();
	glTranslatef(UIPosition.x, UIPosition.y, UIPosition.z);
	
	glScalef(dist /50.f, dist / 50.f, dist / 50.f);
	//printf("%f , %f\n", dist, dist / 50.f);
	
	samplerRectangle(Camera_worldspace);

	glBegin(GL_QUAD_STRIP);
	Vectorworld = V3::times(Camera_worldspace[0], -2.4f * 5.f);
	Vectorup = V3::times(Camera_worldspace[1], -4.0f* 5.f);
	glVertex3f(Vectorworld.x + Vectorup.x, Vectorworld.y + Vectorup.y, Vectorworld.z + Vectorup.z);

	Vectorworld = V3::times(Camera_worldspace[0], -2.4f * 5.f);
	Vectorup = V3::times(Camera_worldspace[1], -3.9f* 5.f);
	glVertex3f(Vectorworld.x + Vectorup.x, Vectorworld.y + Vectorup.y, Vectorworld.z + Vectorup.z);
	for (int i = 0; i < Mapdata->patternNum; i++)
	{
		if (Mapdata->patternHit[i] == 2)
			glColor3f(1.f, 0.45f, 0.83f);
		else if (Mapdata->patternHit[i] == 1)
			glColor3f(0.2f, 0.9f, 0.1f);
		else
			glColor3f(0.24f, 0.24f, 0.24f);
		Vectorworld = V3::times(Camera_worldspace[0], -2.4f * 5.f + gap*(i+1));
		Vectorup = V3::times(Camera_worldspace[1], -4.0f* 5.f);
		glVertex3f(Vectorworld.x + Vectorup.x, Vectorworld.y + Vectorup.y, Vectorworld.z + Vectorup.z);

		Vectorworld = V3::times(Camera_worldspace[0], -2.4f * 5.f + gap*(i + 1));
		Vectorup = V3::times(Camera_worldspace[1], -3.9f* 5.f);
		glVertex3f(Vectorworld.x + Vectorup.x, Vectorworld.y + Vectorup.y, Vectorworld.z + Vectorup.z);
	}
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
