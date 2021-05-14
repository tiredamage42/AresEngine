#pragma once
#include "Ares/config.h"
#include <string>
#include <functional>

struct GLFWwindow;
struct GLFWcursor;

namespace Ares 
{
	struct Event;
	
	enum class Cursor
	{
		Arrow,
		TextInput,
		ResizeAll,
		ResizeNS,
		ResizeEW,
		ResizeNESW,
		ResizeNWSE,
		Hand,
		NotAllowed,
		PointingHand,
		Crosshair
	};

	enum class WindowStatus
	{
		Minimized, Windowed, Maximized, Fullscreen
	};

	// interface representing a desktop system based window
	class _ARES_API Window
	{
		friend class Application;
	public:
		
		inline int GetResolutionWidth() const { return m_Data.ResolutionWidth; }
		inline int GetResolutionHeight() const { return m_Data.ResolutionHeight; }
		void SetResolution(int width, int height) const;

		inline int GetFramebufferWidth() const { return m_Data.FramebufferWidth; }
		inline int GetFramebufferHeight() const { return m_Data.FramebufferHeight; }

		inline float GetContentScaleX() const { return m_Data.ContentScaleX; }
		inline float GetContentScaleY() const { return m_Data.ContentScaleY; }

		inline int GetPosX() const { return m_Data.PosX; }
		inline int GetPosY() const { return m_Data.PosY; }
		void SetPos(int x, int y) const;

		WindowStatus GetWindowStatus() const;
		
		void Minimize();
		void Restore() const;
		void Maximize();
		void SetFullScreen();
		
		inline bool IsFocused() const { return m_Data.Focused; }
		void Focus() const;

		inline bool IsHovered() const { return m_Data.Hovered; }
		
		inline const std::string& GetTitle() const { return m_Data.Title; }
		void SetTitle(const std::string& title);

		inline bool IsVSync() const { return m_Data.VSync; }
		void SetVSync(bool enabled);

		void SetCursor(Cursor cursor);
		void EnableCursor(bool enabled);

		void RequestAttention();
		void Close() const;

	private:
		Window(const char* title, int width, int height, bool resizeable, const std::function<void(Event&)>& callback);
		~Window();

		void CacheCurrentValues();
		void Render();

		inline const void* GetContext() const { return m_Window; }
		void MakeContextCurrent(void* context) const;

		void AddWindowEventCallbacks();
		void AddInputEventCallbacks();

		void Initialize(const char* title, int width, int height, bool resizeable, const std::function<void(Event&)>& callback);
		void Shutdown();

		GLFWwindow* m_Window;
		GLFWcursor* m_MouseCursors[11] = { 0 };

		struct WindowData 
		{
			std::string Title = "";
			bool VSync = false;
			int PosX = 0, PosY = 0;
			int ResolutionWidth = 0, ResolutionHeight = 0;
			
			int CachedPosX = 0, CachedPosY = 0;
			int CachedResolutionWidth = 0, CachedResolutionHeight = 0;

			int FramebufferWidth = 0, FramebufferHeight = 0;
			float ContentScaleX = 1.0f, ContentScaleY = 1.0f;

			bool Focused = false;
			bool Hovered = false;
			
			std::function<void(Event&)> EventCallback = nullptr;
		};

		WindowData m_Data;
	};
}
