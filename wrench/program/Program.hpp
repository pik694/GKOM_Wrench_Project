//
//  Program.hpp
//  GKOM_Wrench
//
//  Created by Piotr Żelazko on 20.01.2018.
//  Copyright © 2018 Piotr Żelazko. All rights reserved.
//

#ifndef Program_hpp
#define Program_hpp

#include <string>
#include <list>

#include "Window.hpp"

namespace wrench{
    namespace program{
        class Program {
        public:
            
            void init();
            
            void createWindow(const std::string& windowTitle,
                              GLuint height = DEFAULT_HEIGHT, GLuint width = DEFAULT_WIDTH);
            
            void run();
            
            
            virtual ~Program();
        private:
            std::unique_ptr<window::Window> window_;


            static const GLuint DEFAULT_HEIGHT;
            static const GLuint DEFAULT_WIDTH;
        };
    }
}


#endif /* Program_hpp */
