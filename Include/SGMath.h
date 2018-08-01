#ifndef _SGMATH_H
#define _SGMATH_H
#include <glm/glm.hpp>
namespace SGEngine
{
    template<typename T>
    class Vector
    {
        public:
        static Vector& instance();
                      
        void dot(T vector1 , T vector2) {
            
        }
        void cross(T vector1 , T vector2);

        ~Vector();
        private :
        Vector();

    };
}

#endif