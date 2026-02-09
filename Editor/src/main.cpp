#include <Engine.h>

int main() {
    Engine::Log::Init();

    ENGINE_INFO("Hello from Engine!");
    APP_INFO("Hello from Editor!");

    Engine::Application app;
    app.Run();

    return 0;
}
