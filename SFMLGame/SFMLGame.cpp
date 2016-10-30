// SFMLGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Application.h"

int main()
{
	try {
		Application app;
		app.run();
	}
	catch (std::exception& e) {
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
	return 0;
}
