#include "stdafx.h"
#include "Player.h"
#include <math.h>
#include <iostream>
#define std_hit_animation_max_size 1.5f

Player::Player()
{
	hit_animation_dir = 1;
	hit_animation_speed = 0.5f;
	hit_animation_max_size = std_hit_animation_max_size;
	hit_animation_cur_size = 1.0f;
}


Player::~Player()
{
}

void Player::update(float fDeltaTime,Vector3 playerPosition)
{
	Position = playerPosition;


	if (0.999f < hit_animation_cur_size < hit_animation_max_size)
	{
		hit_animation_cur_size +=  hit_animation_speed* hit_animation_dir*fDeltaTime;

		if (hit_animation_cur_size < 0.999f)
		{
				hit_animation_dir = 1;
				hit_animation_max_size = std_hit_animation_max_size;
		}
		else if (hit_animation_max_size < hit_animation_cur_size)
		{
			if(hit_animation_dir>0)//안해두면 가끔 무한루프 돌음
			hit_animation_dir = -hit_animation_dir;
		}
	}

}

void Player::render()
{
	glPushMatrix();
	{
		glTranslatef(Position.x, Position.y, Position.z);
		
		////////////////Player Draw///////////////////
		
		glColor3f(1.f, 1.f, 1.f);
		glutSolidSphere(1.f, 16, 16);

		glPushMatrix();
		{
			glScalef(hit_animation_cur_size, hit_animation_cur_size, hit_animation_cur_size);
			glEnable(GL_CULL_FACE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(1.0, 1.0, 1.0, 0.3);
			glutSolidSphere(1.2f, 16, 16);
			glDisable(GL_BLEND);
		}
		glPopMatrix();
		///////////////////////////////////////////////
	}
	glPopMatrix();
}

void Player::hit()
{
	if (abs(hit_animation_dir) == 1)
	{
		hit_animation_dir = 50;
		hit_animation_max_size = std_hit_animation_max_size * 1.5;
	}
}