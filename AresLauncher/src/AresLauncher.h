#pragma once
#include <Ares.h>
namespace Ares
{
	class AresLauncher : public Application
	{
	public:
		AresLauncher();
		virtual void OnInitialize() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;
		virtual void OnShutdown() override;
	};
}
