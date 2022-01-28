#pragma once

#include "PapyrusDebugger.h"
#include <dap/io.h>
#include <dap/dap.h>

namespace PapyrusDebugLogServer
{
	// Event provides a basic wait and signal synchronization primitive.
	class Event
	{
	public:
		// wait() blocks until the event is fired.
		void wait();

		// fire() sets signals the event, and unblocks any calls to wait().
		void fire();

	private:
		std::mutex mutex;
		std::condition_variable cv;
		bool fired = false;
	};


	class DebugSession
	{
		std::shared_ptr<dap::ReaderWriter> m_ClientPipe;
		PapyrusDebugger* m_Debugger;
		std::unique_ptr<dap::Session> m_DapSession;

		
		Event m_Terminate;

		std::thread m_ClientReadThread;

	public:
		DebugSession(std::function<void(std::string)> sendCallback);
		~DebugSession();

		void Receive(std::string message);

	};
}
