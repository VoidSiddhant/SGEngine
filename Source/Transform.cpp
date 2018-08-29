#include "Transform.h"

namespace SGEngine
{
	SGTransform::SGTransform()
	{
		this->position = { 0.0f,0.0f,0.0f };
		this->scale = { 1.0f,1.0f,1.0f };
	}

	SGTransform::SGTransform(SGVector3 position, SGVector3 scale)
	{
		this->position = position;
		this->scale = scale;
	}

	void SGTransform::SetScale(const SGVector3 value)
	{
		this->scale = value;
	}

	void SGTransform::SetPosition(const SGVector3 value)
	{
		this->position = value;
	}

	void SGTransform::SetRotation(const SGVector3 value)
	{
		this->rotation;
	}
}