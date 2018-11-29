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
		glColor3f(1.f, 1.f, 1.f);
		glutSolidSphere(1.f, 16, 16);

		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0, 1.0, 1.0, 0.3);
		glutSolidSphere(1.5f, 16, 16);
		glDisable(GL_BLEND);

		
	}
	glPopMatrix();
}