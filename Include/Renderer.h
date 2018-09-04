#ifndef _RENDERER_H
#define _RENDERER_H

#include "SGUtil.h"
#include "Material.h"
#include"Component.h"

namespace SGEngine
{
	class SGRenderer : public SGComponent
	{
	public:
		SGRenderer() {}
		 const type_ID GetFamilyID() const {
			return std::string("Component_Render");
		}

		 virtual void UpdateMaterial() = 0;
		 virtual void SetMaterial(SG_PTRS<SGMaterial> const new_mat) = 0;
		 virtual SG_PTRS<SGMaterial> GetMaterial() const = 0;

		virtual void Render() = 0;

		virtual ~SGRenderer() {}
	protected:
		SG_PTRS<SGMaterial> material;
	};
}

#endif