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

	gridColor[0] = 0.32f;
	gridColor[1] = 0.32f;
	gridColor[2] = 0.32f;

	flashColor[0] = 0.f;
	flashColor[1] = 0.f;
	flashColor[2] = 0.f;
	flashColor[3] = 0.f;

	printScore = 0;
	score = 0;

	isfadingout = false;

	texture_object[0] = LoadTexture("sky\\Left.bmp", 1024, 1024);
	texture_object[1] = LoadTexture("sky\\Right.bmp", 1024, 1024);
	texture_object[2] = LoadTexture("sky\\Up.bmp", 1024, 1024);
	texture_object[3] = LoadTexture("sky\\Down.bmp", 1024, 1024);
	texture_object[4] = LoadTexture("sky\\Front.bmp", 1024, 1024);
	texture_object[5] = LoadTexture("sky\\Back.bmp", 1024, 1024);
}

GLuint IngameUI::LoadTexture(const char * filename, int width_1, int height_1)
{
	GLuint texture;
	int width, height;
	unsigned char * data;
	FILE * file;

	// 파일 열기
	fopen_s(&file, filename, "rb");

	if (file == NULL) return 0;
	width = width_1;
	height = height_1;
	data = (unsigned char *)malloc(width * height * 3 + 54);
	fread(data, width * height * 3 + 54, 1, file);
	fclose(file);

	// 이후 PDF동일
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Modulate로 함
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data+54);
	free(data);

	return texture;
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

void IngameUI::setGridColor(float x, float y, float z)
{
	gridColor[0] = x;
	gridColor[1] = y;
	gridColor[2] = z;
}

void IngameUI::setFlashColor(float x, float y, float z)
{
	flashColor[0] = x;
	flashColor[1] = y;
	flashColor[2] = z;
	flashColor[3] = 1.0f;
}
void IngameUI::setFlashColor(float x, float y, float z, float a)
{
	flashColor[0] = x;
	flashColor[1] = y;
	flashColor[2] = z;
	flashColor[3] = a;
}

void IngameUI::skybox(float time)
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glColor3f(1.f, 1.f, 1.f);
	if (time > 79.62f)
	{
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, texture_object[0]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1024.f, 1024.f, 1024.f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1024.f, -1024.f, 1024.f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1024.f, -1024.f, -1024.f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1024.f, 1024.f, -1024.f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture_object[1]);
		glBegin(GL_QUADS);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1024.f, 1024.f, 1024.f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1024.f, -1024.f, 1024.f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(1024.f, -1024.f, -1024.f);
		
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(1024.f, 1024.f, -1024.f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture_object[5]);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1024.f, 1024.f, 1024.f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1024.f, -1024.f, 1024.f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(1024.f, -1024.f, 1024.f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(1024.f, 1024.f, 1024.f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture_object[4]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1024.f, -1024.f, -1024.f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1024.f, 1024.f, -1024.f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1024.f, 1024.f, -1024.f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1024.f, -1024.f, -1024.f);

		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture_object[3]);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1024.f, -1024.f, 1024.f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1024.f, -1024.f, -1024.f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1024.f, -1024.f, -1024.f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1024.f, -1024.f, 1024.f);

		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture_object[2]);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1024.f, 1024.f, 1024.f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1024.f, 1024.f, -1024.f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1024.f, 1024.f, -1024.f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1024.f, 1024.f, 1024.f);

		glEnd();

		glDisable(GL_TEXTURE_2D);
	}
}

void IngameUI::grid()
{
	glColor3f(gridColor[0], gridColor[1], gridColor[2]);
	glBegin(GL_LINES);
	{
		for (int i = 0; i <= 20; i++)
		{
			//좌
			glVertex3f(-1000.f, -1000.f + 100.f*i, -1000.f);
			glVertex3f(-1000.f, -1000.f + 100.f*i, 1000.f);

			glVertex3f(-1000.f, -1000.f, -1000.f + i*100.f);
			glVertex3f(-1000.f, 1000.f, -1000.f + i*100.f);
			//우
			glVertex3f(1000.f, -1000.f + 100.f*i, -1000.f);
			glVertex3f(1000.f, -1000.f + 100.f*i, 1000.f);

			glVertex3f(1000.f, -1000.f, -1000.f + i*100.f);
			glVertex3f(1000.f, 1000.f, -1000.f + i*100.f);

			//하
			glVertex3f(-1000.f, -1000.f, -1000.f + 100.f*i);
			glVertex3f(1000.f, -1000.f, -1000.f + 100.f*i);

			glVertex3f(-1000.f + 100.f*i, -1000.f, -1000.f);
			glVertex3f(-1000.f + 100.f*i, -1000.f, 1000.f);
			//상
			glVertex3f(-1000.f, 1000.f, -1000.f + 100.f*i);
			glVertex3f(1000.f, 1000.f, -1000.f + 100.f*i);

			glVertex3f(-1000.f + 100.f*i, 1000.f, -1000.f);
			glVertex3f(-1000.f + 100.f*i, 1000.f, 1000.f);

			//전
			glVertex3f(-1000.f, -1000.f + 100.f*i, 1000.f);
			glVertex3f(1000.f, -1000.f + 100.f*i, 1000.f);

			glVertex3f(-1000.f + i*100.f, -1000.f, 1000.f);
			glVertex3f(-1000.f + i*100.f, 1000.f, 1000.f);
			//후
			glVertex3f(-1000.f, -1000.f + 100.f*i, -1000.f);
			glVertex3f(1000.f, -1000.f + 100.f*i, -1000.f);

			glVertex3f(-1000.f + i*100.f, -1000.f, -1000.f);
			glVertex3f(-1000.f + i*100.f, 1000.f, -1000.f);
		}
	}
	glEnd();
}

void IngameUI::flash(Vector3 CameraPosition)
{
	glPushMatrix();
	{
		glDisable(GL_CULL_FACE);
		glTranslatef(CameraPosition.x, CameraPosition.y, CameraPosition.z);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(flashColor[0], flashColor[1], flashColor[2],flashColor[3]);
		glutSolidCube(1.f);
		glDisable(GL_BLEND);
		glEnable(GL_CULL_FACE);
	}
	glPopMatrix();
}
void IngameUI::render(Vector3 UIPosition, Vector3 * Camera_worldspace, float dist)
{
	glPushMatrix();
	{
		glTranslatef(UIPosition.x, UIPosition.y, UIPosition.z);
		glScalef(dist / 50.f, dist / 50.f, dist / 50.f);

		
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
			Vectorworld = V3::times(Camera_worldspace[0], -2.4f * 5.f + gap*(i + 1));
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
			std::string str = std::to_string(printScore);
			Vectorworld = V3::times(Camera_worldspace[0], (2.3f - (str.length()/20.f)) * 5.f);
			Vectorup = V3::times(Camera_worldspace[1], -3.75f * 5.f);

			glColor3f(1.f, 1.f, 1.f);
			float sz = static_cast<float>(str.size());
			glRasterPos3f(Vectorworld.x + Vectorup.x, Vectorworld.y + Vectorup.y, Vectorworld.z + Vectorup.z);
			for (size_t s = 0; s < str.size(); s++)
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[s]);

		}
		glPopMatrix();

	}
	glPopMatrix();
}

void IngameUI::scoreUp(int critical)
{
	if (critical-1)
	{
		score += 200;
	}
	else
	{
		score += 100;
	}
}

void IngameUI::update(float fDeltaTime)
{
	for (int i = 0; i < 3; i++)
	{
		if (gridColor[i] == 0.32f)
			continue;
		if (gridColor[i] > 0.32f)
			gridColor[i] -= 0.005f;
		else if (gridColor[i] < 0.32f)
			gridColor[i] += 0.005f;
	}

	if (score > printScore)
		printScore += 13;
	else
		score = printScore;

	if (!isfadingout)
	{
		if (flashColor[3] > 0.f)
			flashColor[3] -= 0.03f;
	}

}


bool IngameUI::fadeout(float fDeltaTime)
{
	isfadingout = true;
	flashColor[3] += fDeltaTime * 0.5f;

	if (flashColor[3] >= 1)
		return 1;
	else
		return 0;
}
