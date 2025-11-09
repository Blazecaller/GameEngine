#include "Demonic.h"
#include "TextureManager.h"

Demonic::Demonic(Properties *props): Character(props){
    m_Animation = new Animation();
    m_RigidBody = new RigidBody();
    m_Animation->SetProps(m_TextureID, 1, 6, 120, SDL_FLIP_NONE);

}

void Demonic::Draw(){
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Demonic::Update(float dt){
    m_RigidBody->Update(0.6);
    m_RigidBody->ApplyForceX(15);
    m_Transform->TranslateX(m_RigidBody->Position().X);
    m_Transform->TranslateY(m_RigidBody->Position().Y);


    m_Animation->Update();
}

void Demonic::Clean(){
    TextureManager::GetInstance()->Clean();
}
