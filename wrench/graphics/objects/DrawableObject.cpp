//
//  DrawableObject.cpp
//  GKOM_Wrench
//
//  Created by Piotr Żelazko on 21.01.2018.
//  Copyright © 2018 Piotr Żelazko. All rights reserved.
//

#include "DrawableObject.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace wrench::graphics::objects;


DrawableObject::DrawableObject() {

	glGenBuffers(1, &VBO_);
	glGenBuffers(1, &EBO_);
	glGenVertexArrays(1, &VAO_);

}

void DrawableObject::init() {

	addNormalVectorsToVertices();

	glBindVertexArray(VAO_);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), vertices_.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLuint), indices_.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void DrawableObject::setTexture(GLuint textureID) {
	textureID_ = textureID;
}


void DrawableObject::setShaders(GLuint shadersProgramID) {
	programID_ = shadersProgramID;
}

void DrawableObject::draw() {

	if (textureID_ != 0)
		glBindTexture(GL_TEXTURE_2D, textureID_);

	glUseProgram(programID_);
	glBindVertexArray(VAO_);

	auto ambientLight = AMBIENT_STRENGTH * AMBIENT_LIGHT_COLOUR;
	glm::vec3 lightPos (3,-2,-1);

	glUniform3fv(
			glGetUniformLocation(programID_, "ambientLight"),
			1,
			glm::value_ptr(ambientLight)
	);

	glUniform3fv(
			glGetUniformLocation(programID_, "lightPosition"),
			1,
			glm::value_ptr(lightPos)
	);

	auto light = LIGHT_STRENGTH * LIGHT_COLOUR;
	glUniform3fv(
			glGetUniformLocation(programID_, "lightColour"),
			1,
			glm::value_ptr(light)
	);

}


DrawableObject::~DrawableObject() {

	glDeleteBuffers(1, &VBO_);
	glDeleteBuffers(1, &EBO_);

	glDeleteVertexArrays(1, &VAO_);

}


void DrawableObject::addNormalVectorsToVertices() {


	std::vector<float> vertices;
	std::vector<GLuint> indices;
	vertices.reserve(indices_.size() * 8);


	for (int i = 0, j = 1, k = 2; j < indices_.size(); i += 3, j += 3, k += 3) {

		glm::vec3 first (
				vertices_.at(indices_.at(i)*5), vertices_.at(indices_.at(i)*5 + 1), vertices_.at(indices_.at(i)*5 + 2)
		);

		glm::vec3 second(
				vertices_.at(indices_.at(j)*5), vertices_.at(indices_.at(j)*5 + 1), vertices_.at(indices_.at(j)*5 + 2)
		);
		glm::vec3 third (
				vertices_.at(indices_.at(k)*5), vertices_.at(indices_.at(k)*5 + 1), vertices_.at(indices_.at(k)*5 + 2)
		);


		glm::vec3 normal = glm::cross(
				second - first,
				third - first
		);

		normal = glm::vec3(-normal.x,-normal.y,-normal.z);

		vertices.push_back(first.x);
		vertices.push_back(first.y);
		vertices.push_back(first.z);

		vertices.push_back(normal.x);
		vertices.push_back(normal.y);
		vertices.push_back(normal.z);

		vertices.push_back(vertices_.at(indices_.at(i)*5 + 3));
		vertices.push_back(vertices_.at(indices_.at(i)*5 + 4));


		vertices.push_back(second.x);
		vertices.push_back(second.y);
		vertices.push_back(second.z);

		vertices.push_back(normal.x);
		vertices.push_back(normal.y);
		vertices.push_back(normal.z);

		vertices.push_back(vertices_.at(indices_.at(j)*5 + 3));
		vertices.push_back(vertices_.at(indices_.at(j)*5 + 4));

		vertices.push_back(third.x);
		vertices.push_back(third.y);
		vertices.push_back(third.z);

		vertices.push_back(normal.x);
		vertices.push_back(normal.y);
		vertices.push_back(normal.z);

		vertices.push_back(vertices_.at(indices_.at(k)*5 + 3));
		vertices.push_back(vertices_.at(indices_.at(k)*5 + 4));

		indices.push_back(vertices.size() / 8 - 3);
		indices.push_back(vertices.size() / 8 - 2);
		indices.push_back(vertices.size() / 8 - 1);

	}


	vertices_ = vertices;
	indices_ = indices;

}

void DrawableObject::scale(glm::vec3 scale) {
	model_ = glm::scale(model_, scale);
}

void DrawableObject::rotate(float degrees, glm::vec3 axis) {
	model_ = glm::rotate(model_, glm::radians(degrees), axis);
}

void DrawableObject::translate(glm::vec3 vector) {
	model_ = glm::translate(model_, vector);
}

float DrawableObject::LIGHT_STRENGTH = 0.0f;
float DrawableObject::AMBIENT_STRENGTH = 0.2f;
glm::vec3 DrawableObject::AMBIENT_LIGHT_COLOUR(1.0, 1.0, 1.0);
glm::vec3 DrawableObject::LIGHT_COLOUR(1.0, 1.0, 1.0);
