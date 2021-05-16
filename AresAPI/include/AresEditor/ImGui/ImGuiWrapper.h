#pragma once
#include "config.h"

#ifdef ARES_EDITOR
namespace AresEditorInternal
{
	class _ARES_API ImGuiWrapper
	{
	public:
		static void InitializeImGui();
		static void AddFont(const char* file, float size);
		static void SetDefualtFont(int idx);
		
		static void StartImGuiFrame();
		
		static void BeginDockspace(float yStart, float heightOffset);
		static void EndDockspace();

		static void EndImGuiFrame();

		static void TerminateImGui();
	};
}
#endif
