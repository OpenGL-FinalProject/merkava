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
	float tmp[24];
	pointNum = 0;
	distance = 0;
	patternNum = 0;
	patternLineNum = 0.f;
	speed = (88.f / 60.f) * 10.f;

	map_file.open("Pattern\\map.txt");
	while (!map_file.eof())
	{
		map_file >> tmp[0] >> tmp[1] >> tmp[2];
		map[pointNum].x = tmp[0];
		map[pointNum].y = tmp[1];
		map[pointNum].z = tmp[2];
		pointNum++;
	}
	map_file.close();

	map_file.open("Pattern\\pattern.txt");
	while (!map_file.eof())
	{
		float tmptime = (60.f / 88.f) * 4.f * patternLineNum + 0.65f;
		int count = 0;
		map_file >> tmp[0];

		if (tmp[0] == 8.f)
		{
			map_file >> tmp[0] >> tmp[1] >> tmp[2] >> tmp[3] >> tmp[4] >> tmp[5] >> tmp[6] >> tmp[7];
			for (float i = 0.f; i < 8.f; i += 1.f)
			{
				if (tmp[int(i)] == 1)
				{
					pattern[patternNum + count] = getPlayerPosition(tmptime + (60.f / 88.f)*i/2.f);
					count++;
				}
			}
		}
		else if (tmp[0] == 12.f)
		{
			map_file >> tmp[0] >> tmp[1] >> tmp[2] >> tmp[3] >> tmp[4] >> tmp[5] >> tmp[6] >> tmp[7] >> tmp[8] >> tmp[9] >> tmp[10] >> tmp[11];
			for (float i = 0.f; i < 12.f; i += 1.f)
			{
				if (tmp[int(i)] == 1)
				{
					pattern[patternNum + count] = getPlayerPosition(tmptime + (60.f / 88.f)*i/3.f);
					count++;
				}
			}
		}
		else if (tmp[0] == 16.f)
		{
			map_file >> tmp[0] >> tmp[1] >> tmp[2] >> tmp[3] >> tmp[4] >> tmp[5] >> tmp[6] >> tmp[7] >> tmp[8] >> tmp[9] >> tmp[10] >> tmp[11] >> tmp[12] >> tmp[13] >> tmp[14] >> tmp[15];
			for (float i = 0.f; i < 16.f; i += 1.f)
			{
				if (tmp[int(i)] == 1)
				{
					pattern[patternNum + count] = getPlayerPosition(tmptime + (60.f / 88.f)*i/4.f);
					count++;
				}
			}
		}
		else if (tmp[0] == 24.f)
		{
			map_file >> tmp[0] >> tmp[1] >> tmp[2] >> tmp[3] >> tmp[4] >> tmp[5] >> tmp[6] >> tmp[7] >> tmp[8] >> tmp[9] >> tmp[10] >> tmp[11] >> tmp[12] >> tmp[13] >> tmp[14] >> tmp[15] >> tmp[16] >> tmp[17] >> tmp[18] >> tmp[19] >> tmp[20] >> tmp[21] >> tmp[22] >> tmp[23];
			for (float i = 0.f; i < 24.f; i += 1.f)
			{
				if (tmp[int(i)] == 1)
				{
					pattern[patternNum + count] = getPlayerPosition(tmptime + (60.f / 88.f)*i / 6.f);
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

void MapData::render()
{
	glBegin(GL_LINE_STRIP);
	{
		for (int i = 0; i < pointNum; i++)
		{
			glVertex3f(map[i].x, map[i].y, map[i].z);
		}
	}
	glEnd();

	glColor3f(0.f, 0.2f, 0.9f);
	for (int i = 0; i < patternNum; i++)
	{
		glPushMatrix();
		{
			glTranslatef(pattern[i].x, pattern[i].y, pattern[i].z);
			printf("%f %f %f\n", pattern[i].x, pattern[i].y, pattern[i].z);
			glutSolidSphere(0.5f, 6, 6);
		}
		glPopMatrix();
	}
	glColor3f(1.f, 1.f, 1.f);
}

Vector3 MapData::getCameraPosition(float time)
{

	return Vector3();
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
				break;
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
	PointToPointVector = V3::times(V3::normalize(V3::subtract(map[i + 1], map[i])),distance);

	return V3::add(PointToPointVector,map[i]);
}
