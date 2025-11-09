#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"

Warrior::Warrior(Properties *props): Character(props) {
    m_Row = 1;
    m_FrameCount = 6;
    m_AnimSpeed = 240;
}

void Warrior::Draw(){
    TextureManager::GetInstance()->DrawFrame(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Row, m_Frame, SDL_FLIP_NONE);

}

void Warrior::Update(float dt){
    m_Frame = (SDL_GetTicks()/m_AnimSpeed)%m_FrameCount;
    //if(m_Frame == 1){m_Frame = 0;}
}

void Warrior::Clean(){
    TextureManager::GetInstance()->Clean();
}
