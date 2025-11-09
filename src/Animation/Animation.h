#ifndef ANIMATION_H
#define ANIMATION_H
#include <string>
#include <SDL.h>
#include "TextureManager.h"

class Animation
{
    public:
        Animation(){}

        void Update();
        void Draw(float x, float y, int spriteWidth, int spriteHeight);
        void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        std::string m_TextureID;
        int m_SpriteRow, m_SpriteFrame, m_FrameCount, m_AnimSpeed;
        SDL_RendererFlip m_Flip;
};

#endif // ANIMATION_H
