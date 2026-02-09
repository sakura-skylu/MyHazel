#include "Window.h"

#include "Event.h"
#include "Log.h"
#include <GLFW/glfw3.h>

namespace Engine {

Window::Window(const std::string& title, int width, int height) {
    if (!glfwInit()) {
        ENGINE_ERROR("Fail to init GLFW");
        return;
    }

    m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!m_Window) {
        ENGINE_ERROR("Failed to create window");
        glfwTerminate();
        return;
    }

    m_Data.Title = title;
    m_Data.Width = width;
    m_Data.Height = height;

    glfwSetWindowUserPointer(m_Window, this);
    glfwSetWindowCloseCallback(m_Window, WindowCloseCallback);
    glfwSetWindowSizeCallback(m_Window, WindowResizeCallback);
    glfwSetKeyCallback(m_Window, KeyCallback);
    glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
    glfwSetScrollCallback(m_Window, ScrollCallback);
    glfwSetCursorPosCallback(m_Window, CursorPosCallback);

    ENGINE_INFO("Window creat");
}

Window::~Window() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Window::OnUpdate() {
    glfwPollEvents();

    while (!m_EventQueue.empty()) {
        auto& event = m_EventQueue.front();
        if (m_Data.EventCallback) {
            m_Data.EventCallback(*event);
        }
        m_EventQueue.pop();
    }
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(m_Window);
}

void Window::SetEventCallback(const EventCallbackFn& callback) {
    m_Data.EventCallback = callback;
}

void Window::EnqueueEvent(std::unique_ptr<Event> event) {
    m_EventQueue.push(std::move(event));
}

void Window::WindowCloseCallback(GLFWwindow* window) {
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (!self) {
        return;
    }

    self->EnqueueEvent(std::make_unique<WindowCloseEvent>());
}

void Window::WindowResizeCallback(GLFWwindow* window, int width, int height) {
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (!self) {
        return;
    }

    self->m_Data.Width = width;
    self->m_Data.Height = height;
    self->EnqueueEvent(std::make_unique<WindowResizeEvent>(width, height));
}

void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (!self) {
        return;
    }

    (void)scancode;
    (void)mods;

    switch (action) {
        case GLFW_PRESS:
            self->EnqueueEvent(std::make_unique<KeyPressedEvent>(key, 0));
            break;
        case GLFW_RELEASE:
            self->EnqueueEvent(std::make_unique<KeyReleasedEvent>(key));
            break;
        case GLFW_REPEAT:
            self->EnqueueEvent(std::make_unique<KeyPressedEvent>(key, 1));
            break;
        default:
            break;
    }
}

void Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (!self) {
        return;
    }

    (void)mods;

    switch (action) {
        case GLFW_PRESS:
            self->EnqueueEvent(std::make_unique<MouseButtonPressedEvent>(button));
            break;
        case GLFW_RELEASE:
            self->EnqueueEvent(std::make_unique<MouseButtonReleasedEvent>(button));
            break;
        default:
            break;
    }
}

void Window::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (!self) {
        return;
    }

    self->EnqueueEvent(
        std::make_unique<MouseScrolledEvent>(static_cast<float>(xOffset), static_cast<float>(yOffset)));
}

void Window::CursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (!self) {
        return;
    }

    self->EnqueueEvent(
        std::make_unique<MouseMovedEvent>(static_cast<float>(xPos), static_cast<float>(yPos)));
}

} // namespace Engine
