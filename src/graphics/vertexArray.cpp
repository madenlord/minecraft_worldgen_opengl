#include "vertexArray.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &mRendererID);
    glBindVertexArray(mRendererID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &mRendererID);
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    vb.bind();
    const std::vector<VertexBufferElement> elements = layout.getElements();
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, 
                                element.normalized, layout.getStride(), (const void*) offset);
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}

void VertexArray::bind() const
{
    glBindVertexArray(mRendererID);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}
