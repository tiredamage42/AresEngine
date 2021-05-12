#pragma once

#include "Ares/Core/Application.h"
#include "Engine.h"

// external function that will be defined in the client
extern Ares::Application* Ares::CreateApplication();

int main(int argc, char** argv)
{
	AresInternal::InitializeEngine();
	
	Ares::Application* app = Ares::CreateApplication();
	app->Run();
	delete app;
	
	AresInternal::ShutdownEngine();
}
