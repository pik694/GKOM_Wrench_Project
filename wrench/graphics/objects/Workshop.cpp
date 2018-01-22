//
// Created by Piotr Żelazko on 21.01.2018.
//

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Workshop.h"


using namespace wrench::graphics::objects;


Workshop::Workshop() {

	model_ = glm::scale(model_, glm::vec3(2,1.5,0.5));

	vertices_ = {
			// positions          // texture coords
			 1.0f,  1.0f, 0.0f,      0.95f, 0.95f, // top right
			 1.0f, -1.0f, 0.0f,      0.95f, 0.05f, // bottom right
			 -1.0f, -1.0f, 0.0f,      0.05f, 0.05f, // bottom left
			 -1.0f,  1.0f, 0.0f,      0.05f, 0.95f,  // top left

			 1.0f,  1.0f, -0.1f,     1.0f, 1.0f,
			 1.0f, -1.0f, -0.1f,     1.0f, 0.0f,
			-1.0f, -1.0f, -0.1f,     0.0f, 0.0f,
			-1.0f,  1.0f, -0.1f,     0.0f, 1.0f,
	};
	indices_ = {
			0, 1, 2,
			0, 2, 3,
			0,4,5,
			0,5,1,
			1,5,6,
			1,6,2,
			2,6,7,
			2,7,3,
			3,7,4,
			3,4,0
	};

	init();

}


void Workshop::draw(glm::mat4 view) {

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
