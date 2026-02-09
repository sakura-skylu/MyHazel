#include "Window.h"
#include "Log.h"
#include <GLFW/glfw3.h>

namespace Engine{

    Window::Window(const std::string& title,int width,int height){
        if(!glfwInit()){
            ENGINE_ERROR("Fail to init GLFW");
            return;
        }

        m_Window = glfwCreateWindow(width,height,title.c_str(),nullptr,nullptr);

        if(!m_Window){
            ENGINE_ERROR("Failed to create window");
            glfwTerminate();//清理
            return;
        }

        ENGINE_INFO("Window creat");
    }

    Window::~Window(){
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
    void Window::OnUpdate(){
        glfwPollEvents();//检查是否有事件
    }

    bool Window::ShouldClose(){
        return glfwWindowShouldClose(m_Window);
    }

}