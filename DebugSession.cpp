#include "DebugSession.h"
#include "DebugSession.h"
#include <dap/protocol.h>
#include <dap/network.h>
#include <future>

using json = nlohmann::json;

namespace PapyrusDebugLogServer
{
	void Event::wait()
	{
		std::unique_lock<std::mutex> lock(mutex);
		cv.wait(lock, [&] { return fired; });
	}

	void Event::fire()
	{
		std::unique_lock<std::mutex> lock(mutex);
		fired = true;
		cv.notify_all();
	}

	DebugSession::DebugSession(std::function<void(std::string)> sendCallback)
	{
		//m_ClientPipe = dap::pipe();
		//m_DapSession = dap::Session::create();
		m_Debugger = new PapyrusDebugger(sendCallback);
		/*
		m_DapSession->registerHandler([](const dap::InitializeRequest&) {
			logger::info("InitializeRequest...");

			dap::InitializeResponse response;
			response.supportsConfigurationDoneRequest = true;
			return response;
		});

		m_DapSession->registerSentHandler([&](const dap::ResponseOrError<dap::InitializeResponse>&) {
			m_DapSession->send(dap::InitializedEvent());
		});

		m_DapSession->registerHandler([&](const dap::LaunchRequest&) {
			logger::info("LaunchRequest...");
			return dap::LaunchResponse();
		});

		m_DapSession->registerHandler([&](const dap::DisconnectRequest& request) {
			logger::info("DisconnectRequest...");
			if (request.terminateDebuggee.value(false)) {
				m_Terminate.fire();
			}
			return dap::DisconnectResponse();
		});
		
		m_DapSession->bind(m_ClientPipe);*/
	}

	PapyrusDebugLogServer::DebugSession::~DebugSession()
	{
	}

	void DebugSession::Receive(std::string message)
	{
		//m_ClientPipe->write(message.c_str(), message.size());
	}


}
