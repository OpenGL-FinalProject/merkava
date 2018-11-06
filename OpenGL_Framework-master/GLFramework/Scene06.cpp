#include "stdafx.h"
#include "Scene06.h"
#include "GLFramework.h"

S06Main::S06Main()
{
}

S06Main::~S06Main()
{
}

void S06Main::init()
{
	m_Camera.setDistance(6000.f);
	m_Camera.setPerspective(45.f, 0.125f, 10'000.f);
	m_Camera.setSensitivity(10.f);

	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	m_Plane.setModel("Cube", 3000, false);
	m_Plane.setColor(Vector3(0.8f, 0.8f, 0.8f));
	m_Plane.move(0.f, -700.f, 0.f);
	m_Plane.scale(1.f, 0.01f, 1.f);

	Air.setModel(200);
	Air.setColor({ 0.f,0.f,0.f });
	Air.m_qrRotation.rotate(-180.f / (3.14 * 36), Air.m_qrRotation.rotatePoint({ 0.f,1.f,0.f }));

	Tree[0].setModel("Cube", 230, false);
	Tree[1].setModel("Cube", 230, false);
	Tree[0].move(-1000.f, -565.f, -1000.f);
	Tree[1].move(-1000.f, -335.f, -1000.f);
	Tree[0].setColor({ 0.4f,0.25f,0.08f });
	Tree[1].setColor({ 0.2f,0.8f,0.12f });

	robot.setPosition(0.f, 0.f, 0.f);

	anim = 0;
	spin = 0;
	ad = true;
	s = 0;

	onair = false;
	reverse = false;

	BoxSpin = 0;
	open = false;
}

void S06Main::exit()
{
	m_Plane.move(0.f, 700.f, 0.f);

	Tree[0].setPosition(0.f, 0.f, 0.f);
	Tree[1].setPosition(0.f, 0.f, 0.f);

	Air.m_qrRotation.resetQuaternion();

	tX = 0, tY = 0;
}

void S06Main::reset()
{
}

void S06Main::Triangles()
{
	glColor3f(0.7f, 0.2f, 0.f);
	glBegin(GL_TRIANGLES);						//tree
	{
		glVertex3f(-1500.f, -660.f, -1500.f);
		glVertex3f(-1500.f, -660.f, -200.f);
		glVertex3f(-200.f, -660.f, -1500.f);
	}
	glEnd();
	glColor3f(0.f, 0.7f, 0.2f);
	glBegin(GL_TRIANGLES);						//press
	{
		glVertex3f(1500.f, -660.f, -1500.f);
		glVertex3f(1500.f, -660.f, -200.f);
		glVertex3f(200.f, -660.f, -1500.f);
	}
	glEnd();
	glColor3f(0.2f, 0.f, 0.7f);
	glBegin(GL_TRIANGLES);						//running
	{
		glVertex3f(-1500.f, -660.f, 1500.f);
		glVertex3f(-1500.f, -660.f, 200.f);
		glVertex3f(-200.f, -660.f, 1500.f);
	}
	glEnd();
	glColor3f(0.7f, 0.2f, 0.7f);
	glBegin(GL_TRIANGLES);						//iron
	{
		glVertex3f(1500.f, -660.f, 1500.f);
		glVertex3f(1500.f, -660.f, 200.f);
		glVertex3f(200.f, -660.f, 1500.f);
	}
	glEnd();
	glColor3f(1.f, 1.f, 1.f);
}

void S06Main::Treez()
{
	Tree[0].render();
	Tree[1].render();
}

void S06Main::Pressz()
{
	glColor3f(0.f, 0.f, 1.f);
	glPushMatrix();
	{
		glTranslatef(1100.f, -650.f, -1100.f);
		glScalef(1.f, 0.1f, 1.f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(1100.f, -650.f, -1100.f);
		glScalef(0.4f, 0.4f, 0.7f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(1300.f, -500.f, -1300.f);
		glScalef(0.1f, 1.f, 0.1f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(900.f, -500.f, -1300.f);
		glScalef(0.1f, 1.f, 0.1f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(1100.f, -470.f + (20 - anim) * 10, -1250.f);
		glScalef(1.5f, 0.1f, 0.1f);
		glColor3f(0.4f, 0.4f, 0.4f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(1400.f, -470.f + (20 - anim) * 10, -1250.f);
		glScalef(0.1f, 0.3f, 0.3f);
		glColor3f(1.f, 0.f, 0.f);
		glutSolidSphere(350, 8, 8);
		glColor3f(1.f, 1.f, 1.f);
		glutWireSphere(350, 8, 8);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(800.f, -470.f + (20 - anim) * 10, -1250.f);
		glScalef(0.1f, 0.3f, 0.3f);
		glColor3f(1.f, 0.f, 0.f);
		glutSolidSphere(350, 8, 8);
		glColor3f(1.f, 1.f, 1.f);
		glutWireSphere(350, 8, 8);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();

}

void S06Main::Runningz()
{
	glColor3f(1.f, 0.f, 0.f);

	glPushMatrix();
	{
		glTranslatef(-1100.f, -600.f, 1100.f);
		glRotatef(90, 0.f, 1.f, 0.f);
		glScalef(0.7f, 0.1f, 2.4f);
		glRotatef(-spin, 0.f, 0.f, 1.f);
		glutSolidTorus(50, 350, 18, 18);
		glColor3f(1.f, 1.f, 1.f);
		glutWireTorus(60, 370, 18, 18);
		glColor3f(1.f, 0.f, 0.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-1300.f, -500.f, 1300.f);
		glScalef(0.1f, 1.f, 0.1f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(1.f, 0.f, 0.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-900.f, -500.f, 1300.f);
		glScalef(0.1f, 1.f, 0.1f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-1130.f, -430.f, 1150.f);
		glTranslatef(0.f, 100.f, 0.f);
		glRotatef(anim - 20, 1.f, 0.f, 0.f);
		glTranslatef(0.f, -100.f, 0.f);
		glScalef(0.1f, 1.f, 0.1f);
		glutSolidCube(200);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(205);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(-1030.f, -430.f, 1150.f);
		glTranslatef(0.f, 100.f, 0.f);
		glRotatef(40 - anim - 20, 1.f, 0.f, 0.f);
		glTranslatef(0.f, -100.f, 0.f);
		glScalef(0.1f, 1.f, 0.1f);
		glutSolidCube(200);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(205);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
}

void S06Main::Ironz()
{
	glPushMatrix();
	{
		glTranslatef(1300.f, -500.f, 1100.f);
		glScalef(0.1f, 1.f, 0.1f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(900.f, -500.f, 1100.f);
		glScalef(0.1f, 1.f, 0.1f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
	glPushMatrix();
	{
		glTranslatef(1100.f, -320.f, 1100.f);
		glScalef(1.2f, 0.1f, 0.1f);
		glColor3f(0.4f, 0.4f, 0.4f);
		glutSolidCube(350);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(355);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(1150.f, -430.f, 1100.f);
		glTranslatef(0.f, 100.f, 0.f);
		glRotatef(spin, 1.f, 0.f, 0.f);
		glTranslatef(0.f, -100.f, 0.f);
		glScalef(0.07f, 0.7f, 0.07f);
		glutSolidCube(200);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(205);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(1050.f, -430.f, 1100.f);
		glTranslatef(0.f, 100.f, 0.f);
		glRotatef(spin, 1.f, 0.f, 0.f);
		glTranslatef(0.f, -100.f, 0.f);
		glScalef(0.07f, 0.7f, 0.07f);
		glutSolidCube(200);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(205);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(1100.f, -530.f, 1100.f);
		glTranslatef(0.f, 200.f, 0.f);
		glRotatef(spin, 1.f, 0.f, 0.f);
		glTranslatef(0.f, -200.f, 0.f);
		glScalef(1.f, 1.f, 0.3f);
		glutSolidCube(100);
		glColor3f(1.f, 1.f, 1.f);
		glutWireCube(105);
		glColor3f(0.f, 0.f, 1.f);
	}glPopMatrix();
}

void S06Main::Circlez()
{
	int sic[3];
	int cic[3];
	for (int i = 0; i < 3; i++)
	{
		if (reverse)
		{
			sic[i] = sin(((spin / 12) * 12 + (i + 1) * 10) / 360.f * 3.1415) * 1400.f;
			cic[i] = cos(((spin / 12) * 12 + (i + 1) * 10) / 360.f * 3.1415) * 1400.f;

		}
		else
		{
			sic[i] = sin(((spin / 12) * 12 - (i + 1) * 10) / 360.f * 3.1415) * 1400.f;
			cic[i] = cos(((spin / 12) * 12 - (i + 1) * 10) / 360.f * 3.1415) * 1400.f;
		}
		glPushMatrix();
		{
			glTranslatef(sic[i], 0.f, cic[i]);
			glRotatef(1.0, 0.f, 1.f, 0.f);
			glTranslatef(-70.f*sin(spin), 0.f, -70.f*cos(spin));
			glColor3f(0.25f, 0.25f, 0.25f);
			glutSolidSphere((3 - i) * 15, 12, 12);
			glTranslatef(140.f*sin(spin), 0.f, 140.f*cos(spin));
			glColor3f(0.25f, 0.25f, 0.25f);
			glutSolidSphere((3 - i) * 15, 12, 12);
			glRotatef(-1.0, 0.f, 1.f, 0.f);
		}glPopMatrix();
	}
}

void S06Main::render()
{
	m_Camera.ready();

	robot.render();

	glTranslatef(0.f, 20.f * tY, 0.f);
	glTranslatef(20.f * tX, 0.f, 0.f);

	if (onair)
	{
		m_Camera.setEye({ si,-50.f,co });
		m_Camera.setTarget({ 0.f,-400.f,0.f });
	}

	m_Plane.render();
	//
	//������Ʈ��(������ Ŭ������ ���ߴ�)
	Triangles();
	Treez();
	Pressz();
	Runningz();
	Ironz();

	Air.render();
	Circlez();

	Square();
	//
}

void S06Main::reshape(int w, int h)
{
}

void S06Main::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
	{
		switch (key)
		{
		case ' ': m_Framework->toScene("Main"); break;
		case 'o': if (open) open = false; else open = true; break;
		case '+': m_Camera.setDistance(m_Camera.getDistance() - 5); break;
		case '-': m_Camera.setDistance(m_Camera.getDistance() + 5); break;
		case 'w': robot.setDir(2); break;
		case 'a': robot.setDir(3); break;
		case 's': robot.setDir(0); break;
		case 'd': robot.setDir(1); break;
		case 'z': tY++; break;
		case 'x': tX--; break;
		case 'c': tY--; break;
		case 'v': tX++; break;
		case '1': if (onoff[0]) onoff[0] = false; else onoff[0] = true; break;
		case '2': if (onoff[1]) onoff[1] = false; else onoff[1] = true; break;
		case '3': if (onoff[2]) onoff[2] = false; else onoff[2] = true; break;
		case 'j': robot.jump = true; break;
		case '0': s = (s + 1) % 2; break;
		case '/': reverse = (reverse + 1) % 2;
			Air.m_qrRotation.rotate(-360.f / (3.14 * 36), Air.m_qrRotation.rotatePoint({ 0.f,1.f,0.f })); break;
		case '\\':
			if (onair)
			{
				onair = false;
				m_Camera.init();
				m_Camera.setDistance(4000.f);
				m_Camera.setPerspective(45.f, 0.125f, 7'000.f);
				m_Camera.setSensitivity(10.f);
			}
			else
			{
				onair = true;
				m_Camera.resetRotation();
			}
			break;
		}
	}
}

void S06Main::mouse(int button, bool pressed, int x, int y)
{

}

void S06Main::motion(bool pressed, int x, int y)
{
	if (!onair)
	{
		if (s)
			m_Camera.rotate(x, 0.f, pressed);
		else
			m_Camera.rotate(0.f, y, pressed);
	}
}

void S06Main::update(float fDeltaTime)
{
	robot.update(fDeltaTime);
	
	if (open && BoxSpin < 90)
		BoxSpin++;
	else if (!open && BoxSpin > 0)
		BoxSpin--;
	std::cout << BoxSpin << std::endl;

	si = sin(spin / 360.f * 3.1415) * 1400.f;
	co = cos(spin / 360.f * 3.1415) * 1400.f;
	if (onair)
	{
		m_Camera.setEye({ si*2.f,1500.f,co*2.f });
		m_Camera.setTarget({ si,0.f,co });
	}
	Air.update(fDeltaTime);
	Air.setPosition({ si,0.f,co });
	if (spin == 720)
	{
		spin = 0;
		Air.m_qrRotation.resetQuaternion();
		Air.m_qrRotation.rotate(-180.f / (3.14 * 36), Air.m_qrRotation.rotatePoint({ 0.f,1.f,0.f }));

	}
	if (reverse)
		Air.m_qrRotation.rotate(1.f / (3.1415 * 36), Air.m_qrRotation.rotatePoint({ 0.f,1.f,0.f }));
	else
		Air.m_qrRotation.rotate(-1.f / (3.1415 * 36), Air.m_qrRotation.rotatePoint({ 0.f,1.f,0.f }));

	if (ad)
		anim += 1;
	else
		anim -= 1;
	if (anim >= 40)
		ad = false;
	else if (anim < 1)
		ad = true;
	if (reverse)
		spin--;
	else
		spin++;
	Tree[1].scale(1.f + (anim / 60.f), 1.f + (anim / 60.f), 1.f + (anim / 60.f));

	if (onoff[0])
		glDisable(GL_DEPTH_TEST);
	else
		glEnable(GL_DEPTH_TEST);

	if (onoff[1])
		glDisable(GL_CULL_FACE);
	else
		glEnable(GL_CULL_FACE);


}

void S06Main::Square()
{
	glBegin(GL_QUADS);
	{
		glColor3f(0.2f, 0.2f, 0.2f); // Black
		Point(3);
		Point(0);
		Point(1);
		Point(2);
		glColor3f(0.3f, 0.3f, 0.3f); // Black
		Point(5);
		Point(6);
		Point(2);
		Point(1);
		glColor3f(0.4f, 0.4f, 0.4f); // Black
		Point(1);
		Point(0);
		Point(4);
		Point(5);
		glColor3f(0.5f, 0.5f, 0.5f); // Black
		Point(3);
		Point(2);
		Point(6);
		Point(7);
		
		//����
		glColor3f(0.7f, 0.7f, 0.7f); // Black
		Point(4);
		Point(0);
		Point(3);
		Point(7);
	}
	glEnd();

	//�ո�
	glPushMatrix();
	{
		glRotatef(-BoxSpin, 1.f, 0.f, 0.f);
		glColor3f(0.6f, 0.6f, 0.6f); // Black
		glBegin(GL_QUADS);
		{
			Point(7);
			Point(6);
			Point(5);
			Point(4);
		}glEnd();
	}glPopMatrix();
}

void S06Main::Point(int num)
{
	switch (num)
	{
	case 0:
		glVertex3f(1550.0, 1550.0, -1550.0);
		break;
	case 1:
		glVertex3f(1550.0, -1550.0, -1550.0);
		break;
	case 2:
		glVertex3f(-1550.0, -1550.0, -1550.0);
		break;
	case 3:
		glVertex3f(-1550.0, 1550.0, -1550.0);
		break;
	case 4:
		glVertex3f(1550.0, 1550.0, 1550.0);
		break;
	case 5:
		glVertex3f(1550.0, -1550.0, 1550.0);
		break;
	case 6:
		glVertex3f(-1550.0, -1550.0, 1550.0);
		break;
	case 7:
		glVertex3f(-1550.0, 1550.0, 1550.0);
		break;
	}

}
