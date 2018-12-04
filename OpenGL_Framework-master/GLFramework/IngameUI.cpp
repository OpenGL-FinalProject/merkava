#include "stdafx.h"
#include "IngameUI.h"
#include "MapData.h"
#include "GLScene.h"

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

	Vectorworld = V3::times(Camera_worldspace[0], -1.5f * 5.f);
	Vectorup = V3::times(Camera_worldspace[1], -1.5f * 5.f);

	
	//텍스트 출력
	glPushMatrix();
	{
		//문자열 받아오고  - to_do - 점수 계산
		std::string str = "aaaaaa";
		Vectorworld = V3::times(Camera_worldspace[0], -1.5f * 5.f);
		Vectorup = V3::times(Camera_worldspace[1], -1.5f * 5.f);

		glColor3f(1.f, 1.f, 1.f);
		float sz = static_cast<float>(str.size());
		glRasterPos3f(Vectorworld.x + Vectorup.x, Vectorworld.y + Vectorup.y, Vectorworld.z + Vectorup.z);
		for (size_t s = 0; s < str.size(); s++)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[s]);

	}
	glPopMatrix();


	glPopMatrix();
}

void IngameUI::update()
{
}
