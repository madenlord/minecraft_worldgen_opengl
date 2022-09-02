#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture
{
    private:
        unsigned int _rendererID;
        std::string _filepath;
        unsigned char* _localBuffer;
        int _width, _height, _BPP;


    public:
        Texture(const std::string& path);
        ~Texture();

        void bind(unsigned int slot = 0) const;
        void unbind() const;

        int getWidth() const { return _width; }
        int getHeight() const { return _height; }
};

#endif