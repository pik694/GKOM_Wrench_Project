 //
//  Screw.hpp
//  GKOM_Wrench
//
//  Created by Piotr Żelazko on 21.01.2018.
//  Copyright © 2018 Piotr Żelazko. All rights reserved.
//

#ifndef Screw_hpp
#define Screw_hpp


#include "DrawableObject.hpp"
#include <glm/glm.hpp>


namespace wrench {
    namespace graphics{
        namespace objects{
            class Screw : public DrawableObject {
            public:
                
                Screw();

	            void draw(glm::mat4 view) override;

                void rotate(float degree);
                
                ~Screw() override = default;

            };
        }
    }
}

#endif /* Screw_hpp */
