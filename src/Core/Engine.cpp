#include "Engine.h"
#include "TextureManager.h"
#include "Demonic.h"
#include "Input.h"
#include "Timer.h"
#include "MapParser.h"
#include <iostream>

Engine* Engine::s_Instance = nullptr;
Demonic* player = nullptr;

/** @brief Init
  * Engine init
  * Initialize SDL. Create window and renderer.
  * If successful, texture manager loads assets.
  */
bool Engine::Init(){

    if(SDL_Init(SDL_INIT_VIDEO)!= 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)!= 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }
    SDL_WindowFlags window_flags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    m_Window = SDL_CreateWindow("Soft Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
    if(m_Window == nullptr)
    {
        SDL_Log("Failed to create Window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(m_Renderer == nullptr){
        SDL_Log("Failed to create Renderer: %s", SDL_GetError());
        return false;
    }
    TTF_Init();

    if(!MapParser::GetInstance()->Load()){
        std::cout << "Failed to load map" << std::endl;
    }

    m_LevelMap = MapParser::GetInstance()->GetMap("MAP");


    //Load sprite texture
    TextureManager::GetInstance()->Load("player", "assets/characters/Karasu_tengu/idle.png");
    TextureManager::GetInstance()->Load("player_run", "assets/characters/Karasu_tengu/Run.png");

    player = new Demonic(new Properties(100, 200, 128, 128, "player"));
    return m_IsRunning = true;
}

/** @brief Clean
  * Engine Clean
  * Exit action. Renderer and Window are destroyed;
  * texture is cleared and erased. SDL quit and IMG quit will get rid of all subsystems working.
  */
void Engine::Clean(){
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

/** @brief Quit
  * Engine Quit
  * Break the game loop to stop the engine
  */
void Engine::Quit(){
    m_IsRunning = false;
}

/** @brief Update
  *
  * @todo: document this function
  */
void Engine::Update(){
    float dt = Timer::GetInstance()->GetDeltaTime();
    m_LevelMap->Update();
    player->Update(dt);
}

/** @brief Render
  * Engine Render
  * Render images by drawing texture/image.
  */
void Engine::Render(){
    SDL_SetRenderDrawColor(m_Renderer, 0, 127, 127, 255);
    SDL_RenderClear(m_Renderer);

    m_LevelMap->Render();
    player->Draw();
    SDL_RenderPresent(m_Renderer);

}

/** @brief Events
  *
  * @todo: document this function
  */
void Engine::Events(){
    Input::GetInstance()->Listen();
}

/** @brief Engine
  *
  * @todo: document this function
  */
Engine::Engine(){

}
