#include "PrimitiveShapes.h"

namespace SGEngine
{
SGShapes &SGShapes::instance()
{
    static SGShapes *_instance = new SGShapes();
    return *_instance;
}

void SGShapes::Triangle2D(const SGVector4 &color, SGMeshFilter &outMesh)
{
    outMesh.vertex_list = {
        {SGVector3(0.5f, -0.5f, 0.0f), SGVector4(color) , SGVector2(1.0f,0.0f)},
        {SGVector3(-0.5f, -0.5f, 0.0f), SGVector4(color),SGVector2(0.0f,0.0f)},
        {SGVector3(0.0f, 0.5f, 0.0f), SGVector4(color),SGVector2(0.5f,1.0f)}};

    outMesh.index_list = {
        0, 1, 2};

	outMesh.SetVertexCount(3);
	outMesh.SetIndexCount(3);
}

void SGShapes::Quad2D(const SGVector4 &color, SGMeshFilter &outMesh)
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
	outMesh.SetVertexCount(4);
	outMesh.SetIndexCount(6);
}

void SGShapes::Cube(const SGVector4& color, SGMeshFilter& outMesh)
{
	outMesh.vertex_list = {
		/*      Front Facing          */
	{ SGVector3(0.5f, -0.5f, -0.5f), SGVector4(color) , SGVector2(1.0f,0.0f) },  // Bottom-Right
	{ SGVector3(-0.5f, -0.5f, -0.5f), SGVector4(color), SGVector2(0.0f,0.0f) },  // Bottom-Left
	{ SGVector3(-0.5f, 0.5f, -0.5f), SGVector4(color), SGVector2(0.0f,1.0f)  },	// Top-Left
	{ SGVector3(0.5f, 0.5f, -0.5f), SGVector4(color), SGVector2(1.0f,1.0f)   },	// Top-Right
		
		/*     Back Facing			*/
	{ SGVector3(0.5f, -0.5f, 0.5f), SGVector4(color) , SGVector2(1.0f,0.0f) },  // Bottom-Right
	{ SGVector3(-0.5f, -0.5f, 0.5f), SGVector4(color), SGVector2(0.0f,0.0f) },  // Bottom-Left
	{ SGVector3(-0.5f, 0.5f, 0.5f), SGVector4(color), SGVector2(0.0f,1.0f) },	// Top-Left
	{ SGVector3(0.5f, 0.5f, 0.5f), SGVector4(color), SGVector2(1.0f,1.0f) },	// Top-Right
	};

	outMesh.index_list = {
			/* Front Facing  */
		0,1,2,
		0,2,3,

		//Back Facing
		6,5,4,
		6,4,7,

		//Left Facing
		1,5,6,
		1,6,2,

		//Right Facing
		4,0,3,
		4,3,7,

		//Up Facing
		3,2,6,
		3,6,7,

		//Down Facing
		0,5,1,
		0,4,5
	};

	outMesh.SetVertexCount(8);
	outMesh.SetIndexCount(36);
}
} // namespace SGEngine
