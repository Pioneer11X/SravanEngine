#include <iostream>
#include <memory>
#include "Engine.h"

int main() {
	
	// No Actual use here.. using the unique ptr, except that maybe it cleans itself up when exiting the program.
	std::unique_ptr<Engine>e(new Engine());

	e->Run();

	return 0;
}