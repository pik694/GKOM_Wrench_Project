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

void Screw::draw(){

    DrawableObject::draw();

	glm::mat4 model;
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::mat4 view1;
	view1 = glm::translate(view1, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 1.0f , 0.1f, 100.0f);

	projection = projection * view1 * model * transformation_;


    glUniformMatrix4fv(
            glGetUniformLocation(programID_, "transform"),
            1,
            GL_FALSE,
            glm::value_ptr(projection)
    );

    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
    
}

void Screw::rotate(float degree) {
    transformation_ = glm::rotate(transformation_, glm::radians(degree), glm::vec3(0,0,1));
}


