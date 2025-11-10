#include "Warrior.h"
#include "TextureManager.h"

Warrior::Warrior(Properties *props): Character(props){
    m_Animation = new Animation();
    m_RigidBody = new RigidBody();
    m_Animation->SetProps(m_TextureID, 1, 6, 120, SDL_FLIP_NONE);

}

void Warrior::Draw(){
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Update(float dt){
    m_RigidBody->Update(0.6);
    m_RigidBody->ApplyForceX(8);
    m_Transform->TranslateX(m_RigidBody->Position().X);
    m_Transform->TranslateY(m_RigidBody->Position().Y);


    m_Animation->Update();
}

void Warrior::Clean(){
    TextureManager::GetInstance()->Clean();
}
