#include "Ares/Core/Window.h"
#include "Ares/Core/Debug.h"
#include "Ares/Events/InputEvents.h"
#include "Ares/Events/ApplicationEvents.h"
#include "Ares/Input/InputCodes.h"

#include <GLFW/glfw3.h>
namespace Ares
{
	Window::Window(const char* title, int width, int height, bool resizeable, const std::function<void(Event&)>& callback)
	{
		Initialize(title, width, height, resizeable, callback);
	}
	Window::~Window()
	{
		Shutdown();
	}

	void Window::SetPos(int x, int y) const
	{
		glfwSetWindowPos(m_Window, x, y);
	}
	void Window::SetResolution(int width, int height) const
	{
		glfwSetWindowSize(m_Window, width, height);
	}
	void Window::SetTitle(const std::string& title)
	{
		m_Data.Title = title;
		glfwSetWindowTitle(m_Window, title.c_str());
	}
	void Window::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
		glfwSwapInterval((int)enabled);
	}


	WindowStatus Window::GetWindowStatus() const
	{
		if (glfwGetWindowMonitor(m_Window) != nullptr)
			return WindowStatus::Fullscreen;
		if (glfwGetWindowAttrib(m_Window, GLFW_MAXIMIZED))
			return WindowStatus::Maximized;
		if (glfwGetWindowAttrib(m_Window, GLFW_ICONIFIED))
			return WindowStatus::Minimized;
		return WindowStatus::Windowed;
	}

	void Window::CacheCurrentValues()
	{
		m_Data.CachedResolutionWidth = m_Data.ResolutionWidth;
		m_Data.CachedResolutionHeight = m_Data.ResolutionHeight;
		m_Data.CachedPosX = m_Data.PosX;
		m_Data.CachedPosY = m_Data.PosY;
	}

	void Window::Minimize()
	{
		WindowStatus status = GetWindowStatus();
		if (status == WindowStatus::Minimized)
		{
			return;
		}
		
		if (status != WindowStatus::Fullscreen)
		{
			CacheCurrentValues();
		}

		glfwIconifyWindow(m_Window);
	}

	void Window::Maximize()
	{
		WindowStatus status = GetWindowStatus();
		if (status == WindowStatus::Maximized || status == WindowStatus::Fullscreen)
		{
			return;
		}
		glfwMaximizeWindow(m_Window);
	}

	void Window::Restore() const
	{
		WindowStatus status = GetWindowStatus();
		if (status == WindowStatus::Windowed)
		{
			return;
		}
		if (status == WindowStatus::Fullscreen)
		{
			// restore last window size and position
			glfwSetWindowMonitor(m_Window, nullptr, m_Data.CachedPosX, m_Data.CachedPosY, m_Data.CachedResolutionWidth, m_Data.CachedResolutionHeight, GLFW_DONT_CARE);
		}
		else
		{
			glfwRestoreWindow(m_Window);
		}
	}

	void Window::SetFullScreen()
	{
		WindowStatus status = GetWindowStatus();
		if (status == WindowStatus::Fullscreen)
		{
			return;
		}

		if (status != WindowStatus::Minimized)
		{
			CacheCurrentValues();
		}

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		// get resolution of monitor
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		// switch to full screen
		glfwSetWindowMonitor(m_Window, monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
	}

	void Window::Focus() const
	{
		glfwFocusWindow(m_Window);
	}
	void Window::Close() const
	{
		m_Data.EventCallback(WindowCloseEvent());
	}
	void Window::EnableCursor(bool enabled)
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR, enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
	}
	void Window::SetCursor(Cursor cursor)
	{
		glfwSetCursor(m_Window, m_MouseCursors[static_cast<int>(cursor)]);
	}
	void Window::RequestAttention()
	{
		glfwRequestWindowAttention(m_Window);
	}
	void Window::MakeContextCurrent(void* context) const
	{
		glfwMakeContextCurrent((GLFWwindow*)context);
	}

	static void GLFWErrorCallback(int error, const char* description)
	{
		AresInternal::Debug::Error("GLFW Error ({0}): {1}", error, description);
	}

	void Window::AddWindowEventCallbacks()
	{
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.ResolutionWidth = width;
			data.ResolutionHeight = height;
			data.EventCallback(WindowResolutionResizeEvent(width, height));
		});
		glfwGetWindowSize(m_Window, &m_Data.ResolutionWidth, &m_Data.ResolutionHeight);

		// this is what shoudl be set in glviewport(0,0,width, hiehgt)
		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.FramebufferWidth = width;
			data.FramebufferHeight = height;
			data.EventCallback(WindowFramebufferResizeEvent(width, height));
		});
		glfwGetFramebufferSize(m_Window, &m_Data.FramebufferWidth, &m_Data.FramebufferHeight);

		/*
			The content scale is the ratio between the current DPI and the platform's default DPI.
			This is especially important for text and any UI elements. If the pixel dimensions of your UI scaled by this look
			appropriate on your machine then it should appear at a reasonable size on other machines
			regardless of their DPI and scaling settings.
			This relies on the system DPI and scaling settings being somewhat correct.

			On systems where each monitors can have its own content scale, the window content scale will depend on which monitor
			the system considers the window to be on.
		*/
		glfwSetWindowContentScaleCallback(m_Window, [](GLFWwindow* window, float xscale, float yscale)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.ContentScaleX = xscale;
			data.ContentScaleY = yscale;
			data.EventCallback(WindowContentRescaleEvent(xscale, yscale));
		});
		glfwGetWindowContentScale(m_Window, &m_Data.ContentScaleX, &m_Data.ContentScaleY);

		glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow* window, int minimized)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			if (minimized)
				data.EventCallback(WindowMinimizedEvent());
			else
				data.EventCallback(WindowRestoredEvent());
		});
		
		glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow* window, int maximized)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			if (maximized)
				data.EventCallback(WindowMaximizedEvent());
			else
				data.EventCallback(WindowRestoredEvent());
		});

		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Focused = focused;
			data.EventCallback(WindowFocusChangeEvent(focused));
		});
		m_Data.Focused = glfwGetWindowAttrib(m_Window, GLFW_FOCUSED);
		
		glfwSetCursorEnterCallback(m_Window, [](GLFWwindow* window, int entered)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Hovered = entered;
			data.EventCallback(WindowHoveredChangeEvent(entered));
		});
		m_Data.Hovered = glfwGetWindowAttrib(m_Window, GLFW_HOVERED);
		
		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int x, int y)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.PosX = x;
			data.PosY = y;
			data.EventCallback(WindowPosChangeEvent(x, y));
		});
		glfwGetWindowPos(m_Window, &m_Data.PosX, &m_Data.PosY);

		// get paths dropped onto window (EDITOR ONLY)
		glfwSetDropCallback(m_Window, [](GLFWwindow* window, int count, const char** paths)
		{
			((WindowData*)glfwGetWindowUserPointer(window))->EventCallback(FilesDroppedEvent(paths, count));
		});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			((WindowData*)glfwGetWindowUserPointer(window))->EventCallback(WindowCloseEvent());
		});
	}

	void Window::AddInputEventCallbacks()
	{
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_REPEAT)
				return;
			((WindowData*)glfwGetWindowUserPointer(window))->EventCallback(KeyEvent(GLFWCode2Keycode(key), action == GLFW_PRESS, mods));
		});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int unicodepoint)
		{
			((WindowData*)glfwGetWindowUserPointer(window))->EventCallback(CharTypedEvent(unicodepoint));
		});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			if (action == GLFW_REPEAT)
				return;
			((WindowData*)glfwGetWindowUserPointer(window))->EventCallback(MouseButtonEvent(static_cast<MouseCode>(button), action == GLFW_PRESS, mods));
		});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			((WindowData*)glfwGetWindowUserPointer(window))->EventCallback(MouseScrollEvent((float)xOffset, (float)yOffset));
		});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			((WindowData*)glfwGetWindowUserPointer(window))->EventCallback(MouseMoveEvent((float)xPos, (float)yPos));
		});
		glfwSetJoystickCallback([](int joystickID, int event)
		{
			((WindowData*)glfwGetJoystickUserPointer(joystickID))->EventCallback(GamepadConnectionEvent(joystickID, event == GLFW_CONNECTED));
		});
	}

	void Window::Initialize(const char* title, int width, int height, bool resizeable, const std::function<void(Event&)>& callback)
	{
		m_Data.EventCallback = callback;
		m_Data.Title = title;

		AresInternal::Debug::Log("Creating window '{}'...", title);

		int success = glfwInit();
		_ARES_ASSERT(success, "Could not initialize GLFW!");
		glfwSetErrorCallback(GLFWErrorCallback);
		
		/*
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		*/
		glfwWindowHint(GLFW_RESIZABLE, resizeable);

#ifdef _ARES_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

		m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		
		glfwMakeContextCurrent(m_Window);

		//int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		//_ARES_ASSERT(status, "Could not initialize Glad!");

		glfwSetWindowUserPointer(m_Window, &m_Data);

		for (int i = 0; i < GLFW_JOYSTICK_LAST; ++i)
		{
			glfwSetJoystickUserPointer(i, &m_Data);
		}

		// enable numlock and capslock being included in key mods
		glfwSetInputMode(m_Window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

		// GLFW callbacks
		AresInternal::Debug::Log("Window:: adding callbacks...");
		AddWindowEventCallbacks();		
		AddInputEventCallbacks();

		AresInternal::Debug::Log("Window:: creating cursors...");
		m_MouseCursors[static_cast<int>(Cursor::Arrow)] = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		m_MouseCursors[static_cast<int>(Cursor::TextInput)] = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
		m_MouseCursors[static_cast<int>(Cursor::ResizeAll)] = glfwCreateStandardCursor(GLFW_RESIZE_ALL_CURSOR);
		m_MouseCursors[static_cast<int>(Cursor::ResizeNS)] = glfwCreateStandardCursor(GLFW_RESIZE_NS_CURSOR);
		m_MouseCursors[static_cast<int>(Cursor::ResizeEW)] = glfwCreateStandardCursor(GLFW_RESIZE_EW_CURSOR);
		m_MouseCursors[static_cast<int>(Cursor::ResizeNESW)] = glfwCreateStandardCursor(GLFW_RESIZE_NESW_CURSOR);
		m_MouseCursors[static_cast<int>(Cursor::ResizeNWSE)] = glfwCreateStandardCursor(GLFW_RESIZE_NWSE_CURSOR);
		m_MouseCursors[static_cast<int>(Cursor::Hand)] = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
		m_MouseCursors[static_cast<int>(Cursor::Crosshair)] = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
		m_MouseCursors[static_cast<int>(Cursor::NotAllowed)] = glfwCreateStandardCursor(GLFW_NOT_ALLOWED_CURSOR);
		m_MouseCursors[static_cast<int>(Cursor::PointingHand)] = glfwCreateStandardCursor(GLFW_POINTING_HAND_CURSOR);


		/*
		GLFWimage images[1];
		images[0].pixels = stbi_load(iconPath, &images[0].width, &images[0].height, 0, 4); //rgba channels 
		glfwSetWindowIcon(m_Window, 1, images);
		stbi_image_free(images[0].pixels);
		*/
	}

	void Window::Shutdown()
	{
		AresInternal::Debug::Log("Window:: Destroying Window...");
		glfwDestroyWindow(m_Window);
		AresInternal::Debug::Log("Window:: Terminating GLFW...");
		glfwTerminate();
	}

	void Window::Render()
	{
		glfwSwapBuffers(m_Window);
	}
}