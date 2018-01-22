//
// Created by Piotr Żelazko on 22.01.2018.
//

#ifndef GKOM_WRENCH_WALL_H
#define GKOM_WRENCH_WALL_H


#include "DrawableObject.hpp"

namespace wrench {
	namespace graphics{
		namespace objects{
			class Wall : public  DrawableObject{
			public:
				Wall();

				void draw(glm::mat4 view) override;

				~Wall() override  = default;
			};
		}
	}
}

#endif //GKOM_WRENCH_WALL_H
