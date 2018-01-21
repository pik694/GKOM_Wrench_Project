//
//  ShaderProgram.hpp
//  GKOM_OpenGL_Project
//
//  Created by Piotr Żelazko on 09.12.2017.
//  Copyright © 2017 Piotr Żelazko. All rights reserved.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <iostream>
#include <utility>
#include <GL/glew.h>

namespace wrench {
	namespace graphics {
		class ShaderProgram {
		public:
			ShaderProgram(const std::string &vertexShaderPath,
			              const std::string &fragmentShaderPath);

			GLuint getProgramID();

			void use();

		private:
			GLuint linkProgram();

			std::pair<GLuint, GLuint> compileShaders();

			GLuint compileShader(const std::string &shaderCode, const GLenum &shaderType);

			std::string getShaderSourceCode(const std::string &shaderPath);

			const std::string vertexShaderPath_;
			const std::string fragmentShaderPath_;
			GLuint programID_;

		};
	}
}

#endif /* ShaderProgram_hpp */
