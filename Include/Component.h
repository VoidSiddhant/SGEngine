#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "SGUtil.h"

namespace SGEngine
{
	class SGGameObject;

	class SGComponent
	{
	public:
		using type_ID = std::string;

		virtual const type_ID& GetFamilyID() = 0;
		virtual const type_ID& GetMemberID() = 0;
		virtual void Update() = 0;

		void SetOwnerGO(const SGGameObject* go) {
			ownerGo = go;
		}

		const SGGameObject* GetOwnerGO() const {
			return ownerGo;
		}


	private:
		const SGGameObject * ownerGo;
	};
}

#endif // !_COMPONENT_H
