#pragma once

#include <functional>

namespace RuntimeEvents
{
	class OnLogEvent : public RE::BSTEventSink<RE::BSScript::LogEvent>
	{
		virtual RE::BSEventNotifyControl ProcessEvent(const RE::BSScript::LogEvent* logEvent, RE::BSTEventSource<RE::BSScript::LogEvent>*) override;

		public:
			static OnLogEvent* GetSingleton()
			{
				static OnLogEvent g_LogEventHandler;
				return &g_LogEventHandler;
			}

		static bool RegisterEvent()
		{
			RE::BSScript::Internal::VirtualMachine::GetSingleton()->RegisterForLogEvent(GetSingleton());
			return true;
		}

		std::function<void(const RE::BSScript::LogEvent*)> m_LogCallback;

	};
}
