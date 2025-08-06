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
	for (int i =0;i<gamestate.UI.leaderboard.size(); ++i)
	{
		window.draw(gamestate.UI.leaderboard[i].nickName);
		window.draw(gamestate.UI.leaderboard[i].scores);
		window.draw(gamestate.UI.leaderboard[i].position_on_leaderboard);
	}
}
