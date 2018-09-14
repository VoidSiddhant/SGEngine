#include "Camera.h"

namespace SGEngine
{
	SGCamera::SGCamera()
	{
		transform.position = { 0.0f,0.0f,0.0f };
		transform.rotation = { 0.0f,0.0f,0.0f };
	}

	SGCamera::SGCamera(const SGVector3& position, const SGVector3& rotation)
	{
		transform.position = position;
		transform.SetRotation(rotation);
	}

	SGCamera::SGCamera(const SGTransform& inTransform)
	{
		transform = inTransform;
	}

	void SGCamera::UpdateView()
	{
		glm::mat4 translate(1.0f);
		translate = glm::translate(translate, SGVector3(0.0f,0.0f,3.0f));
		mat_view = translate;
	}

	void SGCamera::UpdateProjection()
	{
		mat_projection = glm::perspectiveFovLH(glm::radians(45.0f), (float)SG_UTIL_SCREEN_WIDTH , (float)SG_UTIL_SCREEN_HEIGHT, 0.1f, 100.0f);
	}

	glm::mat4 SGCamera::operator*(const glm::mat4& mat_model)
	{
		return mat_projection * mat_view * mat_model;
	}

	glm::mat4 SGCamera::operator*(SGTransform& trans)
	{
		return trans * (*this);
	}

	SGCamera::~SGCamera()
	{

	}
}