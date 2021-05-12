#pragma once
#include "Ares/config.h"

int main(int argc, char** argv);

//#pragma warning(push)
//#pragma warning(disable:4251)

namespace Ares 
{

    class _ARES_API Application
    {
        friend int ::main(int argc, char** argv);
    public:
        static void Close();
    protected:
        Application(const char* title);
        virtual ~Application();
    private:
        static const char* GetConfigurationName();
        static Application& GetInstance();
        void Run();
        bool m_Running = true;
        static Application* s_Instance;
    };

    // defined in client
    Application* CreateApplication();
}

//#pragma warning(pop)