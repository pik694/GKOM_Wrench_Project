//
// Created by Piotr Żelazko on 22.01.2018.
//

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Wall.h"


using namespace wrench::graphics::objects;

Wall::Wall() {

	model_ = glm::scale(model_, glm::vec3(2,1.5,2));

	vertices_ = {
			1.0f,  1.0f, 0.0f,      0.0f, 1.0f,
		   -1.0f,  1.0f, 0.0f,      1.0f, 1.0f,
		    1.0f,  1.0f, 1.0f,      0.0f, 0.0f,
		   -1.0f,  1.0f, 1.0f,      1.0f, 0.0f,
	};

	indices_ = {
			0,1,2,
			1,2,3
	};


	init();
}

void Wall::draw(glm::mat4 view) {

	DrawableObject::draw();


	glUniformMatrix4fv(
			glGetUniformLocation(programID_, "model"),
			1,
			GL_FALSE,
			glm::value_ptr(model_)
	);

	glUniformMatrix4fv(
			glGetUniformLocation(programID_, "view"),
			1,
			GL_FALSE,
			glm::value_ptr(view)
	);


	glDrawElements(GL_TRIANGLES, (GLsizei) indices_.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);


}
