#include "Application.h"
#include "Window.h"
#include "Log.h"

namespace Engine {

Application::Application() {
    m_Window = std::make_unique<Window>("MyHazel Editor", 1280, 720);
}

Application::~Application() {
}

void Application::Run() {
    ENGINE_INFO("Application Run()");

    while (!m_Window->ShouldClose()) {
        m_Window->OnUpdate();
    }
}

} // namespace Engine
