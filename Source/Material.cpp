#include "Material.h"
#include "ShaderManager.h"
#include "Mesh.h"
#include "UUIDGenerator.h"

namespace SGEngine
{
	SGMaterial::SGMaterial(std::string material_name)
	{
		name = material_name;
		SGUUIDGenerator::instance().Create(uuid);
		activeShader = nullptr;
	}

	SGMaterial::~SGMaterial()
	{

	}

	void SGMaterial::BindVAO(const SG_UINT& vao) const
	{
		glBindVertexArray(vao);
	}

	void SGMaterial::UnBindVAO() const
	{
		glBindVertexArray(0);
	}

	void SGMaterial::Initialize() const
	{
		// Generate Shader data
		SGMaterialManager::instance().Create(uuid,*activeShader);
		// Set Active shader program , to reflect any changes
//		SGMaterialManager::instance().EnableProgram(activeShader->shaderProgramName);
	}

	void SGMaterial::BuildVAO(const SG_UINT& vao) const
	{
//		SGMaterialManager::instance().EnableProgram(activeShader->shaderProgramName);
		this->BindVAO(vao);
		SG_UINT offsetBytes = 0;
		for (Shader::ShaderAttributeInfo attribInfo : activeShader->vector_sai)
		{
			offsetBytes = static_cast<SG_UINT>(attribInfo._shaderVariable._variable) * sizeof(SGVector3);
			SGMaterialManager::instance().EnableAttribute(uuid,attribInfo._shaderVariable._variable
				, sizeof(SGVertex), offsetBytes, false);
		}
		this->UnBindVAO();
	}

	void SGMaterial::SetShader(SG_PTRS<Shader> const shader)
	{
		activeShader = shader;
		std::cout << "Material name : " << name << " id : " << uuid << "Active Shader : "<<activeShader->shaderProgramName <<std::endl;
		this->Initialize();
	}
}