#include "Mesh.h"
#include "Material.h"
#include "UUIDGenerator.h"

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

	void SGMeshRenderer::SetMaterial(SG_PTRS<SGMaterial> const new_mat)
	{
		material = new_mat;
		this->UpdateMaterial(SG_EUpdateFlag::MaterialUpdate);
	}

	void SGMeshRenderer::UpdateMaterial(const SG_EUpdateFlag& flag)
	{
		switch (flag)
		{
		case SG_EUpdateFlag::MaterialUpdate:
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

			material->BuildVAO(vao);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			break;

		case SG_EUpdateFlag::ColorUpdate:

			break;
		}
	}

	SGMeshRenderer::SGMeshRenderer(SGMeshFilter mesh_copy,SG_PTRS<SGMaterial> mat)
	{
		using namespace std::placeholders;
		SGUUIDGenerator::instance().Create(uuid);
		material = mat;
		auto rc = std::bind(&SGRenderer::UpdateMaterial, this,_1);
		material->RegisterComponent(uuid,rc);

		this->mesh = mesh_copy;
		vao = vbo = ebo = 0;
		glGenVertexArrays(1, &vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		
		for (auto it = mesh.vertex_list.begin(); it != mesh.vertex_list.end(); it++)
		{
			it->color = material->color;
		}

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
		material->RenderBegin(vao);                                 // Configure GPU device for this material
		int indexCount = mesh.index_list.size();
		glDrawElements(GL_TRIANGLES,indexCount, GL_UNSIGNED_INT, 0);
		material->RenderEnd();										// Free device configuration
	}

	void SGMeshRenderer::SetMesh(const SGMeshFilter mesh_copy)
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
		
		material->UnRegisterComponent(uuid);
		uuid = 0;
	}
}