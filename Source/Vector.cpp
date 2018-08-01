#include "Vector.h"

//#0F111A

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

void SGVector2::operator=(const SGVector2 &inVec)
{
    vector.x = inVec.vector.x; // What an idiot i am
    vector.y = inVec.vector.y;
}

bool SGVector2::operator==(const SGVector2 &inVec)
{
    if (vector.x == inVec.vector.x && vector.y == inVec.vector.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

SGVector2 SGVector2::operator+(const SGVector2 &inVec)
{
    SGVector2 outVec;
    outVec.vector.x = vector.x + inVec.vector.x;
    outVec.vector.y = vector.y + inVec.vector.y;
    return outVec;
}

void SGVector2::operator+=(const SGVector2 &inVec)
{
    vector.x += inVec.vector.x;
    vector.y += inVec.vector.y;
}

SGVector2 SGVector2::operator-(const SGVector2 &inVec)
{
    SGVector2 outVec;
    outVec.vector.x = vector.x - inVec.vector.x;
    outVec.vector.y = vector.y - inVec.vector.y;
    return outVec;
}

void SGVector2::operator-=(const SGVector2 &inVec)
{
    vector.x -= inVec.vector.x;
    vector.y -= inVec.vector.y;
}

std::ostream& operator<<(std::ostream& obj , const SGVector2& v)
{
    obj << v.vector.x << ","<<v.vector.y<<std::endl;
    return obj;
}

SGVector3::SGVector3()
{
    vector = {0.0f, 0.0f, 0.0f};
}

SGVector3::SGVector3(const float &x, const float &y, const float &z)
{
    vector = {x, y, z};
}

void SGVector3::operator=(const SGVector3 &inVec)
{
    vector.x = inVec.vector.x;
    vector.y = inVec.vector.y;
    vector.z = inVec.vector.z;
}

SGVector3 SGVector3::operator+(const SGVector3 &inVec)
{
    SGVector3 outVec = {
        vector.x + inVec.vector.x,
        vector.y + inVec.vector.y,
        vector.z + inVec.vector.z};
    return outVec;
}

SGVector3 SGVector3::operator-(const SGVector3 &inVec)
{
    SGVector3 outVec = {
        vector.x - inVec.vector.x,
        vector.y - inVec.vector.y,
        vector.z - inVec.vector.z};
    return outVec;
}

std::ostream& operator<<(std::ostream& o , const SGVector3& v)
{
    o<<v.vector.x << " , "<<v.vector.y<<" , "<<v.vector.z<<std::endl;
    return o;
}

SGVector4::SGVector4()
{
    vector = {0.0f, 0.0f, 0.0f, 0.0f};
}

SGVector4::SGVector4(const float &x, const float &y, const float &z, const float &w)
{
    vector = {x, y, z, w};
}

void SGVector4::operator=(const SGVector4 &inVec)
{
    vector.x = inVec.vector.x;
    vector.y = inVec.vector.y;
    vector.z = inVec.vector.z;
    vector.w = inVec.vector.w;
}

SGVector4 SGVector4::operator+(const SGVector4 &inVec)
{
    SGVector4 outVec = {
        vector.x + inVec.vector.x,
        vector.y + inVec.vector.y,
        vector.z + inVec.vector.z,
        vector.w + inVec.vector.w};

    return outVec;
}

void SGVector4::operator+=(const SGVector4 &inVec)
{
    vector.x += inVec.vector.x;
    vector.y += inVec.vector.y;
    vector.z += inVec.vector.z;
    vector.w += inVec.vector.w;
}

SGVector4 SGVector4::operator-(const SGVector4 &inVec)
{
    SGVector4 outVec = {
        vector.x - inVec.vector.x,
        vector.y - inVec.vector.y,
        vector.z - inVec.vector.z,
        vector.w - inVec.vector.w};

    return outVec;
}

void SGVector4::operator-=(const SGVector4 &inVec)
{
    vector.x -= inVec.vector.x;
    vector.y -= inVec.vector.y;
    vector.z -= inVec.vector.z;
    vector.w -= inVec.vector.w;
}

std::ostream& operator<<(std::ostream& o , const SGVector4& v)
{
    o<<v.vector.x<<" , "<<v.vector.y<<" , "<<v.vector.z<<" , "<<v.vector.w<<std::endl;
    return o;
}

} // namespace SGEngine
