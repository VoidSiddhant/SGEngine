#include "Material.h"
#include "ShaderManager.h"
#include "Mesh.h"

namespace SGEngine
{
	SGMaterial::SGMaterial()
	{

	}

	SGMaterial::~SGMaterial()
	{
		delete activeShader;
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &vao);
	}

	void SGMaterial::BindVAO() const
	{
		glBindVertexArray(vao);
	}

	void SGMaterial::UnBindVAO() const
	{
		glBindVertexArray(0);
	}

	void SGMaterial::Initialize(Shader* shader)
	{
		activeShader = shader;
		SGShaderManager::instance().Create(*shader);
		SGShaderManager::instance().EnableProgram(shader->shaderProgramName);
		glGenVertexArrays(1, &vao);
		this->BindVAO();
		SG_UINT offsetBytes = 0;
		for (Shader::ShaderAttributeInfo attribInfo : shader->vector_sai)
		{
			offsetBytes = static_cast<SG_UINT>(attribInfo._shaderVariable._variable)*sizeof(SGVector3);
			SGShaderManager::instance().EnableAttribute(attribInfo._shaderVariable._variable
														, sizeof(SGVertex), offsetBytes, false);
		}
		this->UnBindVAO();
	}

	void SGMaterial::SetShader(Shader* const shader)
	{
		activeShader = shader;
	}
}