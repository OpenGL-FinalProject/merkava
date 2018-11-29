#include "stdafx.h"
#include "Player.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::update(float fDeltaTime,Vector3 playerPosition)
{
	Position = playerPosition;
}

void Player::render()
{
	glPushMatrix();
	{
		glTranslatef(Position.x, Position.y, Position.z);
		//
		// Player Draw
		//
		glutSolidCube(5.f);
	}
	glPopMatrix();
}