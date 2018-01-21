//
// Created by Piotr Żelazko on 21.01.2018.
//

#ifndef GKOM_WRENCH_TEXTURE_H
#define GKOM_WRENCH_TEXTURE_H

#include <GL/glew.h>
#include <string>

namespace wrench {
	namespace graphics {

		class Texture {
		public:

			Texture(const std::string& textureFile);

			GLuint getTextureID();

			~Texture() = default;

		private:
			GLuint textureID_;
		};
	}
}


#endif //GKOM_WRENCH_TEXTURE_H
