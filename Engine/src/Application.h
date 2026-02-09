#pragma once
#include <memory>

namespace Engine{

    class Window;

    class Application{
        public:
        Application();
        virtual ~Application();

        void Run();
        
        private:
        std::unique_ptr<Window> m_Window;
    };
}