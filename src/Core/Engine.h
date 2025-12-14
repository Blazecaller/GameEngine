#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "GameMap.h"


class Engine{

    public:
        static Engine* GetInstance(){
            return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine();
        }

        bool Init();
        void Clean();
        void Quit();

        void Update();
        void Render();
        void Events();

        inline GameMap *GetMap(){return m_LevelMap;}
        inline bool IsRunning(){
            return m_IsRunning;
        }
        inline SDL_Renderer* GetRenderer(){
            return m_Renderer;
        }

    private:
        Engine();

        GameMap *m_LevelMap;
        bool m_IsRunning;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        static Engine* s_Instance; // Points to the engine object (GetInstance is called if the object is not newed yet)
};

#endif // ENGINE_H
