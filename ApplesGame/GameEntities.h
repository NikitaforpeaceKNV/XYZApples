#pragma once

#include <SFML/Graphics.hpp>
#include "GameSettings.h"

enum class PlayerDirection
{
	Up = 0,
	Right,
	Down,
	Left
};

struct Vector2D
{
	float x = 0.f;
	float y = 0.f;
};

class AppleColor {
public:

	const sf::Color GetColor() {
		color.r = rand() % 255;
		color.g = rand() % 255;
		color.b = rand() % 255;

		sf::Color apple_color(color.r, color.g, color.b, color.alpha);

		return apple_color;
	}

private:
	struct Color {
		unsigned char r = 0;
		unsigned char g = 0;
		unsigned char b = 0;
		unsigned char alpha = 255;
	};

	Color color;
};

namespace entities
{
	namespace player
	{
		struct Player
		{
			Vector2D position;
			float basic_speed = 0.f; // Pixels per second
			PlayerDirection direction = PlayerDirection::Up;
			sf::Sprite sprite;
		};

		void InitPlayer(Player& player, sf::Texture& texture);
		void UpdatePlayer(Player& player, float timeDelta);
	}

	namespace rock
	{
		struct Rock
		{
			Vector2D position;
			sf::Sprite sprite;
		};

		void InitRock(Rock& rock, sf::Texture& texture);
	}

	namespace apple
	{
		struct Apple
		{
			Vector2D position;
			sf::Sprite sprite;
		};

		void InitApple(Apple& apple, sf::Texture& texture);
	}

	sf::Vector2f OurVectorToSf(const Vector2D& v);
	sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const Vector2D& desiredSize);
	sf::Vector2f GetSpriteOrigin(const sf::Sprite& sprite, const Vector2D& relativePosition);
	sf::Vector2f GetTextOrigin(const sf::Text& text, const Vector2D& relativePosition);

	Vector2D RandomPosition();
}