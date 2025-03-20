#include "TextureManager.h"
#include "Engine.h"

TextureManager* TextureManager::s_Instance = nullptr;

/** @brief Load
  *
  * @todo: document this function
  */
bool TextureManager::Load(std::string id, std::string filename){
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if(surface == nullptr){
        SDL_Log("Failed to load the texture: %s, %s", filename.c_str(),SDL_GetError());
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if(texture == nullptr){
        SDL_Log("Failed to create texture from the surface: %s", SDL_GetError());
        return false;
    }

    m_TextureMap[id]= texture; // Texture loaded successfully
    return true;
}

/** @brief Draw
  *
  * @todo: document this function
  */
void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip){
    SDL_Rect srcRect = {0, 0, width, height};//source defined
    SDL_Rect dstRect = {x, y, width, height};//destination defined
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);

}

/** @brief Drop
  *
  * @todo: document this function
  */
void TextureManager::Drop(std::string id){
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id); //texture is destroyed but not removed; erase it (no need to put that in memory anymore).
}

/** @brief Clean
  *
  * @todo: document this function
  */
void TextureManager::Clean(){
    std::map<std::string, SDL_Texture*>::iterator it;
    for(it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
    {
        SDL_DestroyTexture(it->second);
    }
    m_TextureMap.clear();

    SDL_Log("texture map cleaned");

}
