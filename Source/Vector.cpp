#include "Vector.h"

namespace SGEngine
{

SGVector2::SGVector2()
{
    vector = {0.0f, 0.0f};
}

SGVector2::SGVector2(const float &x, const float &y)
{
    vector = {x, y};
}

SGVector3::SGVector3()
{
    vector = {0.0f, 0.0f, 0.0f};
}

SGVector3::SGVector3(const float &x, const float &y, const float &z)
{
    vector = {x, y, z};
}

SGVector4::SGVector4()
{
    vector = {0.0f, 0.0f, 0.0f, 0.0f};
}

SGVector4::SGVector4(const float &x, const float &y, const float &z, const float &w)
{
    vector = {x, y, z, w};
}

} // namespace SGEngine