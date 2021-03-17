#define SDL_MAIN_HANDLED

#include "Engine/Engine.h"

int main(int argc, char* argv[])
{
	Engine engine;
	engine.run();

	return 0;
}
