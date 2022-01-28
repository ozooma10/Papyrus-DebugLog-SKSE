#include "PapyrusDebugServer.h"
#include "PapyrusDebugger.h"

namespace PapyrusDebugLogServer
{
	PapyrusDebugServer::PapyrusDebugServer() :
		m_Debugger(NULL)
	{
	}

	PapyrusDebugServer::~PapyrusDebugServer()
	{
		m_server.stop();
	}

	int PapyrusDebugServer::ListenInternal()
	{
		try {
			m_server.init_asio();

			m_server.set_open_handler(bind(&PapyrusDebugServer::HandleOpen, this, ::_1));
			m_server.set_close_handler(bind(&PapyrusDebugServer::HandleClose, this, ::_1));
			m_server.set_message_handler(bind(&PapyrusDebugServer::HandleMessage, this, ::_1, ::_2));
			m_server.set_max_message_size(1024 * 1024 * 10);
			m_server.set_max_http_body_size(1024 * 1024 * 10);

			// Listen on port 43201
			m_server.listen(43201);

			// Start the server accept loop
			m_server.start_accept();
			
			// Start the ASIO io_service run loop
			m_server.run();
		} catch (websocketpp::exception const& e) {
			logger::info("{} {}"sv, Plugin::NAME, e.what());
			return e.code().value();
		} catch (...) {
			logger::info("{} {}"sv, Plugin::NAME, "other_exception");
			return -1;
		}

		return 0;
	}

	void PapyrusDebugServer::Send(std::string message)
	{
		m_server.send(m_ConnectionHandle, message.c_str(), message.length(), websocketpp::frame::opcode::text);
	}

	void PapyrusDebugServer::HandleMessage(websocketpp::connection_hdl hdl, message_ptr msg)
	{
		/* if (m_Session) {
			m_Session->Receive(msg->get_payload());
		}*/
	}

	void PapyrusDebugServer::HandleOpen(websocketpp::connection_hdl hdl)
	{
		if (m_Debugger && m_server.get_con_from_hdl(hdl) != m_server.get_con_from_hdl(m_ConnectionHandle)) {
			m_server.close(m_ConnectionHandle, websocketpp::close::status::normal, "Connection closed by new session");
		}
		
		m_ConnectionHandle = hdl;
		m_Debugger = new PapyrusDebugger(std::bind(&PapyrusDebugServer::Send, this, ::_1));
	}

	void PapyrusDebugServer::HandleClose(websocketpp::connection_hdl hdl)
	{
		if (m_server.get_con_from_hdl(hdl) != m_server.get_con_from_hdl(m_ConnectionHandle)) {
			return;
		}

		//m_Session->Close();
		delete m_Debugger;
		m_Debugger = NULL;
	}

	DWORD __stdcall PapyrusDebugServer::ListenThreadStart(void* param)
	{
		PapyrusDebugServer* server = (PapyrusDebugServer*)param;
		logger::info("ListenThreadStart...");
		return server->ListenInternal();
	}

	bool PapyrusDebugServer::Listen()
	{
		DWORD threadId;

		m_Thread = CreateThread(NULL, 0, ListenThreadStart, this, 0, &threadId);
		return true;
	}

}
