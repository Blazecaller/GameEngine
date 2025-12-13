#include "Demonic.h"
#include "TextureManager.h"
#include "Input.h"

Demonic::Demonic(Properties *props): Character(props){
    m_Animation = new Animation();
    m_RigidBody = new RigidBody();
    m_Animation->SetProps(m_TextureID, 1, 8, 100, SDL_FLIP_NONE);

}

void Demonic::Draw(){
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Demonic::Update(float dt){
    static SDL_RendererFlip lastDir = SDL_FLIP_NONE;
    m_Animation->SetProps("player", 1, 6, 100, lastDir);
    m_RigidBody->UnsetForce();
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
        lastDir = SDL_FLIP_NONE;
        m_Animation->SetProps("player_run", 1, 8, 100, lastDir);
        m_RigidBody->ApplyForceX(FORWARD*5);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)){
        lastDir = SDL_FLIP_HORIZONTAL;
        m_Animation->SetProps("player_run", 1, 8, 100, lastDir);
        m_RigidBody->ApplyForceX(BACKWARD*5);
    }
    m_RigidBody->Update(dt);

    m_Transform->TranslateX(m_RigidBody->Position().X);
    //m_Transform->TranslateY(m_RigidBody->Position().Y);

    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;
    m_Animation->Update();
}

void Demonic::Clean(){
    TextureManager::GetInstance()->Clean();
}
