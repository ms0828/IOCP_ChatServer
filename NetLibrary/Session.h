#pragma once

#include <WinSock2.h>
#include "CPacket.h"
#include "LockFreeQueue.h"
#include "Config.h"

enum EIOTYPE
{
	ERecv = 0,
	ESend = 1,
};
struct SessionOlp
{
	WSAOVERLAPPED overlapped;
	EIOTYPE type;
};
struct SendOlp
{
	SessionOlp olp;
	CPacket* freePackets[dfMaxSendPacketCount];
	ULONG sendCount;
};
struct RecvOlp
{
	SessionOlp olp;
};


class Session
{
	friend class CLanServer;
	friend class CLanClient;
	friend class CNetServer;
	friend class CNetClient;

public:
	Session()
	{
		sock = INVALID_SOCKET;
		sessionId = 0;
		recvOlp.olp.type = ERecv;
		sendOlp.olp.type = ESend;
		sendLFQ = new CLockFreeQueue<CPacket*>();
		recvQ = nullptr;
		isSending = false;
		isDisconnect = false;
		isAuthenticated = false;
		lastActiveTick = 0;
		bRecvRST = false;  // 디버깅용
		refCount = 0;
		refCount |= (1 << 31);
	}
	~Session()
	{
		delete sendLFQ;
	}


	//------------------------------------------------
	// 초기화 순서 중요
	// - AcquireSessionById에서 예외적 상황으로 증가시킨 RefCount를 감소하는 경우에 재할당된 세션을 끊어버릴 수 있음
	// - RefCount의 ReleaseFlag를 RefCount 증가 이후에 비활성화함으로써 해결
	//------------------------------------------------
	void InitSession(SOCKET _sock, ULONGLONG _id)
	{
		InterlockedIncrement(&refCount);
		recvOlp.olp.type = ERecv;
		memset(&recvOlp, 0, sizeof(WSAOVERLAPPED));
		sendOlp.olp.type = ESend;
		memset(&sendOlp, 0, sizeof(WSAOVERLAPPED));
		recvQ = nullptr;
		isSending = false;
		isDisconnect = false;
		isAuthenticated = false;
		lastActiveTick = timeGetTime();
		bRecvRST = false; // 디버깅용
		sessionId = _id;
		sock = _sock;
		InterlockedAnd((LONG*)&refCount, ~(1 << 31));
	}

	inline void Authenticate() { isAuthenticated = true; }

private:
	SOCKET sock;
	ULONGLONG sessionId;
	SendOlp sendOlp;
	RecvOlp recvOlp;
	CLockFreeQueue<CPacket*>* sendLFQ;
	CPacket* recvQ;
	LONG isSending;
	LONG isDisconnect;
	ULONG refCount;
	ULONG lastActiveTick;
	ULONG isAuthenticated;
	ULONG bRecvRST;  // 디버깅용
};


