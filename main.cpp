#define SDL_MAIN_HANDLED

#include "Engine/Engine.h"

#include <ctime>

int main(int argc, char* argv[])
{
	srand(0);

	std::cout << std::filesystem::current_path() << '\n';

	Engine engine;
	engine.run();

	return 0;
}
