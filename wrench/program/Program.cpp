//
//  Program.cpp
//  GKOM_Wrench
//
//  Created by Piotr Żelazko on 20.01.2018.
//  Copyright © 2018 Piotr Żelazko. All rights reserved.
//

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <graphics/Texture.h>

#include "Program.hpp"
#include "graphics/ShaderProgram.hpp"
#include "graphics/objects/Workshop.h"

using namespace wrench::program;

const GLuint Program::DEFAULT_HEIGHT = 600;
const GLuint Program::DEFAULT_WIDTH = 600;

void Program::init(){
    
    if (glfwInit() != GL_TRUE){
        throw std::runtime_error("Could not initialise GLFW");
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    
}

void Program::createWindow(const std::string& windowTitle, GLuint height, GLuint width){
    
    window_ = std::make_unique<window::Window>(width, height, windowTitle);
    
    glewExperimental = GL_TRUE;
    GLenum status  =  glewInit();
    if (status != GLEW_OK){
        std::string error ((const char*) glewGetErrorString(status));
        
        throw std::runtime_error("Could not initialise GLEW" + error);
    }
    
    glViewport(0, 0, width, height);
}

void Program::run(){
    
    if (!window_) throw std::runtime_error("Window was not set");

    graphics::ShaderProgram shaderProgram (
            "/Users/piotr/Developer/GKOM_Wrench/wrench/graphics/shaders/vertex.glsl",
            "/Users/piotr/Developer/GKOM_Wrench/wrench/graphics/shaders/fragment.glsl"
    );
    graphics::Texture workshopTexture (
        "/Users/piotr/Developer/GKOM_Wrench/wrench/graphics/textures/workshop_texture.jpg"
    );

    graphics::objects::Workshop workshop;

    workshop.setShaders(shaderProgram.getProgramID());
    workshop.setTexture(workshopTexture.getTextureID());

    

    while (!window_->shouldClose()){
        
        glfwPollEvents();
        
        glClearColor( 1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        workshop.draw();

        window_->swapBuffers();
    }
    
    
    
}

Program::~Program(){
    glfwTerminate();
}
