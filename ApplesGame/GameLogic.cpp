#include "GameLogic.h"
#include <iostream>
#include <algorithm>

void logic::HandleInput(init::GameState& gameState)
{
	if (gameState.isGameOver)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			init::RestartGame(gameState);
		}
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		gameState.player.direction = PlayerDirection::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		gameState.player.direction = PlayerDirection::Right;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		gameState.player.direction = PlayerDirection::Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		gameState.player.direction = PlayerDirection::Left;
	}
}

void logic::UpdateGame(init::GameState& gameState, float timeDelta)
{
	if (!gameState.isGameOver)
	{
		// Update player
		entities::player::UpdatePlayer(gameState.player, timeDelta);

		for (int i = 0; i < gameState.apples1.size(); ++i)
		{
			// Checking distance between player and apple
			if (abs((gameState.player.position.x - gameState.apples1[i].position.x)) >= (settings::PLAYER_SIZE + settings::APPLE_SIZE) &&
				abs((gameState.player.position.y - gameState.apples1[i].position.y)) >= (settings::PLAYER_SIZE + settings::APPLE_SIZE))
			{
				continue;
			}

			// Check collision with apple
			if (HasPlayerCollisionWithApple(gameState.player, gameState.apples1[i]))
			{
				// Move apple to a new random position
				gameState.appleEatSound.play();

				if(gameState.mask.bit_mask_m & (1<<gameState.mask.endless_apples_or_not))
				{
				InitApple(gameState.apples1[i], gameState.appleTexture);
				}
				else
				{
					gameState.apples1.erase(gameState.apples1.begin()+i);
				}
				// Increase eaten apples counter
				gameState.numEatenApples++;
				// Increase player speed
				if (gameState.mask.bit_mask_m & (1 << gameState.mask.acceleration_status))
				{
					gameState.player.basic_speed += settings::ACCELERATION;
				}
			}
		}

		for (int i = 0; i < settings::NUM_ROCKS; ++i)
		{
			// Check collision with apple
			if (HasPlayerCollisionWithRock(gameState.player, gameState.rocks[i]))
			{
				gameState.isGameOver = true;
				gameState.timeSinceGameOver = 0.f;
				gameState.deathSound.play();
				GameOver(gameState);
			}
		}

		// Check collision with screen border
		if (HasPlayerCollisionWithScreenBorder(gameState.player))
		{
			gameState.isGameOver = true;
			gameState.timeSinceGameOver = 0.f;
			gameState.deathSound.play();
			GameOver(gameState);
		}
	}
	else
	{
		gameState.timeSinceGameOver += timeDelta;
	}

	//apples and rocks collision
	for (int i = 0; i < settings::NUM_ROCKS; ++i)
	{
		for (int j = 0; j < gameState.apples1.size(); ++j)
		{
			float dx = fabs(gameState.apples1[j].position.x - gameState.rocks[i].position.x);
			float dy = fabs(gameState.apples1[j].position.y - gameState.rocks[i].position.y);
			if (dx <= (settings::ROCK_SIZE + settings::PLAYER_SIZE) / 2.f &&
				dy <= (settings::ROCK_SIZE * 2 + settings::PLAYER_SIZE) / 2.f)
			{
				gameState.apples1[j].position = entities::RandomPosition();
			}
		}
	}

	UpdateUI(gameState, timeDelta);
}

bool logic::HasPlayerCollisionWithScreenBorder(const entities::player::Player& player)
{
	return (player.position.x - settings::PLAYER_SIZE / 2.f < 0) ||
		(player.position.x + settings::PLAYER_SIZE / 2.f > settings::SCREEN_WIDTH) ||
		(player.position.y - settings::PLAYER_SIZE / 2.f < 0) ||
		(player.position.y + settings::PLAYER_SIZE / 2.f > settings::SCREEN_HEGHT);
}

bool logic::HasPlayerCollisionWithApple(const entities::player::Player& player, const entities::apple::Apple& apple)
{
	float dx = player.position.x - apple.position.x;
	float dy = player.position.y - apple.position.y;
	float distance = sqrt(dx * dx + dy * dy);
	return distance < (settings::PLAYER_SIZE + settings::APPLE_SIZE) / 2.f;
}

bool logic::HasPlayerCollisionWithRock(const entities::player::Player& player, const entities::rock::Rock& rock)
{
	float dx = fabs(player.position.x - rock.position.x);
	float dy = fabs(player.position.y - rock.position.y);
	return (dx <= (settings::ROCK_SIZE + settings::PLAYER_SIZE) / 2.f &&
		dy <= (settings::ROCK_SIZE*2 + settings::PLAYER_SIZE) / 2.f);
}

void logic::GameOver(init::GameState& gamestate)
{
	gamestate.player.basic_speed = 0.f;

	gamestate.UI.leaderboard.back().scores.setString(std::to_string(gamestate.numEatenApples));

	//sort leaderboad by highest score
	std::sort(gamestate.UI.leaderboard.begin(), gamestate.UI.leaderboard.end(),
		[](ui::Leaderboard& name_score_one, ui::Leaderboard& name_score_two) {
			return name_score_one.scores_count > name_score_two.scores_count;});

	init::InitLeaderboard(gamestate);
}

void logic::UpdateUI(init::GameState& gamestate, float timeDelta)
{
	gamestate.UI.scoreText.setString("Apples eaten: " + std::to_string(gamestate.numEatenApples));

	gamestate.UI.isGameOverTextVisible = gamestate.isGameOver;
	sf::Color gameOverTextColor = (int)gamestate.timeSinceGameOver % 2 ? sf::Color::Red : sf::Color::Yellow;
	gamestate.UI.gameOverText.setFillColor(gameOverTextColor);
}

void logic::GameSettingSet(init::GameState& gamestate)
{
	while (sf::Event::TextEntered)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
		{
			gamestate.mask.bit_mask_m = gamestate.mask.bit_mask_m | (1 << gamestate.mask.endless_apples_or_not);
			break;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
		{
			break;
		}
	}


	while (sf::Event::TextEntered) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			gamestate.mask.bit_mask_m = gamestate.mask.bit_mask_m | (1 << gamestate.mask.acceleration_status);
			break;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		{
			break;
		}
	}

	gamestate.isGameStart = false;
}
