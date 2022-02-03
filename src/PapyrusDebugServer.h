#pragma once

#include "PapyrusDebugger.h"
#include "Websocket.h"

class PapyrusDebugServer
{
public:
	PapyrusDebugServer();
	~PapyrusDebugServer();

	bool Listen();


private:
	PapyrusDebugger* m_Debugger;

	HANDLE m_Thread;
	websocket_server m_Server;

	websocketpp::connection_hdl m_ConnectionHandle;

	int ListenInternal();

	void Send(std::string message);

	void HandleMessage(websocketpp::connection_hdl hdl, message_ptr msg);
	void HandleOpen(websocketpp::connection_hdl hdl);
	void HandleClose(websocketpp::connection_hdl hdl);
		
	static DWORD WINAPI ListenThreadStart(void* param);
};
