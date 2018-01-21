//
// Created by Piotr Żelazko on 21.01.2018.
//

#include "Workshop.h"


using namespace wrench::graphics::objects;


Workshop::Workshop() {

	vertices_ = {
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top left

			 0.5f,  0.5f, -0.1f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
			 0.5f, -0.5f, -0.1f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
			-0.5f, -0.5f, -0.1f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
			-0.5f,  0.5f, -0.1f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
	};

	indices_ = {
			0, 1, 3,
			1, 2, 3,
	};

	init();

}


void Workshop::draw() {

	DrawableObject::draw();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}
