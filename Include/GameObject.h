#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H
#include "Vector.h"
#include "SGUtil.h"
//#include "Renderer.h"

//#include "Transform.h"
namespace SGEngine
{
    struct Vertex{
        SGVector3 position;
        SGVector4 color;
        SGVector2 texCoord;
    };
    struct Mesh
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
	};

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
        SG_UINT vbo,ebo;
    };
}

#endif

/*
	struct SGMesh{}
	class SGGameObject;

	class SGComponent                           // Base Component Interface
	{
		public:
		SGGOComponent() : ownerGO(nullptr);
		virtual ~SGGOComponent() = 0 {}
		
		virtual const std::string& getComponentID() const = 0;
		virtual const std::string& getFamilyID() const = 0;

		virtual void update();
		void setOwner(const GameObject* go) const = 0;
		const SGGameObject& getOwner() const { return *ownerGO};
		private:
		SGGameObject* ownerGO;
	}

	class SGRenderer : SGGOComponent                // Component Family for Rendering
	{
	public:
		std::string family_id;
		virtual void render() = 0;
	}

	class SGLineRenderer : SGRenderer		// Member of the component family : renderer 
	{
	struct Points{}
		virtual void render() const;
	}

	class SGTrailRenderer: SGRenderer
	{
		struct Vectors{}
	}

	class SGMeshRenderer : SGRenderer	 // Member of the component family : renderer
	{
		struct Mesh{}
	}
	

	class SGGameObject : SGTransform
	{
		public :
		AddComponent(const SGComponent*);
		RemoveComponent(std::string component_type_id);

		private:
		map<const std::string component_type_id,SGComponent*> map_components  // Add MeshRenderer
	}

*/