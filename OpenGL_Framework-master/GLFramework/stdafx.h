#pragma once
/* WINAPI */
#include <Windows.h>

/* C, C++, STL */
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <memory>
#include <assert.h>
#include <chrono>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#define _USE_MATH_DEFINES

/* FMOD */
#include "Dependencies/FMOD/include/fmod.hpp"

/* GL */
#include "Dependencies/GL/glew.h"
#include "Dependencies/GL/freeglut.h"

const int DEF_WIN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);
const int DEF_WIN_WIDTH = DEF_WIN_HEIGHT / 1.5;