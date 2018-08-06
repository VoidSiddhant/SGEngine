
SG_INLINE void SGVector2::operator=(const SGVector2 &inVec)
{
    vector.x = inVec.vector.x; // What an idiot i am
    vector.y = inVec.vector.y;
}

SG_INLINE bool SGVector2::operator==(const SGVector2 &inVec)
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

SG_INLINE SGVector2 SGVector2::operator+(const SGVector2 &inVec)
{
    SGVector2 outVec;
    outVec.vector.x = vector.x + inVec.vector.x;
    outVec.vector.y = vector.y + inVec.vector.y;
    return outVec;
}

SG_INLINE void SGVector2::operator+=(const SGVector2 &inVec)
{
    vector.x += inVec.vector.x;
    vector.y += inVec.vector.y;
}

SG_INLINE SGVector2 SGVector2::operator-(const SGVector2 &inVec)
{
    SGVector2 outVec;
    outVec.vector.x = vector.x - inVec.vector.x;
    outVec.vector.y = vector.y - inVec.vector.y;
    return outVec;
}

SG_INLINE void SGVector2::operator-=(const SGVector2 &inVec)
{
    vector.x -= inVec.vector.x;
    vector.y -= inVec.vector.y;
}

SG_INLINE std::ostream &operator<<(std::ostream &obj, const SGVector2 &v)
{
    obj << v.vector.x << "," << v.vector.y << std::endl;
    return obj;
}

SG_INLINE void SGVector3::operator=(const SGVector3 &inVec)
{
    vector.x = inVec.vector.x;
    vector.y = inVec.vector.y;
    vector.z = inVec.vector.z;
}

SG_INLINE SGVector3 SGVector3::operator+(const SGVector3 &inVec)
{
    SGVector3 outVec = {
        vector.x + inVec.vector.x,
        vector.y + inVec.vector.y,
        vector.z + inVec.vector.z};
    return outVec;
}

SG_INLINE SGVector3 SGVector3::operator-(const SGVector3 &inVec)
{
    SGVector3 outVec = {
        vector.x - inVec.vector.x,
        vector.y - inVec.vector.y,
        vector.z - inVec.vector.z};
    return outVec;
}

SG_INLINE std::ostream &operator<<(std::ostream &o, const SGVector3 &v)
{
    o << v.vector.x << " , " << v.vector.y << " , " << v.vector.z << std::endl;
    return o;
}

SG_INLINE void SGVector4::operator=(const SGVector4 &inVec)
{
    vector.x = inVec.vector.x;
    vector.y = inVec.vector.y;
    vector.z = inVec.vector.z;
    vector.w = inVec.vector.w;
}

SG_INLINE SGVector4 SGVector4::operator+(const SGVector4 &inVec)
{
    SGVector4 outVec = {
        vector.x + inVec.vector.x,
        vector.y + inVec.vector.y,
        vector.z + inVec.vector.z,
        vector.w + inVec.vector.w};

    return outVec;
}

SG_INLINE void SGVector4::operator+=(const SGVector4 &inVec)
{
    vector.x += inVec.vector.x;
    vector.y += inVec.vector.y;
    vector.z += inVec.vector.z;
    vector.w += inVec.vector.w;
}

SG_INLINE SGVector4 SGVector4::operator-(const SGVector4 &inVec)
{
    SGVector4 outVec = {
        vector.x - inVec.vector.x,
        vector.y - inVec.vector.y,
        vector.z - inVec.vector.z,
        vector.w - inVec.vector.w};

    return outVec;
}

SG_INLINE void SGVector4::operator-=(const SGVector4 &inVec)
{
    vector.x -= inVec.vector.x;
    vector.y -= inVec.vector.y;
    vector.z -= inVec.vector.z;
    vector.w -= inVec.vector.w;
}

SG_INLINE std::ostream &operator<<(std::ostream &o, const SGVector4 &v)
{
    o << v.vector.x << " , " << v.vector.y << " , " << v.vector.z << " , " << v.vector.w << std::endl;
    return o;
}