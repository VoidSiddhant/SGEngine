#ifndef _SHAPES_H
#define _SHAPES_H
#include "Mesh.h"
namespace SGEngine
{
class SGShapes
{
  public:
    static SGShapes& instance();
    void Triangle2D(const SGVector4& color, SGMeshFilter& outMesh);
    void Quad2D(const SGVector4& color , SGMeshFilter& outMesh);
  private:
    SGShapes(){}
    ~SGShapes(){}
};
} // namespace SGEngine

#endif