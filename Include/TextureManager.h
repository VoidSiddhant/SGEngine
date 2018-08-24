#ifndef _TEXTURE_MANAGER_H
#define _TEXTURE_MANAGER_H
#include"SGUtil.h"

namespace SGEngine
{
    class TextureManager
    {
        public:
        static TextureManager& instance();
        void GenerateTexture(const char* file);
        private:
        TextureManager(){}
        ~TextureManager(){}

        std::vector<unsigned int> textures;
    };
}

#endif