//
// Created by Piotr Żelazko on 21.01.2018.
//

#ifndef GKOM_WRENCH_WORKSHOP_H
#define GKOM_WRENCH_WORKSHOP_H

#include <glm/glm.hpp>
#include "DrawableObject.hpp"

namespace wrench{
	namespace graphics{
		namespace objects{
			class Workshop : public DrawableObject{
			public:

				Workshop();

				void draw(glm::mat4 view) override ;

				~Workshop() override = default;

			};
		}
	}
}



#endif //GKOM_WRENCH_WORKSHOP_H
