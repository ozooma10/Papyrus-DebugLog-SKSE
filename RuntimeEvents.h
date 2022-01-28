#pragma once

#include <functional>
#include <eventpp/callbacklist.h>


namespace PapyrusDebugLogServer
{
	namespace RuntimeEvents
	{
		typedef eventpp::CallbackList<void(const RE::BSScript::LogEvent*)>::Handle PapyrusLogEventHandle;
		PapyrusLogEventHandle SubscribeToLog(std::function<void(const RE::BSScript::LogEvent*)> handler);
		bool UnSubscribeFromLog(PapyrusLogEventHandle eventHandle);

		void CommitHooks();
	}
}
