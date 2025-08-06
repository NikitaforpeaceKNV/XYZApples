#pragma once
#include "GameInit.h"


namespace draw
{
	void DrawPlayer(entities::player::Player& player, sf::RenderWindow& window);
	void DrawApple(entities::apple::Apple& apple, sf::RenderWindow& window);
	void DrawRock(entities::rock::Rock& rock, sf::RenderWindow& window);
	void DrawGame(init::GameState& gamestate, sf::RenderWindow& window);
	void DrawUI(init::GameState& gamestate, sf::RenderWindow& window);
	void DrawGamestartSettings(init::GameState& gamestate, sf::RenderWindow& window);
	void DrawLeaderboard(init::GameState& gamestate, sf::RenderWindow& window);
}