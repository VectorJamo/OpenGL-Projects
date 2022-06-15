#pragma once

#include <iostream>
#include <string>
#include "Window.h"
#include "stb_image/stb_image.h"

class Texture
{
private:
	unsigned int _textureID;
	std::string _texturePath;
	int _width, _height, _BPP;
	unsigned char* _LocalBuffer;

public:
	Texture(std::string filePath);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;
};