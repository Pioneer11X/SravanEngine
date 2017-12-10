#include <iostream>
#include "Engine.h"

int main() {
	
	// No Actual use here.. using the unique ptr, except that maybe it cleans itself up when exiting the program.
	Engine e = (Engine::getInstance());

	e.Run();

	return 0;
}