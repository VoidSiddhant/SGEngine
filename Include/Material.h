#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "SGUtil.h"
#include "Shader.h"
#include <External/GL/glew.h>

namespace SGEngine
{
	class SGMaterial
	{
	public:
		SGMaterial();
		~SGMaterial();

		void Initialize(Shader* shader);
		void SetShader(Shader*const shader);
		std::string GetShaderName()  {
			return activeShader->shaderProgramName;
		}
		void BindVAO() const;
		void UnBindVAO() const;

	private:
		Shader * activeShader;
		SG_UINT vao;
	};
};

#endif // !_MATERIAL_H
