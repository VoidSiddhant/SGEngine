#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H
#include "Vector.h"
#include "SGUtil.h"
//#include "Transform.h"
namespace SGEngine
{
    struct Vertex{
        SGVector3 position;
        SGVector4 color;
        SGVector2 texCoord;
    };
   typedef struct Mesh
    {
        std::vector<Vertex> vertex_list;      
        std::vector<SG_UINT> index_list;

        Mesh()
        {

        }

        Mesh(const Mesh& copyMesh)
        {
            vertex_list = copyMesh.vertex_list;
            index_list = copyMesh.index_list;
        }
    }* PMesh;

    typedef Mesh* PMesh;

    class GameObject
    {
        public:
        GameObject();
        GameObject(const SGVector3& position , const SGVector3& scale ,const Mesh& mesh);
        ~GameObject();

        void render();
        private:
        PMesh mesh;
        SG_UINT vao,vbo,ebo;
        
    };
}

#endif