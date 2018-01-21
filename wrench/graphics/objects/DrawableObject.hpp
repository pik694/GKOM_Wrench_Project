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


namespace wrench {
    namespace graphics{
        namespace objects{
            class DrawableObject{
            public:
                
                DrawableObject();

                virtual void setTexture(GLuint textureID);
                virtual void setShaders(GLuint shadersProgramID);
                
                virtual void draw();
                
                virtual ~DrawableObject();
                
            protected:
                
                void init();

                std::vector<float> vertices_;
                std::vector<GLuint> indices_;


                GLuint programID_;

                GLuint textureID_;
                
                GLuint VBO_, VAO_, EBO_;
                
            };
        }
    }
}



#endif /* DrawableObject_hpp */
