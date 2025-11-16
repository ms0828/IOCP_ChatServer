#pragma once

#define dfMaxSendPacketCount 300

//-----------------------------------------------
// 기본 패킷 헤더 구조
//-----------------------------------------------
struct st_PacketHeader
{
	USHORT packetType;
	USHORT payloadLen;
};

//-----------------------------------------------
// 컨텐츠 스레드 작업 메시지 구조
//-----------------------------------------------
struct st_JobMessage
{
	ULONGLONG sessionId;
	USHORT packetType;
	CPacketView* packet;
};