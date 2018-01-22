//
// Created by Piotr Żelazko on 22.01.2018.
//

#ifndef GKOM_WRENCH_ROOM_H
#define GKOM_WRENCH_ROOM_H

#include "DrawableObject.hpp"
#include "Wall.h"

namespace wrench{
	namespace graphics{
		namespace objects{
			class Room : public DrawableObject {
			public:

				Room();

				void setWallTextures(GLuint textureID);
				void setFloorTexture(GLuint textureID);

				void scale(glm::vec3 scale) override{};
				void rotate(float degrees, glm::vec3 axis) override{};
				void translate(glm::vec3 vector) override{};

				void draw(glm::mat4 view) override ;

				~Room() override = default;

				void setShaders(GLuint shadersProgramID) override;

			private:
				Wall floor_;
				Wall frontWall_;
				Wall leftWall_;
				Wall rightWall_;
			};
		}
	}
}


#endif //GKOM_WRENCH_ROOM_H
