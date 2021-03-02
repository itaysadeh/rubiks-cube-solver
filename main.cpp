#define SDL_MAIN_HANDLED

#include "Engine/Engine.h"

#include <ctime>

int main(int argc, char* argv[])
{
	std::cout << std::filesystem::current_path() << '\n';
	srand(0);

	Engine engine;
	engine.run();

	return 0;
}
