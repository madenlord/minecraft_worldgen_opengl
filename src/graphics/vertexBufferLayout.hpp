#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#include <glad/glad.h>
#include <vector>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getSizeOfType(unsigned int type)
    {
        switch(type)
        {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
        }
        
        return 0;
    }
};

namespace pushtemp
{
    template<typename T>
    void push(unsigned int count, std::vector<VertexBufferElement>& elements, unsigned int* stride) {}

    template<>
    inline void push<float>(unsigned int count, std::vector<VertexBufferElement>& elements, unsigned int* stride)
    {
        elements.push_back({ GL_FLOAT, count, GL_FALSE });
        *stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
    }

    template<>
    inline void push<unsigned int>(unsigned int count, std::vector<VertexBufferElement>& elements, unsigned int* stride)
    {
        elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
        *stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
    }

    template<>
    inline void push<unsigned char>(unsigned int count, std::vector<VertexBufferElement>& elements, unsigned int* stride)
    {
        elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
        *stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
    }
}

class VertexBufferLayout
{
    private:
        std::vector<VertexBufferElement> mElements;
        unsigned int mStride;

    public:
        VertexBufferLayout()
            : mStride(0) {}
        
        
        template<typename T>
        void push(unsigned int count)
        {
            pushtemp::push<T>(count, mElements, &mStride);
        }
        
        const std::vector<VertexBufferElement> getElements() const { return mElements; }
        unsigned int getStride() const { return mStride; } 
};

#endif