#pragma once
#include <string>

struct  GLFWwindow;

namespace Engine{
class Window{
    public:
    Window(const std::string& title,int width,int height);
    ~Window();
    
    void OnUpdate();
    bool ShouldClose();
    
    private:
    GLFWwindow* m_Window = nullptr;
};

}