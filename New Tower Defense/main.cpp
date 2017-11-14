#include <cstdlib>
#include <string> 
#include <fstream> 
#include <sstream>
#include <iostream> 
#include <cmath>

#include <SFML/Graphics.hpp>
#include "Game.h"

int main(int argc, char *argv[])
{
	Game game;
	game.run();

	return EXIT_SUCCESS;
}
