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
	int tmp[3];
	pointNum = 0;
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

	speed = (88.f / 60.f) * 10.f;

	distance = 0;
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
	PointToPointVector = V3::normalize(V3::subtract(map[i + 1], map[i]));
	PointToPointVector.x *= distance;
	PointToPointVector.y *= distance;
	PointToPointVector.z *= distance;

	return V3::add(PointToPointVector,map[i]);
}
