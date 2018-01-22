//
// Created by Piotr Żelazko on 21.01.2018.
//

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Workshop.h"


using namespace wrench::graphics::objects;


Workshop::Workshop() {

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
			0, 1, 3,
			1, 2, 3,
			0, 1, 4,
			1, 4, 5,
			1, 2, 6,
			1, 5, 6,
			2, 3, 6,
			7, 3, 6,
			7, 3, 4,
			3, 0, 4,
	};

	init();

}


void Workshop::draw() {

	DrawableObject::draw();


	float radius = 1.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

	glm::mat4 model;
	model = glm::rotate(model, glm::radians(-70.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 view1;
// note that we're translating the scene in the reverse direction of where we want to move
	view1 = glm::translate(view1, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 1.0f , 0.1f, 5.0f);

	glUniformMatrix4fv(
			glGetUniformLocation(programID_, "model"),
			1,
			GL_FALSE,
			glm::value_ptr(model)
	);
	glUniformMatrix4fv(
			glGetUniformLocation(programID_, "view"),
			1,
			GL_FALSE,
			glm::value_ptr(view1)
	);

	glUniformMatrix4fv(
			glGetUniformLocation(programID_, "projection"),
			1,
			GL_FALSE,
			glm::value_ptr(projection)
	);


	glDrawElements(GL_TRIANGLES, (GLsizei) indices_.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
