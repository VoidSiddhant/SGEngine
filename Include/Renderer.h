#ifndef _RENDERER_H
#define _RENDERER_H

#include"Component.h"

namespace SGEngine
{
	class SGRenderer : public SGComponent
	{
	public:
		const type_ID& GetFamilyID() const {
			return std::string("Render");
		}

		virtual void Render() = 0;

	private:

	};
}

#endif