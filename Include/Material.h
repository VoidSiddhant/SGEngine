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

		void SetShader(SG_PTRS<Shader>const shader);
		std::string GetShaderName()  {
			return activeShader->shaderProgramName;
		}

		void BuildVAO(const SG_UINT& vao) const;
		void BindVAO(const SG_UINT& vao) const;
		void UnBindVAO() const;

	private:

		void Initialize() const;
		SG_PTRS<Shader> activeShader;
	};
};

#endif // !_MATERIAL_H
