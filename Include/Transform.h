#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Vector.h"

namespace SGEngine
{
	class SGCamera;

	class SGTransform{
		friend class SGGameObject;
		friend class SGCamera;
        public :
			SGTransform();
			SGTransform(const SGVector3& position,const SGVector3& scale);

			void SetRotation(const SGVector3& value);
			void SetScale(const SGVector3& value);
			void SetPosition(const SGVector3& value);
			void Translate(const SGVector3& value);
			void Rotate(const SGVector3& value);
			SGMat4 operator*(SGCamera& cam);

			~SGTransform() {}

	private:
		void UpdateModel();

        public:
        SGVector3 position,scale,rotation;

	private:
		SGVector3 rightAxis, upAxis, forwardAxis;
		glm::mat4 mat_model;
    };
} // SGEngine

#endif