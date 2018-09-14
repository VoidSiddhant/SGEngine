#ifndef _CAMERA_H
#define _CAMERA_H

#include "SGUtil.h"
#include "Transform.h"
#include "Vector.h"

namespace SGEngine
{
	class SGCamera
	{
	public:
		SGCamera();
		SGCamera(const SGVector3& position, const SGVector3& rotation);
		SGCamera(const SGTransform& inTransform);
		~SGCamera();

		void UpdateView();
		void UpdateProjection();

		glm::mat4 operator*(const glm::mat4& mat_model);
		glm::mat4 operator*( SGTransform& trans);

	private:
		glm::mat4 mat_view;
		glm::mat4 mat_projection;

		//View Space Transforms
		SGTransform transform;
	};
};
#endif // !_CAMERA_H
