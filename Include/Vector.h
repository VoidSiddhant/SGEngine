#ifndef _VECTOR_H
#define _VECTOR_H

#include <glm/glm.hpp>
#include <sstream>

namespace SGEngine
{
class SGVector2
{
public:
  SGVector2();
  SGVector2(const float &x, const float &y);

  void operator=(const SGVector2 &);
  bool operator==(const SGVector2 &);
  SGVector2 operator+(const SGVector2 &);
  void operator+=(const SGVector2 &);
  SGVector2 operator-(const SGVector2 &);
  void operator-=(const SGVector2 &);
  friend std::ostream &operator<<(std::ostream &o, const SGVector2 &v);

  ~SGVector2() {}
  glm::vec2 vector;

private:
};

class SGVector3
{
public:
  SGVector3();
  SGVector3(const float &x, const float &y, const float &z);

  void operator=(const SGVector3 &);
  bool operator==(const SGVector3 &);
  SGVector3 operator+(const SGVector3 &);
  void operator+=(const SGVector3 &);
  SGVector3 operator-(const SGVector3 &);
  void operator-=(const SGVector3 &);
  friend std::ostream &operator<<(std::ostream &o, const SGVector3 &v);

  ~SGVector3() {}

  glm::vec3 vector;

private:
};

class SGVector4
{
public:
  SGVector4();
  SGVector4(const float &x, const float &y, const float &z, const float &w);

  void operator=(const SGVector4 &);
  bool operator==(const SGVector4 &);
  SGVector4 operator+(const SGVector4 &);
  void operator+=(const SGVector4 &);
  SGVector4 operator-(const SGVector4 &);
  void operator-=(const SGVector4 &);
  friend std::ostream &operator<<(std::ostream &o, const SGVector4 &v);

  ~SGVector4() {}
  glm::vec4 vector;

private:
};

} // namespace SGEngine

#endif