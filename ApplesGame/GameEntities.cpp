#include "GameEntities.h"

void entities::player::InitPlayer(Player& player, sf::Texture& texture)
{
	player.position.x = (float)settings::SCREEN_WIDTH / 2.f;
	player.position.y = (float)settings::SCREEN_HEGHT / 2.f;
	player.basic_speed = settings::INITIAL_SPEED;
	player.direction = PlayerDirection::Up;

	// Init sprite
	player.sprite.setTexture(texture);
	player.sprite.setOrigin(GetSpriteOrigin(player.sprite, { 0.5f, 0.5f })); // We need to use texture as origin ignores scale
	player.sprite.setScale(GetSpriteScale(player.sprite, { settings::PLAYER_SIZE, settings::PLAYER_SIZE }));
}

void entities::player::UpdatePlayer(Player& player, float timeDelta)
{
	switch (player.direction)
	{
		case PlayerDirection::Up:
		{
			player.position.y -= player.basic_speed * timeDelta;
			break;
		}
		case PlayerDirection::Right:
		{
			player.position.x += player.basic_speed * timeDelta;
			break;
		}
		case PlayerDirection::Down:
		{
			player.position.y += player.basic_speed * timeDelta;
			break;
		}
		case PlayerDirection::Left:
		{
			player.position.x -= player.basic_speed * timeDelta;
			break;
		}
	}
}

void entities::apple::InitApple(Apple& apple, sf::Texture& texture)
{
	apple.position= RandomPosition();

	// Init sprite
	apple.sprite.setTexture(texture);
	apple.sprite.setOrigin(GetSpriteOrigin(apple.sprite, { 0.5f, 0.5f }));
	apple.sprite.setScale(GetSpriteScale(apple.sprite, { settings::APPLE_SIZE, settings::APPLE_SIZE }));
	AppleColor apple_color;
	apple.sprite.setColor(apple_color.GetColor()); // set apple color
}

void entities::rock::InitRock(Rock& rock, sf::Texture& texture)
{
	rock.position = RandomPosition();
	// Init sprite
	rock.sprite.setTexture(texture);
	rock.sprite.setOrigin(GetSpriteOrigin(rock.sprite, { 0.5f, 0.5f }));
	rock.sprite.setScale(GetSpriteScale(rock.sprite, { settings::ROCK_SIZE, settings::ROCK_SIZE*2 }));
}

sf::Vector2f entities::OurVectorToSf(const Vector2D& v)
{
	return sf::Vector2f(v.x, v.y);
}

sf::Vector2f entities::GetSpriteScale(const sf::Sprite& sprite, const Vector2D& desiredSize)
{
	const sf::Vector2u textureSize = sprite.getTexture()->getSize();
	const sf::Vector2f spriteScale = { desiredSize.x / textureSize.x, desiredSize.y / textureSize.y };
	return spriteScale;
}

sf::Vector2f entities::GetSpriteOrigin(const sf::Sprite& sprite, const Vector2D& relativePosition)
{
	const sf::Vector2u textureSize = sprite.getTexture()->getSize();
	return { relativePosition.x * textureSize.x, relativePosition.y * textureSize.y };
}

sf::Vector2f entities::GetTextOrigin(const sf::Text& text, const Vector2D& relativePosition)
{
	sf::FloatRect textSize = text.getLocalBounds();
	return {
		(textSize.left + textSize.width) * relativePosition.x,
		(textSize.top + textSize.height) * relativePosition.y,
	};
}

Vector2D entities::RandomPosition()
{
	float x = (float)(rand() % (settings::SCREEN_WIDTH + 1));
	float y = (float)(rand() % (settings::SCREEN_HEGHT + 1));
	return { x, y };
}
