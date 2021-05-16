#include "Ares/Core/Application.h"
#include "Ares/Core/Window.h"
#include "Ares/Core/Debug.h"
#include "Ares/Events/ApplicationEvents.h"
#include "Ares/Input/Input.h"

namespace Ares 
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const char* title, int width, int height, bool resizeable)
	{
		_ARES_ASSERT(!s_Instance, "Application Instance Already Exists!");
		s_Instance = this;
		
		auto eventCallback = std::bind(&Application::EventCallback, this, std::placeholders::_1);
		m_Window = new Window(title, width, height, resizeable, eventCallback);
	}

	void Application::Initialize()
	{
		m_Window->SetVSync(false);
		m_Window->Maximize();
		OnInitialize();
	}

	Application::~Application()
	{
		delete m_Window;
		s_Instance = nullptr;
	}

	void Application::Close()
	{
		if (s_Instance)
		{
			s_Instance->m_Window->Close();
		}
	}

	void Application::EventCallback(Event& e)
	{
		// give events to app first.
		// what if mouse clicked on ui button? we don't want event propogated to input, 
		// or else gun might fire
		OnEvent(e);
		if (e.m_Handled)
		{
			return;
		}

		Input::OnEvent(e);
		if (e.m_Handled)
		{
			return;
		}

		e.DispatchFuncIfType<WindowResolutionResizeEvent>(this, &Application::OnWindowResize);
		if (e.m_Handled)
		{
			return;
		}

		e.DispatchFuncIfType<WindowCloseEvent>(this, &Application::OnWindowClose);
	}

	bool Application::OnWindowResize(const WindowResolutionResizeEvent& e)
	{
		return false;
	}
	
	bool Application::OnWindowClose(const WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::Run()
	{
		Initialize();
		while (m_Running)
		{
			if (m_Window->GetWindowStatus() != WindowStatus::Minimized)
			{
				OnUpdate();
			}
			Input::RemoveSingleFrameStatuses();
			m_Window->Render();
			Input::PollInputs();
		}
		OnShutdown();
	}

	const char* Application::GetConfigurationName()
	{
#ifdef _ARES_DEBUG
		return "Debug";
#else
		return "Release";
#endif
	}
}