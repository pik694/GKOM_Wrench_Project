//
// Created by Piotr Żelazko on 22.01.2018.
//

#ifndef GKOM_WRENCH_CAMERA_H
#define GKOM_WRENCH_CAMERA_H


#include <glm/detail/type_mat.hpp>

class Camera {
public:

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void ZoomIn();
	void ZoomOut();

	glm::mat4 getView();

private:





};


#endif //GKOM_WRENCH_CAMERA_H
