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
	//타이틀 미완 (외곽선 추가 예정)
	TITLE.render();
	
	
	//텍스트도 객체로 빼야하는데.. 귀찮아
	print("Press s to start",6 , -30, 100,1.f,1.f,1.f, start_button_alpha); //현재 x,y값 상수 
	           																			
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
	//기존 텍스쳐 매핑 터진다고 해서 따로 만듦
	//다른 곳에 쓸 일 없을 거라고 믿고 S00_Logo에 박는다!
	FILE *fp; GLubyte *bits; int bitsize, infosize;
	BITMAPFILEHEADER header;

	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		std::cout << "error" << std::endl;
	// 비트맵 파일 헤더를 읽는다. 
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1)
	{
		fclose(fp);
		std::cout << "error" << std::endl;
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다. 
	if (header.bfType != 'MB')
	{
		fclose(fp);
		std::cout << "error" << std::endl;
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 간다. 

	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다. 
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL)
	{
		fclose(fp);
		exit();
		std::cout << "error" << std::endl;
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize)
	{
		free(*info);
		fclose(fp);
		std::cout << "error" << std::endl;
		return NULL;
	}
	// 비트맵의 크기 설정 
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 *  abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL)
	{
		free(*info);
		fclose(fp);
		std::cout << "error" << std::endl;
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다. 
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