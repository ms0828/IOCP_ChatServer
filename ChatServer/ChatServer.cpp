#include "pch.h"
#include "ChatServer.h"

CChatServer::CChatServer() : userPool(false, 0, 4)
{
	hChatEvent = CreateEvent(nullptr, false, false, nullptr);
}

CChatServer::~CChatServer()
{
	CloseHandle(hChatEvent);
}

bool CChatServer::OnConnectionRequest(SOCKADDR_IN* requestAdr)
{
	return false;
}

void CChatServer::OnClientJoin(ULONGLONG sessionId)
{

}

void CChatServer::OnClientLeave(ULONGLONG sessionId)
{
	
}

void CChatServer::OnMessage(ULONGLONG sessionId, USHORT packetType, CPacketView* packet)
{
	switch (packetType)
	{
	case PACKET_TYPE::PKT_CS_REQ_LOGIN:
	case PACKET_TYPE::PKT_CS_REQ_USER_ENTER_ROOM:
	case PACKET_TYPE::PKT_CS_REQ_USER_LEAVE_ROOM:
	case PACKET_TYPE::PKT_CS_REQ_USER_CHAT:
		// 채팅 처리 스레드 작업 큐(LFQ) enqueue
		st_JobMessage jobMsg;
		jobMsg.sessionId = sessionId;
		jobMsg.packetType = packetType;
		jobMsg.packet = packet;

		chatContentsJobQ.Enqueue(jobMsg);
		SetEvent(hChatEvent);
		break;
		
	}
}

void CChatServer::OnMonitoring()
{

}

unsigned int CChatServer::ChatContentsProc(void* arg)
{
	CChatServer* server = static_cast<CChatServer*>(arg);
	
	HANDLE events[2] = { server->shutdownEvent, server->hChatEvent };

	while (1)
	{
		DWORD ret = WaitForMultipleObjects(2, events, false, INFINITE);
		if (ret == WAIT_OBJECT_0)
		{
			_LOG(dfLOG_LEVEL_SYSTEM, L"shutdown event is signal - ChatContentsProcThread Exit!");
			break;
		}
		
		st_JobMessage jobMsg;
		bool ret = server->chatContentsJobQ.Dequeue(jobMsg);
		// 락 프리 큐에서 Enqueue 했으나 아직 연결되지 않아 Dequeue가 실패할 가능성이 존재
		if (ret == false)
		{
			__debugbreak();
			continue;
		}
		
		
		switch (jobMsg.packetType)
		{
		case PACKET_TYPE::PKT_CS_REQ_LOGIN:
			server->NetPacketProc_ReqLogin(jobMsg.sessionId, jobMsg.packet);
			break;
		case PACKET_TYPE::PKT_CS_REQ_USER_ENTER_ROOM:
			break;
		case PACKET_TYPE::PKT_CS_REQ_USER_LEAVE_ROOM:
			break;
		case PACKET_TYPE::PKT_CS_REQ_USER_CHAT:
			break;
		}


	}

	return 0;
}

void CChatServer::NetPacketProc_ReqLogin(ULONGLONG sessionId, CPacketView* packet)
{
	
	ULONGLONG accountNumber;
	WCHAR* nickname;
	char* sessionKey;
	//*packet >> accountNo;
	//... Todo

	//-------------------------------------------------
	//Todo
	// - 세션 로그인 인증
	// - 지금은 인증이 완료되었다고 가정
	//-------------------------------------------------
	Session* session = FindSessionById(sessionId);
	session->Authenticate();

	User* newUser = userPool.allocObject();
	newUser->InitUser(sessionId, accountNumber, nickname, sessionKey);
	userMap.insert({ sessionId, newUser });
	
	// ResLogin 만들어 세션에게 Send

	// 방 번호?
}

void CChatServer::User::InitUser(ULONGLONG _sessionId, ULONGLONG accountNumber, const WCHAR* nickName, const char* sessionKey)
{

}
