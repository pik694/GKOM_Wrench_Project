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
         0.0f,     0.1f,   0.0f,     0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         0.0866f,  0.05f,  0.0f,     0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         0.0866f, -0.05f,  0.0f,     0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         0.0f,    -0.1f,   0.0f,     0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -0.0866f, -0.05f,  0.0f,     0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -0.0866f,  0.05f,  0.0f,     0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    };
    
    indices_ = {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5
    };
    
    init();

}

void Screw::draw(){

    DrawableObject::draw();

    glUniformMatrix4fv(
            glGetUniformLocation(programID_, "transform"),
            1,
            GL_FALSE,
            glm::value_ptr(transformation_)
    );

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
    
}

void Screw::rotate(float degree) {
    transformation_ = glm::rotate(transformation_, glm::radians(degree), glm::vec3(0,0,1));
}


