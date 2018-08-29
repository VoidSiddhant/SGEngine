#include "GameObject.h"
#include <External/GL/glew.h>
#include "FileWriter.h"
#include "Renderer.h"

namespace SGEngine
{

SGGameObject::SGGameObject()
{
	transform = new SGTransform();
	name = "";
}

SGGameObject::SGGameObject(const SGVector3 &p, const SGVector3 &s,std::string go_name)
{
	transform = new SGTransform(p, s);
	name = go_name;
}

void SGGameObject::AddComponent(SGComponent* component)
{
#ifdef _DEBUG
	SGFileWriter logger("BuildLog.txt");
#endif // _DEBUG

	const std::string name = component->GetMemberID();
	auto it = _map_component.find(name);
	if (it == _map_component.end())
	{
#ifdef _DEBUG
		logger << "Adding Component : " << name << std::endl;
#endif // _DEBUG

		_map_component.insert(std::pair<std::string,SGComponent*>(name, component));
	}
	else
	{
#ifdef _DEBUG
		SGFileWriter logger("BuildLog.txt");
		logger << "Component Already Exist : " << name << std::endl;
#endif // _DEBUG
	}
}

void SGGameObject::Render()
{
	auto it = _map_component.begin();
	while (it != _map_component.end())
	{
		SGRenderer* rComp = dynamic_cast<SGRenderer*>(it->second);
		if (rComp != nullptr)
		{
			rComp->Render();
		}
		it++;
	}
}

SGGameObject::~SGGameObject()
{
	auto it = _map_component.begin();
	while (it != _map_component.end())
	{
		delete it->second;
		it++;
	}

	delete transform;
}
} // namespace SGEngine
