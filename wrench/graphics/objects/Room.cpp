//
// Created by Piotr Żelazko on 22.01.2018.
//

#include "Room.h"

using namespace wrench::graphics::objects;


Room::Room() {

	floor_.translate(glm::vec3(0,-2.5,0));
	floor_.scale(glm::vec3(4,4,3));
	floor_.translate(glm::vec3(0.0, 0.0,-1));

	frontWall_.translate(glm::vec3(0,-2.5f,0));
	frontWall_.scale(glm::vec3(4,4,3));
	frontWall_.translate(glm::vec3(0, 1, 0));
	frontWall_.rotate(90.0f,glm::vec3(1,0,0));

	leftWall_.translate(glm::vec3(0,-2.5,0));
	leftWall_.scale(glm::vec3(4,4,3));
	leftWall_.translate(glm::vec3(-1, 0, 0));
	leftWall_.rotate(90.0f, glm::vec3(0,0,1));
	leftWall_.rotate(90.0f, glm::vec3(1,0,0));

	rightWall_.translate(glm::vec3(0,-2.5,0));
	rightWall_.scale(glm::vec3(4,4,3));
	rightWall_.translate(glm::vec3(1, 0, 0));
	rightWall_.rotate(270.0f, glm::vec3(0,0,1));
	rightWall_.rotate(90.0f, glm::vec3(1,0,0));

}

void Room::draw(glm::mat4 view) {

	frontWall_.draw(view);

	leftWall_.draw(view);
	rightWall_.draw(view);

	floor_.draw(view);

}

void Room::setWallTextures(GLuint textureID) {

	frontWall_.setTexture(textureID);
	leftWall_.setTexture(textureID);
	rightWall_.setTexture(textureID);

}

void Room::setFloorTexture(GLuint textureID) {
	floor_.setTexture(textureID);
}

void Room::setShaders(GLuint shadersProgramID) {


	frontWall_.setShaders(shadersProgramID);
	leftWall_.setShaders(shadersProgramID);
	rightWall_.setShaders(shadersProgramID);

	floor_.setShaders(shadersProgramID);

}






