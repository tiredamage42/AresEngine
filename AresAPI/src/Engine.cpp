#include "Engine.h"
#include "Ares/Core/Debug.h"
#include <filesystem>
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


		try
		{
			std::filesystem::remove_all("Temp/");
		}
		catch (std::filesystem::filesystem_error e)
		{
			AresInternal::Debug::Error("Error Removing Temp Directory: {}", e.what());
		}
	}
}
