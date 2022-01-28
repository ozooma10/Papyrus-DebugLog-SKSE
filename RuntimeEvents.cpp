#include "RuntimeEvents.h"

namespace PapyrusDebugLogServer
{
	namespace RuntimeEvents
	{
		eventpp::CallbackList<void(const RE::BSScript::LogEvent*)> g_PapyrusLogEvent;

		class LogEventSink : public RE::BSTEventSink<RE::BSScript::LogEvent>
		{
			RE::BSEventNotifyControl ProcessEvent(const RE::BSScript::LogEvent* logEvent, RE::BSTEventSource<RE::BSScript::LogEvent>*) override
			{
				g_PapyrusLogEvent(logEvent);
				return RE::BSEventNotifyControl::kContinue;
			};
		};

		PapyrusLogEventHandle SubscribeToLog(std::function<void(const RE::BSScript::LogEvent*)> handler)
		{
			return g_PapyrusLogEvent.append(handler);
		}

		bool UnSubscribeFromLog(PapyrusLogEventHandle eventHandle)
		{
			return g_PapyrusLogEvent.remove(eventHandle);
		}
		void CommitHooks()
		{
			RE::BSScript::Internal::VirtualMachine::GetSingleton()->RegisterForLogEvent(new LogEventSink());
		}
	}
}
