#pragma once


#include "DrawGame.h"


namespace logic 
{
	void HandleInput(init::GameState& gameState);
	void UpdateGame(init::GameState& gameState, float timeDelta);
	bool HasPlayerCollisionWithScreenBorder(const entities::player::Player& player);
	bool HasPlayerCollisionWithApple(const entities::player::Player& player, const entities::apple::Apple& apple);
	bool HasPlayerCollisionWithRock(const entities::player::Player& player, const entities::rock::Rock& rock);
	void GameOver(init::GameState& gamestate);
	void UpdateUI(init::GameState& gamestate, float timeDelta);
	void GameSettingSet(init::GameState& gamestate);
	void HandleMainMenuInput(init::GameState& gamestate, sf::RenderWindow& window);
	void UpdateMenuColors(init::GameState& gamestate);
	void HandleSettingsInput(init::GameState& gamestate);
}