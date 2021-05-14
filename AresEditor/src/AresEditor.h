#pragma once
#include <Ares.h>
namespace Ares
{
	class AresEditor : public Application
	{
	public:
		AresEditor();
		virtual void OnInitialize() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;
		virtual void OnShutdown() override;
	};
}
