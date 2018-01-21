//
// Created by Piotr Żelazko on 21.01.2018.
//

#ifndef GKOM_WRENCH_WORKSHOP_H
#define GKOM_WRENCH_WORKSHOP_H

#include "DrawableObject.hpp"

namespace wrench{
	namespace graphics{
		namespace objects{
			class Workshop : public DrawableObject{
			public:

				Workshop();

				void draw() override ;

				~Workshop() override = default;

			protected:



			};
		}
	}
}



#endif //GKOM_WRENCH_WORKSHOP_H
