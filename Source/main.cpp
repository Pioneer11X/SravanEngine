#include <iostream>
#include "Engine.h"

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#endif // _DEBUG


int main() {

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif // _DEBUG

	
	// No Actual use here.. using the unique ptr, except that maybe it cleans itself up when exiting the program.
	Engine e = (Engine::getInstance());

	e.Run();

	return 0;
}