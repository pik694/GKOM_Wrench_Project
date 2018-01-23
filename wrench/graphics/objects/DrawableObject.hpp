//
//  DrawableObject.hpp
//  GKOM_Wrench
//
//  Created by Piotr Żelazko on 21.01.2018.
//  Copyright © 2018 Piotr Żelazko. All rights reserved.
//

#ifndef DrawableObject_hpp
#define DrawableObject_hpp

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>


namespace wrench {
    namespace graphics{
        namespace objects{
            class DrawableObject{
            public:
                
                DrawableObject();

                virtual void setTexture(GLuint textureID);
                virtual void setShaders(GLuint shadersProgramID);
                
                virtual void draw();

	            virtual void draw(glm::mat4 view){}

	            virtual void scale(glm::vec3 scale);
	            virtual void rotate(float degrees, glm::vec3 axis);
	            virtual void translate(glm::vec3 vector);
                
                virtual ~DrawableObject() = 0;

	            static float AMBIENT_STRENGTH;
	            static float LIGHT_STRENGTH;
	            static glm::vec3 AMBIENT_LIGHT_COLOUR;
	            static glm::vec3 LIGHT_COLOUR;

            protected:
                
                void init();

	            void addNormalVectorsToVertices();

                std::vector<float> vertices_;
                std::vector<GLuint> indices_;

	            glm::mat4 model_;

                GLuint programID_;

                GLuint textureID_;
                
                GLuint VBO_, VAO_, EBO_;



            };
        }
    }
}



#endif /* DrawableObject_hpp */
