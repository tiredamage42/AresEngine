#include "AresEditor.h"
#include <AresEditorAPI.h>
#include <filesystem>
using namespace AresEditorInternal;
namespace Ares
{
	AresEditor::AresEditor() 
		: Application("Ares Editor", 1280, 720, true)
	{
	}
	void AresEditor::OnInitialize()
	{
		ImGuiWrapper::InitializeImGui();
		ImGuiWrapper::AddFont("EditorData/Fonts/OpenSans/OpenSans-Regular.ttf", 18.0f);
		ImGuiWrapper::AddFont("EditorData/Fonts/OpenSans/OpenSans-Bold.ttf", 18.0f);
		ImGuiWrapper::AddFont("EditorData/Fonts/OpenSans/OpenSans-Italic.ttf", 18.0f);
		ImGuiWrapper::AddFont("EditorData/Fonts/OpenSans/OpenSans-BoldItalic.ttf", 18.0f);
		ImGuiWrapper::SetDefualtFont(0);
	}
	void AresEditor::OnShutdown()
	{
		ImGuiWrapper::TerminateImGui();
		
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
		/*
		*/



		OnImGuiDraw();
	}
	void AresEditor::OnEvent(Event& event)
	{
	}






	


	void AresEditor::OnImGuiDraw()
	{
		ImGuiWrapper::StartImGuiFrame();
		ImGuiWrapper::BeginDockspace(0, 0);

		ImGuiWrapper::EndDockspace();
		ImGuiWrapper::EndImGuiFrame();
	}


}