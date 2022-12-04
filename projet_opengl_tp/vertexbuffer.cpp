#include "vertexbuffer.h"
#include "renderer.h"

unsigned int VertexBuffer::getSize() const
{
    return size;
}

unsigned int VertexBuffer::getCount() const
{
    return count;
}

VertexBuffer::VertexBuffer(const std::vector<glm::vec3> &data): size(data.size()*sizeof(glm::vec3))
{
    count = size/sizeof(data[0]);
    (glGenBuffers(1, &m_rendererID));
    (glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
    (glBufferData(GL_ARRAY_BUFFER,size, &data[0], GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    (glDeleteBuffers(1,&m_rendererID));
}

void VertexBuffer::Bind(int index) const{
    (glEnableVertexAttribArray(index));
    (glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
    (glVertexAttribPointer(
       index,                  // l'index du point à modifier.
       3,                  // taille d'un point
       GL_FLOAT,           // type de valeur
       GL_FALSE,           // normalisation?
       0,                  // taille des valeurs supplémentaires dans le vertexbuffer
       (void*)0            // offset : est-ce qu'on commence à un autre indice que 0
    ));
}

void VertexBuffer::Unbind() const{
    (glBindBuffer(GL_ARRAY_BUFFER, 0));
}
