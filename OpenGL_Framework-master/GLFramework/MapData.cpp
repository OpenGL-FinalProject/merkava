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

void MapData::render(bool coaster)
{
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
		if (patternHit[i])
			glColor3f(1.f, 0.45f, 0.83f);
		else
			glColor3f(0.f, 0.2f, 0.9f);
		glPushMatrix();
		{
			glTranslatef(pattern[i].x, pattern[i].y, pattern[i].z);
			if (coaster)
				glutWireCube(0.5f);
			else
				glutSolidSphere(0.5f, 6, 6);
		}
		glPopMatrix();
	}
	glColor3f(1.f, 1.f, 1.f);
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
				//printf("%d to %d, %.2f %.2f %.2f => %.3f\n", i, i + 1, map[i+1].x, map[i+1].y, map[i+1].z, V3::dist(map[i], map[i+1]));
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
	//printf("p : %f %f %f\n", V3::add(PointToPointVector, camera[i]).x, V3::add(PointToPointVector, camera[i]).y, V3::add(PointToPointVector, camera[i]).z);
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
				//printf("%d to %d, %.2f %.2f %.2f => %.3f\n", i, i + 1, map[i+1].x, map[i+1].y, map[i+1].z, V3::dist(map[i], map[i+1]));
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
	PointToPointVector = V3::times(V3::normalize(V3::subtract(map[i + 1], map[i])),distance);
	//printf("p : %f %f %f\n", V3::add(PointToPointVector, map[i]).x, V3::add(PointToPointVector, map[i]).y, V3::add(PointToPointVector, map[i]).z);
	return V3::add(PointToPointVector,map[i]);
}

Vector3 MapData::getcoasterPlayerPosition(float time)
{
	distance = time*speed;

	int i = 0;
	while (true)
	{
		if (i + 1 < pointNum)
		{
			if (distance < V3::dist(map[i], map[i + 1]))
			{
				//printf("%d to %d, %.2f %.2f %.2f => %.3f\n", i, i + 1, map[i+1].x, map[i+1].y, map[i+1].z, V3::dist(map[i], map[i+1]));
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
	//printf("p : %f %f %f\n", V3::add(PointToPointVector, map[i]).x, V3::add(PointToPointVector, map[i]).y, V3::add(PointToPointVector, map[i]).z);
	return V3::add(PointToPointVector, map[i]);
}

bool MapData::clap(Player& P)
{
	for (int i = 0; i < patternNum; i++)
	{
		if (V3::dist(pattern[i], P.Position) < 1.f)
		{
			patternHit[i] = true;
			return true;
		}
	}

	return false;
}