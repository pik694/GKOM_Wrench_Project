//
// Created by Piotr Żelazko on 21.01.2018.
//

#include "Texture.h"

#include "SOIL/SOIL.h"

using namespace wrench::graphics;

Texture::Texture(const std::string &textureFile) {

	int width, height;

	auto image = SOIL_load_image(textureFile.c_str(), &width, &height, 0, SOIL_LOAD_AUTO);

	if (image == nullptr)
		throw std::runtime_error("Could not open texture");

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	textureID_ = texture;


}


GLuint Texture::getTextureID() {
	return textureID_;
}
