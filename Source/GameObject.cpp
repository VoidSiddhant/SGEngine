#include "GameObject.h"
#include <GL/glew.h>

namespace SGEngine
{
GameObject::GameObject()
{
    SGVector2 v,v2,v3;
    v3 = v+v2;
    std::cout<<v3;
    vao = vbo = ebo = 0;
    mesh = nullptr;
}

GameObject::GameObject(const SGVector3 &p, const SGVector3 &s, const Mesh &mesh)
{
    this->mesh = new Mesh(mesh);
    std::cout << sizeof(this->mesh->vertex_list) << std::endl;
    std::cout << sizeof(this->mesh->index_list);
    vao = vbo = ebo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->mesh->vertex_list.size(), &this->mesh->vertex_list[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(sizeof(SGVector3)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SG_UINT) * this->mesh->index_list.size(), &this->mesh->index_list[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GameObject::render()
{
    glBindVertexArray(vao);
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
    glDeleteVertexArrays(1,&vao);
    vbo = vao = ebo = 0;
    delete mesh;
}
} // namespace SGEngine
