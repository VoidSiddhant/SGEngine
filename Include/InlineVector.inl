
/*****************************************************************************************
************************** Possible Unecesarry Stuff ************************************
*****************************************************************************************/

/*

// **********************************	VECTOR2 SPACE		********************************************************************************

SG_INLINE void SGVector2::operator=(const SGVector2 &inVec)
{
	vector = inVec.vector;
}

SG_INLINE bool SGVector2::operator==(const SGVector2 &inVec)
{
	return vector == inVec.vector;
}

SG_INLINE SGVector2& SGVector2::operator+(const SGVector2 &inVec)
{
	vector += inVec.vector;
	return *this;
}

SG_INLINE SGVector2& SGVector2::operator+=(const SGVector2 &inVec)
{
	vector += inVec.vector;
	return *this;
}

SG_INLINE SGVector2& SGVector2::operator-(const SGVector2 &inVec)
{
	vector -= inVec.vector;
	return *this;
}

SG_INLINE SGVector2& SGVector2::operator-=(const SGVector2 &inVec)
{
	vector -= inVec.vector;
	return *this;
}


SG_INLINE std::ostream &operator<<(std::ostream &obj, const SGVector2 &v)
{
	obj << v.vector.x << "," << v.vector.y << std::endl;
	return obj;
}

// **********************************	VECTOR3 SPACE		*********************************************************************************


SG_INLINE void SGVector3::operator=(const SGVector3 &inVec)
{
	vector = inVec.vector;
}

SG_INLINE SGVector3& SGVector3::operator+(const SGVector3 &inVec)
{
	vector += inVec.vector;
	return *this;
}

SG_INLINE SGVector3& SGVector3::operator-(const SGVector3 &inVec)
{
	vector -= inVec.vector;
	return *this;
}

SG_INLINE bool SGVector3::operator==(const SGVector3& inVec)
{
	return vector == inVec.vector;
}

SG_INLINE SGVector3& operator*(const float& inVec)
{
	this->vector *= inVec;
	return *this;
}

SG_INLINE std::ostream &operator<<(std::ostream &o, const SGVector3 &v)
{
	o << v.vector.x << " , " << v.vector.y << " , " << v.vector.z << std::endl;
	return o;
}

//***********************************	VECTOR4 SPACE		*********************************************************************************	

SG_INLINE void SGVector4::operator=(const SGVector4 &inVec)
{
	vector = inVec.vector;
}


SG_INLINE SGVector4& SGVector4::operator+(const SGVector4 &inVec)
{
	vector += inVec.vector;
	return *this;
}

SG_INLINE SGVector4& SGVector4::operator+=(const SGVector4 &inVec)
{
	vector += inVec.vector;
	return *this;
}

SG_INLINE SGVector4& SGVector4::operator-(const SGVector4 &inVec)
{
	vector -= inVec.vector;
	return *this;
}

SG_INLINE SGVector4& SGVector4::operator-=(const SGVector4 &inVec)
{
	vector -= inVec.vector;
	return *this;
}

SG_INLINE bool SGVector4::operator==(const SGVector4& inVec)
{
	return vector == inVec.vector;
}

SG_INLINE std::ostream &operator<<(std::ostream &o, const SGVector4 &v)
{
	o << v.vector.x << " , " << v.vector.y << " , " << v.vector.z << " , " << v.vector.w << std::endl;
	return o;
}
*/