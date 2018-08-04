#include "PrimitiveShapes.h"

namespace SGEngine
{
SGShapes &SGShapes::instance()
{
    static SGShapes *_instance = new SGShapes();
    return *_instance;
}

void SGShapes::Triangle2D(const SGVector4 &color, Mesh &outMesh)
{
    outMesh.vertex_list = {
        {SGVector3(0.5f, -0.5f, 0.0f), SGVector4(color) , SGVector2(1.0f,0.0f)},
        {SGVector3(-0.5f, -0.5f, 0.0f), SGVector4(color),SGVector2(0.0f,0.0f)},
        {SGVector3(0.0f, 0.5f, 0.0f), SGVector4(color),SGVector2(0.5f,1.0f)}};

    outMesh.index_list = {
        0, 1, 2};
}

void SGShapes::Quad2D(const SGVector4 &color, Mesh &outMesh)
{
    outMesh.vertex_list = {
        {SGVector3(0.5f, -0.5f, 0.0f), SGVector4(color) , SGVector2(1.0f,0.0f)},
        {SGVector3(-0.5f, -0.5f, 0.0f), SGVector4(color), SGVector2(0.0f,0.0f)},
        {SGVector3(-0.5f, 0.5f, 0.0f), SGVector4(color), SGVector2(0.0f,1.0f)},
        {SGVector3(0.5f, 0.5f, 0.0f), SGVector4(color), SGVector2(1.0f,1.0f)}
    };

    outMesh.index_list = {
        0 , 3 , 2 ,
        0 , 1 , 2
    };
}
} // namespace SGEngine
