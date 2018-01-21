//
//  Window.hpp
//  GKOM_Wrench
//
//  Created by Piotr Żelazko on 10.12.2017.
//  Copyright © 2017 Piotr Żelazko. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <functional>
#include <boost/optional.hpp>

namespace wrench{
    namespace program {
        namespace window{
            class Window {
            public:
                
                Window(GLuint width, GLuint height, const std::string& title);
                
                Window(Window&& rWindow);
                
                virtual ~Window();
                
                Window& operator=(Window&& rvalue);
                
                void swapBuffers();
                bool shouldClose();
                
                
            private:
                void createWindow(GLuint width, GLuint height, const std::string& title);
                
                static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
                
                GLFWwindow* window_;
            };
        }
    }
}

#endif /* Window_hpp */
