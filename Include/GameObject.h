#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H
#include "Vector.h"
#include "SGUtil.h"
//#include "Renderer.h"
#include "Component.h"
#include <unordered_map>
#include "Transform.h"
namespace SGEngine
{
    class SGGameObject
    {
		public:
			SGTransform transform;
			std::string name;
		//Methods
        public:
        SGGameObject();
        SGGameObject(const SGVector3& position , const SGVector3& scale,std::string GameObjectName);
        ~SGGameObject();

		void Render();
		virtual void Update(float dt) {};

		void AddComponent(SGComponent* component);
		SGComponent* GetComponent(std::string component_id) const {
			return _map_component.at(component_id);
		}
        private:

			std::unordered_map<std::string, SGComponent*> _map_component;
    };
}

#endif
