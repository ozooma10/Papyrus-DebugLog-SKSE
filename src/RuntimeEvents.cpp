#include "RuntimeEvents.h"

RE::BSEventNotifyControl RuntimeEvents::OnLogEvent::ProcessEvent(const RE::BSScript::LogEvent* logEvent, RE::BSTEventSource<RE::BSScript::LogEvent>*)
{
	m_LogCallback(logEvent);
	return RE::BSEventNotifyControl();
}
