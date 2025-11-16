#include "pch.h"
#include "ChatServer.h"

int main()
{
	CChatServer server;
	server.Start(L"127.0.0.1", dfChatServerPort, 5, 100);
	

}