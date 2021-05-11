#include <Ares.h>
#include <EntryPoint.h>
namespace Ares
{
	class AresLauncher : public Application
	{
	public:
		AresLauncher() : Application("Ares Launcher")
		{
		}
	};

	Application* CreateApplication()
	{
		return new AresLauncher();
	}
}
