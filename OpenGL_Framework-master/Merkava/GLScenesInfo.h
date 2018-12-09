#pragma once
#define _SCENES_
/*--------------------ADD SCENES HERE--------------------*/

/*~~~~~HEADER FILES~~~~*/
#include "Scene00_Main.h"
#include "Scene02_MIR.h"
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
	{"Main", new S00_Logo, true},
	{"Made In Love", new Scene02_MIR, false},
	{"Result", new S03Main, false},

};

/*~~~STARTING SCENE~~~*/
const std::string STARTING_SCENE { "Main" };

/*-------------------------------------------------------*/
