#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "SGUtil.h"
#include "Mesh.h"
#include "ShaderManager.h"
#include <External/GL/glew.h>

namespace SGEngine
{
	class SGTexture;

	class SGMaterial
	{
		friend class SGMeshRenderer;

	public:
		SGMaterial(std::string material_name);
		~SGMaterial();

		/****************************************************************************************************************
		******************************	SHADER HANDLERS *****************************************************************
		*****************************************************************************************************************/
		void SetColor(const SGVector4& color);
		SGVector4 GetColor() const {
			return color;
		}
		void SetShader(SG_PTRS<Shader>const shader);
		std::string GetShaderName()  {
			return activeShader->shaderProgramName;
		}
							/* MODIFY UNIFORMS OF ACTIVE SHADER */
		template<typename UniformData>
		void SetUniform(const Shader_Uniform& uniform_name, const UniformData& data);


		/****************************************************************************************************************
		******************************	TEXTURE HANDLERS ********************************************************************
		*****************************************************************************************************************/

		void SetTexture(const char* name, const SG_UCHAR index);
		void RemoveTexture(const char* name);
		void RemoveTexture(const SG_UCHAR& index);
		const char* GetTextureName( const SG_UCHAR& index) {
			return _map_textures[index];
		}

		/****************************************************************************************************************
		******************************	UNIQUE ID GET ********************************************************************
		*****************************************************************************************************************/

		const long int& GetUUID() const {
			return uuid;
		}

	private:
		SGMaterial() {}

		/****************************************************************************************************************
		******************************	VERTEX BUFFER HANDLERS **********************************************************
		*****************************************************************************************************************/

		void BuildVAO(const SG_UINT& vao) const;
		void BindVAO(const SG_UINT& vao) const;
		void UnBindVAO() const;

		/****************************************************************************************************************
		******************************	TEXTURE HANDLERS ********************************************************************
		*****************************************************************************************************************/
		void BindTexture();

		/****************************************************************************************************************
		******************************	RENDER COMPONENT HANDLERS *****************************************************************
		*****************************************************************************************************************/
		using RCUpdateMethod =  std::function<void (const SG_EUpdateFlag&)>;
		using MapRCUCallbacks = std::unordered_map<SG_UUID, RCUpdateMethod>;
		void RegisterComponent(const SG_UUID& uuid, RCUpdateMethod method);
		void UnRegisterComponent(const SG_UUID& uuid);

		void RenderBegin(const SG_UINT& vao);
		void RenderEnd();

		/****************************************************************************************************************
		******************************	DATA ****************************************************************************
		*****************************************************************************************************************/
		
		SG_PTRS<Shader> activeShader;
		SG_UUID uuid;
		std::string name;
		std::unordered_map<SG_UCHAR, const char*> _map_textures;
		SGVector4 color;
		MapRCUCallbacks map_renderCompCallbacks;
	};

#include "Material.inl"

};

#endif // !_MATERIAL_H