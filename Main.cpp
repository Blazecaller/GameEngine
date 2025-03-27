#include "Engine.h"
int main(int argc, char** agrv)
{
    Engine::GetInstance()->Init();
    while(Engine::GetInstance()->IsRunning())
    {
        Engine::GetInstance()->Events();  // Events such as key activation, quit etc..
        Engine::GetInstance()->Update();  // States such as dead, alive
        Engine::GetInstance()->Render();  // Draw the result
    }

    Engine::GetInstance()->Clean();
    return 0;
}
