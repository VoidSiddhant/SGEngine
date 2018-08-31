#include "Mesh.h"
#include "ShaderManager.h"
namespace SGEngine
{
	SGMeshFilter::SGMeshFilter()
	{
		vertex_list.resize(0);
		index_list.resize(0);
		vertexCount = indexCount = 0;
	}
	SGMeshFilter::SGMeshFilter(SGMeshFilter& copyMesh)
	{
		vertex_list = copyMesh.vertex_list;
		index_list = copyMesh.index_list;
	}

	void SGMeshFilter::SetVertexCount(const SG_UINT count)
	{
		vertexCount = count;
	}
	void SGMeshFilter::SetIndexCount(const SG_UINT count)
	{
		indexCount = count;
	}

	SGMeshRenderer::SGMeshRenderer(SGMeshFilter mesh_copy,SG_PTRS<SGMaterial> mat)
	{
		material = mat;

		this->mesh = mesh_copy;
		vao = vbo = ebo = 0;
		glGenVertexArrays(1, &vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(SGVertex)*mesh.vertex_list.size(), &mesh.vertex_list[0], GL_STATIC_DRAW);
		
		// BUILD VAO OF THIS OBJECT USING THIS MATERIAL
		material->BuildVAO(vao);

		material->BindVAO(vao);
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SG_UINT)*mesh.index_list.size(), &mesh.index_list[0], GL_STATIC_DRAW);
		
		material->UnBindVAO();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void SGMeshRenderer::Render()
	{
		SGShaderManager::instance().EnableProgram(material->GetShaderName());
		material->BindVAO(vao);
	}

	void SGMeshRenderer::AddMesh(const SGMeshFilter mesh_copy)
	{
		mesh = mesh_copy;
	}

	SGMeshRenderer::~SGMeshRenderer()
	{
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
		glDeleteBuffers(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
		vao = vbo = ebo = 0;
	}
}