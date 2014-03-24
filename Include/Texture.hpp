#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>
#include <GL/GL.h>

#include <string>

class Texture
{
public:
	Texture(const std::string& fileName);
	~Texture();

	void bind();

	int getId() const;

public:
	int width;
	int height;

private:
	void generateTexture();
	void setWrapping();
	void setFiltering();
	void generateMipmap();
	unsigned char* loadTextureData();
	void createTexture(unsigned char* textureData);

private:
	std::string m_FileName;

	GLuint m_Texture;

	static int ID;
	int m_Id;
};

#endif