#pragma once

//--------------------------------------------------
// Windows
//--------------------------------------------------
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <timeapi.h>
#include <Process.h>
#pragma comment (lib, "ws2_32")
#pragma comment(lib, "winmm.lib")

//--------------------------------------------------
// NetLibrary Core
//--------------------------------------------------
#include "LanServer.h"
#include "LanClient.h"
#include "Session.h"


//--------------------------------------------------
// NetLibrary Utils
//--------------------------------------------------
#include "RingBuffer.h"
#include "CPacket.h"
#include "Profiler.h"
#include "LockFreeQueue.h"
#include "LockFreeStack.h"
#include "Log.h"
#include "Config.h"


//--------------------------------------------------
// std data structure
//--------------------------------------------------
#include <list>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>

