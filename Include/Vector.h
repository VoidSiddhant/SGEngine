#ifndef _VECTOR_H
#define _VECTOR_H

#include "SGUtil.h"
#include <glm/glm.hpp>
#include <sstream>

namespace SGEngine
{
class SGVector2
{
public:
  SGVector2();
  SGVector2(const SGVector2 &v)
  {
    this->vector.x = v.vector.x;
    this->vector.y = v.vector.y;
  }
  SGVector2(const float &x, const float &y);

  SG_INLINE void operator=(const SGVector2 &);
  SG_INLINE bool operator==(const SGVector2 &);
  SG_INLINE SGVector2 operator+(const SGVector2 &);
  SG_INLINE void operator+=(const SGVector2 &);
  SG_INLINE SGVector2 operator-(const SGVector2 &);
  SG_INLINE  void operator-=(const SGVector2 &);
  SG_INLINE friend std::ostream &operator<<(std::ostream &o, const SGVector2 &v);

  ~SGVector2() {}
  glm::vec2 vector;

private:
};

class SGVector3
{
public:
  SGVector3();
  SGVector3(const SGVector3 &v)
  {
    this->vector.x = v.vector.x;
    this->vector.y = v.vector.y;
    this->vector.z = v.vector.z;
  }
  SGVector3(const float &x, const float &y, const float &z);

  SG_INLINE void operator=(const SGVector3 &);
  SG_INLINE bool operator==(const SGVector3 &);
  SG_INLINE SGVector3 operator+(const SGVector3 &);
  SG_INLINE void operator+=(const SGVector3 &);
  SG_INLINE SGVector3 operator-(const SGVector3 &);
  SG_INLINE void operator-=(const SGVector3 &);
  SG_INLINE friend std::ostream &operator<<(std::ostream &o, const SGVector3 &v);

  ~SGVector3() {}

  glm::vec3 vector;

private:
};

class SGVector4
{
public:
  SGVector4();
  SGVector4(const SGVector4 &v)
  {
    this->vector.x = v.vector.x;
    this->vector.y = v.vector.y;
    this->vector.z = v.vector.z;
    this->vector.w = v.vector.w;
  }
  SGVector4(const float &x, const float &y, const float &z, const float &w);

  SG_INLINE void operator=(const SGVector4 &);
  SG_INLINE bool operator==(const SGVector4 &);
  SG_INLINE SGVector4 operator+(const SGVector4 &);
  SG_INLINE void operator+=(const SGVector4 &);
  SG_INLINE SGVector4 operator-(const SGVector4 &);
  SG_INLINE void operator-=(const SGVector4 &);
  SG_INLINE friend std::ostream &operator<<(std::ostream &o, const SGVector4 &v);

  ~SGVector4() {}
  glm::vec4 vector;

private:
};
#include "InlineVector.inl"
} // namespace SGEngine
#endif