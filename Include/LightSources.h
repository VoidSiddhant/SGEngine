#ifndef _LIGHTSOURCES_H
#define _LIGHTSOURCES_H

#include "Vector.h"
#include "Component.h"

namespace SGEngine
{
	class SGLight : public SGComponent
	{
	public:
		const type_ID GetFamilyID() const {
			return "LightSource";
		}

	private:
		float intensity;
		float range;
		SGVector4 color;
	};

	class SGPointLight : SGLight
	{
	public:
		const type_ID GetMemberID() const {
			return "PointLight";
		}
	};

	class SGDirectionalLight : SGLight
	{
	public:
		const type_ID GetMemberID() const {
			return "DirectionalLight";
		}
	};

	class SGSpotLight : SGLight
	{
	public:
		const type_ID GetMemberID() const {
			return "SpotLight";
		}
	};
}

#endif // !_LIGHTSOURCES_H
