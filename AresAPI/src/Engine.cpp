#include "Engine.h"
#include "Ares/Core/Debug.h"

namespace AresInternal
{
	void InitializeEngine()
	{
		AresInternal::Debugging::Initialize();
		AresInternal::Debug::Log("Initializing Engine...");
	}
	void ShutdownEngine()
	{
		AresInternal::Debug::Log("Shutting Down Engine...");
	}
}
