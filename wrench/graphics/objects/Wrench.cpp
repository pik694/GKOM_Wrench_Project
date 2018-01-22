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

        0,1,14,
        0,13,14,
		1,3,16,
        1,14,16,
        3,16,17,
        3,4,17,
        4,17,19,
        4,6,19,
        6,19,20,
        6,7,20,
        7,8,21,
        7,20,21,
        8,10,23,
        8,21,23,
        10,23,25,
        10,12,25,
        11,12,25,
        11,24,25,
        0,2,13,
        2,13,15,
        2,5,15,
        5,15,18,
        5,9,18,
        9,18,22,
        9,11,24,
        9,22,24
    };
    
    init();

}

void Wrench::draw(){

    DrawableObject::draw();

	glm::mat4 model;
	model = glm::rotate(model, glm::radians(-70.0f), glm::vec3(1.0f, 0.0f, 0.0f));

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





