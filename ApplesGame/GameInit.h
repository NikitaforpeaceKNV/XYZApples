#pragma once

#include <SFML/Audio.hpp>
#include "GameEntities.h"
#include "UI.h"


namespace init
{

	struct BIT_Mask 
	{
		int bit_mask_m = 0;
		int endless_apples_or_not = 1;
		int acceleration_status = 2;
	};

	struct GameState
	{

		BIT_Mask mask;

		entities::player::Player player;
		std::vector<entities::apple::Apple> apples1;
		entities::rock::Rock rocks[settings::NUM_ROCKS];

		int numEatenApples = 0;
		bool isGameOver = false;
		bool isGameStart = true;
		float timeSinceGameOver = 0.f;

		sf::Font font;
		ui::UIState UI;

		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::SoundBuffer appleEatSoundBuffer;
		sf::SoundBuffer deathSoundBuffer;
		sf::Sound appleEatSound;
		sf::Sound deathSound;
	};

	void RestartGame(GameState& gameState);
	void InitGame(GameState& gameState);
	void InitLeaderboard(GameState& gamestate);
	void InitScoreText(GameState& gamestate);
	void InitSettingsText(GameState& gamestate);
	void InitHintText(GameState& gamestate);
	void InitGameoverText(GameState& gamestate);
}