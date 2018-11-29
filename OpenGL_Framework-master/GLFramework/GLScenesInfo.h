#pragma once
#define _SCENES_
/*--------------------ADD SCENES HERE--------------------*/

/*~~~~~HEADER FILES~~~~*/
#include "Scene00_Main.h"
#include "Scene01_Tutorial.h"
#include "Scene02_MIR.h"
#include "Scene02.h"
#include "Scene03.h"


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
	{"Tutorial", new S01_Tutorial, false},
	{"Made In Love", new Scene02_MIR, false},
	{"2", new S02Main, false},
	{"3", new S03Main, false},

};

/*~~~STARTING SCENE~~~*/
const std::string STARTING_SCENE { "Main" };

/*-------------------------------------------------------*/
