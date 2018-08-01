#ifndef _SHAPES_H
#define _SHAPES_H

#include "Vector.h"
#include "GameObject.h"
namespace SGEngine
{
class SGShapes
{
  public:
    static SGShapes& instance();
    void Triangle2D(const SGVector4& color, Mesh& outMesh);
    void Quad2D(const SGVector4& color , Mesh& outMesh);
  private:
    SGShapes(){}
    ~SGShapes(){}
};
} // namespace SGEngine

#endif