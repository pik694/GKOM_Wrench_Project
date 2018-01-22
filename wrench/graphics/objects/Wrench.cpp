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
    vertices_ = {
         0.091f,    0.05f,  0.0f,       0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         0.1285f,   0.05f,  0.0f,       0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         0.091f,   -0.055f, 0.0f,       0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         0.1285f,  -0.076f, 0.0f,       0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         0.05f,    -0.122f, 0.0f,       0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         0.0f,     -0.107f, 0.0f,       0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         0.05f,    -0.85f,  0.0f,       0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -0.05f,    -0.85f,  0.0f,       0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -0.05f,    -0.122f, 0.0f,       0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -0.091f,   -0.055f, 0.0f,       0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -0.1285f,  -0.076f, 0.0f,       0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -0.091f,    0.05f,  0.0f,       0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -0.1285f,   0.05f,  0.0f,       0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    };
    
    indices_ = {
        0,1,3,
        0,2,3,
        2,3,4,
        5,4,2,
        5,7,4,
        7,6,4,
        5,7,8,
        8,9,10,
        8,9,5,
        9,10,12,
        9,11,12,
    };
    
    init();

}

void Wrench::draw(){

    DrawableObject::draw();

	glUniformMatrix4fv(
			glGetUniformLocation(programID_, "transform"),
			1,
			GL_FALSE,
			glm::value_ptr(transformation_)
	);

    glDrawElements(GL_TRIANGLES, 33, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
    
}

void Wrench::updatePosition() {

	switch(movementState_){
		case MovementState_E::none:
			break;
		case MovementState_E::rotateLeft:
			transformation_ = glm::rotate(transformation_, glm::radians(ROTATION_STEP), glm::vec3(0,0,1));
			screw_->rotate(ROTATION_STEP);
			rotation_ += ROTATION_STEP;
			break;
		case MovementState_E::rotateRight:
			transformation_ = glm::rotate(transformation_, glm::radians(-ROTATION_STEP), glm::vec3(0,0,1));
			screw_->rotate(-ROTATION_STEP);
			rotation_ -= ROTATION_STEP;
			break;
		case MovementState_E::moveBackward:
			if (movementDistance_ == MOVEMENT_DISTANCE){
				movementState_ = MovementState_E::none;
			}
			else{
				transformation_ = transformation_ + glm::mat4(
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
				transformation_ = transformation_ + glm::mat4(
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





