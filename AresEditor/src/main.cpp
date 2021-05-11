#include <Ares.h>
#include <EntryPoint.h>
namespace Ares
{
	class AresEditor : public Application
	{
	public:
		AresEditor() : Application("Ares Editor")
		{
		}
	};

	Application* CreateApplication()
	{
		return new AresEditor();
	}
}
