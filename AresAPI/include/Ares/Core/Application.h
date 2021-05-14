#pragma once
#include "Ares/config.h"

int main(int argc, char** argv);

namespace Ares 
{
    class Window;
    struct Event;
    struct WindowCloseEvent;
    struct WindowResolutionResizeEvent;

    class _ARES_API Application
    {
        friend int ::main(int argc, char** argv);
    public:
        static void Close();
        inline Window* GetWindow() const { return m_Window; }
    protected:
        Application(const char* title, int windowWidth, int windowHeight, bool resizable);
        virtual ~Application();

        virtual void OnInitialize() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnEvent(Event& event) = 0;
        virtual void OnShutdown() = 0;

    private:
        void Initialize();
                
        void EventCallback(Event& e);

        bool OnWindowClose(const WindowCloseEvent& e);
        bool OnWindowResize(const WindowResolutionResizeEvent& e);

        static const char* GetConfigurationName();
        void Run();
        bool m_Running = true;
        Window* m_Window = nullptr;
        static Application* s_Instance;
    };

    // defined in client
    Application* CreateApplication();
}
