#pragma once
#include <string>
#include <cstdlib>

namespace settings
{
	// Resources path
	const std::string RESOURCES_PATH = "Resources/";

	// Game settings constants
	const float PLAYER_SIZE = 20.f;
	const float APPLE_SIZE = 20.f;
	const float INITIAL_SPEED = 100.f;
	const float ACCELERATION = 10.f; // For each eaten apple player speed will be increased by this value
	const float ROCK_SIZE = 40.f;
	const int NUM_ROCKS = 4;
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEGHT = 600;
}
