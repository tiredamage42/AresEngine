#include "AresLauncher.h"
#include <EntryPoint.h>
namespace Ares
{
	Application* CreateApplication()
	{
		return new AresLauncher();
	}
}
