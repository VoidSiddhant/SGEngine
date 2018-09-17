#include "Camera.h"

namespace SGEngine
{
	SGCamera::SGCamera()
	{
		transform.position = { 0.0f,0.0f,0.0f };
		transform.rotation = { 0.0f,0.0f,0.0f };
		this->UpdateProjection();
		this->UpdateView();
	}

	SGCamera::SGCamera(const SGVector3& position, const SGVector3& rotation)
	{
		transform.position = position;
		transform.SetRotation(rotation);
		this->UpdateProjection();
		this->UpdateView();
	}

	SGCamera::SGCamera(const SGTransform& inTransform)
	{
		transform = inTransform;
	}

	void SGCamera::UpdateView()
	{
		
		/*// Keep Camera's axis orthogonal to each other and of unit length
		transform.forwardAxis = glm::normalize(transform.forwardAxis);
		// Calculate ortho-normal up axis
		transform.upAxis = glm::normalize(glm::cross(transform.forwardAxis, transform.rightAxis));

		//Calculate ortho-normal Right Axis
		transform.rightAxis = glm::cross(transform.upAxis, transform.forwardAxis);

		//Calculate the position of the camera including rotations ( Negate the results Camera moves opposite to the world)
		float Qx = -glm::dot(transform.position, transform.rightAxis);
		float Qy = -glm::dot(transform.position, transform.upAxis);
		float Qz = -glm::dot(transform.position, transform.forwardAxis);

		//First Column
		mat_view[0][0] = transform.rightAxis.x;
		mat_view[1][0] = transform.rightAxis.y;
		mat_view[2][0] = transform.rightAxis.z;
		mat_view[3][0] = Qx;

		//Second Column
		mat_view[0][1] = transform.upAxis.x;
		mat_view[1][1] = transform.upAxis.y;
		mat_view[2][1] = transform.upAxis.z;
		mat_view[3][1] = Qy;

		//Third Column
		mat_view[0][2] = transform.forwardAxis.x;
		mat_view[1][2] = transform.forwardAxis.y;
		mat_view[2][2] = transform.forwardAxis.z;
		mat_view[2][2] = Qz;

		//Fourth Column
		mat_view[0][3] = 0.0f;
		mat_view[1][3] = 0.0f;
		mat_view[2][3] = 0.0f;
		mat_view[3][3] = 1.0f;*/


		//mat_view = glm::lookAtLH(transform.position, transform.forwardAxis, transform.upAxis);
		mat_view = glm::inverse(transform.mat_model);
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