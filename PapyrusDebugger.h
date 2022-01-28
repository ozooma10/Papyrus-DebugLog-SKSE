#pragma once
#include "RuntimeEvents.h"
#include <dap/session.h>
#include "nlohmann/json.hpp"

namespace PapyrusDebugLogServer
{
	class PapyrusDebugger
	{
	public:
		PapyrusDebugger(std::function<void(std::string)> callback);
		~PapyrusDebugger();

	private:
		uint64_t m_SequenceCounter = 0;

		RuntimeEvents::PapyrusLogEventHandle m_LogEventHandle;

		void EventLogged(const RE::BSScript::LogEvent* logEvent);

		std::function<void(std::string)> m_SendCallback;

	private:
		void EmitEvent(const std::string& name, const nlohmann::json& body);
	};
}
