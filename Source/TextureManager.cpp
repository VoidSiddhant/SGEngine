#include "TextureManager.h"

namespace SGEngine
{
    TextureManager& TextureManager::instance()
    {
        static TextureManager* _instance = new TextureManager();
        return *_instance;
    }

    void TextureManager::GenerateTexture(const char* file)
    {
        textures
    }
}