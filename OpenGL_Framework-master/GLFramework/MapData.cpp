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
	speed = (88.f / 60.f) * 10.f;
	distance = 0;
	pointNum = 4;				//�����鼭 �ٲ���ϴ� �κ�
	
	map[0].x = 0;
	map[0].y = 0;
	map[0].z = 0;

	map[1].x = 100;
	map[1].y = 0;
	map[1].z = 0;

	map[2].x = 100;
	map[2].y = 100;
	map[2].z = 100;

	map[3].x = 0;
	map[3].y = 0;
	map[3].z = 100;
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
	Vector3 PointToPointVector;
	PointToPointVector = V3::normalize(V3::subtract(map[i + 1], map[i]));
	PointToPointVector.x *= distance;
	PointToPointVector.y *= distance;
	PointToPointVector.z *= distance;

	return V3::add(PointToPointVector,map[i]);
}
