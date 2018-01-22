//
//  DrawableObject.cpp
//  GKOM_Wrench
//
//  Created by Piotr Żelazko on 21.01.2018.
//  Copyright © 2018 Piotr Żelazko. All rights reserved.
//

#include "DrawableObject.hpp"

using namespace wrench::graphics::objects;


DrawableObject::DrawableObject(){
    
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);
    glGenVertexArrays(1, &VAO_);
    
}

void DrawableObject::init() {

    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), vertices_.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLuint), indices_.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)) );
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void DrawableObject::setTexture(GLuint textureID){
    textureID_ = textureID;
}


void DrawableObject::setShaders(GLuint shadersProgramID){
    programID_ = shadersProgramID;
}

void DrawableObject::draw() {

    if (textureID_ != 0)
        glBindTexture(GL_TEXTURE_2D, textureID_);

    glUseProgram(programID_);
    glBindVertexArray(VAO_);

}


DrawableObject::~DrawableObject(){
    
    glDeleteBuffers(1, &VBO_);
    glDeleteBuffers(1, &EBO_);
    
    glDeleteVertexArrays(1, &VAO_);
    
}
