//
//  Wrench.hpp
//  GKOM_Wrench
//
//  Created by Piotr Żelazko on 21.01.2018.
//  Copyright © 2018 Piotr Żelazko. All rights reserved.
//

#ifndef Wrench_hpp
#define Wrench_hpp

#include "DrawableObject.hpp"
#include "Screw.hpp"
#include <glm/glm.hpp>

namespace wrench {
    namespace graphics{
        namespace objects{
            class Wrench : public DrawableObject {
            public:

                Wrench();

                void setScrew(Screw* screw);
                
                void draw(glm::mat4 view) override;

                void rotateLeft();
                void rotateRight();

                void moveFromScrew();
                void moveToScrew();

                void updatePosition();

                static Wrench* WRENCH;

                ~Wrench() override  = default;

            private:
                enum class MovementState_E{
                    none,
                    rotateLeft,
                    rotateRight,
                    moveForward,
                    moveBackward
                } movementState_;

                Screw* screw_;

                bool isByTheScrew_;

                float rotation_;
                int movementDistance_;

                const float LINEAR_MOVE_STEP = 0.01f;
                const float ROTATION_STEP = 1.0f;

                const unsigned int MOVEMENT_DISTANCE = 50;

            };
        }
    }
}

#endif /* Wrench_hpp */
