#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Vector.h"

namespace SGEngine
{
    class Transform{
        public :
        Transform(){}
		~Transform();

        protected:
        SGVector3 position,scale,rotation;
    };
} // SGEngine


#endif