#include "PapyrusDebugServer.h"
#include "RuntimeEvents.h"

using namespace PapyrusDebugLogServer;

PapyrusDebugServer* g_PapyrusDebugServer;

namespace
{
	void InitializeLog()
	{
		auto path = logger::log_directory();
		if (!path) {
			util::report_and_fail("Failed to find standard logging directory"sv);
		}

		*path /= fmt::format("{}.log"sv, Plugin::NAME);
		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);

#ifndef NDEBUG
		const auto level = spdlog::level::info;
#else
		const auto level = spdlog::level::trace;
#endif

		auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));
		log->set_level(level);
		log->flush_on(level);

		spdlog::set_default_logger(std::move(log));
		spdlog::set_pattern("%g(%#): [%^%l%$] %v"s);
	}

	void MessageHandler(SKSE::MessagingInterface::Message* message)
	{
		logger::info("{} v{}"sv, Plugin::NAME, Plugin::VERSION.string());
		switch (message->type) {
		case SKSE::MessagingInterface::kDataLoaded:
			RuntimeEvents::CommitHooks();

			g_PapyrusDebugServer->Listen();
			logger::info("Listening For Connections from DebugLog Adapter...");
			break;
		}
	}
}


extern "C" DLLEXPORT constinit auto SKSEPlugin_Version = []() {
	SKSE::PluginVersionData v;

	v.PluginVersion(Plugin::VERSION);
	v.PluginName(Plugin::NAME);

	v.UsesAddressLibrary(true);
	v.CompatibleVersions({ SKSE::RUNTIME_LATEST });

	return v;
}();

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	InitializeLog();
	logger::info("{} v{}"sv, Plugin::NAME, Plugin::VERSION.string());
	SKSE::Init(a_skse);

	g_PapyrusDebugServer = new PapyrusDebugServer();

	auto messagingInterface = SKSE::GetMessagingInterface();
	if (!messagingInterface->RegisterListener(MessageHandler)) {
		return false;
	}

	return true;
}