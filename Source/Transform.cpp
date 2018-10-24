#include "Transform.h"
#include "Camera.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "External/glm/gtx/rotate_vector.hpp"
namespace SGEngine
{
	SGTransform::SGTransform()
	{
		this->position = { 0.0f,0.0f,0.0f };
		this->rotation = { 0.0f,0.0f,0.0f };
		this->scale = { 1.0f,1.0f,1.0f };
		rightAxis = { 1.0f,0.0f,0.0f };
		upAxis = { 0.0f,1.0f,0.0f };
		forwardAxis = { 0.0f,0.0f,1.0f };
		this->UpdateModel();
	}

	SGTransform::SGTransform(const SGVector3& position,const SGVector3& scale)
	{
		this->position = position;
		this->scale = scale;
		this->rotation = { 0.0f,0.0f,0.0f };
		rightAxis = { 1.0f,0.0f,0.0f };
		upAxis = { 0.0f,1.0f,0.0f };
		forwardAxis = { 0.0f,0.0f,1.0f };
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
		mat_model = glm::rotate(mat_model, glm::radians(value.x), SGVector3(1.0f, 0.0f, 0.0f));
		mat_model = glm::rotate(mat_model, glm::radians(value.y), SGVector3(0.0f, 1.0f, 0.0f));
		mat_model = glm::rotate(mat_model, glm::radians(value.z), SGVector3(0.0f, 0.0f, 1.0f));
	}

	void SGTransform::Rotate(const SGVector3& value)
	{
		this->rotation += value;

		//Update Rotation Axis (Local Space)
		glm::rotateX(upAxis, rotation.x);
		glm::rotateX(forwardAxis, rotation.x);

		glm::rotateY(rightAxis, rotation.y);
		glm::rotateY(forwardAxis, rotation.y);

		glm::rotateZ(upAxis, rotation.z);
		glm::rotateZ(rightAxis, rotation.z);

		mat_model = glm::rotate(mat_model, glm::radians(value.x), SGVector3(1.0f,0.0f,0.0f));
		mat_model = glm::rotate(mat_model, glm::radians(value.y), SGVector3(0.0f, 1.0f, 0.0f));
		mat_model = glm::rotate(mat_model, glm::radians(value.z), SGVector3(0.0f, 0.0f, 1.0f));

		//this->UpdateModel();
	}

	void SGTransform::Translate(const SGVector3& value)
	{
		position += value;
		mat_model = glm::translate(mat_model, value);
		//this->UpdateModel();
	}

	void SGTransform::UpdateModel()
	{
		glm::mat4 world(1.0f);

		world = glm::scale(world, scale);
		world = glm::rotate(world, glm::radians(rotation.x), rightAxis);
		world = glm::rotate(world, glm::radians(rotation.y), upAxis);
		world = glm::rotate(world, glm::radians(rotation.z), forwardAxis);
		world = glm::translate(world, position);

		mat_model = world;
	}

	SGMat4 SGTransform::operator*(SGCamera& cam)
	{
		return cam * mat_model;
	}

}