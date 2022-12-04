
#include <GL/glew.h>

#include <iostream>
class Texture
{
public:
	Texture(const char* TextureIMageFilePath);
	~Texture();
	void bind(GLuint slot);
	void unbind();
	int GetWidth() { return this->textureWidth; };
	int GetHeight() { return this->textureHeight; };

private:
	GLuint textureID;
	int textureWidth;
	int textureHeight;
	int textureNbChannel;

};

