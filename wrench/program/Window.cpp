//
//  Window.cpp
//  GKOM_Wrench
//
//  Created by Piotr Żelazko on 10.12.2017.
//  Copyright © 2017 Piotr Żelazko. All rights reserved.
//

#include "Window.hpp"
#include <string>
#include <iostream>
#include "graphics/objects/Wrench.hpp"

using namespace wrench::program::window;

Window::Window(GLuint width,GLuint height,const std::string& title) {
    createWindow(width, height, title);
}


Window::~Window(){
    if (window_)
    glfwDestroyWindow(window_);
    
}
bool Window::shouldClose(){
    return glfwWindowShouldClose(window_);
}

Window& Window::operator=(Window&& rvalue){
    window_ = std::move(rvalue.window_);
    return *this;
}
Window::Window(Window&& rValue) {
    if (&rValue != this){
        window_ = std::move(rValue.window_);
        rValue.window_ = nullptr;
    }
}

void Window::swapBuffers() {
    glfwSwapBuffers(window_);
}

void Window::createWindow(GLuint width,GLuint height,const std::string& title) {
    
    window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (window_ == nullptr){
        throw std::runtime_error("Could not create window : " + title);
    }
    
    glfwMakeContextCurrent(window_);
    glfwSetKeyCallback(window_, Window::keyCallback);
}

void Window::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {

    
    if (action == GLFW_RELEASE)
        std::cout << key << std::endl;
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS){
        graphics::objects::Wrench::WRENCH->moveFromScrew();
    }
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS){
        graphics::objects::Wrench::WRENCH->moveToScrew();
    }
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS){
        graphics::objects::Wrench::WRENCH->rotateLeft();
    }
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
        graphics::objects::Wrench::WRENCH->rotateRight();
    }

}













