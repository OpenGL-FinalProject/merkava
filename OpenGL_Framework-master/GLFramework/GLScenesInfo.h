#pragma once
#define _SCENES_
/*--------------------ADD SCENES HERE--------------------*/

/*~~~~~HEADER FILES~~~~*/
#include "Scene00_Main.h"
#include "Scene01.h"
#include "Scene02.h"
#include "Scene03.h"
#include "Scene04.h"
#include "Scene05.h"
#include "Scene06.h"
#include "Scene07.h"

struct GLSceneInfo
{
	std::string name;
	GLScene*	pScene;
	bool		bInitAtStart{ true };
};

/*~~~~~~~SCENES~~~~~~~*/
const GLSceneInfo SCENES[] =
{
	{"Main", new S00Logo, true},
	{"1", new S01Main, false},
	{"2", new S02Main, false},
	{"3", new S03Main, false},
	{"4", new S04Main, false},
	{"5", new S5Main,  false},
	{"6", new S06Main, false},
	{"7", new S07Main, false}
};

/*~~~STARTING SCENE~~~*/
const std::string STARTING_SCENE { "Main" };

/*-------------------------------------------------------*/
