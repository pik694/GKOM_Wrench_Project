//
//  main.cpp
//  GKOM_Wrench
//
//  Created by Piotr Żelazko on 20.01.2018.
//  Copyright © 2018 Piotr Żelazko. All rights reserved.
//

#include <iostream>
#include "program/Program.hpp"

int main(int argc, const char * argv[]) {

	wrench::program::Program program;
	try {
		program.init();

		program.createWindow("Test window");

		program.run();

	} catch (std::exception& e ) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
