#include "PapyrusDebugger.h"
#include <dap/io.h>
#include <dap/protocol.h>

namespace PapyrusDebugLogServer
{
	PapyrusDebugger::PapyrusDebugger(std::function<void(std::string)> callback)
	{
		m_SendCallback = callback;

		m_LogEventHandle = RuntimeEvents::SubscribeToLog(std::bind(&PapyrusDebugger::EventLogged, this, std::placeholders::_1));
	}

	PapyrusDebugger::~PapyrusDebugger()
	{
		RuntimeEvents::UnSubscribeFromLog(m_LogEventHandle);
	}

	void PapyrusDebugger::EventLogged(const RE::BSScript::LogEvent* logEvent)
	{
		const auto message = std::string(logEvent->errorMsg);

		nlohmann::json body;
		body["category"] = "console";
		body["output"] = message + "\r\n";

		EmitEvent("output", body);
	}

	void PapyrusDebugger::EmitEvent(const std::string& name, const nlohmann::json& body) 
	{
		nlohmann::json response;
		response["type"] = "event";
		response["event"] = name;
		response["body"] = body;

		std::string output = response.dump();
		m_SendCallback(output);
	}
}
