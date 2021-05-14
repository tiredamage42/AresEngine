#include "AresEditor.h"


namespace Ares
{
	AresEditor::AresEditor() 
		: Application("Ares Editor", 1280, 720, true)
	{
	}
	void AresEditor::OnInitialize()
	{
	}
	void AresEditor::OnShutdown()
	{
	}
	void AresEditor::OnUpdate()
	{
		Window* window = Application::GetWindow();
		
		if (Input::GetKeyDown(KeyCode::F))
		{
			window->SetFullScreen();
		}
		if (Input::GetKeyDown(KeyCode::I))
		{
			window->Minimize();
		}
		if (Input::GetKeyDown(KeyCode::M))
		{
			window->Maximize();
		}
		if (Input::GetKeyDown(KeyCode::R))
		{
			window->Restore();
		}

		if (Input::GetKeyDown(KeyCode::Q))
		{
			Application::Close();
		}
	}
	void AresEditor::OnEvent(Event& event)
	{
	}


}