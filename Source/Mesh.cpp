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

	SGMeshRenderer::SGMeshRenderer(SGMeshFilter mesh_copy,Shader* const shader)
	{
		this->mesh = mesh_copy;
		vbo = ebo = 0;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(SGVertex)*mesh.vertex_list.size(), &mesh.vertex_list[0], GL_STATIC_DRAW);

		material.Initialize(shader);
		material.BindVAO();

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SG_UINT)*mesh.index_list.size(), &mesh.index_list[0], GL_STATIC_DRAW);
		
		material.UnBindVAO();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void SGMeshRenderer::Render()
	{
		SGShaderManager::instance().EnableProgram(material.GetShaderName());
		material.BindVAO();
	}

	void SGMeshRenderer::AddMesh(const SGMeshFilter mesh_copy)
	{
		mesh = mesh_copy;
	}

	SGMeshRenderer::~SGMeshRenderer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
		vbo = ebo = 0;
	}
}