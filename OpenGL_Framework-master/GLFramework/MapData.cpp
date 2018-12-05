#include "stdafx.h"
#include "MapData.h"

MapData::MapData()
{

}

MapData::~MapData()
{

}

void MapData::init(int stageNum)
{
	float tmp[25];
	savedCameraOffset[0] = 50;
	savedCameraOffset[1] = 50;
	savedCameraOffset[2] = 50;
	pointNum = 0;
	distance = 0;
	patternNum = 0;
	patternLineNum = 0.f;
	speed = (88.f / 60.f) * 10.f;

	map_file.open("Pattern\\map.txt");
	while (!map_file.eof())
	{
		map_file >> tmp[0] >> tmp[1] >> tmp[2] >> tmp[3];
		map[pointNum].x = tmp[0];
		map[pointNum].y = tmp[1];
		map[pointNum].z = tmp[2];
		if (tmp[3] == 1)
		{
			map_file >> savedCameraOffset[0] >> savedCameraOffset[1] >> savedCameraOffset[2];
			camera[pointNum].x = tmp[0] + savedCameraOffset[0];
			camera[pointNum].y = tmp[1] + savedCameraOffset[1];
			camera[pointNum].z = tmp[2] + savedCameraOffset[2];
		}
		else
		{
			camera[pointNum].x = tmp[0] + savedCameraOffset[0];
			camera[pointNum].y = tmp[1] + savedCameraOffset[1];
			camera[pointNum].z = tmp[2] + savedCameraOffset[2];
		}
		pointNum++;
	}
	map_file.close();

	map_file.open("Pattern\\pattern.txt");
	while (!map_file.eof())
	{
		float tmptime = (60.f / 88.f) * 4.f * patternLineNum + 0.56f;
		int count = 0;
		map_file >> tmp[0];

		if (tmp[0] == 8.f)
		{
			map_file >> tmp[0] >> tmp[1] >> tmp[2] >> tmp[3] >> tmp[4] >> tmp[5] >> tmp[6] >> tmp[7];
			for (float i = 0.f; i < 8.f; i += 1.f)
			{
				if (tmp[int(i)] >= 1)
				{
					pattern[patternNum + count] = getPlayerPosition(tmptime + (60.f / 88.f)*i / 2.f);
					patternTime[patternNum + count] = tmptime + (60.f / 88.f)*i / 2.f;
					count++;
				}
			}
		}
		else if (tmp[0] == 12.f)
		{
			map_file >> tmp[0] >> tmp[1] >> tmp[2] >> tmp[3] >> tmp[4] >> tmp[5] >> tmp[6] >> tmp[7] >> tmp[8] >> tmp[9] >> tmp[10] >> tmp[11];
			for (float i = 0.f; i < 12.f; i += 1.f)
			{
				if (tmp[int(i)] >= 1)
				{
					pattern[patternNum + count] = getPlayerPosition(tmptime + (60.f / 88.f)*i / 3.f);
					patternTime[patternNum + count] = tmptime + (60.f / 88.f)*i / 3.f;
					count++;
				}
			}
		}
		else if (tmp[0] == 16.f)
		{
			map_file >> tmp[0] >> tmp[1] >> tmp[2] >> tmp[3] >> tmp[4] >> tmp[5] >> tmp[6] >> tmp[7] >> tmp[8] >> tmp[9] >> tmp[10] >> tmp[11] >> tmp[12] >> tmp[13] >> tmp[14] >> tmp[15];
			for (float i = 0.f; i < 16.f; i += 1.f)
			{
				if (tmp[int(i)] >= 1)
				{
					pattern[patternNum + count] = getPlayerPosition(tmptime + (60.f / 88.f)*i / 4.f);
					patternTime[patternNum + count] = tmptime + (60.f / 88.f)*i / 4.f;
					count++;
				}
			}
		}
		else if (tmp[0] == 24.f)
		{
			map_file >> tmp[0] >> tmp[1] >> tmp[2] >> tmp[3] >> tmp[4] >> tmp[5] >> tmp[6] >> tmp[7] >> tmp[8] >> tmp[9] >> tmp[10] >> tmp[11] >> tmp[12] >> tmp[13] >> tmp[14] >> tmp[15] >> tmp[16] >> tmp[17] >> tmp[18] >> tmp[19] >> tmp[20] >> tmp[21] >> tmp[22] >> tmp[23];
			for (float i = 0.f; i < 24.f; i += 1.f)
			{
				if (tmp[int(i)] >= 1)
				{
					pattern[patternNum + count] = getPlayerPosition(tmptime + (60.f / 88.f)*i / 6.f);
					patternTime[patternNum + count] = tmptime + (60.f / 88.f)*i / 6.f;
					count++;
				}
			}

		}
		else
		{
			assert(false);
		}
		patternNum += count;
		patternLineNum += 1.f;
	}
	map_file.close();

}

void MapData::render(bool coaster, float time, Vector3* Camera_worldspace, Vector3* axis)
{
	glColor3f(1.f, 1.f, 1.f);
	glBegin(GL_LINE_STRIP);
	{
		for (int i = 0; i < pointNum; i++)
		{
			glVertex3f(map[i].x, map[i].y, map[i].z);
		}
	}
	glEnd();

	for (int i = 0; i < patternNum; i++)
	{
		if (patternHit[i] == 2)
			glColor3f(1.f, 0.45f, 0.83f);
		else if (patternHit[i] == 1)
			glColor3f(0.2f, 0.9f, 0.1f);
		else
			glColor3f(0.f, 0.2f, 0.9f);

		glPushMatrix();
		{
			glTranslatef(pattern[i].x, pattern[i].y, pattern[i].z);
			if (coaster)
				glutWireCube(0.5f);
			else
				glutSolidSphere(0.5f, 6, 6);
			if (patternTime[i] - time < 0.7f && patternTime[i] - time > 0.f)
			{
				if (coaster)
					drawBillboardCircle((patternTime[i] - time) + 0.2f, Camera_worldspace);
				else
					drawBillboardCircle((patternTime[i] - time) * 3.2f + 0.8f, Camera_worldspace);
			}
			//drawArrowNote(time, getCurrentLineVector(patternTime[i]), axis[2], 1); //dir = 1 or -1 
		}glPopMatrix();
	}
	glColor3f(1.f, 1.f, 1.f);
}

void MapData::drawBillboardCircle(float size, Vector3* Camera_worldspace)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 31; i++)
	{
		Vector3 Vectorworld = V3::times(Camera_worldspace[0], cos(i*3.14f*6.f / 90.f) * size);
		Vector3 Vectorup = V3::times(Camera_worldspace[1], sin(i*3.14f*6.f / 90.f) * size);

		glVertex3f(Vectorworld.x + Vectorup.x, Vectorworld.y + Vectorup.y, Vectorworld.z + Vectorup.z);
	}
	glEnd();
}
void MapData::drawArrowNote(float time, Vector3 getCurrentLineVec, Vector3 Vec_look, int dir)
{
	float temp_time = ((time * 2) - (int)(time) * 2) / 4;

	Vector3 Vec_cross_line_look = V3::normalize(V3::cross(getCurrentLineVec, Vec_look));
	Vec_cross_line_look = V3::times(Vec_cross_line_look, dir);

	Vector3 Vec_cross_line_look_look = V3::normalize(V3::cross(Vec_look, Vec_cross_line_look));

	float size = 0.4f;
	float width_height_offset = 1.2; //몰라 변수 이름 짓는게 제일 어려워
	glPushMatrix();
	{

		glTranslatef(Vec_cross_line_look.x*temp_time, Vec_cross_line_look.y*temp_time, Vec_cross_line_look.z*temp_time);

		glColor3f(1.f, 1.f, 1.f);
		glPushMatrix();
		{
			glBegin(GL_LINE_LOOP);
			glVertex3f(Vec_cross_line_look.x + getCurrentLineVec.x*-size, Vec_cross_line_look.y + getCurrentLineVec.y*-size, Vec_cross_line_look.z + getCurrentLineVec.z*-size);
			glVertex3f(Vec_cross_line_look.x*width_height_offset + getCurrentLineVec.x*-size, Vec_cross_line_look.y*width_height_offset + getCurrentLineVec.y*-size, Vec_cross_line_look.z*width_height_offset + getCurrentLineVec.z*-size);
			glVertex3f(Vec_cross_line_look.x*width_height_offset + getCurrentLineVec.x*size, Vec_cross_line_look.y*width_height_offset + getCurrentLineVec.y*size, Vec_cross_line_look.z*width_height_offset + getCurrentLineVec.z*size);
			glVertex3f(Vec_cross_line_look.x + getCurrentLineVec.x*size, Vec_cross_line_look.y + getCurrentLineVec.y*size, Vec_cross_line_look.z + getCurrentLineVec.z*size);
			glEnd();

			glTranslatef(Vec_cross_line_look.x*0.5f, Vec_cross_line_look.y*0.5f, Vec_cross_line_look.z*0.5f);

			glBegin(GL_LINE_LOOP);
			glVertex3f(Vec_cross_line_look.x + getCurrentLineVec.x*-size, Vec_cross_line_look.y + getCurrentLineVec.y*-size, Vec_cross_line_look.z + getCurrentLineVec.z*-size);
			glVertex3f(Vec_cross_line_look.x*width_height_offset + getCurrentLineVec.x*-size, Vec_cross_line_look.y*width_height_offset + getCurrentLineVec.y*-size, Vec_cross_line_look.z*width_height_offset + getCurrentLineVec.z*-size);
			glVertex3f(Vec_cross_line_look.x*width_height_offset + getCurrentLineVec.x*size, Vec_cross_line_look.y*width_height_offset + getCurrentLineVec.y*size, Vec_cross_line_look.z*width_height_offset + getCurrentLineVec.z*size);
			glVertex3f(Vec_cross_line_look.x + getCurrentLineVec.x*size, Vec_cross_line_look.y + getCurrentLineVec.y*size, Vec_cross_line_look.z + getCurrentLineVec.z*size);
			glEnd();

			glTranslatef(Vec_cross_line_look.x*0.5f, Vec_cross_line_look.y*0.5f, Vec_cross_line_look.z*0.5f);

			glBegin(GL_LINE_LOOP);
			glVertex3f(Vec_cross_line_look.x + getCurrentLineVec.x*-size, Vec_cross_line_look.y + getCurrentLineVec.y*-size, Vec_cross_line_look.z + getCurrentLineVec.z*-size);
			glVertex3f(Vec_cross_line_look.x*width_height_offset + getCurrentLineVec.x*-size, Vec_cross_line_look.y*width_height_offset + getCurrentLineVec.y*-size, Vec_cross_line_look.z*width_height_offset + getCurrentLineVec.z*-size);
			glVertex3f(Vec_cross_line_look.x*width_height_offset + getCurrentLineVec.x*size, Vec_cross_line_look.y*width_height_offset + getCurrentLineVec.y*size, Vec_cross_line_look.z*width_height_offset + getCurrentLineVec.z*size);
			glVertex3f(Vec_cross_line_look.x + getCurrentLineVec.x*size, Vec_cross_line_look.y + getCurrentLineVec.y*size, Vec_cross_line_look.z + getCurrentLineVec.z*size);
			glEnd();
			glTranslatef(Vec_cross_line_look.x*0.5f, Vec_cross_line_look.y*0.5f, Vec_cross_line_look.z*0.5f);

			glBegin(GL_LINE_LOOP);
			glVertex3f(Vec_cross_line_look.x + getCurrentLineVec.x*-size, Vec_cross_line_look.y + getCurrentLineVec.y*-size, Vec_cross_line_look.z + getCurrentLineVec.z*-size);
			glVertex3f(Vec_cross_line_look.x*width_height_offset + getCurrentLineVec.x*-size, Vec_cross_line_look.y*width_height_offset + getCurrentLineVec.y*-size, Vec_cross_line_look.z*width_height_offset + getCurrentLineVec.z*-size);
			glVertex3f(Vec_cross_line_look.x*width_height_offset + getCurrentLineVec.x*size, Vec_cross_line_look.y*width_height_offset + getCurrentLineVec.y*size, Vec_cross_line_look.z*width_height_offset + getCurrentLineVec.z*size);
			glVertex3f(Vec_cross_line_look.x + getCurrentLineVec.x*size, Vec_cross_line_look.y + getCurrentLineVec.y*size, Vec_cross_line_look.z + getCurrentLineVec.z*size);
			glEnd();
			glTranslatef(Vec_cross_line_look.x*0.5f, Vec_cross_line_look.y*0.5f, Vec_cross_line_look.z*0.5f);

			glBegin(GL_LINE_LOOP);
			glVertex3f(Vec_cross_line_look.x + getCurrentLineVec.x*-size, Vec_cross_line_look.y + getCurrentLineVec.y*-size, Vec_cross_line_look.z + getCurrentLineVec.z*-size);
			glVertex3f(Vec_cross_line_look.x*width_height_offset + getCurrentLineVec.x*-size, Vec_cross_line_look.y*width_height_offset + getCurrentLineVec.y*-size, Vec_cross_line_look.z*width_height_offset + getCurrentLineVec.z*-size);
			glVertex3f(Vec_cross_line_look.x*width_height_offset + getCurrentLineVec.x*size, Vec_cross_line_look.y*width_height_offset + getCurrentLineVec.y*size, Vec_cross_line_look.z*width_height_offset + getCurrentLineVec.z*size);
			glVertex3f(Vec_cross_line_look.x + getCurrentLineVec.x*size, Vec_cross_line_look.y + getCurrentLineVec.y*size, Vec_cross_line_look.z + getCurrentLineVec.z*size);
			glEnd();

			glTranslatef(Vec_cross_line_look.x*0.5f, Vec_cross_line_look.y*0.5f, Vec_cross_line_look.z*0.5f);
			//glTranslatef(Vec_cross_line_look.x*-temp_time, Vec_cross_line_look.y*-temp_time, Vec_cross_line_look.z*-temp_time);


			glBegin(GL_LINE_LOOP);
			glVertex3f(Vec_cross_line_look.x + getCurrentLineVec.x*-size * 2, Vec_cross_line_look.y + getCurrentLineVec.y*-size * 2, Vec_cross_line_look.z + getCurrentLineVec.z*-size * 2);
			glVertex3f(Vec_cross_line_look.x*width_height_offset*1.5, Vec_cross_line_look.y*width_height_offset*1.5, Vec_cross_line_look.z*width_height_offset*1.5);
			glVertex3f(Vec_cross_line_look.x + getCurrentLineVec.x*size * 2, Vec_cross_line_look.y + getCurrentLineVec.y*size * 2, Vec_cross_line_look.z + getCurrentLineVec.z*size * 2); glEnd();


		}
		glPopMatrix();

	}
	glPopMatrix();
}

Vector3 MapData::getCameraPosition(float time)
{
	distance = time*speed;
	int i = 0;
	while (true)
	{
		if (i + 1 < pointNum)
		{
			if (distance < V3::dist(camera[i], camera[i + 1]))
			{
				break;
			}
			else
			{
				distance -= V3::dist(camera[i], camera[i + 1]);
				i++;
			}
		}
		else
		{
			return Vector3(0.f, 0.f, 0.f);
		}
	}
	PointToPointVector = V3::times(V3::normalize(V3::subtract(camera[i + 1], camera[i])), distance);
	return V3::add(PointToPointVector, camera[i]);
}

Vector3 MapData::getPlayerPosition(float time)
{
	distance = time*speed;

	int i = 0;
	while (true)
	{
		if (i + 1 < pointNum)
		{
			if (distance < V3::dist(map[i], map[i + 1]))
			{
				break;
			}
			else
			{
				distance -= V3::dist(map[i], map[i + 1]);
				i++;
			}
		}
		else
		{
			return Vector3(0.f, 0.f, 0.f);
		}
	}
	PointToPointVector = V3::times(V3::normalize(V3::subtract(map[i + 1], map[i])), distance);
	return V3::add(PointToPointVector, map[i]);
}

Vector3 MapData::getCurrentLineVector(float time)
{
	distance = time * speed;

	int i = 0;
	while (true)
	{
		if (i + 1 < pointNum)
		{
			if (distance < V3::dist(map[i], map[i + 1]))
			{
				break;
			}
			else
			{
				distance -= V3::dist(map[i], map[i + 1]);
				i++;
			}
		}
		else
		{
			return Vector3(0.f, 0.f, 0.f);
		}
	}
	return V3::normalize(V3::subtract(map[i + 1], map[i]));
}

MapData::clap_check MapData::clap(Player& P)
{
	//가장 가까운 노드 - 못쳤을 때 못친 노트 반환용 
	Vector3 temp_closest_pattern;
	float temp_closest_pattern_dist = -1;

	for (int i = 0; i < patternNum; i++)
	{

		if (patternHit[i] == 0)
		{
			if (V3::dist(pattern[i], P.Position) < 1.f)
			{
				perfect_num++;
				patternHit[i] = 2;
				return clap_check{ true, pattern[i], patternHit[i] };
			}
			else if (V3::dist(pattern[i], P.Position) < 1.5f)
			{
				good_num++;
				patternHit[i] = 1;
				return clap_check{ true, pattern[i], patternHit[i] };
			}
		}
		if (temp_closest_pattern_dist < 0)
		{
			temp_closest_pattern = pattern[i];
			temp_closest_pattern_dist = V3::dist(pattern[i], P.Position);
		}

		if (V3::dist(pattern[i], P.Position) < temp_closest_pattern_dist)
		{
			temp_closest_pattern = pattern[i];
			temp_closest_pattern_dist = V3::dist(pattern[i], P.Position);
		}
	}

	return clap_check{ false, temp_closest_pattern, 0 };
}


