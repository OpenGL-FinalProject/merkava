#include <atlimage.h>
#include "stdafx.h"
#include "Scene00_Main.h"
#include "GLFramework.h"
#define _USE_MATH_DEFINES
#include <math.h>

	
S00_Logo::S00_Logo()
{

}


S00_Logo::~S00_Logo()
{
}

void S00_Logo::init()
{
	m_Camera.setDistance(200.f);
	m_Camera.setPerspective(60.f, 0.125f, 3500.f);
	m_Camera.setSensitivity(1.f);

	is_started_to_change_scene = false;
	get_time = 0;
	start_button_alpha = 0.f;
	elapsed_time_since_scene_change_started = 0.f;
	time_to_change_scene = 2.f;
}

void S00_Logo::exit()
{
}

void S00_Logo::reset()
{
}

void S00_Logo::render()
{
	m_Camera.ready();

	BG.render();
	//Ÿ��Ʋ �̿� (�ܰ��� �߰� ����)
	TITLE.render();
	
	
	//�ؽ�Ʈ�� ��ü�� �����ϴµ�.. ������
	print("Press s to start",6 , -30, 100,1.f,1.f,1.f, start_button_alpha); //���� x,y�� ��� 
	           																			
}

void S00_Logo::reshape(int w, int h)
{

}

void S00_Logo::keyboard(int key, bool pressed, int x, int y, bool special)
{
	if (pressed)
		switch (key)
		{
		case's':
			start_to_change_scene();
			BG.start_to_change_scene();
			break;
		}
		
}

void S00_Logo::mouse(int button, bool pressed, int x, int y)
{
}

void S00_Logo::motion(bool pressed, int x, int y)
{
}

void S00_Logo::update(float fDeltaTime)
{
	BG.update(fDeltaTime);
	get_time += fDeltaTime;

	if (is_started_to_change_scene == false)
	{
		start_button_alpha = sin((get_time - (int)get_time) * M_PI);
	}
	else if (is_started_to_change_scene == true)
	{
		elapsed_time_since_scene_change_started += fDeltaTime;
		start_button_alpha = sin((1 - elapsed_time_since_scene_change_started)*M_PI / (time_to_change_scene));
	}

	if (elapsed_time_since_scene_change_started >= time_to_change_scene + 1.0f)
		m_Framework->toScene("Made In Love");

}

void S00_Logo::start_to_change_scene()
{
	is_started_to_change_scene = true;
	start_button_alpha = 1.f;
}

GLubyte* S00_Logo::LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	//���� �ؽ��� ���� �����ٰ� �ؼ� ���� ����
	//�ٸ� ���� �� �� ���� �Ŷ�� �ϰ� S00_Logo�� �ڴ´�!
	FILE *fp; GLubyte *bits; int bitsize, infosize;
	BITMAPFILEHEADER header;

	// ���̳ʸ� �б� ���� ������ ����
	if ((fp = fopen(filename, "rb")) == NULL)
		std::cout << "error" << std::endl;
	// ��Ʈ�� ���� ����� �д´�. 
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1)
	{
		fclose(fp);
		std::cout << "error" << std::endl;
		return NULL;
	}
	// ������ BMP �������� Ȯ���Ѵ�. 
	if (header.bfType != 'MB')
	{
		fclose(fp);
		std::cout << "error" << std::endl;
		return NULL;
	}
	// BITMAPINFOHEADER ��ġ�� ����. 

	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// ��Ʈ�� �̹��� �����͸� ���� �޸� �Ҵ��� �Ѵ�. 
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL)
	{
		fclose(fp);
		exit();
		std::cout << "error" << std::endl;
		return NULL;
	}
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize)
	{
		free(*info);
		fclose(fp);
		std::cout << "error" << std::endl;
		return NULL;
	}
	// ��Ʈ���� ũ�� ���� 
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 *  abs((*info)->bmiHeader.biHeight);
	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� �Ҵ��Ѵ�.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL)
	{
		free(*info);
		fclose(fp);
		std::cout << "error" << std::endl;
		return NULL;
	}
	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� �����Ѵ�. 
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize)
	{
		free(*info);
		free(bits);
		fclose(fp);
		std::cout << "error" << std::endl;
		return NULL;
	}
	fclose(fp);
	return bits;


};