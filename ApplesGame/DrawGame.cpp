#include "DrawGame.h"

void draw::DrawPlayer(entities::player::Player& player, sf::RenderWindow& window)
{
	player.sprite.setPosition(entities::OurVectorToSf(player.position));

	const sf::Vector2f spriteScale = (entities::GetSpriteScale(player.sprite, { settings::PLAYER_SIZE, settings::PLAYER_SIZE }));

	// We need to rotate and flip sprite to match player direction
	switch (player.direction)
	{
	case PlayerDirection::Up:
	{
		player.sprite.setScale(spriteScale.x, spriteScale.y);
		player.sprite.setRotation(-90.f);
		break;
	}
	case PlayerDirection::Right:
	{
		player.sprite.setScale(spriteScale.x, spriteScale.y);
		player.sprite.setRotation(0.f);
		break;
	}
	case PlayerDirection::Down:
	{
		player.sprite.setScale(spriteScale.x, spriteScale.y);
		player.sprite.setRotation(90.f);
		break;
	}
	case PlayerDirection::Left:
	{
		player.sprite.setScale(-spriteScale.x, spriteScale.y);
		player.sprite.setRotation(0.f);
		break;
	}
	}

	window.draw(player.sprite);
}

void draw::DrawApple(entities::apple::Apple& apple, sf::RenderWindow& window)
{
	apple.sprite.setPosition(entities::OurVectorToSf(apple.position));
	window.draw(apple.sprite);
}

void draw::DrawRock(entities::rock::Rock& rock, sf::RenderWindow& window)
{
	rock.sprite.setPosition(entities::OurVectorToSf(rock.position));
	window.draw(rock.sprite);
}

void draw::DrawGame(init::GameState& gamestate, sf::RenderWindow& window)
{
	if (!gamestate.isGameOver) {
		DrawPlayer(gamestate.player, window);


		for (int i = 0; i < gamestate.apples1.size(); ++i)
		{
			DrawApple(gamestate.apples1[i], window);
		}

		for (int i = 0; i < settings::NUM_ROCKS; ++i)
		{
			DrawRock(gamestate.rocks[i], window);
		}

		DrawUI(gamestate, window);
	}
	else
	{
		DrawUI(gamestate, window);
	}

}

void draw::DrawUI(init::GameState& gamestate, sf::RenderWindow& window)
{
	gamestate.UI.scoreText.setPosition(10.f, 10.f);
	window.draw(gamestate.UI.scoreText);

	gamestate.UI.inputHintText.setPosition(window.getSize().x - 10.f, 10.f);
	window.draw(gamestate.UI.inputHintText);

	if (gamestate.UI.isGameOverTextVisible)
	{
		DrawLeaderboard(gamestate, window);
		gamestate.UI.gameOverText.setPosition(window.getSize().x / 2.f, 75.f);
		window.draw(gamestate.UI.gameOverText);

	}
}

void draw::DrawGamestartSettings(init::GameState& gamestate, sf::RenderWindow& window)
{
	gamestate.UI.gameSettings.setPosition(window.getSize().x / 2 - 300.f, window.getSize().y / 2 - 150.f);
	window.draw(gamestate.UI.gameSettings);
}

void draw::DrawLeaderboard(init::GameState& gamestate, sf::RenderWindow& window)
{
	for (int i = 0; i < gamestate.UI.leaderboard.size(); ++i)
	{
		window.draw(gamestate.UI.leaderboard[i].nickName);
		window.draw(gamestate.UI.leaderboard[i].scores);
		window.draw(gamestate.UI.leaderboard[i].position_on_leaderboard);

		sf::Text hint;
		hint.setString("Press ESC to return to menu");
		hint.setFont(gamestate.font);
		hint.setCharacterSize(20);
		hint.setPosition(settings::SCREEN_WIDTH / 2.f - 150.f, settings::SCREEN_HEGHT - 50.f);
		window.draw(hint);
	}
}

void draw::DrawMainMenu(const init::GameState& gamestate, sf::RenderWindow& window)
{
	for (const auto& item : gamestate.UI.mainMenu.items)
	{
		window.draw(item);
	}
}

void draw::DrawSettings(init::GameState& gamestate, sf::RenderWindow& window)
{
	sf::Text title;
	title.setString("GAME SETTINGS");
	title.setFont(gamestate.font);
	title.setCharacterSize(40);
	title.setFillColor(sf::Color::Cyan);
	title.setPosition(settings::SCREEN_WIDTH / 2.f - 150.f, 100.f);
	window.draw(title);

	// Настройка 1: Бесконечные яблоки
	sf::Text option1;
	option1.setString("1. Endless Apples: " +
		std::string(gamestate.settings.endlessApples ? "ON" : "OFF"));
	option1.setFont(gamestate.font);
	option1.setCharacterSize(30);
	option1.setPosition(200.f, 200.f);
	window.draw(option1);

	// Настройка 2: Ускорение
	sf::Text option2;
	option2.setString("2. Acceleration: " +
		std::string(gamestate.settings.accelerationEnabled ? "ON" : "OFF"));
	option2.setFont(gamestate.font);
	option2.setCharacterSize(30);
	option2.setPosition(200.f, 250.f);
	window.draw(option2);

	// Подсказка
	sf::Text hint;
	hint.setString("Press 1/2 to toggle options, ENTER to confirm");
	hint.setFont(gamestate.font);
	hint.setCharacterSize(20);
	hint.setPosition(150.f, settings::SCREEN_HEGHT - 50.f);
	hint.setFillColor(sf::Color::Yellow);
	window.draw(hint);
}
