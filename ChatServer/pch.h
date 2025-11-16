#pragma once

#define WIN32_LEAN_AND_MEAN

#define PROFILE

#ifdef _DEBUG
#pragma comment(lib, "Debug\\NetLibrary.lib")
#else
#pragma comment(lib, "Release\\NetLibrary.lib")
#endif

#include "Config.h"

#include <Windows.h>

#include <list>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>