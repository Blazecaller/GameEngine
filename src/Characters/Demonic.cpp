#include "Demonic.h"
#include "TextureManager.h"
#include "Input.h"
#include "Camera.h"
#include "Engine.h"
#include "CollisionHandler.h"
#include "UtilDebug.h"

Demonic::Demonic(Properties *props): Character(props){
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;

    m_Collider = new Collider();
    m_Collider->SetBuffer(0, 0, 0, 0);
    m_Collider->Set(10, 20, 0, 0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(9.0);

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 8, 100, SDL_FLIP_NONE);

}

void Demonic::Draw(){
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
    //TODO: remove the draw rect, Collider box is for debug purposes only!
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

#if IS_BOX_DEBUGGABLE == 1
    int box_w = 30, box_h = 70;
    int marge_x = 50, marge_y = 40;
#endif
void Demonic::Update(float dt){
    static SDL_RendererFlip lastDir = SDL_FLIP_NONE;

    m_Animation->SetProps("player", 1, 6, 100, lastDir);
    m_RigidBody->UnsetForce();

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)){
        lastDir = SDL_FLIP_HORIZONTAL;
        m_Animation->SetProps("player_run", 1, 8, 100, lastDir);
        m_RigidBody->ApplyForceX(BACKWARD*5);
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
        lastDir = SDL_FLIP_NONE;
        m_Animation->SetProps("player_run", 1, 8, 100, lastDir);
        m_RigidBody->ApplyForceX(FORWARD*5);
    }
    #if IS_BOX_DEBUGGABLE == 5
        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_UP)){
            box_h++;
        }

        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_DOWN)){
            box_h--;
        }
        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RIGHT)){
            box_w++;
        }

        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_LEFT)){
            box_w--;
        }
        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_M)){
            marge_x++;
        }
        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_N)){
            marge_x--;
        }
        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J)){
            marge_y++;
        }
        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K)){
            marge_y--;
        }
    #endif
    //Jump
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsGrounded){
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsJumping && (m_JumpTime > 0)){
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
    }else{
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    //move on X axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += m_RigidBody->Position().X;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 125);
    #if IS_BOX_DEBUGGABLE == 1
        m_Collider->Set(m_Transform->X+marge_x, m_Transform->Y+marge_y, box_w, box_h);
        std::cout << "m_Collider" << m_Collider->Get().x <<" "<< m_Collider->Get().y <<" " << m_Collider->Get().w <<" "<< m_Collider->Get().h <<std::endl;
    #endif
    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_Transform->X = m_LastSafePosition.X;
    }
    //move on Y axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += m_RigidBody->Position().Y;
    m_Collider->Set(m_Transform->X, m_Transform->Y, 96, 125);
    #if IS_BOX_DEBUGGABLE == 1
        m_Collider->Set(m_Transform->X+marge_x, m_Transform->Y+marge_y, box_w, box_h);
    #endif
    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
    }else{
        #if IS_COLLISION_DEBUGGABLE == 1
            std::cout << "m_Collider" << m_Collider->Get().x <<" "<< m_Collider->Get().y <<" " << m_Collider->Get().w <<" "<< m_Collider->Get().h <<std::endl;
        #endif
        m_IsGrounded = false;
    }

    m_Origin->X = m_Transform->X + m_Width/2;
    m_Origin->Y = m_Transform->Y + m_Height/2;
    m_Animation->Update();
}

void Demonic::Clean(){
    TextureManager::GetInstance()->Clean();
}
