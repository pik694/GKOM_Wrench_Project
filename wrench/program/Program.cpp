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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <graphics/Texture.h>
#include <graphics/objects/Screw.hpp>
#include <graphics/objects/Wrench.hpp>
#include <graphics/objects/Wall.h>
#include <graphics/Camera.h>
#include <graphics/objects/Room.h>

#include "Program.hpp"
#include "graphics/ShaderProgram.hpp"
#include "graphics/objects/Workshop.h"

using namespace wrench::program;

const GLuint Program::DEFAULT_HEIGHT = 600;
const GLuint Program::DEFAULT_WIDTH = 600;

void Program::init() {

	if (glfwInit() != GL_TRUE) {
		throw std::runtime_error("Could not initialise GLFW");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

}

void Program::createWindow(const std::string &windowTitle, GLuint height, GLuint width) {

	window_ = std::make_unique<window::Window>(width, height, windowTitle);

	glewExperimental = GL_TRUE;
	GLenum status = glewInit();
	if (status != GLEW_OK) {
		std::string error((const char *) glewGetErrorString(status));

		throw std::runtime_error("Could not initialise GLEW" + error);
	}

	glViewport(0, 0, width, height);
}

void Program::run() {

	if (!window_) throw std::runtime_error("Window was not set");

	graphics::ShaderProgram textureProgram(
			"/Users/piotr/Developer/GKOM_Wrench/wrench/graphics/shaders/texture_vertex.glsl",
			"/Users/piotr/Developer/GKOM_Wrench/wrench/graphics/shaders/texture_fragment.glsl"
	);
	graphics::Texture workshopTexture(
			"/Users/piotr/Developer/GKOM_Wrench/wrench/graphics/textures/workshop_texture.jpg"
	);
	graphics::Texture toolsWallTexture(
			"/Users/piotr/Developer/GKOM_Wrench/wrench/graphics/textures/tools_texture.jpg"
	);

	graphics::Texture wallTexture (
			"/Users/piotr/Developer/GKOM_Wrench/wrench/graphics/textures/tools_texture.jpg"

	);

	graphics::Texture floorTexture{
			"/Users/piotr/Developer/GKOM_Wrench/wrench/graphics/textures/floor_texture.jpg"
	};

	graphics::ShaderProgram colourProgram (
			"/Users/piotr/Developer/GKOM_Wrench/wrench/graphics/shaders/colour_vertex.glsl",
			"/Users/piotr/Developer/GKOM_Wrench/wrench/graphics/shaders/colour_fragment.glsl"
	);

	graphics::objects::Room room;

	room.setShaders(textureProgram.getProgramID());
	room.setWallTextures(wallTexture.getTextureID());
	room.setFloorTexture(floorTexture.getTextureID());


//	graphics::objects::Workshop workshop;
//	graphics::objects::Wall wall;
//	graphics::objects::Screw screw;
//	graphics::objects::Wrench wrench;
//
//	graphics::objects::Wrench::WRENCH = &wrench;
//	wrench.setScrew(&screw);
//
//	workshop.setShaders(textureProgram.getProgramID());
//	workshop.setTexture(workshopTexture.getTextureID());
//
//	wall.setShaders(textureProgram.getProgramID());
//	wall.setTexture(wallTexture.getTextureID());
//
//	screw.setShaders(colourProgram.getProgramID());
//	wrench.setShaders(colourProgram.getProgramID());

	glEnable(GL_DEPTH_TEST);


	glm::mat4 projection = glm::perspective(glm::radians(30.0f), 1.0f, 0.1f, 100.0f);

	while (!window_->shouldClose()) {

		glfwPollEvents();

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//		wrench.updatePosition();

		glm::mat4 view;
		float radius = 10.0f;
		float cam   = cos(glfwGetTime()) * radius;
		view = glm::lookAt(glm::vec3(5, 0, 3), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

		glm::mat4 camera = projection * view;

		room.draw(camera);

//		workshop.draw(camera);
//		wall.draw(camera);
//		screw.draw(camera);
//		wrench.draw(camera);

		window_->swapBuffers();

		usleep(200);
	}


}

Program::~Program() {
	glfwTerminate();
}


