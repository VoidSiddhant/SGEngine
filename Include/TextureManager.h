#ifndef _TEXTURE_MANAGER_H
#define _TEXTURE_MANAGER_H

#include"SGUtil.h"
#include "External/GL/glew.h"
#include "External/stb_image.h"

namespace SGEngine
{
	enum class TextureFiltering : int
	{
		TF_LINEAR = GL_LINEAR,
		TF_NEAREST = GL_NEAREST
	};

	enum class TextureWrapMode : int
	{
		WRAP_REPEAT = GL_REPEAT,
		WRAP_CLAMP_EDGE = GL_CLAMP_TO_EDGE,
		WRAP_CLAMP_BORDER = GL_CLAMP_TO_BORDER
	};

	class SGTexture
	{
		friend class SGTextureManager;

	public:
		struct PConfig
		{
			TextureFiltering magFilter, minFilter;
			TextureWrapMode wrapMode;
			bool flipY = false;
		};

	public:
		SGTexture(const char* texturename,const char* filename, const PConfig& config);
		SGTexture(const char* texturename , const char* filename);
		void SetParameters(const PConfig& config);
		~SGTexture();

	private:
		const char* mapName;
		const char* textureFile;
		PConfig configParams;
	};

    class SGTextureManager
    {
        public:
        static SGTextureManager& instance();
        void GenerateTexture(const SGTexture& textureObject,const bool& EnableMipMapLevels= false);
		bool BindTexture(const char* map_name , const SG_UCHAR index);
		void UnBindTexture();
        private:
			SGTextureManager(){}
        ~SGTextureManager(){}

        std::unordered_map<std::string,SG_UINT> _map_tBufferObjects;
    };
}

#endif