#include "Ares/Core/Application.h"

namespace Ares 
{
	Application* Application::s_Instance = nullptr;
	Application& Application::GetInstance() { return *s_Instance; }

	Application::Application(const char* title)
	{
		s_Instance = this;
	}

	Application::~Application()
	{
	}

	void Application::Close()
	{
		GetInstance().m_Running = false;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			
		}
	}

	const char* Application::GetConfigurationName()
	{
#ifdef ARES_DEBUG
		return "Debug";
#else
		return "Release";
#endif
	}
}