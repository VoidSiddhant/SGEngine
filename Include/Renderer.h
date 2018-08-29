#ifndef _RENDERER_H
#define _RENDERER_H

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

		virtual void Render() = 0;

		virtual ~SGRenderer() {}
	protected:
		SGMaterial material;
	};
}

#endif