#include "TextureManager.h"
#include "FileWriter.h"

namespace SGEngine
{
	SGTexture::SGTexture(const char* texturename,const char* filename)
	{
		mapName = texturename;
		textureFile = filename;
		configParams.flipY = false;
		configParams.magFilter = TextureFiltering::TF_LINEAR;
		configParams.minFilter = TextureFiltering::TF_LINEAR;
		configParams.wrapMode = TextureWrapMode::WRAP_REPEAT;
	}

	SGTexture::SGTexture(const char* texturename,const char* filename, const PConfig& config)
	{
		mapName = texturename;
		textureFile = filename;
		configParams = config;
	}

	void SGTexture::SetParameters(const PConfig& config)
	{
		configParams = config;
	}

	SGTexture::~SGTexture()
	{
	}

	SGTextureManager& SGTextureManager::instance()
    {
        static SGTextureManager* _instance = new SGTextureManager();
        return *_instance;
    }

	bool SGTextureManager::BindTexture(const char* map_name ,const SG_UCHAR index)
	{
#ifdef _DEBUG
		SGFileWriter logger("BuildLog.text");
		logger << "Binding Texture : " << map_name << "\n";
#endif // _DEBUG

		try
		{
			auto it = _map_tBufferObjects.find(map_name);
			if (it == _map_tBufferObjects.end())
			{
				return false;
			}
			else
			{
				// Bind the texture at this texture unit
				glActiveTexture(GL_TEXTURE0 + index);
				glBindTexture(GL_TEXTURE_2D, it->second);
				return true;
			}
		}
		catch (...)
		{
#ifdef _DEBUG
			logger << "Exception thrown at :" << __FUNCTION__<<"\nBinding Texture : " << map_name << "\n Did you create?\n";
			std::cout << "Failed to Bind Texture : " << map_name;
#endif // _DEBUG
			return false;
		}
	}

	void SGTextureManager::UnBindTexture()
	{
		for (SG_UCHAR index = 0; index < 16; index++)
		{
			glActiveTexture(GL_TEXTURE0 + index);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

    void SGTextureManager::GenerateTexture(const SGTexture& textureObject, const bool& EnableMipMapLevels)
    {
#ifdef _DEBUG
		SGFileWriter logger("BuildLog.text");
		logger << "Generating Texture for File : " << textureObject.textureFile<<"\n";
#endif // _DEBUG

		SG_UINT tbo = 0;
		glGenTextures(1, &tbo);
		glBindTexture(GL_TEXTURE_2D, tbo);

		//Set up texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)textureObject.configParams.magFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)textureObject.configParams.minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)textureObject.configParams.wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)textureObject.configParams.wrapMode);
		stbi_set_flip_vertically_on_load(textureObject.configParams.flipY);

		//load and generate the texture
		int width, height, nrChannels;
		unsigned char* data = stbi_load(textureObject.textureFile, &width, &height,&nrChannels,0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,GL_RGB, GL_UNSIGNED_BYTE, data);
			if(EnableMipMapLevels)
				glGenerateMipmap(GL_TEXTURE_2D);
			//Store reference of Texture Buffer Object
			_map_tBufferObjects.insert(std::pair<std::string, SG_UINT>(textureObject.mapName, tbo));
		}
		else
		{
#ifdef _DEBUG
			logger << "Could not load data  : " << textureObject.textureFile<<std::endl;
			std::cout << "Error Loading Texture Data\n";
#endif // _DEBUG
		}

		// Unbind buffer , free image data from memory
		glBindTexture(GL_TEXTURE_2D,0);
		stbi_image_free(data);
    }
}