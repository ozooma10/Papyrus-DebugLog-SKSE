#pragma once
#include "RuntimeEvents.h"
#include "nlohmann/json.hpp"

class PapyrusDebugger
{
public:
	PapyrusDebugger(std::function<void(std::string)> callback);

private:
	uint64_t m_SequenceCounter = 0;

	void EventLogged(const RE::BSScript::LogEvent* logEvent);

	std::function<void(std::string)> m_SendCallback;

private:
	void EmitEvent(const std::string& name, const nlohmann::json& body);
};
