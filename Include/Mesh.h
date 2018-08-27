#ifndef _MESH_H
#define _MESH_H

#include "Renderer.h"

namespace SGEngine
{

	struct MeshFilter
	{
		std::vector<Vertex> vertex_list;
		std::vector<SG_UINT> index_list;

		MeshFilter(const Mesh& copyMesh)
		{
			vertex_list = copyMesh.vertex_list;
			index_list = copyMesh.index_list;
		}
	};

	class SGMeshRenderer : SGRenderer
	{
	public :

		const type_ID& GetMemberID() const {
			return type_ID("Mesh");
		}

		void Render():

	private:

	};
}
#endif // !_MESH_H
