#include "GameObject.h"
#include <External/GL/glew.h>

namespace SGEngine
{

GameObject::GameObject()
{
    vbo = ebo = 0;
    mesh = nullptr;
}

GameObject::GameObject(const SGVector3 &p, const SGVector3 &s, const Mesh &mesh)
{

    this->mesh = new Mesh(mesh);
    std::cout << sizeof(this->mesh->vertex_list) << std::endl;
    std::cout << sizeof(this->mesh->index_list);
    vbo = ebo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->mesh->vertex_list.size(), &this->mesh->vertex_list[0], GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SG_UINT) * this->mesh->index_list.size(), &this->mesh->index_list[0], GL_STATIC_DRAW);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GameObject::render()
{
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
}

GameObject::~GameObject()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    vbo = ebo = 0;
    delete mesh;
}
} // namespace SGEngine
