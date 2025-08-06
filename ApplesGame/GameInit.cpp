#include "GameInit.h"
#include <cassert>

using namespace entities;

void init::RestartGame(GameState& gameState)
{
	player::InitPlayer(gameState.player, gameState.playerTexture);

	for (int i = 0; i < settings::NUM_ROCKS; ++i)
	{
		rock::InitRock(gameState.rocks[i], gameState.rockTexture);
	}

	gameState.apples1.resize(rand() % 40); // random apples count, 40 max

	if (gameState.apples1.size() <=5) { gameState.apples1.resize(15); }

	for (int i = 0; i < gameState.apples1.size(); ++i)
	{
		apple::InitApple(gameState.apples1[i], gameState.appleTexture);
	}

	// Init game state
	gameState.numEatenApples = 0;
	gameState.isGameOver = false;
	gameState.timeSinceGameOver = 0.f;
}

void init::InitLeaderboard(GameState& gamestate)
{
	float step = 250.f;

	std::vector<std::string> tmp_position = { "1. ", "2. ", "3. ", "4. ", "5. ", "6. ", "7. ", "8. ", "9. ", "10. " };
	int i = 0;

	for (auto& name_score : gamestate.UI.leaderboard)
	{
		name_score.nickName.setFillColor(sf::Color::Red);
		name_score.nickName.setFont(gamestate.font);
		name_score.nickName.setCharacterSize(20);
		name_score.nickName.setPosition ({ settings::SCREEN_WIDTH/2.f - 150.f ,step});
		

		name_score.scores.setFillColor(sf::Color::Red);
		name_score.scores.setFont(gamestate.font);
		name_score.scores.setCharacterSize(20);
		name_score.scores.setPosition({ settings::SCREEN_WIDTH / 2.f + 200.f ,step });

		name_score.position_on_leaderboard.setString(tmp_position[i]);
		name_score.position_on_leaderboard.setFillColor(sf::Color::Red);
		name_score.position_on_leaderboard.setFont(gamestate.font);
		name_score.position_on_leaderboard.setCharacterSize(20);
		name_score.position_on_leaderboard.setPosition({ settings::SCREEN_WIDTH / 2.f - 200.f ,step });

		step += 30.f;
		++i;
	}
}

void init::InitScoreText(GameState& gamestate)
{
	gamestate.UI.scoreText.setFont(gamestate.font);
	gamestate.UI.scoreText.setCharacterSize(24);
	gamestate.UI.scoreText.setFillColor(sf::Color::Yellow);
}

void init::InitSettingsText(GameState& gamestate)
{
	gamestate.UI.gameSettings.setFont(gamestate.font);
	gamestate.UI.gameSettings.setCharacterSize(24);
	gamestate.UI.gameSettings.setFillColor(sf::Color::Red);
	gamestate.UI.gameSettings.setString("Please, choose settings below: \n 1. Would you like endless apples? (1 - yes / 2 - no) \n 2. Would you like player acceleration? (y / n)");
}

void init::InitHintText(GameState& gamestate)
{
	gamestate.UI.inputHintText.setFont(gamestate.font);
	gamestate.UI.inputHintText.setCharacterSize(24);
	gamestate.UI.inputHintText.setFillColor(sf::Color::White);
	gamestate.UI.inputHintText.setString("Use arrow keys to move, Space to restart, ESC to exit");
	gamestate.UI.inputHintText.setOrigin(GetTextOrigin(gamestate.UI.inputHintText, { 1.f, 0.f }));
}

void init::InitGameoverText(GameState& gamestate)
{
	gamestate.UI.isGameOverTextVisible = false;
	gamestate.UI.gameOverText.setFont(gamestate.font);
	gamestate.UI.gameOverText.setCharacterSize(48);
	gamestate.UI.gameOverText.setStyle(sf::Text::Bold);
	gamestate.UI.gameOverText.setFillColor(sf::Color::Red);
	gamestate.UI.gameOverText.setString("GAME OVER");
	gamestate.UI.gameOverText.setOrigin(GetTextOrigin(gamestate.UI.gameOverText, { 0.5f, 0.5f }));
}


void init::InitGame(GameState& gameState)
{
	assert(gameState.playerTexture.loadFromFile(settings::RESOURCES_PATH + "Apple.png"));
	assert(gameState.appleTexture.loadFromFile(settings::RESOURCES_PATH + "Pacman.png"));
	assert(gameState.rockTexture.loadFromFile(settings::RESOURCES_PATH + "Rock.png"));
	assert(gameState.font.loadFromFile(settings::RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
	assert(gameState.appleEatSoundBuffer.loadFromFile(settings::RESOURCES_PATH + "AppleEat.wav"));
	assert(gameState.deathSoundBuffer.loadFromFile(settings::RESOURCES_PATH + "Death.wav"));

	gameState.appleEatSound.setBuffer(gameState.appleEatSoundBuffer);
	gameState.deathSound.setBuffer(gameState.deathSoundBuffer);

	InitScoreText(gameState);

	InitSettingsText(gameState);

	InitHintText(gameState);

	InitGameoverText(gameState);
	
	gameState.UI.LeaderBoardInit(gameState.UI.leaderboard);

	RestartGame(gameState);

}

void init::InitMainMenu(GameState& gamestate)
{
	gamestate.UI.mainMenu.items.resize(4);

	gamestate.UI.mainMenu.items[0].setString("Start Game");
	gamestate.UI.mainMenu.items[1].setString("Settings");
	gamestate.UI.mainMenu.items[2].setString("Leaderboard");
	gamestate.UI.mainMenu.items[3].setString("Exit");

	for (size_t i = 0; i < gamestate.UI.mainMenu.items.size(); ++i)
	{
		gamestate.UI.mainMenu.items[i].setFont(gamestate.font);
		gamestate.UI.mainMenu.items[i].setCharacterSize(30);
		gamestate.UI.mainMenu.items[i].setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White);
		gamestate.UI.mainMenu.items[i].setPosition(
			settings::SCREEN_WIDTH / 2.f - 100.f,
			settings::SCREEN_HEGHT / 2.f + i * 40.f
		);
	}
}


