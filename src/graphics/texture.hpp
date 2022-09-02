#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture
{
    private:
        unsigned int mRendererID;
        std::string mFilepath;
        unsigned char* mLocalBuffer;
        int mWidth, mHeight, mBPP;


    public:
        Texture(const std::string& path);
        ~Texture();

        void bind(unsigned int slot = 0) const;
        void unbind() const;

        int getWidth() const { return mWidth; }
        int getHeight() const { return mHeight; }
};

#endif