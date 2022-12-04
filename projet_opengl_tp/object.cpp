#include "object.h"

#include <iostream>
#include "renderer.h"
#include "glm/gtx/transform.hpp"

#include <exception>




Object::Object(std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, const char* texturePath) :m_vb(0), m_uvsb(0), position(0, 0, 0), rotationAngles(0, 0, 0)
{
     m_vb = new VertexBuffer(vertices);
     m_uvsb = new UVBuffer(uvs);
     m_texture = new Texture(texturePath);
}


Object::~Object()
{
    delete m_vb;
    if (m_uvsb) delete m_uvsb;
    if (m_texture) delete m_texture;
}

void Object::Bind() const
{
    m_vb->Bind(0);
    if (m_uvsb) m_uvsb->Bind(1);
    if (m_texture) m_texture->bind(0);
}

void Object::Unbind() const
{
    m_vb->Unbind();
    if (m_uvsb) m_uvsb->Unbind();
    if (m_texture) m_texture->unbind();
}



void Object::Draw() const
{
    (glDrawArrays(GL_TRIANGLES,0, m_vb->getSize()));
}

glm::mat4 Object::getModelMatrix()
{
    glm::mat4 m = glm::rotate(glm::translate(glm::mat4(1), position), rotationAngles.x, glm::vec3(1,0,0));
    m=glm::rotate(m, rotationAngles.y, glm::vec3(0,1,0));
    m=glm::rotate(m, rotationAngles.z, glm::vec3(0,0,1));
    return m;
}

glm::vec3 Object::moveObjectPosition(float t, int x, int y, int h )
{
    int radius = 50;
    float centerCircleX = 246.0;
    float centerCircleY = 246.0;
    float posX = centerCircleX + radius * cos(t);
    float posY = centerCircleY + radius * sin(t);
    int posZ = h + 5;
    return glm::vec3(posX, posZ, posY);

}