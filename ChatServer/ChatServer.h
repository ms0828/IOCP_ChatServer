#pragma once

#include "NetLibrary.h"

using namespace std;

class CChatServer : public CLanServer
{
public:
	class User
	{
	public:
		User() : sessionId(0), accountNumber(0), nickname{0}, sessionKey{0} {}
		~User() {}
		inline void SetSessionId(ULONGLONG _sessionId) { sessionId = _sessionId; }
		void InitUser(ULONGLONG _sessionId, ULONGLONG accountNumber, const WCHAR* nickName, const char* sessionKey);
		
	private:
		ULONGLONG sessionId;
		ULONGLONG accountNumber;
		WCHAR nickname[20];
		char sessionKey[32];
	};

	struct st_UserInfo
	{
		ULONGLONG accountNumber;
		WCHAR nickname[20];
	};


public:
	CChatServer();
	~CChatServer();

	virtual bool OnConnectionRequest(SOCKADDR_IN* requestAdr);
	virtual void OnClientJoin(ULONGLONG sessionId);
	virtual void OnClientLeave(ULONGLONG sessionId);
	virtual void OnMessage(ULONGLONG sessionId, USHORT packetType, CPacketView* packet);
	virtual void OnMonitoring();


	//---------------------------------------------------------
	// ÄÁÅÙÃ÷ ½º·¹µå °ü·Ã
	//---------------------------------------------------------
	static unsigned int ChatContentsProc(void* arg);



	void NetPacketProc_ReqLogin(ULONGLONG sessionId, CPacketView* packet);

private:
	CObjectPool_TLS<User, true> userPool;
	unordered_map<ULONGLONG, User*> userMap;
	
	//---------------------------------------------------------
	// ÄÁÅÙÃ÷ ½º·¹µå °ü·Ã
	//---------------------------------------------------------
	CLockFreeQueue<st_JobMessage> chatContentsJobQ;
	HANDLE hChatEvent;
};