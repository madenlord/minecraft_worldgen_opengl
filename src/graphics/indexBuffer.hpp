#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

class IndexBuffer 
{
    private:
        unsigned int _rendererID;
        unsigned int _count;

    public:
        IndexBuffer(const unsigned int* data, unsigned int count);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;

        unsigned int getCount() const { return _count; }
};

#endif