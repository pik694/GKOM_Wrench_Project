//
//  Wrench.cpp
//  GKOM_Wrench
//
//  Created by Piotr Żelazko on 21.01.2018.
//  Copyright © 2018 Piotr Żelazko. All rights reserved.
//

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Wrench.hpp"


using namespace wrench::graphics::objects;

Wrench* Wrench::WRENCH = nullptr;

Wrench::Wrench():
	isByTheScrew_(true),
	rotation_(-90.0f),
	movementState_(MovementState_E::none),
	movementDistance_(0),
	screw_(nullptr)
{

	model_ = glm::scale(model_, glm::vec3(1,1,0.5));

    vertices_ = {
         0.091f,    0.05f,  0.115f,    0.0f, 0.0f,
         0.1285f,   0.05f,  0.115f,    0.0f, 0.0f,
         0.091f,   -0.055f, 0.115f,    0.0f, 0.0f,
         0.1285f,  -0.076f, 0.115f,    0.0f, 0.0f,
         0.05f,    -0.122f, 0.115f,    0.0f, 0.0f,
         0.0f,     -0.107f, 0.115f,    0.0f, 0.0f,
         0.05f,    -0.85f,  0.115f,    0.0f, 0.0f,
        -0.05f,    -0.85f,  0.115f,    0.0f, 0.0f,
        -0.05f,    -0.122f, 0.115f,    0.0f, 0.0f,
        -0.091f,   -0.055f, 0.115f,    0.0f, 0.0f,
        -0.1285f,  -0.076f, 0.115f,    0.0f, 0.0f,
        -0.091f,    0.05f,  0.115f,    0.0f, 0.0f,
        -0.1285f,   0.05f,  0.115f,    0.0f, 0.0f,

         0.091f,    0.05f,  0.0f,    0.0f, 0.0f,
         0.1285f,   0.05f,  0.0f,    0.0f, 0.0f,
         0.091f,   -0.055f, 0.0f,    0.0f, 0.0f,
         0.1285f,  -0.076f, 0.0f,    0.0f, 0.0f,
         0.05f,    -0.122f, 0.0f,    0.0f, 0.0f,
         0.0f,     -0.107f, 0.0f,    0.0f, 0.0f,
         0.05f,    -0.85f,  0.0f,    0.0f, 0.0f,
        -0.05f,    -0.85f,  0.0f,    0.0f, 0.0f,
        -0.05f,    -0.122f, 0.0f,    0.0f, 0.0f,
        -0.091f,   -0.055f, 0.0f,    0.0f, 0.0f,
        -0.1285f,  -0.076f, 0.0f,    0.0f, 0.0f,
        -0.091f,    0.05f,  0.0f,    0.0f, 0.0f,
        -0.1285f,   0.05f,  0.0f,    0.0f, 0.0f,
    };

    indices_ = {
        0,1,3,
        0,3,2,
        2,3,4,
        2,4,5,
        5,4,7,
        4,6,7,
        5,7,8,
        5,8,9,
        8,10,9,
        9,10,11,
        10,12,11,

        0,13,14,
        1,0,14,
        1,14,16,
        1,16,3,
        3,16,17,
        3,17,4,
        4,17,19,
        4,19,6,
        6,19,20,
        6,20,7,
        7,20,21,
        7,21,8,
        8,21,23,
        8,23,10,
        10,23,25,
        10,25,12,
        12,25,24,
        11,12,24,
        11,24,22,
        11,22,9,
        9,22,18,
        9,18,5,
        5,18,15,
        5,15,2,
        2,15,13,
        2,13,0
    };
    
    init();

}

void Wrench::draw(glm::mat4 view, glm::vec3 cameraPos){

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

	glm::vec3 colour (0,0,1);

	glUniform3fv(
			glGetUniformLocation(programID_, "objectColour"),
			1,
			glm::value_ptr(colour)
	);


	auto ambientLight = AMBIENT_STRENGTH * AMBIENT_LIGHT_COLOUR;

	glUniform3fv(
			glGetUniformLocation(programID_, "material.ambient"),
			1,
			glm::value_ptr(glm::vec3(0.5, 0.5, 0.5))

	);

	glUniform3fv(
			glGetUniformLocation(programID_, "material.diffuse"),
			1,
			glm::value_ptr(glm::vec3(0.5, 0.5, 0.5))
	);

	glUniform3fv(
			glGetUniformLocation(programID_, "material.specular"),
			1,
			glm::value_ptr(glm::vec3(0.1, 0.1, 0.1))

	);

	glUniform1f(
			glGetUniformLocation(programID_, "material.shininess"),
			99.0f
	);

	glUniform3fv(
			glGetUniformLocation(programID_, "viewPos"),
			1,
			glm::value_ptr(cameraPos)
	);



    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
    
}

void Wrench::updatePosition() {

	switch(movementState_){
		case MovementState_E::none:
			break;
		case MovementState_E::rotateLeft:
			model_ = glm::rotate(model_, glm::radians(ROTATION_STEP), glm::vec3(0,0,1));
			screw_->rotate(ROTATION_STEP);
			rotation_ += ROTATION_STEP;
			break;
		case MovementState_E::rotateRight:
			model_ = glm::rotate(model_, glm::radians(-ROTATION_STEP), glm::vec3(0,0,1));
			screw_->rotate(-ROTATION_STEP);
			rotation_ -= ROTATION_STEP;
			break;
		case MovementState_E::moveBackward:
			if (movementDistance_ == MOVEMENT_DISTANCE){
				movementState_ = MovementState_E::none;
			}
			else{
				model_ = model_ + glm::mat4(
						glm::vec4(0, 0, 0, 0),
						glm::vec4(0, 0, 0, 0),
						glm::vec4(0, 0, 0, 0),
						glm::vec4(
								cos(glm::radians(rotation_)) * LINEAR_MOVE_STEP,
								sin(glm::radians(rotation_)) * LINEAR_MOVE_STEP,
								0.0f,
								0.0f)
				);
				++movementDistance_;
			}
			break;
		case MovementState_E::moveForward:
			if (movementDistance_ == 0){
				movementState_ = MovementState_E::none;
			}
			else{
				model_ = model_ + glm::mat4(
						glm::vec4(0, 0, 0, 0),
						glm::vec4(0, 0, 0, 0),
						glm::vec4(0, 0, 0, 0),
						glm::vec4(
								-cos(glm::radians(rotation_)) * LINEAR_MOVE_STEP,
								-sin(glm::radians(rotation_)) * LINEAR_MOVE_STEP,
								0.0f,
								0.0f)
				);
				--movementDistance_;
			}
			break;
	}
}


void Wrench::moveToScrew() {

	switch(movementState_)
	{
		case MovementState_E::none :
		case MovementState_E::moveBackward:

			if (movementDistance_ != 0){
				movementState_ = MovementState_E::moveForward;
			}

			break;
		default:
			break;
	}

}

void Wrench::moveFromScrew() {

	if (movementDistance_ != MOVEMENT_DISTANCE){
		movementState_ = MovementState_E::moveBackward;
	}

}

void Wrench::rotateLeft() {
	if (movementState_ == MovementState_E::rotateLeft){
		movementState_ = MovementState_E::none;
		return;
	}
	if (movementDistance_ == 0){
		movementState_ = MovementState_E::rotateLeft;
	}

}

void Wrench::rotateRight() {

	if (movementState_ == MovementState_E::rotateRight){
		movementState_ = MovementState_E::none;
		return;
	}
	if (movementDistance_ == 0){
		movementState_ = MovementState_E::rotateRight;
	}

}

void Wrench::setScrew(Screw *screw) {
	screw_ = screw;
}





