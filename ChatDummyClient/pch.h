#pragma once

#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#pragma comment(lib, "Debug\\NetLibrary.lib")
#else
#pragma comment(lib, "Release\\NetLibrary.lib")
#endif

#include "NetLibrary.h"

