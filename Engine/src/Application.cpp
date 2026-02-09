#include "Application.h"

#include "Event.h"
#include "Log.h"
#include "Window.h"

namespace Engine {

Application::Application() {
    m_Window = std::make_unique<Window>("MyHazel Editor", 1280, 720);
    m_Window->SetEventCallback([](Event& event) {
        ENGINE_INFO("Event: {}", event.ToString());
    });
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
