#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Vector.h"

namespace SGEngine
{
    class SGTransform{
        public :
			SGTransform();
			SGTransform(SGVector3 position, SGVector3 scale);

			void SetRotation(const SGVector3 value);
			void SetScale(const SGVector3 value);
			void SetPosition(const SGVector3 value);
			
			~SGTransform() {}

        protected:
        SGVector3 position,scale,rotation;
    };
} // SGEngine


#endif