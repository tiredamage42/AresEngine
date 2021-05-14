#include "AresEditor.h"
#include <EntryPoint.h>
namespace Ares
{
	Application* CreateApplication()
	{
		return new AresEditor();
	}
}
