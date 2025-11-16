#pragma once

#define WIN32_LEAN_AND_MEAN  // 거의 사용되지 않는 내용을 Windows 헤더에서 제외

#define PROFILE

//--------------------------------------------------
// Windows
//--------------------------------------------------
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <timeapi.h>
#include <Process.h>
#include <iostream>
#pragma comment (lib, "ws2_32")
#pragma comment(lib, "winmm.lib")


//--------------------------------------------------
// NetLibrary Utils
//--------------------------------------------------
#include "Session.h"
#include "RingBuffer.h"
#include "CPacket.h"
#include "Profiler.h"
#include "LockFreeQueue.h"
#include "LockFreeStack.h"
#include "Log.h"
#include "Config.h"
