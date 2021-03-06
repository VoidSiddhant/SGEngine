#ifndef _RENDERER_H
#define _RENDERER_H

#include "SGUtil.h"
#include"Component.h"

namespace SGEngine
{
	enum class SG_EUpdateFlag : char;
	class SGMaterial;
	class SGRenderer : public SGComponent
	{
	public:
		SGRenderer() {}
		 const type_ID GetFamilyID() const {
			return std::string("Component_Render");
		}

		 virtual void UpdateMaterial(const SG_EUpdateFlag& flag) = 0;
		 virtual void SetMaterial(SG_PTRS<SGMaterial> const new_mat) = 0;
		 virtual SG_PTRS<SGMaterial> GetMaterial() const = 0;

		virtual void Render() = 0;

		virtual ~SGRenderer() {}
	protected:
		SG_PTRS<SGMaterial> material;
	};
}

#endif