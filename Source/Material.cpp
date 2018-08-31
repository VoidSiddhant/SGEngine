#include "Material.h"
#include "ShaderManager.h"
#include "Mesh.h"

namespace SGEngine
{
	SGMaterial::SGMaterial()
	{
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
		SGShaderManager::instance().Create(*activeShader);
		// Set Active shader program , to reflect any changes
		SGShaderManager::instance().EnableProgram(activeShader->shaderProgramName);
	}

	void SGMaterial::BuildVAO(const SG_UINT& vao) const
	{
		SGShaderManager::instance().EnableProgram(activeShader->shaderProgramName);
		this->BindVAO(vao);
		SG_UINT offsetBytes = 0;
		for (Shader::ShaderAttributeInfo attribInfo : activeShader->vector_sai)
		{
			offsetBytes = static_cast<SG_UINT>(attribInfo._shaderVariable._variable) * sizeof(SGVector3);
			SGShaderManager::instance().EnableAttribute(attribInfo._shaderVariable._variable
				, sizeof(SGVertex), offsetBytes, false);
		}
		this->UnBindVAO();
	}

	void SGMaterial::SetShader(SG_PTRS<Shader> const shader)
	{
		activeShader = shader;
		this->Initialize();
	}
}