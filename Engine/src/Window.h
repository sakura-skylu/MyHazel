#pragma once

#include <functional>
#include <memory>
#include <queue>
#include <string>

struct GLFWwindow;

namespace Engine {

class Event;

class Window {
public:
    using EventCallbackFn = std::function<void(Event&)>;

    Window(const std::string& title, int width, int height);
    ~Window();

    void OnUpdate();
    bool ShouldClose();

    void SetEventCallback(const EventCallbackFn& callback);

private:
    void EnqueueEvent(std::unique_ptr<Event> event);

    static void WindowCloseCallback(GLFWwindow* window);
    static void WindowResizeCallback(GLFWwindow* window, int width, int height);
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
    static void CursorPosCallback(GLFWwindow* window, double xPos, double yPos);

    GLFWwindow* m_Window = nullptr;

    struct WindowData {
        std::string Title;
        int Width = 0;
        int Height = 0;
        EventCallbackFn EventCallback;
    };

    WindowData m_Data;
    std::queue<std::unique_ptr<Event>> m_EventQueue;
};

} // namespace Engine
