#include "Material.h"
#include "UUIDGenerator.h"
#include "TextureManager.h"

namespace SGEngine
{
	SGMaterial::SGMaterial(std::string material_name)
	{
		name = material_name;
		color = SGVector4(1.0f, 1.0f, 1.0f, 1.0f);
		SGUUIDGenerator::instance().Create(uuid);
		activeShader = nullptr;
	}

	void SGMaterial::RegisterComponent(const SG_UUID& object_uuid, RCUpdateMethod method)
	{
		map_renderCompCallbacks.insert(MapRCUCallbacks::value_type(object_uuid,method));
	}

	void SGMaterial::UnRegisterComponent(const SG_UUID& object_uuid)
	{
		for (auto it = map_renderCompCallbacks.begin(); it != map_renderCompCallbacks.end(); it++)
		{
			if (it->first == object_uuid)
			{
				map_renderCompCallbacks.erase(it->first);
			}
		}
	}

	void SGMaterial::SetColor(const SGVector4& value)
	{
		color = value;

	}

	SGMaterial::~SGMaterial()
	{

	}

	void SGMaterial::BindVAO(const SG_UINT& vao) const
	{
		glBindVertexArray(vao);
	}

	void SGMaterial::BindTexture()
	{
		auto it = _map_textures.begin();

		for( ; it!= _map_textures.end(); it++)
		{
			bool success = SGTextureManager::instance().BindTexture(it->second, it->first);
			if (!success)
			{
				std::cout << "Create the Texture before binding : " << uuid << std::endl << it->second;
			}
		}
	}

	void SGMaterial::UnBindVAO() const
	{
		glBindVertexArray(0);
	}

	void SGMaterial::BuildVAO(const SG_UINT& vao) const
	{
		this->BindVAO(vao);
		SG_UINT offsetBytes = 0;
		SG_UINT prevDataSize = 0;
		for (Shader::ShaderAttributeInfo attribInfo : activeShader->vector_sai)
		{
			offsetBytes =  prevDataSize  * sizeof(float);
			std::cout << "START OF FUNCTION : " <<__FUNCTION__ << std::endl;
			std::cout << "**********************************************************************\n";
			std::cout << attribInfo._strName <<" : "<<offsetBytes << " : " << sizeof(SGVertex) <<"\n";
			std::cout << "**********************************************************************\n";
			std::cout << "END OF FUNCTION : " << __FUNCTION__ << std::endl;
			SGMaterialManager::instance().EnableAttribute(uuid,attribInfo._shaderVariable._variable
				, sizeof(SGVertex), offsetBytes, false);
			prevDataSize += attribInfo._dataSize;
		}
		this->UnBindVAO();
	}

	void SGMaterial::SetShader(SG_PTRS<Shader> const shader)
	{
		activeShader = shader;
		std::cout << "START OF FUNCTION : " << __FUNCTION__ << std::endl;
		std::cout << "Material name : " << name << " id : " << uuid << "Active Shader : "<<activeShader->shaderProgramName <<std::endl;
		std::cout << "END OF FUNCTION : " << __FUNCTION__ << std::endl;
		// Generate Shader data
		SGMaterialManager::instance().Create(uuid, *activeShader);
		// Update all the RendererComponents using this material ( ReBuild- VAOs)
		for (auto it = map_renderCompCallbacks.begin(); it != map_renderCompCallbacks.end(); it++)
		{
			it->second(SG_EUpdateFlag::MaterialUpdate);
		}
	}

	void SGMaterial::SetTexture(const char* name , const SG_UCHAR index)
	{
		_map_textures.insert(std::pair<SG_UCHAR, const char*>(index , name));
	}

	void SGMaterial::RemoveTexture(const char* name)
	{
		auto it = _map_textures.begin();
		while (it != _map_textures.end())
		{
			if (it->second == name)
			{
				_map_textures.erase(it->first);
				break;
			}
			it++;
		}
	}

	void SGMaterial::RemoveTexture(const SG_UCHAR& index)
	{
		_map_textures.erase(index);
	}

	void SGMaterial::RenderBegin(const SG_UINT& vao)
	{
		SGMaterialManager::instance().EnableProgram(this->GetUUID());
		this->BindTexture();
		this->BindVAO(vao);
	}

	void SGMaterial::RenderEnd()
	{
		this->UnBindVAO();
		//this->BindTexture(); // Unbind Texture here
	}
}