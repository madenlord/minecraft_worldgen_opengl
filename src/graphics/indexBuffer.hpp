#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <vector>

class IndexBuffer 
{
    private:
        unsigned int _rendererID;
        unsigned int _count;

    public:
        IndexBuffer(const std::vector<unsigned int>& indices);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;

        unsigned int getCount() const { return _count; }
};

#endif