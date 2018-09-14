#include "Transform.h"
#include "Camera.h"

namespace SGEngine
{
	SGTransform::SGTransform()
	{
		this->position = { 0.0f,0.0f,0.0f };
		this->rotation = { 0.0f,0.0f,0.0f };
		this->scale = { 1.0f,1.0f,1.0f };

		this->UpdateModel();
	}

	SGTransform::SGTransform(const SGVector3& position,const SGVector3& scale)
	{
		this->position = position;
		this->scale = scale;
		this->rotation = { 0.0f,0.0f,0.0f };
		
		this->UpdateModel();
	}

	void SGTransform::SetScale(const SGVector3& value)
	{
		this->scale = value;
		this->UpdateModel();
	}

	void SGTransform::SetPosition(const SGVector3& value)
	{
		this->position = value;
		this->UpdateModel();
	}

	void SGTransform::SetRotation(const SGVector3& value)
	{
		this->rotation = value;
		this->UpdateModel();
	}

	void SGTransform::Rotate(const SGVector3& value)
	{
		this->rotation += value;
		this->UpdateModel();
	}

	void SGTransform::Translate(const SGVector3& value)
	{
		position += value;
		this->UpdateModel();
	}

	void SGTransform::UpdateModel()
	{
		glm::mat4 world(1.0f);
		world = glm::scale(world, scale);
		world = glm::rotate(world, glm::radians(rotation.x), SGVector3(1.0f, 0.0f, 0.0f));
		world = glm::rotate(world, glm::radians(rotation.y), SGVector3(0.0f, 1.0f, 0.0f));
		world = glm::rotate(world, glm::radians(rotation.z), SGVector3(0.0f, 0.0f, 1.0f));
		mat_model = glm::translate(world, position);
	}

	SGMat4 SGTransform::operator*(SGCamera& cam)
	{
		return cam * mat_model;
	}

}