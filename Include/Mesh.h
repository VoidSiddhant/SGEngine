#ifndef _MESH_H
#define _MESH_H

#include "Renderer.h"
#include "Vector.h"
#include "Material.h"
#include "External/GL/glew.h"

namespace SGEngine
{
	struct SGVertex {
		SGVector3 position;
		SGVector4 color;
		SGVector2 texCoord;
	};
	struct SGMeshFilter
	{
		std::vector<SGVertex> vertex_list;
		std::vector<SG_UINT> index_list;

		explicit SGMeshFilter();
		SGMeshFilter(SGMeshFilter& copyMesh);

		void SetVertexCount(const SG_UINT count);
		void SetIndexCount(const SG_UINT count);

		SG_UINT GetVertexCount() const {
			return vertexCount;
		}
		SG_UINT GetIndexCount() const {
			return indexCount;
		}

		//Operator Overloads
		SG_INLINE SGMeshFilter& operator=(const SGMeshFilter& copy)
		{
			vertex_list = copy.vertex_list;
			index_list = copy.index_list;
			return *this;
		}

	private:
		SG_UINT vertexCount,indexCount;
	};

	using PMesh = SGMeshFilter * ;

	class SGMeshRenderer : public SGRenderer
	{
	public :

		explicit SGMeshRenderer(SGMeshFilter mesh_copy,SG_PTRS<SGMaterial> material);
		~SGMeshRenderer();

		void SetMesh(const SGMeshFilter mesh_copy);
		const PMesh GetMesh() {
			return &mesh;
		}

		/*****************************************************************/
		/****************	Virtual Override  ****************************/
		/*****************************************************************/
		
		const type_ID GetMemberID() const {
			return type_ID("Component_MeshRenderer");
		}

		void Update() {}   // TRICKY
		void Render();
		void UpdateMaterial();
		void SetMaterial(SG_PTRS<SGMaterial> const new_mat);
		SG_PTRS<SGMaterial> GetMaterial() const {
			return material;
		}

	private:
		SGMeshFilter mesh;
		SG_UINT vbo, ebo,vao;
	};
}
#endif // !_MESH_H
