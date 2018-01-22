//
//  Screw.cpp
//  GKOM_Wrench
//
//  Created by Piotr Żelazko on 21.01.2018.
//  Copyright © 2018 Piotr Żelazko. All rights reserved.
//

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Screw.hpp"


using namespace wrench::graphics::objects;

Screw::Screw(){

	model_ = glm::scale(model_, glm::vec3(1,1,5));

    vertices_ = {
         0.0f,     0.1f,   0.01f,    0.0f, 0.0f,
         0.0866f,  0.05f,  0.01f,    0.0f, 0.0f,
         0.0866f, -0.05f,  0.01f,    0.0f, 0.0f,
         0.0f,    -0.1f,   0.01f,    0.0f, 0.0f,
        -0.0866f, -0.05f,  0.01f,    0.0f, 0.0f,
        -0.0866f,  0.05f,  0.01f,    0.0f, 0.0f,

         0.0f,     0.1f,   0.0f,     0.0f, 0.0f,
         0.0866f,  0.05f,  0.0f,     0.0f, 0.0f,
         0.0866f, -0.05f,  0.0f,     0.0f, 0.0f,
         0.0f,    -0.1f,   0.0f,     0.0f, 0.0f,
        -0.0866f, -0.05f,  0.0f,     0.0f, 0.0f,
        -0.0866f,  0.05f,  0.0f,     0.0f, 0.0f,

    };

    indices_ = {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,

        0,1,6,
        1,6,7,
        2,3,9,
        2,8,9,
        1,2,7,
        2,7,8,
        3,9,10,
        3,4,10,
        5,10,11,
        4,5,10,
        0,5,6,
        5,6,11,

        6,7,8,
        6,8,9,
        6,9,10,
        6,10,11

    };

    init();

}

void Screw::draw(glm::mat4 view){

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

	glm::vec3 colour (0,1,0);

	glUniform3fv(
		glGetUniformLocation(programID_, "objectColour"),
		1,
		glm::value_ptr(colour)
	);

    glDrawElements(GL_TRIANGLES, (GLsizei) indices_.size(), GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
    
}

void Screw::rotate(float degree) {
    model_ = glm::rotate(model_, glm::radians(degree), glm::vec3(0,0,1));
}


