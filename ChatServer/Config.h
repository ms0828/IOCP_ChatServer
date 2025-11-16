#pragma once

#define dfChatServerPort 3000

enum PACKET_TYPE : unsigned short
{
	//-----------------------------------------------------
	// PKT_CS_REQ_LOGIN
	// - ULONGLONG accountNumber
	// - USHORT sessionKeyLen
	// - CHAR sessionKey[sessionKeyLen]
	//-----------------------------------------------------
	PKT_CS_REQ_LOGIN = 0,

	//-----------------------------------------------------
	// PKT_SC_RES_LOGIN
	// - bool result
	// - USHORT nicknameLen
	// - WCHAR nickname[nicknameLen]
	//-----------------------------------------------------
	PKT_SC_RES_LOGIN,

	//-----------------------------------------------------
	// PKT_CS_REQ_USER_ENTER_ROOM
	// - ULONGLONG accountNumber
	//-----------------------------------------------------
	PKT_CS_REQ_USER_ENTER_ROOM,

	//-----------------------------------------------------
	// PKT_SC_REQ_USER_ENTER_ROOM
	// - bool result
	// - list<st_UserINFO> roomUserList
	//-----------------------------------------------------
	PKT_SC_RES_USER_ENTER_ROOM,

	//-----------------------------------------------------
	// PKT_SC_NTF_USER_ENTER_ROOM
	// - st_UserINFO enterUser
	//-----------------------------------------------------
	PKT_SC_NTF_USER_ENTER_ROOM,

	//-----------------------------------------------------
	// PKT_CS_REQ_USER_LEAVE_ROOM
	// - ULONGLONG accountNumber
	//-----------------------------------------------------
	PKT_CS_REQ_USER_LEAVE_ROOM,

	//-----------------------------------------------------
	// PKT_SC_NTF_USER_LEAVE_ROOM
	// - ULONGLONG accountNumber
	//-----------------------------------------------------
	PKT_SC_NTF_USER_LEAVE_ROOM,



	//-----------------------------------------------------
	// PKT_CS_REQ_USER_CHAT
	// - ULONGLONG accountNumber
	// - USHORT messageLen
	// - WCHAR message[messageLen]
	//-----------------------------------------------------
	PKT_CS_REQ_USER_CHAT,

	//-----------------------------------------------------
	// PKT_SC_NTF_USER_CHAT
	// - ULONGLONG accountNumber
	// - USHORT messageLen
	// - WCHAR message[messageLen]
	//-----------------------------------------------------
	PKT_SC_NTF_USER_CHAT,
};